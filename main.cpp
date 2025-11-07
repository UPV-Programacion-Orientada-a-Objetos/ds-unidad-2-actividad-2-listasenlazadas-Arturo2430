/**
 * @file main.cpp
 * @brief Aplicación principal - Decodificador PRT-7 (RECEPTOR)
 * 
 * Este programa recibe tramas del protocolo PRT-7 desde el puerto serial,
 * las procesa usando el rotor de mapeo y decodifica el mensaje original.
 * 
 * Formato de tramas:
 * - L,<caracter> : Carga un carácter (ej: L,H o L,Space)
 * - M,<numero>   : Rota el rotor (ej: M,2 o M,-2)
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "include/TramaLoad.h"
#include "include/TramaMap.h"
#include "include/RotorDeMapeo.h"
#include "include/ListaDeCarga.h"

/**
 * @brief Compara dos cadenas C-style (case-insensitive)
 */
bool strcmp_nocase(const char* a, const char* b) {
    while (*a && *b) {
        char ca = (*a >= 'a' && *a <= 'z') ? *a - 32 : *a;
        char cb = (*b >= 'a' && *b <= 'z') ? *b - 32 : *b;
        if (ca != cb) return false;
        a++;
        b++;
    }
    return *a == *b;
}

/**
 * @brief Configura el puerto serial para comunicación con ESP32
 * @param portName Nombre del puerto (ej: /dev/ttyUSB0)
 * @return File descriptor del puerto abierto, -1 si falla
 */
int configurarPuertoSerial(const char* portName) {
    int serial_port = open(portName, O_RDONLY | O_NOCTTY);
    
    if (serial_port < 0) {
        return -1;
    }
    
    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        close(serial_port);
        return -1;
    }
    
    // Configurar baudrate 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    
    // 8N1
    tty.c_cflag &= ~PARENB;        // Sin paridad
    tty.c_cflag &= ~CSTOPB;        // 1 bit de parada
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;            // 8 bits
    
    tty.c_cflag &= ~CRTSCTS;       // Sin control de flujo hardware
    tty.c_cflag |= CREAD | CLOCAL; // Activar lectura
    
    tty.c_lflag &= ~ICANON;        // Modo no canónico
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Sin control de flujo software
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;
    
    tty.c_cc[VTIME] = 10;  // Timeout de 1 segundo
    tty.c_cc[VMIN] = 0;
    
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        close(serial_port);
        return -1;
    }
    
    return serial_port;
}

/**
 * @brief Procesa una línea de entrada (parseo C-style)
 * @param linea Buffer con la línea leída (será modificado por strtok)
 * @param rotor Puntero al rotor de mapeo
 * @param carga Puntero a la lista de carga
 */
void procesarLinea(char* linea, RotorDeMapeo* rotor, ListaDeCarga* carga) {
    // Eliminar saltos de línea
    char* pos = linea;
    while (*pos) {
        if (*pos == '\n' || *pos == '\r') {
            *pos = '\0';
            break;
        }
        pos++;
    }
    
    // Si la línea está vacía, ignorar
    if (linea[0] == '\0') return;
    
    // Parsear: formato "L,X" o "M,N"
    char tipo = linea[0];
    
    if (tipo == 'L' || tipo == 'l') {
        // Trama LOAD
        if (linea[1] != ',') {
            std::cerr << "[ERROR] Formato inválido. Esperado: L,<caracter>" << std::endl;
            return;
        }
        
        // Extraer el dato después de la coma
        char* dato = linea + 2;  // Saltar "L,"
        
        char caracter;
        
        // Detectar "Space" y convertirlo a espacio
        if (strcmp_nocase(dato, "space") || strcmp_nocase(dato, "Space")) {
            caracter = ' ';
        } else if (dato[0] != '\0') {
            caracter = dato[0];  // Tomar primer carácter
        } else {
            std::cerr << "[ERROR] Trama LOAD sin dato" << std::endl;
            return;
        }
        
        // Crear y procesar trama
        TramaLoad* trama = new TramaLoad(caracter);
        trama->procesar(carga, rotor);
        delete trama;
        
    } else if (tipo == 'M' || tipo == 'm') {
        // Trama MAP
        if (linea[1] != ',') {
            std::cerr << "[ERROR] Formato inválido. Esperado: M,<numero>" << std::endl;
            return;
        }
        
        // Extraer el número después de la coma
        char* dato = linea + 2;  // Saltar "M,"
        int rotacion = atoi(dato);  // Convierte a int (soporta negativos)
        
        // Crear y procesar trama
        TramaMap* trama = new TramaMap(rotacion);
        trama->procesar(carga, rotor);
        delete trama;
        
    } else {
        // Ignorar líneas que no son tramas (como separadores ---, líneas vacías, etc.)
        bool esSeparador = true;
        for (int i = 0; linea[i] != '\0'; i++) {
            if (linea[i] != '-' && linea[i] != ' ' && linea[i] != '\t') {
                esSeparador = false;
                break;
            }
        }

        if (!esSeparador && linea[0] != '\0') {
        }
    }
}

/**
 * @brief Función principal - Lee del stdin (simulando puerto serial)
 */
int main() {
    std::cout << "=== DECODIFICADOR PRT-7 ===" << std::endl;
    std::cout << "Iniciando Decodificador PRT-7. Conectando a puerto COM..." << std::endl;
    
    // Intentar conectar al ESP32
    const char* puertoSerial = "/dev/ttyUSB0";
    int serial_fd = configurarPuertoSerial(puertoSerial);
    
    if (serial_fd < 0) {
        std::cerr << "✗ ERROR: No se pudo abrir el puerto " << puertoSerial << std::endl;
        std::cerr << "Asegúrate de que:" << std::endl;
        std::cerr << "  1. El ESP32 esté conectado al puerto USB" << std::endl;
        std::cerr << "  2. Tengas permisos de lectura (sudo usermod -a -G dialout $USER)" << std::endl;
        std::cerr << "  3. El puerto esté disponible (ls -la /dev/ttyUSB*)" << std::endl;
        return 1;
    }
    
    std::cout << "Conexión establecida. Esperando tramas..." << std::endl;
    std::cout << "NOTA: Si el ESP32 ya estaba transmitiendo, presiona el botón RESET para reiniciar la secuencia." << std::endl;
    std::cout << std::endl;
    
    // Limpiar buffer serial (flush)
    tcflush(serial_fd, TCIFLUSH);
    usleep(100000); // Esperar 100ms
    
    // Crear estructuras de datos usando punteros
    RotorDeMapeo* rotor = new RotorDeMapeo();
    ListaDeCarga* carga = new ListaDeCarga();
    
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int bufferPos = 0;
    int tramasRecibidas = 0;
    int secuenciaNum = 0; // Empezar en 0 para ignorar la primera secuencia
    
    std::cout << "Esperando primera secuencia completa (descartando datos parciales)..." << std::endl;
    std::cout << "Presiona Ctrl+C para detener el programa." << std::endl;
    std::cout << std::endl;
    
    // Leer del puerto serial continuamente
    while (true) {
        char c;
        int n = read(serial_fd, &c, 1);
        
        if (n > 0) {
            if (c == '\n' || c == '\r') {
                if (bufferPos > 0) {
                    buffer[bufferPos] = '\0';
                    
                    // Detectar reinicio de secuencia
                    if (strstr(buffer, "REINICIANDO SECUENCIA") != nullptr) {
                        // Mostrar mensaje final de la secuencia anterior (solo si no es la primera)
                        if (tramasRecibidas > 0 && secuenciaNum > 0) {
                            std::cout << std::endl;
                            std::cout << "---" << std::endl;
                            std::cout << "Flujo de datos terminado." << std::endl;
                            std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
                            carga->imprimirMensaje();
                            std::cout << "---" << std::endl;
                            std::cout << std::endl;
                            
                            // Preguntar si desea continuar
                            std::cout << "¿Desea continuar con la siguiente secuencia? (Y/N): ";
                            std::cout.flush();
                            
                            char respuesta;
                            std::cin >> respuesta;
                            std::cin.ignore(); // Limpiar el buffer
                            
                            if (respuesta != 'Y' && respuesta != 'y') {
                                std::cout << "Finalizando programa..." << std::endl;
                                std::cout << "Liberando memoria... Sistema apagado." << std::endl;
                                close(serial_fd);
                                delete rotor;
                                delete carga;
                                return 0;
                            }
                            std::cout << std::endl;
                        }
                        
                        // Incrementar secuencia
                        secuenciaNum++;
                        tramasRecibidas = 0;
                        
                        // Limpiar las estructuras (borrar y crear nuevas)
                        delete rotor;
                        delete carga;
                        rotor = new RotorDeMapeo();
                        carga = new ListaDeCarga();
                        
                        // Solo mostrar desde la secuencia 2 en adelante (secuenciaNum > 1)
                        if (secuenciaNum > 1) {
                            std::cout << "=== SECUENCIA #" << (secuenciaNum - 1) << " ===" << std::endl;
                            std::cout << std::endl;
                        }
                    } else if ((buffer[0] == 'L' || buffer[0] == 'l' || 
                                buffer[0] == 'M' || buffer[0] == 'm') && 
                               buffer[1] == ',') {
                        // Solo procesar y mostrar si no es la primera secuencia
                        if (secuenciaNum > 0) {
                            procesarLinea(buffer, rotor, carga);
                            tramasRecibidas++;
                        }
                    }
                    // Ignorar cualquier otra línea (---, líneas vacías, etc.)
                    
                    bufferPos = 0;
                }
            } else if (bufferPos < BUFFER_SIZE - 1) {
                buffer[bufferPos++] = c;
            }
        } else if (n < 0) {
            std::cerr << "Error al leer del puerto serial" << std::endl;
            break;
        }
    }
    
    // Cerrar puerto serial
    close(serial_fd);
    
    // Mostrar último mensaje si hay datos pendientes
    std::cout << std::endl;
    
    if (tramasRecibidas > 0) {
        std::cout << "---" << std::endl;
        std::cout << "Flujo de datos terminado." << std::endl;
        std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
        carga->imprimirMensaje();
        std::cout << "---" << std::endl;
    }
    
    // Liberar memoria
    delete rotor;
    delete carga;
    
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    return 0;
}

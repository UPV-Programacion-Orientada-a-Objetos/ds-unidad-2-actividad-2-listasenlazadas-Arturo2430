/**
 * @file TramaLoad.cpp
 * @brief Implementación de la clase TramaLoad
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#include "TramaLoad.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <iostream>

/**
 * Constructor de TramaLoad
 */
TramaLoad::TramaLoad(char c) : dato(c) {
}

/**
 * Destructor de TramaLoad
 */
TramaLoad::~TramaLoad() {
    // No hay recursos dinámicos que liberar
}

/**
 * Procesa la trama LOAD
 * Decodifica el carácter usando el rotor y lo agrega a la lista de carga
 */
void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    if (carga == nullptr || rotor == nullptr) return;
    
    // Decodificar el carácter usando el rotor
    char decodificado = rotor->getMapeo(dato);
    
    // Agregar ambos caracteres (codificado y decodificado) a la lista
    carga->insertarAlFinal(dato, decodificado);
    
    // Mostrar en formato: Fragmento 'X' decodificado como 'Y' -> Codificado: 'X'
    std::cout << "Trama recibida: [L," << dato << "] -> Procesando... -> Fragmento '" 
              << dato << "' decodificado como '" << decodificado << "'. ";
    
    // Mostrar mensaje parcial acumulado
    carga->imprimirMensajeParcial();
}

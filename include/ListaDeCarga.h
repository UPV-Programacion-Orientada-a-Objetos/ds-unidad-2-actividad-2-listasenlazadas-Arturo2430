/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar caracteres decodificados
 * 
 * Implementación manual de una lista doblemente enlazada que almacena
 * los caracteres del mensaje conforme se van decodificando.
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#ifndef LISTADECARGA_H
#define LISTADECARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada
 * 
 * Contiene un carácter codificado, decodificado y punteros al nodo anterior y siguiente.
 */
struct NodoCarga {
    char datoCodificado;    ///< Carácter original (codificado)
    char datoDecodificado;  ///< Carácter decodificado
    NodoCarga* siguiente;   ///< Puntero al siguiente nodo
    NodoCarga* previo;      ///< Puntero al nodo anterior
    
    /**
     * @brief Constructor del nodo
     * @param codif Carácter codificado
     * @param decodif Carácter decodificado
     */
    NodoCarga(char codif, char decodif) : datoCodificado(codif), datoDecodificado(decodif), 
                                           siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada para almacenar el mensaje decodificado
 * 
 * Almacena los caracteres en el orden en que son decodificados,
 * manteniendo la estructura del mensaje final.
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;  ///< Puntero al primer nodo
    NodoCarga* cola;    ///< Puntero al último nodo
    int tamanio;        ///< Número de elementos en la lista
    
public:
    /**
     * @brief Constructor
     * 
     * Inicializa una lista vacía.
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor
     * 
     * Libera toda la memoria de los nodos.
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param codificado Carácter original (codificado)
     * @param decodificado Carácter decodificado
     */
    void insertarAlFinal(char codificado, char decodificado);
    
    /**
     * @brief Imprime el mensaje completo decodificado
     * 
     * Recorre la lista y muestra el mensaje en consola.
     */
    void imprimirMensaje() const;
    
    /**
     * @brief Imprime el mensaje parcial acumulado (formato: Mensaje: [H][O][L])
     * 
     * Muestra el mensaje decodificado hasta el momento en formato de corchetes.
     */
    void imprimirMensajeParcial() const;
    
    /**
     * @brief Obtiene el tamaño de la lista
     * @return Número de caracteres almacenados
     */
    int obtenerTamanio() const;
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;
};

#endif // LISTADECARGA_H

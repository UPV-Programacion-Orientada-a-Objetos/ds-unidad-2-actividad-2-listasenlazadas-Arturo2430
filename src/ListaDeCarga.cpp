/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la lista doblemente enlazada
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#include "ListaDeCarga.h"
#include <iostream>

/**
 * Constructor de ListaDeCarga
 */
ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamanio(0) {
}

/**
 * Destructor de ListaDeCarga
 * Libera toda la memoria de los nodos
 */
ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
}

/**
 * Inserta un carácter al final de la lista
 */
void ListaDeCarga::insertarAlFinal(char codificado, char decodificado) {
    NodoCarga* nuevoNodo = new NodoCarga(codificado, decodificado);
    
    if (estaVacia()) {
        // Si la lista está vacía, el nuevo nodo es tanto cabeza como cola
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        // Agregar al final
        cola->siguiente = nuevoNodo;
        nuevoNodo->previo = cola;
        cola = nuevoNodo;
    }
    
    tamanio++;
}

/**
 * Imprime el mensaje completo decodificado
 */
void ListaDeCarga::imprimirMensaje() const {
    if (estaVacia()) {
        std::cout << "[MENSAJE VACIO]" << std::endl;
        return;
    }
    
    // Mostrar solo el mensaje decodificado
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->datoDecodificado;
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}

/**
 * Imprime el mensaje parcial acumulado en formato [X][Y][Z]
 * Muestra los caracteres DECODIFICADOS (después del mapeo del rotor)
 */
void ListaDeCarga::imprimirMensajeParcial() const {
    std::cout << "Mensaje: ";
    
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "[" << actual->datoDecodificado << "]";
        actual = actual->siguiente;
    }
    
    std::cout << std::endl;
}

/**
 * Obtiene el tamaño de la lista
 */
int ListaDeCarga::obtenerTamanio() const {
    return tamanio;
}

/**
 * Verifica si la lista está vacía
 */
bool ListaDeCarga::estaVacia() const {
    return cabeza == nullptr;
}

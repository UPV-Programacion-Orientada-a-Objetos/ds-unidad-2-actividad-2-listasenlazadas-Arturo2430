/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la lista circular (rotor de cifrado)
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#include "RotorDeMapeo.h"
#include <iostream>

/**
 * Constructor de RotorDeMapeo
 * Inicializa el rotor con A-Z y espacio
 */
RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamanio(0) {
    // Alfabeto A-Z (26 letras) + espacio (27 caracteres total)
    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    const int numCaracteres = 27;
    
    NodoRotor* primerNodo = nullptr;
    NodoRotor* ultimoNodo = nullptr;
    
    // Crear la lista circular
    for (int i = 0; i < numCaracteres; i++) {
        NodoRotor* nuevoNodo = new NodoRotor(alfabeto[i]);
        
        if (primerNodo == nullptr) {
            // Primer nodo
            primerNodo = nuevoNodo;
            ultimoNodo = nuevoNodo;
            cabeza = nuevoNodo;
        } else {
            // Enlazar con el anterior
            ultimoNodo->siguiente = nuevoNodo;
            nuevoNodo->previo = ultimoNodo;
            ultimoNodo = nuevoNodo;
        }
        
        tamanio++;
    }
    
    // Cerrar el círculo
    if (primerNodo != nullptr && ultimoNodo != nullptr) {
        ultimoNodo->siguiente = primerNodo;
        primerNodo->previo = ultimoNodo;
    }
}

/**
 * Destructor de RotorDeMapeo
 * Libera toda la memoria de los nodos
 */
RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;
    
    // Romper el círculo
    NodoRotor* ultimoNodo = cabeza->previo;
    ultimoNodo->siguiente = nullptr;
    
    // Eliminar todos los nodos
    NodoRotor* actual = cabeza;
    while (actual != nullptr) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    
    cabeza = nullptr;
    tamanio = 0;
}

/**
 * Encuentra un nodo por su carácter
 */
NodoRotor* RotorDeMapeo::encontrarNodo(char c) const {
    if (cabeza == nullptr) return nullptr;
    
    NodoRotor* actual = cabeza;
    do {
        if (actual->dato == c) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    return nullptr;
}

/**
 * Calcula la distancia entre dos nodos
 */
int RotorDeMapeo::calcularDistancia(NodoRotor* desde, NodoRotor* hasta) const {
    if (desde == nullptr || hasta == nullptr) return 0;
    
    int distancia = 0;
    NodoRotor* actual = desde;
    
    while (actual != hasta && distancia < tamanio) {
        actual = actual->siguiente;
        distancia++;
    }
    
    return distancia;
}

/**
 * Rota el rotor N posiciones
 */
void RotorDeMapeo::rotar(int n) {
    if (cabeza == nullptr || tamanio == 0) return;
    
    // Normalizar n al rango [-tamanio, tamanio]
    n = n % tamanio;
    
    if (n > 0) {
        // Rotar hacia adelante
        for (int i = 0; i < n; i++) {
            cabeza = cabeza->siguiente;
        }
    } else if (n < 0) {
        // Rotar hacia atrás
        for (int i = 0; i > n; i--) {
            cabeza = cabeza->previo;
        }
    }
}

/**
 * Obtiene el carácter mapeado según la rotación actual
 * Implementa el cifrado César dinámico
 */
char RotorDeMapeo::getMapeo(char in) const {
    if (cabeza == nullptr) return in;
    
    // Convertir a mayúsculas si es minúscula
    if (in >= 'a' && in <= 'z') {
        in = in - 'a' + 'A';
    }
    
    // Buscar el nodo que contiene el carácter de entrada
    NodoRotor* nodoEntrada = encontrarNodo(in);
    
    if (nodoEntrada == nullptr) {
        // Si no está en el rotor, devolver sin cambios
        return in;
    }
    
    // Calcular la distancia desde la cabeza hasta el nodo de entrada
    int distancia = calcularDistancia(cabeza, nodoEntrada);
    
    // El mapeo es: la posición de entrada se mapea a la posición 0 (cabeza)
    // pero manteniendo el desplazamiento relativo
    // Si la cabeza está en 'C' (rotación +2), entonces:
    // 'A' (pos 0) -> 'C' (pos 0 actual)
    // 'B' (pos 1) -> 'D' (pos 1 actual)
    // Etc.
    
    NodoRotor* nodoSalida = cabeza;
    for (int i = 0; i < distancia; i++) {
        nodoSalida = nodoSalida->siguiente;
    }
    
    return nodoSalida->dato;
}

/**
 * Obtiene la posición actual del rotor
 */
char RotorDeMapeo::getPosicionActual() const {
    if (cabeza == nullptr) return '?';
    return cabeza->dato;
}

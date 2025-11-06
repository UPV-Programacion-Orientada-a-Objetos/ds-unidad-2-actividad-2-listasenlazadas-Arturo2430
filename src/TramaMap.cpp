/**
 * @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <iostream>

/**
 * Constructor de TramaMap
 */
TramaMap::TramaMap(int n) : rotacion(n) {
}

/**
 * Destructor de TramaMap
 */
TramaMap::~TramaMap() {
    // No hay recursos dinámicos que liberar
}

/**
 * Procesa la trama MAP
 * Aplica la rotación al rotor de mapeo
 */
void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    if (rotor == nullptr) return;
    
    // Rotar el rotor
    rotor->rotar(rotacion);
    
    std::cout << std::endl;
    std::cout << "Trama recibida: [M," << rotacion << "] -> Procesando... -> ROTANDO ROTOR ";
    if (rotacion >= 0) std::cout << "+";
    std::cout << rotacion << ". (Ahora 'A' se mapea a '" << rotor->getMapeo('A') << "')" << std::endl;
    std::cout << std::endl;
}

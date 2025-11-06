/**
 * @file TramaMap.h
 * @brief Clase para tramas de tipo MAP del protocolo PRT-7
 * 
 * Las tramas MAP contienen instrucciones para rotar el disco
 * de cifrado (rotor), modificando el mapeo de caracteres.
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#ifndef TRAMAMAP_H
#define TRAMAMAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Representa una trama de mapeo (MAP) del protocolo PRT-7
 * 
 * Esta trama contiene un valor de rotación que modifica el estado
 * del rotor, cambiando la forma en que se decodifican los caracteres.
 * 
 * Formato: M,N donde N es un entero (positivo o negativo)
 */
class TramaMap : public TramaBase {
private:
    int rotacion; ///< Valor de rotación (positivo o negativo)
    
public:
    /**
     * @brief Constructor
     * @param n Valor de rotación a aplicar
     */
    TramaMap(int n);
    
    /**
     * @brief Destructor
     */
    ~TramaMap();
    
    /**
     * @brief Procesa la trama MAP
     * 
     * Aplica la rotación al rotor de mapeo, modificando el estado
     * del cifrado para las siguientes tramas LOAD.
     * 
     * @param carga Puntero a la lista de carga (no usado en MAP)
     * @param rotor Puntero al rotor que será rotado
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMAMAP_H

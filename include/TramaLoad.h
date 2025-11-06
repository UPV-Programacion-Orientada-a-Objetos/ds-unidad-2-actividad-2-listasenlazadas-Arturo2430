/**
 * @file TramaLoad.h
 * @brief Clase para tramas de tipo LOAD del protocolo PRT-7
 * 
 * Las tramas LOAD contienen un fragmento de datos (un carácter)
 * que debe ser decodificado según el estado actual del rotor.
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#ifndef TRAMALOAD_H
#define TRAMALOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Representa una trama de carga (LOAD) del protocolo PRT-7
 * 
 * Esta trama contiene un carácter que debe ser decodificado
 * usando el rotor de mapeo y luego almacenado en la lista de carga.
 * 
 * Formato: L,X donde X es un carácter
 */
class TramaLoad : public TramaBase {
private:
    char dato; ///< Carácter a decodificar
    
public:
    /**
     * @brief Constructor
     * @param c Carácter a almacenar en la trama
     */
    TramaLoad(char c);
    
    /**
     * @brief Destructor
     */
    ~TramaLoad();
    
    /**
     * @brief Procesa la trama LOAD
     * 
     * Decodifica el carácter usando el rotor y lo agrega a la lista de carga.
     * 
     * @param carga Puntero a la lista donde se almacenará el dato decodificado
     * @param rotor Puntero al rotor de mapeo para decodificación
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMALOAD_H

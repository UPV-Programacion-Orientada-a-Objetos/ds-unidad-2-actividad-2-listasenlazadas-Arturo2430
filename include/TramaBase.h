/**
 * @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 * 
 * Define la interfaz común que deben implementar todas las tramas
 * del protocolo (LOAD y MAP).
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#ifndef TRAMABASE_H
#define TRAMABASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta para tramas del protocolo PRT-7
 * 
 * Esta clase define la interfaz común para todas las tramas que
 * pueden ser recibidas a través del puerto serial. Cada tipo de
 * trama debe implementar el método procesar() de acuerdo a su
 * lógica específica.
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual
     * 
     * Es CRUCIAL que sea virtual para permitir la correcta
     * destrucción polimórfica de objetos derivados.
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Procesa la trama según su tipo específico
     * 
     * Método virtual puro que debe ser implementado por cada
     * clase derivada para ejecutar la lógica específica de
     * procesamiento.
     * 
     * @param carga Puntero a la lista donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo para decodificación
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMABASE_H

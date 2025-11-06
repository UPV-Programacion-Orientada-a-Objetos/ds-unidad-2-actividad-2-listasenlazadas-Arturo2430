/**
 * @file RotorDeMapeo.h
 * @brief Lista circular doblemente enlazada para el cifrado de caracteres
 * 
 * Implementación manual de una lista circular que actúa como un
 * "disco de cifrado" similar a una Rueda de César. Puede rotar
 * para cambiar el mapeo de caracteres.
 * 
 * @author Arturo
 * @date 2025-11-06
 */

#ifndef ROTORDEMAPEO_H
#define ROTORDEMAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo de la lista circular doblemente enlazada
 * 
 * Contiene un carácter y punteros al nodo anterior y siguiente
 * de forma circular.
 */
struct NodoRotor {
    char dato;              ///< Carácter almacenado
    NodoRotor* siguiente;   ///< Puntero al siguiente nodo (circular)
    NodoRotor* previo;      ///< Puntero al nodo anterior (circular)
    
    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular para mapeo de caracteres (Rueda de César)
 * 
 * Implementa un rotor de cifrado que contiene el alfabeto A-Z más
 * el espacio. Puede rotar su posición para cambiar el mapeo de
 * caracteres, implementando un cifrado César dinámico.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza;  ///< Puntero a la posición 'cero' actual del rotor
    int tamanio;        ///< Número de elementos en el rotor
    
    /**
     * @brief Encuentra un nodo por su carácter
     * @param c Carácter a buscar
     * @return Puntero al nodo que contiene el carácter, nullptr si no existe
     */
    NodoRotor* encontrarNodo(char c) const;
    
    /**
     * @brief Calcula la distancia entre dos nodos
     * @param desde Nodo de inicio
     * @param hasta Nodo de destino
     * @return Número de saltos desde 'desde' hasta 'hasta'
     */
    int calcularDistancia(NodoRotor* desde, NodoRotor* hasta) const;
    
public:
    /**
     * @brief Constructor
     * 
     * Inicializa el rotor con el alfabeto A-Z y espacio.
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor
     * 
     * Libera toda la memoria de los nodos.
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * 
     * Mueve la cabeza del rotor N posiciones hacia adelante (positivo)
     * o hacia atrás (negativo).
     * 
     * @param n Número de posiciones a rotar
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el carácter mapeado según la rotación actual
     * 
     * Aplica el cifrado César basado en la posición actual del rotor.
     * 
     * @param in Carácter de entrada a mapear
     * @return Carácter mapeado según la rotación actual
     */
    char getMapeo(char in) const;
    
    /**
     * @brief Obtiene la posición actual del rotor
     * @return Carácter en la posición 'cero' del rotor
     */
    char getPosicionActual() const;
};

#endif // ROTORDEMAPEO_H

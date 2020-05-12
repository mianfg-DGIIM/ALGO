/**
 * @file worker_common.hpp
 * @brief Fichero con funcionalidades comunes a los problemas de los trabajadores
 * @author segfault
 * */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

namespace common{

// Generacion de numeros aleatorios
//==============================================================================

/**
 * @brief Devuelve el valor absoluto de un valor double 
 * @param val el double con el que trabajamos
 * @return el valor absoluto de un valor double
 * */
double abs(double val){
    return val < 0 ? - val : val;
}

/**
 * @brief inicia la generacion de numeros aleatorios
 * */
void startRandom(){
    std::srand(time(NULL));
}

/**
 * @brief Genera un double aleatorio en un intervalo dado
 * @param min, el minimo valor que se puede tomar
 * @param max, el maximo valor que se puede tomar
 * @return un double en el intervalo [min, max]
 * */
double random_double(double min, double max){
    return (std::rand() / (double) RAND_MAX ) * (max - min) + min;
}

/**
 * @brief Genera un entero aleatorio en un intervalo dado
 * @param min, el minimo valor que se puede tomar
 * @param max, el maximo valor que se puede tomar
 * @return un entero en el intervalo [min, max]
 * */
double random_int(int min, int max){
    return (int)(std::rand() / (double) RAND_MAX ) * (max - min) + min;
}

// Generacion de los datos del problema
//==============================================================================
/**
 * @brief Genera una matriz aleatoria con las asignaciones de trabajo
 * @param size, tamaño del problema (nº de trabajadores y trabajos)
 * @return una matriz cuadrada de dimension size con valores aleatorios en el intervalo [0, size]
 * */
std::vector<std::vector<double> > generate_matrix(int size){
    // Inicio una matriz llena de ceros
    std::vector<double> empty_row(size, 0);
    std::vector<std::vector<double> > matrix(size, empty_row);

    for(int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            matrix[row][col] = random_double(0, size);
        }
    }

    return matrix;
}

// Calculos sobre datos del problema
//==============================================================================
/**
 * @brief Calcula el coste de una asignacion dada
 * @param matrix, la matriz con los costes
 * @param asignation, la asignacion cuyo coste se calcula
 * @return el coste de la asignacion
 * */
double get_cost(std::vector<std::vector<double> > matrix, std::vector<int> asignation){
    double cost = 0;

    for(int i = 0; i < asignation.size(); i++){
        cost = cost + matrix[i][asignation[i]];
    }

    return cost;
}

// Muestra de datos del problema
//==============================================================================
void show_matrix(std::vector<std::vector<double> > matrix, char sep = '\t'){
    for(int row = 0; row < matrix.size(); row++){
        for(int col = 0; col < matrix[row].size(); col++){
            std::cout << matrix[row][col] << sep;
        }
        std::cout << std::endl;
    }
}
    
}// namespace common

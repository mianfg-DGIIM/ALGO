/**
 * @file functions_stl.h
 * @author Sergio Quijano Rey
 * @brief Funciones auxiliares para el codigo que usa la STL
 * */
#include <vector>
#include <iostream>
#include<stdlib.h>
#include<time.h>

// Constantes del programa
//==============================================================================
const int lower_delta = 0;
const int upper_delta = 20;
const int n = 1000;

// Generacion de numeros aleatorios
//==============================================================================
/**
 * @brief 	Inicia la generacion de numeros aleatorios
 * 			Se toma el reloj como semilla
 * */
void startRandom(){
		srand(time(NULL)); //Inicializo los numeros aleatorios
}

/**
 * @brief Genera un numero entero aleatorio
 * @param min, valor entero minimo
 * @param max, valor entero maximo
 * @return un entero en el intervalo [min, max]
 * */
int randomInt(int min, int max){
		int value = min + rand() % (max +1 - min) ;
		return value;
} 


// Generacion de los datos del problema
//==============================================================================
/**
 * @brief Genera un vector aleatorio ya ordenado
 * @param size, tamaño del vector a generar
 * @return un vector ordenado
 * */
std::vector<int> generate_sorted_vector(int size){
		std::vector<int> random_sorted(size);
		int current = 0;

		for(int i = 0; i < size; i++){
				random_sorted[i] = current + randomInt(lower_delta, upper_delta);
				current = random_sorted[i];
		}

		return random_sorted;
}
/**
 * @brief Genera k vectores ordenados de tamaño n
 * @param k, el numero de vectores
 * @param n, el tamaño de los vectores
 * @return un array almacenando los k vectores ordenados de tamaño n (array k x n)
 * */
std::vector<std::vector<int> > generate_sorted_vectors(int k, int n){
		std::vector<std::vector<int> > matrix(k);

		for(int i = 0; i < k; i++){
				matrix[i] = generate_sorted_vector(n);
		}

		return matrix;
}

/**
 * @brief Muestra un conjunto de vectores almacenados en un array
 * @param matrix, la matriz a mostrar
 * @param sep, caracter que separa dos elementos de un vector
 * */
void display_vectors(std::vector<std::vector<int> > matrix, char sep = '\t'){
		for(int i = 0; i < matrix.size(); i++){
				std::cout << "Vector" << i << ": ";
				for(int j = 0; j < matrix[i].size(); j++){
						std::cout << matrix[i][j] << sep;
				}
				std::cout << std::endl;
		}
}

/**
 * @brief muestra un vector
 * @param v, el vector a mostrar
 * @param sep, el separador entre los elementos del vector
 * */
void display_vector(std::vector<int> v, char sep = '\t'){
		for(int i = 0; i < v.size(); i++){
				std::cout << v[i] << sep;
		}
		std::cout << std::endl;
}

/**
 * @brief Convierte una matriz fila a un vector, es decir, una matriz con un solo vector
 * @param matrix, la matriz a convertir
 * @return un vector con los datos de la matriz
 * */
std::vector<int> parse_matrix_to_vector(std::vector<std::vector<int> > matrix){
		return matrix[0];
}

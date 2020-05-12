/**
 * @file merge_stl.cpp
 * @author Sergio Quijano Rey
 * @brief Codigo principal para el segundo problema de la practica usando stl::vector,
 *        usando divide y venceras
 * */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include "functions_stl.h"
using namespace std;
using namespace std::chrono;

// FUNCIONES AUXILIARES
//==============================================================================
/**
 * @brief mezcla dos vectores previamente ordenados
 * @param v1, el primer vector, ordenado
 * @param v2, el segundo vector, ordenado
 * @return la mezcla de ambos vectores
 * */
vector<int> merge(vector<int> v1, vector<int> v2){
		vector<int> merged(v1.size() + v2.size());
		int pos1 = 0;
		int pos2 = 0;

		while(pos1 < v1.size() || pos2 < v2.size()){
				if(pos1 == v1.size()){
						merged[pos1 + pos2] = v2[pos2];
						pos2++;
				}else if(pos2 == v2.size()){
						merged[pos1 + pos2] = v1[pos1];
						pos1++;
				}else{
						if(v1[pos1] < v2[pos2]){
								merged[pos1 + pos2] = v1[pos1];
								pos1++;
						}else{
								merged[pos1 + pos2] = v2[pos2];
								pos2++;
						}
				}
		}

		return merged;
}

/**
 * @brief Mezcla dos a dos los vectores de una matriz, obteniendo asi una matriz
 *        de tamaño la mitad
 * @param matrix, la matriz sobre la que vamos a trabajar
 * @return una matriz, con la mitad del tamaño, como ya se ha especificado
 * */
vector<vector<int> > merge_two_by_two(vector<vector<int> > matrix){
		// Generamos la nueva matriz
		int new_size = (matrix.size() / 2) + matrix.size() % 2;
		vector<vector<int> > merged_matrix(new_size);

		// Tomamos los datos de la nueva matriz
		for(int i = 0; i < merged_matrix.size(); i++){
				// Ultimo elemento de la matriz sin hacer merge
				if(2*i + 1 >= matrix.size()){
						merged_matrix[i] = merged_matrix[2*i + 1];
				}

				vector<int> new_vector = merge(matrix[2*i], matrix[2*i + 1]);
				merged_matrix[i] = new_vector;
		}

		return merged_matrix;
}

/**
 * @brief Mezcla k vectores ordenados
 *		  Se usa divide y venceras
 * @return un vector resultado de mezclar todos los vectores de la matriz
 * */
vector<int> merge_divide_and_conquer(vector<vector<int> > matrix){
		// Caso base para finalizar la recursividad
		if(matrix.size() == 1){
				return parse_matrix_to_vector(matrix);
		}
		
		// Reduzco el tamaño del problema a la mitad y aplico recursivdad
		matrix = merge_two_by_two(matrix);
		return merge_divide_and_conquer(matrix);
}

// FUNCION PRINCIPAL
//==============================================================================
int main(int argc, char ** argv){
		int start = 0;
		int end = 0;

		// Inicio de los numeros aleatorios
		startRandom();
		
		// Proceso la entrada de parametros
		if(argc != 3){
				cerr << "Error! Parametros incorrectos" << endl;
				cerr << "Modo de uso: ./merge <inicio> <fin>" << endl;
				return 1;
		}else{
				start = stoi(argv[1]);
				end = stoi(argv[2]);
		}

		clog << "Size, Time(seconds)" << endl;
		for(int i = 0; i < end; i++){
				int k = pow(2, i);
				vector<vector<int> > vectores = generate_sorted_vectors(k, n);

				auto start = high_resolution_clock::now();
				merge_divide_and_conquer(vectores);
				auto end = high_resolution_clock::now();
				auto duration = (duration_cast<microseconds>(end - start)).count();

				clog << k << ", " << duration << endl;
		}

		// Todo ha salido OK
		return 0;
}

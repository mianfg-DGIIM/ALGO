/**
 * @file merge_stl.cpp
 * @author Sergio Quijano Rey
 * @brief Codigo principal para el segundo problema de la practica usando stl::vector
 * */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <math.h>
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
 * @brief Mezcla los dos primeros vectores de un conjunto de vectores
 * @param matrix, el conjunto de vectores en forma de matriz
 * @return el nuevo conjunto resultado, en forma de 
 * */
vector<vector<int> > merge_first_two_vectors(vector<vector<int> > matrix){
		// Matriz con un vector menos, resultado de la mezcla
		vector<vector<int> > merged_matrix(matrix.size() - 1);

		// Vector que hemos mezclado
		vector<int> merged = merge(matrix[0], matrix[1]);

		// Calculamos los datos de la nueva matriz
		merged_matrix[0] = merged;
		for(int i = 1; i < merged_matrix.size(); i++){
				merged_matrix[i] = matrix[i+1];
		}

		return merged_matrix;
}

/**
 * @brief	Mezcla k vectores ordenados
 *			Se van mezclando 2 a 2, de izquierda a derecha
 * @return un vector resultado de mezclar todos los vectores de la matriz
 * */
vector<int> merge_vectors_basic(vector<vector<int> > matrix){
		// Caso base para parar la recursividad
		if(matrix.size() == 1){
				return parse_matrix_to_vector(matrix);

		}else{
				matrix = merge_first_two_vectors(matrix);
				return merge_vectors_basic(matrix);
		}
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
				int k = (int)pow(2, i);
				vector<vector<int> > vectores = generate_sorted_vectors(k, n);

				auto start = high_resolution_clock::now();
				merge_vectors_basic(vectores);
				auto end = high_resolution_clock::now();
				auto duration = (duration_cast<microseconds>(end - start)).count();

				clog << k << ", " << duration << endl;
		}

		// Todo ha salido OK
		return 0;
}

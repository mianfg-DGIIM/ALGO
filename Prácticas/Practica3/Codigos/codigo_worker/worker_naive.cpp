/**
 * @file worker_naive.cpp
 * @brief Solucion al problema de los trabajadores con fuerza bruta
 * @author segfault
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include "worker_common.hpp"
using namespace std;

// Declaracion de funciones auxiliares
//==============================================================================
/**
 * @brief Genera todas las permutaciones del conjunto {0, 1, ..., n-1}
 * @param n, el maximo del conjunto sobre el que se permuta
 * @return un array con todas las permutaciones anteriormente descritas
 * */
vector<vector<int> > generate_permutations(int n);

/**
 * @brief Calcula la asignacion optima dada una matriz de costes, usando fuerza bruta
 * @param matrix, la matriz que almacena los costes
 * @return la asignacion optima
 * */
vector<int> get_best_solution(vector<vector<double> > matrix);

// Funcion principal
//==============================================================================
int main(){
    // Parametro para hacer pruebas con las entradas
    int size = 4;

    // Inicio la generacion de numeros aleatorios
    common::startRandom();

    // Tomo una matriz con los datos del problema
    vector<vector<double> > worker_matrix = common::generate_matrix(size);

    // Calculo la solucion al problema
    vector<int> asignation = get_best_solution(worker_matrix);

    // Muestro el coste de la solucion optima
    cout << "El coste optimo es: " << common::get_cost(worker_matrix, asignation) << endl;

    // Muestro las asignaciones hechas
    for(int i = 0; i < size; i++){
        cout << "Trabajador " << i << " asignado al trabajo " << asignation[i] << endl;
    }

    // Todo ha salido OK
    return 0;
}

// Implementacion de funciones auxiliares
//==============================================================================
vector<vector<int> > generate_permutations(int n){
    vector<vector<int> > permutations;

    // We get the base permutation to work with
    vector<int> base_perm;
    for(int i = 0; i < n; i++){
        base_perm.push_back(i);
    }

    do{
        permutations.push_back(base_perm);
    }while(next_permutation(base_perm.begin(), base_perm.end()));


    return permutations;
}

vector<int> get_best_solution(vector<vector<double> > matrix){
    // Tomo el array de permutaciones, del que me tengo que quedar con solo una 
    // permutacion, la permutacion de la asignacion optima
    vector<vector<int> > permutations = generate_permutations(matrix.size());

    // Valores base para empezar a realizar comparaciones
    int best_permutation = 0;
    double best_cost = common::get_cost(matrix, permutations[0]);

    // Comparo todas las permutaciones
    for(int i = 0; i < permutations.size(); i++){
        double current_cost = common::get_cost(matrix, permutations[i]);

        if(current_cost < best_cost){
            best_cost = current_cost;
            best_permutation = i;
        }
    }

    return permutations[best_permutation];
}

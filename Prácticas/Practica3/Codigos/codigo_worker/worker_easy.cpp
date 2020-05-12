/**
 * @file worker_easy.cpp
 * @brief Solucion greedy al problema de los trabajadores
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
 * @brief Calcula la asignacion parcialmente optima dada una matriz de costes, usando un algoritmo greedy
 * @param matrix, la matriz que almacena los costes
 * @return la asignacion parcialmente optima
 * */
vector<int> get_best_solution(vector<vector<double> > matrix);

/**
 * @brief Halla dado un vector de costo de tareas, la mejor tarea que se encuentra disponible
 * @param tasks_cost, vector con los costos de las tareas
 * @param available, vector para controlar si las tareas se encuentra o no disponibles
 * */
int find_best_task(vector<double>tasks_cost, vector<bool> available);

// Funcion principal
//==============================================================================
int main(){
    // Parametro para hacer pruebas con las entradas
    int size = 4000;

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
    // Vector que almacena las tareas que todavia no han sido asignadas
    vector<bool> available_tasks(matrix.size(), true);

    // Vector con la solucion parcial
    vector<int> asignation;

    // Asigno a cada trabajador la tarea con menor coste que quede disponible
    for(int i = 0; i < matrix.size(); i++){
        // Busco la mejor tarea que quede disponible
        int current_task = find_best_task(matrix[i], available_tasks);

        // Añado la tarea a la asignacion
        asignation.push_back(current_task);

        // Esa tarea ya no esta disponible
        available_tasks[current_task] = false;
    }

    return asignation;
}

int find_best_task(vector<double>tasks_cost, vector<bool> available){
    // Encuentro la primera tarea disponible para comenzar las comparaciones
    int best_task = 0;
    while(available[best_task] == false){
        best_task++;
    }
    double best_cost = tasks_cost[best_task];

    // Comparo todos los costes que quedan disponibles
    for(int i = best_task; i < tasks_cost.size(); i++){
        if(available[i] == true){ // La tarea sigue disponible
            if(tasks_cost[i] < best_cost){
                best_cost = tasks_cost[i];
                best_task = i;
            }
        }
    }

    return best_task;
}

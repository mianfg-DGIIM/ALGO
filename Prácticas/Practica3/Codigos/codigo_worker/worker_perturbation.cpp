/**
 * @file worker_perturbation.cpp
 * @brief Solucion greedy con perturbaciones al problema de los trabajadores
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
 * @brief Calcula la asignacion parcialmente optima dada una matriz de costes, 
 *        usando un algoritmo greedy a partir de una solucion parcial por insercion
 * @param matrix, la matriz que almacena los costes
 * @param num_permutations, el numero de perturbaciones que se van a realizar para mejorar la matriz
 * @return la asignacion parcialmente optima
 * */
vector<int> get_best_solution(vector<vector<double> > matrix, int num_permutations);

/**
 * @brief Encuentra el trabajador con peor coste
 * @param matrix, la matriz con los costes 
 * @param asignation, la asignacion de la que se tiene que encontrar el peor trabajador
 * */
int find_worst_worker(vector<vector<double> > matrix, vector<int> asignation);

/**
 * @brief Encuentra cual es la mejor permutacion para mejorar el coste de una asignacion
 * @param matrix, la matriz con los costes asociados
 * @param base_asignation, asignacion base que tenemos que mejorar
 * @param worst_worker, trabajador con pero coste, el cual se tiene que intercambiar con otro
 * @return el indice del trabajador con el que se tiene que intercambiar el peor trabajador
 * */
int find_best_permutation(vector<vector<double> > matrix, vector<int> base_asignation, int worst_worker);

/**
 * @brief Realiza un intercambio entre trabajadores
 * @param base_asignation, asignacion sobre la que realizamos el intercambio, SE MODIFICA
 * @param first_worker, indice del trabajador que se intercambia
 * @param second_worker, indice del otro trabajador que se intercambia
 * */
void perturbate(vector<int> & base_asignation, int first_worker, int second_worker);

/**
 * @brief Calcula la asignacion parcialmente optima dada una matriz de costes, 
 *        usando un algoritmo greedy
 * @param matrix, la matriz que almacena los costes
 * @return la asignacion parcialmente optima
 * */
vector<int> get_insertion_solution(vector<vector<double> > matrix);

/**
 * @brief Halla dado un vector de costo de tareas, la mejor tarea que se encuentra disponible
 * @param tasks_cost, vector con los costos de las tareas
 * @param available, vector para controlar si las tareas se encuentra o no disponibles
 * */
int find_best_task(vector<double>tasks_cost, vector<bool> available);
        
// Funcion principal
//==============================================================================
int main(){
    // Parametros para hacer pruebas con las entradas
    int size = 400;
    int num_permutations = 20;

    // Inicio la generacion de numeros aleatorios
    common::startRandom();

    // Tomo una matriz con los datos del problema
    vector<vector<double> > worker_matrix = common::generate_matrix(size);

    // Calculo la solucion al problema
    vector<int> asignation = get_best_solution(worker_matrix, num_permutations);

    // Muestro las asignaciones hechas
    for(int i = 0; i < size; i++){
        cout << "Trabajador " << i << " asignado al trabajo " << asignation[i] << endl;
    }

    // Muestro el coste de la solucion optima
    cout << "El coste optimo es: " << common::get_cost(worker_matrix, asignation) << endl;

    // Todo ha salido OK
    return 0;
}

// Implementacion de funciones auxiliares
//==============================================================================
vector<int> get_best_solution(vector<vector<double> > matrix, int num_permutations){
    // Parto de la solucion parcial del greedy por insercion
    vector<int> base_asignation = get_insertion_solution(matrix.size());

    // Hacemos el numero de perturbaciones dado
    for(int i = 0; i < num_permutations; i++){
        // Busco cual es el trabajador con mayor coste
        int worst_worker = find_worst_worker(matrix, base_asignation);
        
        // Busco cual es la mejor permutacion
        int best_permutation = find_best_permutation(matrix, base_asignation, worst_worker);

        // Hago el cambio si hay un cambio a mejor
        perturbate(base_asignation, worst_worker, best_permutation);
    }

    return base_asignation;
}

int find_worst_worker(vector<vector<double> > matrix, vector<int> asignation){
    double worst_cost = matrix[0][asignation[0]];
    int worst_worker = 0;

    for(int i = 0; i < asignation.size(); i++){
        if(matrix[i][asignation[i]] > worst_cost){
            worst_cost = matrix[i][asignation[i]];
            worst_worker = i;
        }
    }

    return worst_worker;
}

int find_best_permutation(vector<vector<double> > matrix, vector<int> base_asignation, int worst_worker){
    // Coste base y coste de cada iteracion
    double base_cost = common::get_cost(matrix, base_asignation);         

    // Genero una perturbacion aleatoria
    int best_permutation = common::random_int(0, base_asignation.size() -1);
    vector<int> current_perturbation = base_asignation;
    perturbate(current_perturbation, worst_worker, best_permutation);

    // Calculo la ganancia de la perturbacion aleatoria
    double current_cost = common::get_cost(matrix, current_perturbation);
    double best_gain = base_cost - current_cost;

    // Busco la mejor perturbacion
    for(int i = 0; i < base_asignation.size(); i++){
        // Tomo la perturbacion actual
        current_perturbation = base_asignation;
        perturbate(current_perturbation, worst_worker, i);
        
        // Calculo el nuevo coste de la perturbacion y la ganancia
        current_cost = common::get_cost(matrix, current_perturbation);
        double current_gain = base_cost - current_cost;

        // Hago la comparativa
        if(current_gain < best_gain){
            best_gain = current_gain;
            best_permutation = i;
        }
    }

    return best_permutation;
}

void perturbate(vector<int> & base_asignation, int first_worker, int second_worker){
    int tmp = base_asignation[first_worker];
    base_asignation[first_worker] = base_asignation[second_worker];
    base_asignation[second_worker] = tmp;
}

vector<int> get_insertion_solution(vector<vector<double> > matrix){
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

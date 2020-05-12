/**
 * @file tsp_naive.cpp
 * @brief TSP Naive - Solucion al TSP por *fuerza bruta*
 * @author segfault
 * */

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "tsp_common.hpp"
using namespace std;

// Declaracion de las funciones que vamos a calcular
//==============================================================================

/**
 * @brief Genera todas las permutaciones posibles del conjunto {0, 1, ..., n-1}
 * @return un vector con todas las permutaciones posibles
 * */
vector<vector<int> > generate_permutations(int n);

/**
 * @brief Calcula la mejor solucion para un conjunto de puntos, por fuerza bruta
 * @param points, el conjunto de puntos sobre el que vamos a operar
 * @return el camino cuya distancia es la minima
 * */
vector<common::Point> get_best_solution(vector<common::Point> points);



int main(){
    // Parametro del programa para probar cosas
    int num_points = 10;

    // Puntos con los que voy a trabajar
    vector<common::Point> points = common::generate_problem_data(10);

    // Soluciono el problema por fuerza bruta
    vector<common::Point> road = get_best_solution(points);

    // Muestro el resultado del problema
    cout << "El camino optimo para el problemma es: " << endl;
    for(auto point : road){
        cout << "x: " << point.x << " y: " << point.y << endl;
    }

    cout << "La distancia del camino optimo es: " << get_road_distance(road) << endl;


    // Todo ha salido OK
    return 0;
}

// Implementacion de las funciones
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

vector<common::Point> get_best_solution(vector<common::Point> points){
    // Permutaciones con las que vamos a trabajar
    vector<vector<int> > permutations = generate_permutations(points.size());

    // Camino y distancia minima
    vector<common::Point> min_road = points;
    double min_distance = common::get_road_distance(min_road);

    // Calculo las distancias de todas las permutaciones
    for(auto permutation : permutations){
        vector<common::Point> current_road = common::generate_road_by_indexes(points, permutation);
        double current_distance = common::get_road_distance(current_road);

        if(current_distance < min_distance){
            min_distance = current_distance;
            min_road = current_road;
        }
    }

    return min_road;
}

/**
 * @file tsp_snf.cpp
 * @brief Solucion del TSP por SNF usando un vector con los puntos que quedan
 * @author segfault
 * */

#include <iostream>
#include <vector>
#include "tsp_common.hpp"
using namespace std;

// Declaracion de funciones con las que trabajamos
//==============================================================================

/**
 * @brief Calcula la mejor solucion para un conjunto de puntos, por Shortest Neighbor First
 * @param points, el conjunto de puntos sobre el que vamos a operar
 * @pre points.size() > 0
 * @return el camino cuya distancia es la minima
 * */
vector<common::Point> get_best_solution(vector<common::Point> points);

// Funcion principal
//==============================================================================
int main(){
    // Parametro sobre el tamaño del problema
    int problem_size = 10000;

    // Inicio los numeros aleatorios
    common::startRandom();

    // Puntos con los que vamos a trabajar
    vector<common::Point> points = common::generate_problem_data(problem_size);

    // Calculo la solucion aproximada
    vector<common::Point> road = get_best_solution(points);

    // Muestro el resultado
    cout << "La distancia de la solucion obtenida es: " << common::get_road_distance(road) << endl;

    // Todo ha salido OK
    return 0;
}

// Implementacion de las funciones 
//==============================================================================
vector<common::Point> get_best_solution(vector<common::Point> points){
    vector<common::Point> road;                 // Solucion que vamos a construir
    vector<common::Point> points_left = points; // Puntos que quedan por añadir a la solucion

    // Parto siempre del primer punto del vector
    road.push_back(points_left[0]);
    points_left.erase(points_left.begin() + 0);

    // Voy construyendo la solucion, sacando puntos de points_left y colocandolos en road
    while(points_left.size() > 0){
        double min_distance = common::distance(road[road.size() -1], points_left[0]);
        int min_pos = 0;

        // Buscamos el punto mas cercano
        for(int i = 0; i < points_left.size(); i++){
            double current_distance = common::distance(road[road.size() -1], points_left[i]);
            if(current_distance < min_distance){
                min_distance = current_distance;
                min_pos = i;
            }
        }

        // Añadimos el punto mas cercano a la solucion y lo quitamos de los puntos que faltan
        road.push_back(points_left[min_pos]);
        points_left.erase(points_left.begin() + min_pos);
    }

    return road;
}

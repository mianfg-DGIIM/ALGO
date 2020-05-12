/**
 * @file tsp_insertion.cpp
 * @brief Solucion al TSP por insercion greedy
 * @author segfault
 * */

#include <iostream>
#include <vector>
#include "tsp_common.hpp"
using namespace std;

// Declaracion de funciones
//==============================================================================
/**
 * @brief Calcula el camino parcialmente optimo por un algoritmo de insercion
 * @param points, el conjunto de puntos sobre el que vamos a trabajar
 * @return el camino descrito anteriormente
 * */
vector<common::Point> get_best_solution(vector<common::Point> points);

/**
 * @brief Calcula el mejor punto que añadir a un camino
 * @param current_road, el camino al que queremos añadir un punto
 * @param points, puntos entre los que queremos encontrar uno optimo
 * @return un vector con dos enteros
 *              - El primero: posicion del punto optimo
 *              - El segundo: posicion donde insertar el punto en el camino
 * */
vector<int> get_best_candidate(vector<common::Point> current_road, vector<common::Point> points);

/**
 * @brief Calcula el punto que esta mas al norte de un conjunto de puntos
 * @param points, el conjunto de puntos sobre el que operamos
 * @return la posicion del punto que esta mas al norte
 * */
int get_most_north(vector<common::Point> points);

/**
 * @brief Calcula el punto que esta mas al este de un conjunto de puntos
 * @param points, el conjunto de puntos sobre el que operamos
 * @return la posicion del punto que esta mas al este
 * */
int get_most_east(vector<common::Point> points);

/**
 * @brief Calcula el punto que esta mas al oeste de un conjunto de puntos
 * @param points, el conjunto de puntos sobre el que operamos
 * @return la posicion del punto que esta mas al oeste
 * */
int get_most_west(vector<common::Point> points);

/**
 * @brief Calcula el mejor camino que se genera añadiendole a otro camino un punto
 * @param road, camino al que el añadimos un punto
 * @param point, punto que se añade
 * @return el mejor camino generado como ya se ha especificado
 * */
vector<common::Point> get_best_road(vector<common::Point> road, common::Point point);

/**
 * @brief Calcula cual es la mejor posicion en la que se puede insertar un punto en un camino dado
 * @param road, el camino al que queremos insertar el punto
 * @param point, el punto que queremos añadir
 * @return la mejor posicion en la que podemos añadir el punto
 * */
int get_best_position(vector<common::Point> road, common::Point point);

// Funcion principal
//==============================================================================
int main(){
    // Inicio la generacion de numeros aleatorios
    common::startRandom();

    // Parametro para controlar el tamaño del problema
    int size = 100;

    // Genero los datos del problema
    vector<common::Point> points = common::generate_problem_data(size);

    // Calculo la solucion
    vector<common::Point> road = get_best_solution(points);

    // Muestro la distancia de la solucion encontrada
    cout << "La distancia de la solucion encontrada es: " << get_road_distance(road) << endl;

    // Todo ha salido OK
    return 0;
}

// Implementacion de funciones
//==============================================================================
vector<common::Point> get_best_solution(vector<common::Point> points){
    vector<common::Point> candidates = points;  // Vector con los candidatos
    vector<common::Point> road;                 // Vector con la solucion parcial

    // Tomo los tres puntos extremos del plano y los coloco como solucion parcial inicial
    int most_north = get_most_north(candidates);
    int most_east = get_most_east(candidates);
    int most_west = get_most_west(candidates);

    road.push_back(candidates[most_north]);
    road.push_back(candidates[most_west]);
    road.push_back(candidates[most_east]);

    candidates.erase(candidates.begin() + most_north);
    candidates.erase(candidates.begin() + most_west);
    candidates.erase(candidates.begin() + most_east);

    // Construyo las soluciones parciales
    while(candidates.size() > 0){
        // Tomo el mejor candidato para la siguiente iteracion
        vector<int> best_candidate_and_pos = get_best_candidate(road, candidates);
        int best_candidate = best_candidate_and_pos[0];
        int best_pos = best_candidate_and_pos[1];

        // Hago el traspase de candidatos a solucion parcial
        road.insert(road.begin() + best_pos, candidates[best_candidate]);
        candidates.erase(candidates.begin() + best_candidate);
    }

    return road;
}

int get_most_north(vector<common::Point> points){
    int most_point = 0;
    double most_val = points[most_point].y;

    // Busco el punto mas al norte
    for(int i = 0; i < points.size(); i++){
        if(points[i].y > most_val){
            most_point = i;
            most_val = points[i].y;
        }
    }

    return most_point;
}

int get_most_east(vector<common::Point> points){
    int most_point = 0;
    double most_val = points[most_point].x;

    // Busco el punto mas al norte
    for(int i = 0; i < points.size(); i++){
        if(points[i].x > most_val){
            most_point = i;
            most_val = points[i].x;
        }
    }

    return most_point;
}

int get_most_west(vector<common::Point> points){
    int most_point = 0;
    double most_val = points[most_point].x;

    // Busco el punto mas al norte
    for(int i = 0; i < points.size(); i++){
        if(points[i].x < most_val){
            most_point = i;
            most_val = points[i].x;
        }
    }

    return most_point;
}

vector<int> get_best_candidate(vector<common::Point> current_road, vector<common::Point> points){
    vector<int> candidate(2);
    int best_position = 0;
    double best_distance = common::get_road_distance(get_best_road(current_road, points[0]));


    // Recorro todos los puntos realizando los calculos
    for(int i = 0; i < points.size(); i++){
        if(common::get_road_distance(get_best_road(current_road, points[i])) < best_distance){
            best_distance = common::get_road_distance(get_best_road(current_road, points[i]));
            best_position = i;
        }
    }
    
    // Devuelvo los resultados
    candidate[0] = best_position;
    candidate[1] = get_best_position(current_road, points[best_position]);
    return candidate;
}

vector<common::Point> get_best_road(vector<common::Point> road, common::Point point){
    // Tomo la mejor posicion posible
    int best_pos = get_best_position(road, point);
    
    // Inserto el nuevo punto y lo devuelvo
    vector<common::Point> new_road = road;
    new_road.insert(new_road.begin() + best_pos, point);
    return new_road;
}

int get_best_position(vector<common::Point> road, common::Point point){
   int best_pos = 0;
   double best_distance = 0;

   // Punto inicial
   vector<common::Point> current_road = road;
   current_road.insert(current_road.begin() + 0, point);
   best_distance = get_road_distance(current_road);
    
   // Compruebo todas las posiciones para el punto
   for(int i = 0; i < road.size(); i++){
        current_road = road;
        current_road.insert(current_road.begin() + i, point);
        
        if(get_road_distance(current_road) < best_distance){
            best_distance = get_road_distance(current_road);
            best_pos = i;
        }
   }
   
   return best_pos;;
}

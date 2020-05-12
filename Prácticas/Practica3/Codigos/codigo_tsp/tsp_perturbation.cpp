/**
 * @file tsp_perturbation.cpp
 * @brief Solucion del TSP por SNF usando perturbaciones, partiendo del SNF
 * @author segfault
 * */

#include <iostream>
#include <vector>
#include "tsp_common.hpp"
using namespace std;

// Declaracion de funciones con las que trabajamos
//==============================================================================

/**
 * @brief Calcula la solucion para un conjunto de puntos, por Shortest Neighbor First
 * @param points, el conjunto de puntos sobre el que vamos a operar
 * @pre points.size() > 0
 * @return el camino siguiendo este algoritmo
 * */
vector<common::Point> get_snf_solution(vector<common::Point> points);

/**
 * @brief Calcula un camino partiendo de un algoritmo SNF y aplicandole una serie de perturbaciones
 * @param points, conjunto de puntos sobre el que calcular el mejor camino posible
 * @parma perturbations, numero de perturbaciones que se van a realizar
 * @return el camino obtenido como ya se ha descrito
 * */
vector<common::Point> get_best_solution(vector<common::Point> points, int perturbations);

/**
 * @brief Perturba un camino respecto de un punto dado
 * @brief road, el camino a perturbar, SE MODIFICA
 * @param pos, la posicion respecto la que se perturba
 * */
void perturbate(vector<common::Point> road, int pos);

/**
 * @brief Calcula el punto cuya distancia al siguiente punto es mayor
 * @param road, camino cuyo peor camino hay que calcular 
 * @return la posicion del peor punto ya descrito
 * */
int get_worst_node(vector<common::Point> road);

// Funcion principal
//==============================================================================
int main(){
    // Parametro sobre el tamaño del problema
    int problem_size = 100;
    int perturbations = 100;

    // Inicio los numeros aleatorios
    common::startRandom();

    // Puntos con los que vamos a trabajar
    vector<common::Point> points = common::generate_problem_data(problem_size);

    // Calculo la solucion aproximada
    vector<common::Point> road = get_best_solution(points, perturbations);

    // Muestro el resultado
    cout << "La distancia de la solucion obtenida es: " << common::get_road_distance(road) << endl;

    // Todo ha salido OK
    return 0;
}

// Implementacion de las funciones 
//==============================================================================
vector<common::Point> get_snf_solution(vector<common::Point> points){
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

vector<common::Point> get_best_solution(vector<common::Point> points, int perturbations){
    // Tomo la solucion dada por el snf
    vector<common::Point> base_road = get_snf_solution(points);

    // Perturbo el numero de veces indicada
    for(int i = 0; i < perturbations; i++){
        // Calculo la posicion respecto a la que perturbar
        int pos = get_worst_node(points);

        // Perturbo el camino base
        perturbate(base_road, pos);
    }

    return base_road;
}

void perturbate(vector<common::Point> road, int pos){
    vector<common::Point> current_perb = road;
    double best_gain = 0;
    int best_perturbation = pos;
    double base_distance = common::get_road_distance(road);
    
    // Calculo la distancia de todas las permutaciones
    for(int i = 0; i < road.size(); i++){
        // Calculo la ganancia de esta permutacion
        current_perb = common::get_swap(road, pos, i);
        double swap_distance = common::get_road_distance(current_perb);
        double current_gain = swap_distance - base_distance;

        // Compruebo si he mejorado la ganancia
        if(current_gain > best_gain){
            best_perturbation = i;
            best_gain = current_gain;
        }
    }

    // Hago el cambio con la mejor perturbacion
    road = common::get_swap(road, pos, best_perturbation);
}

int get_worst_node(vector<common::Point> road){
    double worst_distance = common::distance(road[0], road[1]);
    int worst_pos = 0;

    // Recorro todos los puntos para ver cual es el peor
    for(int i = 0; i < road.size() - 1; i++){
        if(distance(road[i], road[i+1]) > worst_distance){
            worst_distance = distance(road[i], road[i+1]);
            worst_pos = i;
        }
    }

    // Compruebo la distancia del ultimo al primero
    if(distance(road[road.size()-1], road[0]) > worst_distance){
        worst_distance = road.size() - 1;
    }

    return worst_pos;
}

/**
 * @file tsp_common.hpp
 * @brief Codigo con funcionalidades comunes a todos los codigos que resuelven el TSP
 * @author segfault
 * */

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

namespace common{

// Generacion de numeros aleatorios
//==============================================================================

/**
 * @brief Devuelve el valor absoluto de un valor double 
 * @param val el double con el que trabajamos
 * @return el valor absoluto de un valor double
 * */
double abs(double val){
    return val < 0 ? - val : val;
}

void startRandom(){
    std::srand(time(NULL));
}

int randomInt(int min, int max){
    int value = min + std::rand() % (max +1 - min) ;
    return value;
} 

double random_double(double min, double max){
    return (std::rand() / (double) RAND_MAX ) * (max - min) + min;
}

// Estructura basicas Punto
//==============================================================================
/**
 * @brief Estructura para representar un punto en el plano
 *
 * En esta estructura se implementa la distancia base que usa el resto de las funciones
 * */
struct Point{
    double x = 0;
    double y = 0;

    /**
     * @brief Distancia entre dos puntos
     *
     * Cambiar esta funcion si queremos cambiar la distancia entre dos puntos para 
     * cualquier funcion que haga uso de la distancia (esta es la implementacion base)
     * */
    double distance(Point other){
        return abs(other.x - x) + abs(other.y - y);
    }
};

// Generacion de datos para el problema
//==============================================================================

/**
 * @brief Genera los puntos necesarios para el problema
 * @param num_points, la cantidad de puntos con la que queremos trabajar
 * @return un vector de puntos, cuyas coordenadas estan en el intevalo [0, num_points]
 * */
std::vector<Point> generate_problem_data(int num_points){
    std::vector<Point> points;

    for(int i = 0; i < num_points; i++){
        double x = random_double(0, num_points);
        double y = random_double(0, num_points);

        Point p = {x, y};
        points.push_back(p);
    }

    return points;
}

// Funcionalidades para solucionar partes comunes del problema
//==============================================================================

/**
 * @brief Genera un camino dado una permutacion de indices
 * @param points, los puntos sobre los que queremos calcular el camino
 * @param permutation, la permutacion de indices
 * @return un camino dado los puntos y la permutacion
 * */
std::vector<Point> generate_road_by_indexes(std::vector<common::Point> points, std::vector<int> permutation){
    std::vector<Point> road;

    for(auto index : permutation){
        road.push_back(points[index]);
    }

    return road;
}

/**
 * @brief Genera el camino resultado de intercambiar dos posiciones de un camino
 * @param road, el camino base
 * @param pos1, la primera posicon con la que intercambiamos
 * @param pos2, la segunda posicon con la que intercambiamos
 * @return un camino resultado del cambio descrito
 * */
std::vector<Point> get_swap(std::vector<Point> road, int pos1, int pos2){
    std::vector<Point> changed = road;

    Point tmp = road[pos1];
    road[pos1] = road[pos2];
    road[pos2] = tmp;

    return changed;
}

// Calculo de distancias
//==============================================================================
/**
 * @brief Calcula la distancia entre dos puntos
 * @param p1, el primer punto del que queremos calcular la distancia
 * @param p2, el segundo punto del que queremos calcular la distancia
 * @return al distancia entre ambos puntos
 * */
double distance(Point p1, Point p2){
    return p1.distance(p2);
}

/**
 * @brief Calcula la distancia de un camino dado
 * @param road, vector de puntos que forman un camino
 * @return la distancia total de ese camino
 * */
double get_road_distance(std::vector<Point> road){
    double road_distance = 0;

    // Distancia entre los n puntos
    for(int i = 0; i < road.size() - 1; i++){
        road_distance = road_distance + distance(road[i], road[i+1]);

    }

    // Distancia entre el ultimo y primer punto
    road_distance = road_distance + distance(road[0], road[road.size()-1]);

    return road_distance;
}

} // namespace common

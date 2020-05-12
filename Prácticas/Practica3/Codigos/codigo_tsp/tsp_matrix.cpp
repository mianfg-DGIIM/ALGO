/**
 * @file tsp_matrix.cpp
 * @brief Solucion del TSP por SNF usando matrices de distancias
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
 * @return el camino cuya distancia es la minima, si todo sale bien
 *         un vector vacio, si ocurre algun error
 * */
vector<common::Point> get_best_solution(vector<common::Point> points);

/**
 * @brief Genera una matriz con las distancias entre los puntos 
 * @param points, los puntos sobre los que calculamos las distancias
 * @return una matriz con las distancias entre los puntos
 *
 * Matriz[i][j] := distance(pi, pj)
 *
 *
 * WIP -- Tiene una violacion del segmento
 * */
vector<vector<double> > generate_distances_matrix(vector<common::Point> points);

/**
 * @brief Limpia las distancias de una determinada posicion
 *        Ello implica poner a cero la fila y columna de una determinada posicion
 * @param distances_matrix, matriz sobre la que trabajamos, SE MODIFICA
 * @param pos, la posicion sobre la que tenemos que limpiar
 * */
void clean_position(vector<vector<double> > & distances_matrix, int pos);

/**
 * @brief Halla la posicion en una fila con la menor distancia
 * @param distances_matrix, la matriz con las distancias
 * @param position, la posicion respecto la que queremos buscar el minimo elemento
 * @return la posicion cuya distancia es la minima, si todo sale bien
 *         -1, si ocurre algun error
 * */
int get_min_row_element(vector<vector<double> > distances_matrix, int position);

/**
 * @brief Genera una matriz size x size llena de ceros
 * @parma size, la dimension de la matriz cuadrada
 * @return la matriz cuadrada llena de ceros
 * */
vector<vector<double> > get_empty_matrix(int size);

// Funcion principal
//==============================================================================
int main(){
    // Parametro sobre el tamaño del problema
    int problem_size = 100;

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
void clean_position(vector<vector<double> > & distances_matrix, int pos){
    // Cleaning the row
    for(int col = 0; col < distances_matrix.size(); col++){
        distances_matrix[pos][col] = 0;
    }

    // Cleaning the col
    for(int row = 0; row < distances_matrix.size(); row++){
        distances_matrix[row][pos] = 0;
    }
}

int get_min_row_element(vector<vector<double> > distances_matrix, int position){
    int min_pos = 0;
    int starting_pos = 0;

    // Busco la primera posicion con distancia no nula
    while(distances_matrix[position][starting_pos] == 0 && starting_pos < distances_matrix.size()){
        starting_pos = starting_pos + 1;
    }

    // Comprobacion de seguridad
    if(starting_pos = distances_matrix.size()-1){
        cerr << "ERROR! Posicion no encontrada en get_min_row_element()" << endl;
        cerr << "Se devuelve -1 como codigo de error!" << endl;
        return -1;
    }

    // Busco el elemento optimo de la columna
    min_pos = starting_pos;
    double min_val = distances_matrix[position][starting_pos];

    for(int col = starting_pos; col < distances_matrix[position].size(); col++){
        if(distances_matrix[position][col] < min_val){
            min_pos = col;
            min_val = distances_matrix[position][col];
        }
    }

    return min_pos;
}

vector<common::Point> get_best_solution(vector<common::Point> points){
    vector<common::Point> road;
    vector<vector<double> > distances_matrix = generate_distances_matrix(points);

    // WIP
    for(int row = 0; row < distances_matrix.size(); row++){
        for(int col = 0; col < distances_matrix.size(); col++){
            cout << distances_matrix[row][col] << " ";
        }
        cout << endl;
    }
 
    // Empiezo siempre por el primer punto
    int last_point = 0;
    road.push_back(points[0]);

    while(road.size() < points.size()){
        // Hallo el punto mas cercano al anterior
        int best_position = get_min_row_element(distances_matrix, last_point);

        // Comprobacion de seguridad
        if(best_position == -1){
            cerr << "ERROR! Posicion optima no encontrada en get_best_solution()" << endl;
            cerr << "Se devuelve un vector nulo!" << endl;

            // Devuelvo un vector vacio
            return vector<common::Point>();
        }

        // Lo añado al road
        road.push_back(points[best_position]);
        
        // Limpio la fila y columna del anterior punto, ya no me hace falta
        clean_position(distances_matrix, best_position);

        // Tomo el nuevo punto anterior
        last_point = best_position;
    }

    return road;
}

vector<vector<double> > generate_distances_matrix(vector<common::Point> points){
    // Genero una matriz de points.size() x points.size() llena de ceros
    vector<vector<double> > distances_matrix = get_empty_matrix(points.size());

    for(int row = 0; row < points.size(); row++){
        for(int col = 0; col < points.size(); col++){
            distances_matrix[row][col] = common::distance(points[row], points[col]);
        }
    }       

    return distances_matrix;
}

vector<vector<double> > get_empty_matrix(int size){
    vector<vector<double> > empty;
    vector<double> empty_row(size, 0);

    for(int i = 0; i < size; i++){
        empty.push_back(empty_row);
    }

    return empty;
}

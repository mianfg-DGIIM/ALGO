/**
 * @brief Medición de tiempos para LCS
 * @filename measure.cpp
 * @author segfault
 */
#include "lcs_dynamic.hpp"
#include "lcs_brute.hpp"
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

using namespace std;


/**
 * @brief Inicia generador aleatorio
 */
void startRandom() {
    std::srand(time(NULL));
}

/**
 * @brief Genera un número aleatorio en un rango específico
 * @param min: mínimo en rango [min..max]
 * @param max: máximo en rango [min..max]
 * @return Número aleatorio en rango [min..max]
 */
int randomInt(int min, int max) {
    int value = min + std::rand() % (max +1 - min) ;
    return value;
}

/**
 * @brief Genera un string aleatorio de cierto tamaño
 * @param size: el tamaño del string aleatorio que queremos
 * @return el string especificado
 **/
string generateRandomString(int size){
    string random_string;

    for ( int i = 0; i < size; i++ ) {
        char random_char = randomInt(97, 122);
        random_string.push_back(random_char);
    }

    return random_string;
}

int main(int argc, char** argv) {
    int n;

    if ( argc < 2 ) {
        cerr << "Error, parámetros incorrectos" << endl;
        cerr << "Modo de uso: [nombre-programa] <size>" << endl;
        return 1;
    } else {
        n = atoi(argv[1]);
    }

    string t1 = generateRandomString(n);
    string t2 = generateRandomString(n);

    // Dynamic
    // =========================================================================

    // Empiezo a cronometrar
	auto start = chrono::high_resolution_clock::now(); 

    // Se calcula y muestra la solución
    string common = dynamic::getLCS(t1, t2);

    // Termino de cronometrar
    auto end = chrono::high_resolution_clock::now();

    // Tomo el tiempo
	auto duration_microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count(); 
    auto duration_seconds = duration_microseconds / 1000000.0;

    cout << n << ", " << (double)duration_seconds;

    // Brute
    // =========================================================================

    // Ídem anterior
    start = chrono::high_resolution_clock::now();
    common = brute::getLCS(t1, t2);
    end = chrono::high_resolution_clock::now();

    cout << ", " << (double)duration_seconds << endl;

    // Todo ha salido OK
    return 0;
}
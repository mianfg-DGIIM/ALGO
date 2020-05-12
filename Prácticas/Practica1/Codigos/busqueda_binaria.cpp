#include <cstdlib>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

// Algoritmo Busqueda Binaria
//==============================================================================
int BuscarBinario(int *v, const int ini, const int fin, const int x){
		int centro;
		if(ini > fin){
				return -1;
		}

		centro = (ini + fin) / 2;

		if(v[centro] == x){
				return centro;
		}
		
		if(v[centro] > x){
				return BuscarBinario(v, ini, centro-1, x);
		}

		return BuscarBinario(v, centro+1, fin, x);
}

// Generacion de numeros aleatorios
//==============================================================================
void startRandom(){ 
		srand(time(NULL)); //Inicializo los numeros aleatorios 
} 

int randomInt(int min, int max){ 
		int value = min + rand() % (max +1 - min) ; 
		return value; 
}

// Generacion de un vector aleatorio y muestra
//==============================================================================
void random_vector(int * vector, int vector_size, int lower = 0, int upper = 100){
		for(int i = 0; i < vector_size; i++){
				vector[i] = i;
		}
}

void display_vector(int *v, int size){
		for(int i = 0; i < size; i++){
				cout << v[i] << " ";
		}
		cout << endl;
}

// Cronometraje de la funcion
//==============================================================================
unsigned long get_function_time(int (*func)(int*, const int, const int, int), int size, int repeats){
		unsigned long time_sum = 0;
		int *v; // our random vector

		// times are calculated
		for(int i = 0; i < repeats; i++){
				// random vector is generated
				v = new int[size];
				random_vector(v, size);
				int val_to_search = -2;//randomInt(0, size);

				// function is executed and timed 
				auto start = high_resolution_clock::now();
				func(v, 0, size-1, val_to_search);
				auto end = high_resolution_clock::now();
				auto duration = (duration_cast<nanoseconds>(end - start)).count();

				// we add up the total time
				time_sum = time_sum + duration;

				// free dinamyc memory
				delete[] v;
		}

		// security check
		if(repeats != 0){
				return time_sum; // WIP / (unsigned long)repeats;
		}else{
				cerr << "warning! you've tried 0 repeats" << endl;
				return 0;
		}

}

// Generacion de datos
//==============================================================================
void generate_data(int (*func)(int*, const int, const int, const int), int inicio, int final, int incremento, int repeats){
		unsigned long current_time;

		cout << "Size, time(nanoseconds)" << endl;
		for(int i = inicio; i < final; i = i + incremento){
				current_time = get_function_time(func, i, repeats);
				cout << i << "," << current_time << endl;
		}
		cout << endl;
}

// Variables globales
//==============================================================================
const int repeats = 1000000;	// Numero de veces que se repite el programa para el mismo tamaño de entrada

// Programa principal
//==============================================================================
int main(int argc, char *argv[]) {
		int inicio = 0;
		int fin = 0;
		int incremento = 0;

		// Depuro la entrada
		if(argc != 4){
				cerr << "Error! Parámetros incorrectos" << endl;
				cerr << "./bubble_sort inicio fin incremento" << endl;

				// La ejecucion se termina
				return 1;
		}else{
				inicio = atoi(argv[1]);
				fin = atoi(argv[2]);
				incremento = atoi(argv[3]);

		}

		// Comprobacion de seguridad
		if(incremento <= 0){
				// Por defecto tomo 1000 muestras del intervalo
				incremento = (fin - inicio) / 1000;
		}

		// Inicio la generacion de numeros aleatorios
		startRandom();

		// Genero los datos
		generate_data(BuscarBinario, inicio, fin, incremento, repeats);

		// Todo ha salido OK
		return 0;
}

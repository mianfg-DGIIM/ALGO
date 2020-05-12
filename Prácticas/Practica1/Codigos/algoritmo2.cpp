#include <iostream>
#include <chrono>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Algoritmo de busqueda binaria
//==============================================================================
void bubble_sort(int *v, int n) {
		int i, j, aux;
		bool haycambios= true;

		i= 0;
		while (haycambios) {
				haycambios=false; // Suponemos vector ya ordenado
				for (j= n-1; j>i; j--) { // Recorremos vector de final a i
						if (v[j-1]>v[j]) { // Dos elementos consecutivos mal ordenados
								aux= v[j]; // Los intercambiamos
								v[j]= v[j-1];
								v[j-1]= aux;
								haycambios= true; // Al intercambiar, hay cambio
						}
				}
		}
}

int Busqueda(int *v, int n, int elem){
		int inicio, fin, centro;

		inicio = 0;
		fin = n-1;
		centro = (inicio+fin)/2;

		while((inicio <= fin) && (v[centro] != elem)){
				if(elem <v[centro]){
						fin = centro - 1;
				}else{
						inicio = centro + 1;
						centro = (inicio + fin) / 2;
				}

		}

		if(inicio > fin){
				return -1;
		}

		return centro;
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
				vector[i] = randomInt(lower, upper);
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
unsigned long get_function_time(int (*func)(int*, int, int), int size, int repeats){
		unsigned long time_sum = 0;
		int *v; // our random vector

		// times are calculated
		for(int i = 0; i < repeats; i++){
				// random vector is generated
				v = new int[size];
				random_vector(v, size);
				bubble_sort(v, size);
				int val = randomInt(0, 100);

				// function is executed and timed 
				auto start = high_resolution_clock::now();
				func(v, size, val);
				auto end = high_resolution_clock::now();
				auto duration = (duration_cast<microseconds>(end - start)).count();

				// we add up the total time
				time_sum = time_sum + duration;

				// free dinamyc memory
				delete[] v;
		}

		// security check
		if(repeats != 0){
				return time_sum / (unsigned long)repeats;
		}else{
				cerr << "warning! you've tried 0 repeats" << endl;
				return 0;
		}

}

// Generacion de datos
//==============================================================================
void generate_data(int (*func)(int*, int, int), int inicio, int final, int incremento, int repeats){
		unsigned long current_time;

		cout << "Size, time(us)" << endl;
		for(int i = inicio; i < final; i = i + incremento){
				current_time = get_function_time(func, i, repeats);
				cout << i << "," << current_time << endl;
		}
		cout << endl;
}

// Variables Globales
//==============================================================================
const int repeats = 100;

// Programa principal
//==============================================================================
int main(int argc, char *argv[]) {
		int inicio = 0;
		int fin = 0;
		int incremento = 0;

		// Depuro la entrada
		if(argc != 4){
				cerr << "Error! Parámetros incorrectos" << endl;
				cout << "./bubble_sort inicio fin incremento" << endl;

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
		generate_data(Busqueda, inicio, fin, incremento, repeats);

		// Todo ha salido OK
		return 0;
}

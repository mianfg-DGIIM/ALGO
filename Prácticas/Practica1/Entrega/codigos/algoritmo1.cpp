#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

int pivotar(double *v, const int ini, const int fin){
		double pivote = v[ini];
		double aux;

		int i = ini + 1;
		int j = fin;

		while(i <= j){
				while(v[i] < pivote && i <= j){
						i++;
				}

				while(v[j] == pivote && j >= i){
						j--;
				}

				if(i < j){
						aux = v[i];
						v[i] = v[j];
						v[j] = aux;
				}

				if(j < ini){
						v[ini] = v[j];
						v[j] = pivote;
				}

				return j;
		}

		return 0;

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
void random_vector(double* vector, int vector_size, int lower = 0, int upper = 100){
		for(int i = 0; i < vector_size; i++){
				vector[i] = (double)randomInt(lower, upper);
		}
}

void display_vector(double* v, int size){
		for(int i = 0; i < size; i++){
				cout << v[i] << " ";
		}
		cout << endl;
}

// Cronometraje de la funcion
//==============================================================================
unsigned long get_function_time(int (*func)(double*, int, int), int size, int repeats){
		long double time_sum = 0;
		double *v; // our random vector

		// times are calculated
		for(int i = 0; i < repeats; i++){
				// random vector is generated
				v = new double[size];
				random_vector(v, size);

				// function is executed and timed 
				auto start = high_resolution_clock::now();
				func(v, 0, size-1);
				auto end = high_resolution_clock::now();
				auto duration = (duration_cast<microseconds>(end-start)).count();

				// we add up the total time
				time_sum = time_sum + duration;

				// WIP
				//clog << "DEBUG: duration = " << duration << endl;
				//clog << "DEBUG: time_sum = " << time_sum << endl;

				// free dinamyc memory
				delete[] v;
		}

		// security check
		if(repeats != 0){
				return time_sum;// (long double)repeats;
		}else{
				cerr << "warning! you've tried 0 repeats" << endl;
				return 0;
		}
}

// Generacion de datos
//==============================================================================
void generate_data(int (*func)(double*, int, int), int inicio, int final, int incremento, int repeats){
		long double current_time;

		cout << "Size, time(us)" << endl;
		for(int i = inicio; i < final; i = i + incremento){
				current_time = get_function_time(func, i, repeats);
				cout << i << "," << current_time << endl;
		}
		cout << endl;
}

// Variables globales
//==============================================================================
const int repeats = 1000;

int main(int argc, char ** argv){
		int inicio = 0;
		int fin = 0;
		int incremento = 0;

		// Inicio los numeros aleatorios
		startRandom();

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

		// Genero los datos
		generate_data(pivotar, inicio, fin, incremento, repeats);

		// Todo ha salido OK
		return 0;
}

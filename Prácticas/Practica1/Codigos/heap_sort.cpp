#include <cstdlib>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;

// Algoritmo Heap Sort
//==============================================================================
void reajustar(int T[], int num_elem, int k){
  int j,v;
  v = T[k];
  bool esAPO = false;
  while((k < num_elem/2) && !esAPO){
    j = k+k+1;	// IR A HIJO IZDA
    if ((j<(num_elem-1)) && (T[j] < T[j+1])) j++; // Comparo hijo dcha con hijo izda, en cuyo caso, me voy al hijo derecha
    if (v >= T[j]) esAPO = true;
    T[k] = T[j];
    k = j;
  }
  T[k] = v;
}

void heapsort(int T[], int num_elem){
  int i;
  for (i = num_elem/2; i >= 0; i--)
    reajustar(T, num_elem,i);
    for (i = num_elem-1; i>= 1; i--){
      int aux = T[0];
      T[0] = T[i];
      T[i] = aux;
      reajustar(T, i,0);
    }
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
unsigned long get_function_time(void (*func)(int*, int), int size, int repeats){
		unsigned long time_sum = 0;
		int *v; // our random vector

		// times are calculated
		for(int i = 0; i < repeats; i++){
				// random vector is generated
				v = new int[size];
				random_vector(v, size);

				// function is executed and timed 
				auto start = high_resolution_clock::now();
				func(v, size);
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
void generate_data(void (*func)(int*, int), int inicio, int final, int incremento, int repeats){
		unsigned long current_time;

		cout << "Size, time(us)" << endl;
		for(int i = inicio; i < final; i = i + incremento){
				current_time = get_function_time(func, i, repeats);
				cout << i << "," << current_time << endl;
		}
		cout << endl;
}

// Variables globales
//==============================================================================
const int repeats = 100;	// Numero de veces que se repite el programa para el mismo tamaño de entrada

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
		generate_data(heapsort, inicio, fin, incremento, repeats);

		// Todo ha salido OK
		return 0;
}

#include <cstdlib>
#include <chrono>
#include <iostream>
#include <ctime>
using namespace std;
using namespace std::chrono;

// Algoritmo para resolver las torres de hanoi
//==============================================================================
/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: n�mero de discos. M > 1.
   @param i: n�mero de columna en que est�n los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: n�mero de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta funci�n imprime en la salida est�ndar la secuencia de 
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restricci�n de que ning�n
   disco se puede situar sobre otro de tama�o menor. Utiliza
   una �nica columna auxiliar.
*/
void hanoi (int M, int i = 1, int j = 2){
		if (M > 0){
				hanoi(M-1, i, 6-i-j);
				hanoi (M-1, 6-i-j, j);
		}
}

// Cronometraje de la funcion
//==============================================================================
unsigned long get_function_time(void (*func)(int, int, int), int size, int repeats){
		unsigned long time_sum = 0;

		// Times are calculated
		for(int i = 0; i < repeats; i++){
				// Function is executed and timed 
				auto start = high_resolution_clock::now();
				func(size, 1, 2);
				auto end = high_resolution_clock::now();
				auto duration = (duration_cast<microseconds>(end - start)).count();

				// We add up the total time
				time_sum = time_sum + duration;
		}

		// Security check
		if(repeats != 0){
				return time_sum / (unsigned long)repeats;
		}else{
				cerr << "WARNING! You've tried 0 repeats" << endl;
				return 0;
		}

}

// Generacion de datos
//==============================================================================
void generate_data(void (*func)(int, int, int), int inicio, int final, int incremento, int repeats){
		unsigned long current_time;

		cout << "Size, time(us)" << endl;
		for(int i = 0; i < final; i = i + incremento){
				current_time = get_function_time(func, i, repeats);
				cout << i << "," << current_time << endl;
		}
		cout << endl;
}

// Variables globales
//==============================================================================
const int repeats = 100;	// Numero de veces que se repite el programa para el mismo tama�o de entrada

int main(int argc, char **argv){
		int inicio = 0;
		int fin = 0;
		int incremento = 0;

		// Depuro la entrada
		if(argc != 4){
				cerr << "Error! Par�metros incorrectos" << endl;
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
		generate_data(hanoi, inicio, fin, incremento, repeats);

		// Todo ha salido OK
		return 0;
}

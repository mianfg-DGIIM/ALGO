/**
   @file Ordenación por mezcla
*/

#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
using namespace std;
using namespace std::chrono;

/* ************************************************************ */ 
/*  Método de ordenación por mezcla  */

/**
   @brief Ordena un vector por el método de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static 
void mergesort(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el método de mezcla.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(int T[], int inicial, int final);


/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static 
void insercion(int T[], int num_elem);


/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la inserción.
*/
static void insercion_lims(int T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a escribir.
   @param final: Posición detrás de la última de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El número de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static void fusion(int T[], int inicial, int final, int U[], int V[]);



/**
   Implementación de las funciones
**/


inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_MS = 100;

void mergesort(int T[], int num_elem)
{
  mergesort_lims(T, 0, num_elem);
}

static void mergesort_lims(int T[], int inicial, int final)
{
  if (final - inicial < UMBRAL_MS)
    {
      insercion_lims(T, inicial, final);
    } else {
      int k = (final - inicial)/2;

      int * U = new int [k - inicial + 1];
      assert(U);
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++)
        U[l] = T[l2];
      U[l] = INT_MAX;

      int * V = new int [final - k + 1];
      assert(V);
      for (l = 0, l2 = k; l < final - k; l++, l2++)
        V[l] = T[l2];
      V[l] = INT_MAX;

      mergesort_lims(U, 0, k);
      mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}
  

static void fusion(int T[], int inicial, int final, int U[], int V[])
{
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k]) {
	T[i] = U[j];
	j++;
      } else{
	T[i] = V[k];
	k++;
      };
    };
}


// Algoritmo de ordenacion por burbuja
//==============================================================================
void OrdenaBurbuja(int *v, int n) {
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
		generate_data(mergesort, inicio, fin, incremento, repeats);

		// Todo ha salido OK
		return 0;
}

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <time.h>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <cmath>

using namespace std;

void traspuesta_fuerza_bruta(int **v, int fin){

  int aux;
  for (int i = 0; i < fin; i++){
    for (int j = i+1; j< fin; j ++){
      if ( i != j){
        aux = v[j][i];
        v[j][i] = v[i][j];
        v[i][j] = aux;
      }
    }
  }
}

int main(){
	/*
  int tamano = 8;
  int **v;
  v = new int *[tamano];
  int k = 0;
  for (int i = 0; i < tamano; i++){
    v[i] = new int[tamano];
    for (int j = 0; j < tamano; j++){
      v[i][j] = k;
      k++;
    }
  }


  cout << "Mostramos matriz" << endl;


  for (int i = 0; i < tamano; i++){
    for (int j = 0; j < tamano; j++){

      cout << v[i][j] << " ";
    }
      cout << endl;
  }

  traspuesta_fuerza_bruta(v, tamano);

  cout << "Mostramos matriz traspuesta" << endl;


  for (int i = 0; i < tamano; i++){
    for (int j = 0; j < tamano; j++){

      cout << v[i][j] << " ";
    }
      cout << endl;
  }

*/
	
  /* Código para ejecutarlo de verdad*/

 int **v;
	
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; 
	double tejecucion; 
	ofstream fsalida;
	fsalida.open("salida_traspuesta_fuerzabruta.txt");

	int min = pow(2,15);
	int max = pow(2,16);
	int total = 0;
	int tiempo;
	int num_veces = 100;

	for (int tamano = min; tamano<max; tamano*=2) {
		cout  << "entramos al for"  << log2(tamano) << endl;

		v= new int*[tamano];
		int k = 0;
		for (int i = 0; i < tamano; i++){
    			v[i] = new int[tamano];
   			 for (int j = 0; j < tamano; j++){
    				  v[i][j] = k;
    				  k++;
   			 }
 		 }


			total = 0;

			for (int j = 0; j < num_veces; j++){
				t0= std::chrono::high_resolution_clock::now(); 
				traspuesta_fuerza_bruta(v, tamano); 
				tf= std::chrono::high_resolution_clock::now();  

				unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
				total = total + tejecucion;
			}

			tiempo = total / num_veces;
		
			fsalida<<tamano<<" "<<tiempo<<"\n";

			
		for (int i = 0; i < tamano; i++)
			delete [] v[i];
		delete []v;
	}


}




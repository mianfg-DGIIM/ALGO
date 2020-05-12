#include <iostream>
#include <chrono>
#include <fstream>
#include<cmath>

using namespace std;

void mostrarMatriz(int **v, int tam) {
    for ( int i = 0; i < tam; i++ ) {
        for ( int j = 0; j < tam; j++ )
            cout << v[i][j] << '\t';
        cout << endl;
    }
}

void trasponerRec(int **mat, int inicio_c, int fin_c, int fila) {
    if ( fin_c - inicio_c > 1 ) {
        int aux;

        for ( int i = fila; i < fila + (fin_c - inicio_c)/2; i++ ) {
            for ( int j = inicio_c + (fin_c - inicio_c)/2; j < fin_c; j++ ) {
                //swap(mat[i][j], mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2]);
                aux = mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2];
                mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2] = mat[i][j];
                mat[i][j] = aux;
            }
        }

        trasponerRec(mat, inicio_c, inicio_c + (fin_c - inicio_c)/2, fila);
        trasponerRec(mat, inicio_c + (fin_c - inicio_c)/2, fin_c, fila);
        trasponerRec(mat, inicio_c, inicio_c + (fin_c - inicio_c)/2, fila + (fin_c - inicio_c)/2);
        trasponerRec(mat, inicio_c + (fin_c - inicio_c)/2, fin_c, fila + (fin_c - inicio_c)/2);
    }
}

void trasponer(int **mat, int tam) {
    trasponerRec(mat, 0, tam, 0);
}

int main(int argc, char* argv[]) {
    
   int **v;
	
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; 
	double tejecucion; 
	ofstream fsalida;
	fsalida.open("salida_traspuesta_dyv.txt");

	int min = pow(2,2);
	int max = pow(2,15);
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
				trasponer(v, tamano); 
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
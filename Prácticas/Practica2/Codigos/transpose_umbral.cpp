#include <iostream>
#include <unistd.h>

using namespace std;

const int UMBRAL = 4;

void mostrarMatriz(int **v, int tam) {
    for ( int i = 0; i < tam; i++ ) {
        for ( int j = 0; j < tam; j++ )
            cout << v[i][j] << '\t';
        cout << endl;
    }
}

void trasponerRec(int **mat, int inicio_c, int fin_c, int fila) {
    if ( fin_c - inicio_c > UMBRAL ) {
        int aux;

        for ( int i = fila; i < fila + (fin_c - inicio_c)/2; i++ ) {
            for ( int j = inicio_c + (fin_c - inicio_c)/2; j < fin_c; j++ ) {
                aux = mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2];
                mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2] = mat[i][j];
                mat[i][j] = aux;
            }
        }

        trasponerRec(mat, inicio_c, inicio_c + (fin_c - inicio_c)/2, fila);
        trasponerRec(mat, inicio_c + (fin_c - inicio_c)/2, fin_c, fila);
        trasponerRec(mat, inicio_c, inicio_c + (fin_c - inicio_c)/2, fila + (fin_c - inicio_c)/2);
        trasponerRec(mat, inicio_c + (fin_c - inicio_c)/2, fin_c, fila + (fin_c - inicio_c)/2);
    } else if ( fin_c - inicio_c > 1 ) {
        // ejecutar versión iterativa
    }
}

void trasponer(int **mat, int tam) {
    trasponerRec(mat, 0, tam, 0);
}

int main(int argc, char* argv[]) {
    
    if ( argc != 2 ) {
        cerr << "Debe llamar a este programa con: ./transpose [orden_matriz]";
        exit(EXIT_FAILURE);
    }

    int tam = atoi(argv[1]);
    int **v = new int*[tam];
    int index = 0;
    for ( int i = 0; i < tam; i++ ) {
        v[i] = new int[tam];
        for ( int j = 0; j < tam; j++ ) {
            v[i][j] = index;
            index++;
        }
    }

    cout << "Matriz sin trasponer:" << endl;
    mostrarMatriz(v, tam);

    trasponer(v, tam);

    cout << "Matriz traspuesta:" << endl;
    mostrarMatriz(v, tam);
}
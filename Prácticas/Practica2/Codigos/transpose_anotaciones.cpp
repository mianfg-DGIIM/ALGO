#include <iostream>
#include <unistd.h>

using namespace std;

#define TAMANIO_TEST 8

void generarMatriz(int **v, int tam) {
    v = new int*[tam];
    int index = 0;
    for ( int i = 0; i < tam; i++ ) {
        v[i] = new int[tam];
        for ( int j = 0; j < tam; j++ ) {
            v[i][j] = index;
            index++;
        }
    }
}

void mostrarMatriz(int **v, int tam) {
    for ( int i = 0; i < tam; i++ ) {
        for ( int j = 0; j < tam; j++ )
            cout << v[i][j] << '\t';
        cout << endl;
    }
}

void mostrarTrozo(int **mat, int inicio_c, int fin_c, int fila) {
    for ( int i = fila; i < fila + (fin_c - inicio_c)/2; i++ ) {
        for ( int j = inicio_c + (fin_c - inicio_c)/2; j < fin_c; j++ )
            cout << mat[i][j] << '\t';
        cout << endl;
    }
}

void mostrarTrozoMirror(int **mat, int inicio_c, int fin_c, int fila) {
    for ( int i = fila; i < fila + (fin_c - inicio_c)/2; i++ ) {
        for ( int j = inicio_c + (fin_c - inicio_c)/2; j < fin_c; j++ )
            cout << mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2] << '\t';
        cout << endl;
    }
}

void trasponerRec(int **mat, int inicio_c, int fin_c, int fila) {    
    if ( fin_c - inicio_c > 1 ) {
        cout << "Trasponer de mat: inicio_c="<<inicio_c<<", fin_c="<<fin_c<<", fila="<<fila<<endl;
        int aux;

        cout << "Matriz antes:"<< endl;
        mostrarMatriz(mat, TAMANIO_TEST);
        for ( int i = fila; i < fila + (fin_c - inicio_c)/2; i++ ) {
            for ( int j = inicio_c + (fin_c - inicio_c)/2; j < fin_c; j++ ) {
                aux = mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2];
                mat[i + (fin_c - inicio_c)/2][j-(fin_c - inicio_c)/2] = mat[i][j];
                mat[i][j] = aux;
            }
            cout << endl;
        }

        cout << "Matriz despues: inicio_c="<<inicio_c<<", fin_c="<<fin_c<<", fila="<<fila<< endl;
        mostrarMatriz(mat, TAMANIO_TEST);

        sleep(1);
        cout << "En trasponer de mat: inicio_c="<<inicio_c<<", fin_c="<<fin_c<<", fila="<<fila<<endl;
        cout << "  Llamando a trasponer de mat: inicio_c="<<inicio_c<<", fin_c="<<inicio_c + (fin_c - inicio_c)/2<<", fila="<<fila<<endl;
        cout << "  Llamando a trasponer de mat: inicio_c="<<inicio_c + (fin_c - inicio_c)/2<<", fin_c="<<fin_c<<", fila="<<fila<<endl;
        cout << "  Llamando a trasponer de mat: inicio_c="<<inicio_c<<", fin_c="<<inicio_c + (fin_c - inicio_c)/2<<", fila="<<fila + (fin_c - inicio_c)/2<<endl;
        cout << "  Llamando a trasponer de mat: inicio_c="<<inicio_c + (fin_c - inicio_c)/2<<", fin_c="<<fin_c<<", fila="<<fila + (fin_c - inicio_c)/2<<endl;
        trasponerRec(mat, inicio_c, inicio_c + (fin_c - inicio_c)/2, fila);
        trasponerRec(mat, inicio_c + (fin_c - inicio_c)/2, fin_c, fila);
        trasponerRec(mat, inicio_c, inicio_c + (fin_c - inicio_c)/2, fila + (fin_c - inicio_c)/2);
        trasponerRec(mat, inicio_c + (fin_c - inicio_c)/2, fin_c, fila + (fin_c - inicio_c)/2);
    }


}

void trasponer(int **mat, int tam) {
    trasponerRec(mat, 0, tam, 0);
}

int main() {
    int tam = TAMANIO_TEST;
    int **v = new int*[tam];
    int index = 0;
    for ( int i = 0; i < tam; i++ ) {
        v[i] = new int[tam];
        for ( int j = 0; j < tam; j++ ) {
            v[i][j] = index;
            index++;
        }
    }

    mostrarMatriz(v, TAMANIO_TEST);

    cout << "Mostrar trozo: "<<endl;
    mostrarTrozo(v, 0, TAMANIO_TEST, 0);
    cout << "Mostrar trozo mirror: " <<endl;
    mostrarTrozoMirror(v, 0, TAMANIO_TEST, 0);
    trasponer(v, TAMANIO_TEST);
    cout << "Resultado: " << endl;
    mostrarMatriz(v, TAMANIO_TEST);

}

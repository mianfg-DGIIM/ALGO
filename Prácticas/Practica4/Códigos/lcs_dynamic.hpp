/**
 * @brief Longest Common Subsequence: encontrar subcadena más larga - Versión Programación Dinámica
 * @file lcs_dynamic.cpp
 * @author segfault
 */
#include <vector>
#include <string>
#include <iostream>

using namespace std;


namespace dynamic {

    /**
     * @brief Calcula el máximo de dos enteros
     * @param a: uno
     * @param b: el otro
     * @return el máximo de ambos
     */
    int max(int a, int b) {
        if (a > b)
            return a;
        else
            return b;
    }

    /**
     * @brief Función para imprimir la matriz LCS, incluyendo caracteres
     * @param mat: matriz LCS
     * @param str1: primera palabra
     * @param str2: segunda palabra
     */
    void printmat(vector<vector<int> > mat, string str1, string str2) {
        // cabecera: segunda palabra
        cout << "    ";
        for ( int i = 0; i < str2.size(); i++ )
            cout << str2[i] << ' ';
        cout << endl;

        for ( int i = 0; i < mat.size(); i++ ) {
            // primera palabra
            if ( i == 0 )
                cout << "  ";
            else
                cout << str1[i-1] << ' ';

            // imprimir elementos de la matriz
            for ( int j = 0; j < mat[0].size(); j++ )
                cout << mat[i][j] << " ";

            cout << endl;
        }
    }

    /**
     * @brief Crea la matriz LCS
     * @param str1: primera palabra
     * @param str2: segunda palabra
     * @return matriz LCS de las palabras str1, str2
     */
    vector<vector<int> > constructLCSMat(string str1, string str2) {
        vector<vector<int> > lcs_mat(str1.size() + 1, vector<int>(str2.size() + 1, 0));

        for ( int i = 1; i <= str1.size(); i++ ) {
            for ( int j = 1; j <= str2.size(); j++ ) {
                if ( str1[i-1] == str2[j-1] )
                    lcs_mat[i][j] = 1 + lcs_mat[i-1][j-1];
                else
                    lcs_mat[i][j] = max(lcs_mat[i-1][j], lcs_mat[i][j-1]);
            }
        }

        //printmat(lcs_mat, str1, str2);

        return lcs_mat;
    }

    /**
     * @brief Obtiene la LCS (longest common subsequence)
     * @param str1: primera palabra
     * @param str2: segunda palabra
     * @return la subcadena común más larga
     */
    string getLCS(string str1, string str2) {
        vector<vector<int> > lcs_mat = constructLCSMat(str1, str2);
        string word;

        int i = str1.size(), j = str2.size();

        while ( j > 0 ) {
            j--;
            if ( lcs_mat[i][j] != lcs_mat[i][j+1] ) {
                word = str2[j] + word;
                i--;
            }
        }

        return word;
    }

}
/**
 * @brief Interfaz para LCS
 * @file lcs.cpp
 * @author segfault
 */

#include "lcs_dynamic.hpp"
#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char** argv) {
    if ( argc != 3 ) {
        cerr << "[ERROR] - Debe usar este programa como: [nombre-programa] <str1> <str2>\n";
        exit(EXIT_FAILURE);
    }

    string str1 = argv[1], str2 = argv[2];

    vector<vector<int> > mat = dynamic::constructLCSMat(str1, str2);
    //dynamic::printmat(mat, str1, str2);

    string result = dynamic::getLCS(str1, str2);
    cout << "Grupo: segfault (GIM)\nLCS: " << result << " (tamaño: " << result.size() << ")" << endl;

    exit(EXIT_SUCCESS);
}
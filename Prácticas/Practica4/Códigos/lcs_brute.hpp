/**
 * @brief Longest Common Subsequence: encontrar cadena más larga - versión Fuerza Bruta
 * @file lcs_brute.cpp
 * @author segfault
 * @note Tener mucho cuidado al ejecutar, para valores muy grandes usar valgrind
 *       para que la recursividad no acabe con vuestro ordenador
 */
#include <vector>
#include <string>

using namespace std;


namespace brute {

    /**
     * @brief Devuelve todas las subsecuencias de un texto
     * @param text: el texto del que queremos obtener todas las subsecuencias
     * @return un vector con todas las subsecuencias
     */
    vector<string> getSubsequences(string text) {
        if ( text.size() > 1 ) {
            vector<string> subsequences;

            string slice = string(text.begin() + 1, text.end());

            for ( auto sub : getSubsequences(slice) ) {
                string current1 = text[0] + sub;
                string current2 = "" + sub;
                subsequences.push_back(current1);
                subsequences.push_back(current2);
            }
            
            return subsequences;
        } else {
            vector<string> subsequences;
        
            subsequences.push_back(text);
            subsequences.push_back("");

            return subsequences;
        }
    }

    /**
     * @brief Calcula una porción de un string
     * @param text: el texto del que quiero obtener una porción suya
     * @param start: la posición de inicio
     * @param end: la posición final
     * @return text[start:end]
     * */
    string slice(string text, int start, int end) {
        string current;

        for(int i = start; i <= end; i++){
            current.push_back(text[i]);
        }

        return current;
    }

    /**
     * @brief Encuentra por fuerza bruta la subsecuencia común mas larga 
     * @param text1: el primer texto
     * @param text2: el segundo texto
     * @return la subsecuencia común mas larga,
     *         "" si no hay ninguna letra en común
     * */
    string getLCS(string text1, string text2) {
        string largest = "";

        for(auto sub1 : getSubsequences(text1)){
            for(auto sub2 : getSubsequences(text2)){
                if(sub1 == sub2 && sub1.size() > largest.size()){
                    largest = sub1;
                }
            }
        }

        return largest;
    }

}
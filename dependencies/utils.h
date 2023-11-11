#include <iostream>
#include "./macros.h"
#include <cctype>

using namespace std;


template <typename T, size_t N>
size_t get_length(T(&)[N]) {
    return N;
}


/**
 * retornara true si el valor ascii_num es un numero segun ascii
 * false en caso contrario
 */
bool char_is_num(char c){
    int ascci_num = (int) c;
    return (57 >= ascci_num) && (ascci_num >= 48);
}

/*
 *  comprueba si la cadena string es completamente un numero
 *  retornara false si consigue un caracter que no sea un numero
 *  true en caso contrario
 * */
bool string_is_num(std::string string){
    for (char c : string){
        if (!(char_is_num(c))){
            return false;
        }
    }
    return true;
}



void print_header(){
    system("clear");
    cout << Y_SEPARATION << X_SEPARATION << "Santiago De Andrade, 31.065.103"               << endl;
    cout << X_SEPARATION <<                 "Proyecto de Algoritmos y estructuras de Datos"  << endl;
    cout << Y_SEPARATION << X_SEPARATION << "Pulsa enter para comenzar ... ";
    getchar();
}

/*
 *  Retornara true en caso de que el option se encuentre en el rango de max y min
 */
int option_is_valid(int option, int max_option_possible, int min_option_possible){
    return (option >= min_option_possible) && (option <= max_option_possible);
}


string uppercase(string target){
    for (int i = 0; i < target.length(); i++){
        target[i] = toupper(target[i]);
    }
    return target;
}

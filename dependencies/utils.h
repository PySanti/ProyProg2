#include <iostream>
#include "./macros.h"

using namespace std;
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

/**
 *  Determinara la longitud de la cadena string
 */
int string_length(std::string string){
    int i = 0;
    while (((int) string[i]) != 0){
        i++;
    }
    return i;
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



/**
 * Recibira un arreglo de strings que representaran las opciones
 * del menu.
 * 
 * Imprimira el menu hasta que el usuario ingrese una opcion valida.
 * Posteriormente, retornara la opcion ingresada
*/
int print_menu(string options_list[], int max_option, int min_option){
    bool failed = false;
    string option;
    while (1){
        system("clear");
        for (int i = 0 ; i < max_option; i++){
            if ( i == 0){
                cout << Y_SEPARATION << X_SEPARATION;
            } else {
                cout << X_SEPARATION;
            }
            cout << i+1 << " ~ " << options_list[i] << endl;
        }
        cout << Y_SEPARATION << X_SEPARATION;
        if (failed)
            cout << BAD_INPUT_MSG << X_SEPARATION;
        cout << "-> Ingresa una opción : ";
        cin  >> option;
        if ((string_length(option) > 5) || !(string_is_num(option))){
            failed = true;
        } else{
            int numbered_option = stoi(option);
            if (!option_is_valid(numbered_option, max_option, min_option))
                failed = true;
            else
                return numbered_option;
        }
    };
}
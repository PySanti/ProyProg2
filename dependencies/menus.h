#include <iostream>
#include "./macros.h"
#include "./utils.h"
/**
 * Aca almacenaremos todo el codigo para manejo de menus
*/

using namespace std;

/**
 * Funcion creada para modularizar codigo de la 
 * impresión de opciones en print_menu
*/
void print_menu_options(string options[],int max_option){
    for (int i = 0 ; i < max_option; i++){
        if ( i == 0){
            cout << Y_SEPARATION << X_SEPARATION;
        } else {
            cout << X_SEPARATION;
        }
        cout << i+1 << " ~ " << options[i] << endl;
    }
}
/**
 * Funcion creada para modularizar codigo de impresion
 * de input del print_menu
 * 
 * Retornara el valor ingresado en el input
*/
string print_menu_input(bool option_failed){
    string entered_option;
    cout << Y_SEPARATION << X_SEPARATION;
    if (option_failed)
        cout << BAD_INPUT_MSG << X_SEPARATION;
    cout << "-> Ingresa una opción : ";
    cin  >> entered_option;
    return entered_option;
}

/**
 * Funcion creada para modularizar la validacion
 * de la opcion ingresada en el print_menu.
 * 
 * Retornara -1 en caso de que la opcion ingresada sea invalida
 * 
 * Retornara la opcion ingresada en forma de entero en caso de que la opcion sea valida
*/
int check_entered_menu_option(string entered_option,int max_option,int min_option){
    if ((get_string_length(entered_option) > 5) || !(string_is_num(entered_option))){
        return -1;
    } else{
        int numbered_option = stoi(entered_option);
        return option_is_valid(numbered_option, max_option, min_option) ? numbered_option : -1 ;
    }
}
/**
 * Funcion creada para modularizar la impresion del menu_title en el print_menu
*/
void print_menu_title(string menu_title){
    cout << "\n\n\n" << X_SEPARATION << " ~~ " << uppercase(menu_title) << " ~~ ";
}


/**
 * Recibira un arreglo de strings que representaran las opciones
 * del menu.
 * 
 * Imprimira el menu hasta que el usuario ingrese una opcion valida.
 * Posteriormente, retornara la opcion ingresada
*/
int print_menu(string options_list[], int max_option, int min_option, string menu_title){
    bool failed = false;
    int checked_option;
    string option;
    while (1){
        system("clear");
        print_menu_title(menu_title);
        print_menu_options(options_list, max_option);
        option = print_menu_input(failed);
        checked_option = check_entered_menu_option(option, max_option, min_option);
        if (checked_option == -1)
            failed = true;
        else
            return checked_option; 
    };
}
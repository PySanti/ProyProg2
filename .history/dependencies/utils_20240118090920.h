#include <iostream>
#include "./macros.h"
#include <map>
#include <regex>


using namespace std;
void cls(){
    system("cls");
}
void pause(){
    cin.get();
}

void clean_buffer(){
    cin.clear();
    cin.ignore(1);
}
template <typename T, size_t N>
size_t get_length(T(&)[N]) {
    return N;
}

bool validate_field(string pattern,string value){
    regex current_pattern;
    current_pattern = pattern;
    return (pattern == "_" || regex_search(value, current_pattern)) && (value.length() > 0);
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
    if (string.length() == 0){
        return false;
    } else {
        for (char c : string){
            if (!(char_is_num(c))){
                return false;
            }
        }
        return true;
    }
}



void print_header(){
    cls();;
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


string to_lower(string target){
    for (int i = 0; i < target.length(); i++){
        target[i] = tolower(target[i]);
    }
    return target;
}

string capitalize(string target){
    for (int i = 0; i < target.length() ; i++){
        target[i] = (i == 0)? toupper(target[i]) : tolower(target[i]);
    }
    return target;
}

/**
 * Funcion creada para imprimir y validar formularios.
 * 
 * 
 * Recibira un map con claves como los campos del formulario y
 * como patron, la expresion regular que deben cumplir.
 * 
 * En caso de que el campo no tenga ninguna restriccion,
 * asignar '-' como valor
*/
map<string, string> validate_form(map<string, string> patterns_dict){
    int current_field = 0;
    int current_field_iterator = 0;
    bool validation_finished = false;
    string current_value;
    string error_log;
    while (!validation_finished){
        cls();;
        for (const auto& par : patterns_dict) {
            const string& field = par.first;
            const string& pattern = par.second;
            if (current_field_iterator == 0)
                cout << Y_SEPARATION << endl;
            if (current_field_iterator == current_field){
                if (error_log != "")
                    cout << X_SEPARATION << error_log << endl;
                cout << X_SEPARATION << capitalize(field) << " : ";
                getline(cin, current_value);
                cout << endl;
                if (validate_field(pattern, current_value)){
                    patterns_dict[field] = current_value;
                    current_field ++;
                    current_field_iterator = 0;
                    error_log = "";
                    if (current_field == patterns_dict.size()){
                        validation_finished = true;
                    }
                    break;
                } else {
                    error_log = "Error, has ingresado un valor para " + field + " invalido !";
                    current_field_iterator = 0;
                    break;
                }
            } else {
                cout << X_SEPARATION << capitalize(field) << " : " << pattern << endl << endl;
                current_field_iterator ++;
            }
        }
    }
    return patterns_dict;
}


void success_screen(string msg){
    cls();;
    cout << Y_SEPARATION << X_SEPARATION << uppercase(msg);
    cout << Y_SEPARATION;
    cout << X_SEPARATION << "Pulse enter para continuar ... ";
    pause();
}


bool string_contains(string str, string target){
    return str.find(target) != string::npos;

}
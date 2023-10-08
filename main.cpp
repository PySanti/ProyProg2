#include <iostream>
#include <cstdlib>

using namespace std;

#define Y_SEPARATION "\n\n\n\n\n\n\n"
#define X_SEPARATION "\t\t\t\t\t"
#define BIGGEST_MENU_OPTION 4
#define SMALLEST_MENU_OPTION 1
#define MENU_OPTION_MAX_SIZE 20
#define BAD_INPUT_MSG "Error, la opcion ingresada no es valida ... \n"

bool char_is_num(int ascci_num){
    return (57 >= ascci_num) && (ascci_num >= 48);
}

bool string_is_num(std::string string){
    // comprueba si la cadena string es completamente un numero
    // retornara false si consigue un caracter que no sea un numero

    for (int i = 0; ((int) string[i]) != 0; i++){
        if (!(char_is_num((int) string[i]))){
            return false;
        }
    }
    return true;
}


int length(std::string string){
    int i = 0;
    while (((int) string[i]) != 0){
        i++;
    }
    return i;
}

int numbered(std::string string){
    // convierte una cadena numerica en un numero
    // retornara -1 si hubo algun error

    int string_length = length(string);
    int num = 0, current_exp = 1;
    if (string_length > 9)
        return -1;
    for (int i = string_length-1; i != -1; i--){
        if (char_is_num((int) string[i])){
            num += (((int) string[i]) - 48)*current_exp;
            current_exp *=10;
        } else {
            return -1;
        }
    }
    return num;
}

void print_header(){
    system("clear");
    cout << Y_SEPARATION << X_SEPARATION << "Santiago De Andrade, 31.065.103"               << endl;
    cout << X_SEPARATION <<                 "Proyecto de Algoritmos y ascii_char de Datos"  << endl;
    cout << Y_SEPARATION << X_SEPARATION << "Pulsa enter para comenzar ... ";
    getchar();
}



int option_is_valid(int option, int max_option_possible, int min_option_possible){
    return (option >= min_option_possible) && (option <= max_option_possible);
}


int print_menu(){
    bool failed = false;
    std::string option;
    while (1){
        system("clear");
        cout << Y_SEPARATION << X_SEPARATION << "1 ~ Agregar elementos"      << endl;
        cout << X_SEPARATION                 << "2 ~ Modificar elementos"    << endl;
        cout << X_SEPARATION                 << "3 ~ Buscar elementos"       << endl;
        cout << X_SEPARATION                 << "4 ~ Eliminar elementos"     << endl;
        if (failed)
            cout << Y_SEPARATION << X_SEPARATION << BAD_INPUT_MSG << X_SEPARATION << "-> Ingresa una opcion : ";
        else
            cout << Y_SEPARATION << X_SEPARATION << "-> Ingresa una opcion : ";
        cin  >> option;
        if ((length(option) > 5) || !(string_is_num(option))){
            failed = true;
        } else{
            int numbered_option = numbered(option);
            if (!option_is_valid(numbered_option, 4, 1))
                failed = true;
            else
                break;
        }
    };
    return 1;
}


int main(int argc, char **argv){
    int selected_option;
    print_header();
    selected_option = print_menu();
    return 0;
}

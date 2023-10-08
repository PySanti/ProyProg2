#include <iostream>
#include <cstdlib>

using namespace std;

#define Y_SEPARATION "\n\n\n\n\n\n\n"
#define X_SEPARATION "\t\t\t\t\t"
#define BIGGEST_MENU_OPTION 4
#define SMALLEST_MENU_OPTION 1
#define MENU_OPTION_MAX_SIZE 20
#define BAD_INPUT_MSG "Error, la opcion ingresada no es valida ... \n"

bool string_is_num(std::string string){
    // comprueba si la cadena string es completamente un numero
    // retornara false si consigue un caracter que no sea un numero

    for (int i = 0; ((int) string[i]) != 0; i++){
        if (!((57 >= ((int) string[i])) &&  (((int) string[i]) >= 48))){
            return false;
        }
    }
    return true;
}

int numbered(std::string string){
    // convierte una cadena numerica en un numero
    return 0;
}

void print_header(){
    system("clear");
    cout << Y_SEPARATION << X_SEPARATION << "Santiago De Andrade, 31.065.103"               << endl;
    cout << X_SEPARATION <<                 "Proyecto de Algoritmos y ascii_char de Datos"  << endl;
    cout << Y_SEPARATION << X_SEPARATION << "Pulsa enter para comenzar ... ";
    getchar();
}

int length(std::string string){
    int i = 0;
    while (((int) string[i]) != 0){
        i++;
    }
    return i + 1;
}


int print_menu(){
    bool failed = false;
    std::string option;
    while (1){
        cout << Y_SEPARATION << X_SEPARATION << "1 ~ Agregar elementos"      << endl;
        cout << X_SEPARATION                 << "2 ~ Modificar elementos"    << endl;
        cout << X_SEPARATION                 << "3 ~ Buscar elementos"       << endl;
        cout << X_SEPARATION                 << "4 ~ Eliminar elementos"     << endl;
        if (failed)
            cout << Y_SEPARATION << X_SEPARATION << BAD_INPUT_MSG << X_SEPARATION << "-> Ingresa una opcion : ";
        else
            cout << Y_SEPARATION << X_SEPARATION << "-> Ingresa una opcion : ";
        cin  >> option;
        if ((length(option) > 5) || !(string_is_num(option)))
            failed = true;
        else
            break;
    };
    return 1;
}


int main(int argc, char **argv){
    int selected_option;
    print_header();
    while (1){
        selected_option = print_menu();
    }
    return 0;
}

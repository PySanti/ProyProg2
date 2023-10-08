#include <iostream>
#include <cstdlib>

using namespace std;

#define Y_SEPARATION "\n\n\n\n\n\n\n"
#define X_SEPARATION "\t\t\t\t\t"
#define BIGGEST_MENU_OPTION 4
#define SMALLEST_MENU_OPTION 1
#define MENU_OPTION_MAX_SIZE 20
#define BAD_INPUT_MSG "Error, la opcion ingresada no es valida ... \n"

bool is_num(int ascii_char){
    return (57 >= ascii_char) &&  (ascii_char >= 48);
}

bool option_is_valid(std::string option){
    for (int i = 0; ((int) option[i]) != 0; i++){
        if (!is_num((int) option[i])){
            return false;
        }
    }
    return true;
}

void print_header(){
    system("clear");
    cout << Y_SEPARATION << X_SEPARATION << "Santiago De Andrade, 31.065.103"               << endl;
    cout << X_SEPARATION <<                 "Proyecto de Algoritmos y ascii_char de Datos"  << endl;
    cout << Y_SEPARATION << X_SEPARATION << "Pulsa enter para comenzar ... ";
    getchar();
}


int print_menu(){
    std::string option;
    bool failed = false;
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
        if (!option_is_valid(option))
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

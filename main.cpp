#include <iostream>
#include <cstdlib>

using namespace std;

#define Y_SEPARATION "\n\n\n\n\n\n\n"
#define X_SEPARATION "\t\t\t\t\t"
#define BIGGEST_MENU_OPTION 4
#define SMALLEST_MENU_OPTION 1
#define MENU_OPTION_MAX_SIZE 20

int check_option_entered(std::string option){
    int i = 0;
    while ((int) option[i] != 0){
        cout << option[i] << endl;
        if ((57 < (int) option[i]) ||  ((int) (option[i]) < 48)){
            cout << option[i] << endl;
            cout << "Error, el usuario ha ingresado un caracter" << endl;
            return 0;
        }
        i++;
    }
    return 1;
}

void print_header(){
    system("clear");
    cout << Y_SEPARATION << X_SEPARATION << "Santiago De Andrade, 31.065.103" << endl;
    cout << X_SEPARATION << "Proyecto de Algoritmos y Estructuras de Datos" << endl;
    cout << Y_SEPARATION << X_SEPARATION << "Pulsa enter para comenzar ... ";
    getchar();
}


int print_menu(){
    std::string option;
    do {
        cout << Y_SEPARATION << X_SEPARATION << "1 - Agregar elementos"      << endl;
        cout << X_SEPARATION                 << "2 - Modificar elementos"    << endl;
        cout << X_SEPARATION                 << "3 - Buscar elementos"       << endl;
        cout << X_SEPARATION                 << "4 - Eliminar elementos"     << endl;
        cout << Y_SEPARATION << X_SEPARATION << "-> Ingresa una opcion : ";
        cin  >> option;
    } while (check_option_entered(option) == 1);

    return 1;
}


int main(int argc, char **argv){
    int selected_option;
    while (1){
        selected_option = print_menu();
    }
    return 0;
}

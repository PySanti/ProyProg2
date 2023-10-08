#include <iostream>
#include <cstdlib>

using namespace std;

#define Y_SEPARATION "\n\n\n\n\n\n\n"
#define X_SEPARATION "\t\t\t\t\t"

void print_header(){
    system("clear");
    cout << Y_SEPARATION << X_SEPARATION << "Santiago De Andrade, 31.065.103" << endl;
    cout << X_SEPARATION << "Proyecto de Algoritmos y Estructuras de Datos" << endl;
    cout << Y_SEPARATION << X_SEPARATION << "Pulsa enter para comenzar ...";
    getchar();
}


int print_menu(){
    system("clear");
    int option;

    cout << Y_SEPARATION << X_SEPARATION << "1- Agregar elementos"      << endl;
    cout << X_SEPARATION                 << "2- Modificar elementos"    << endl;
    cout << X_SEPARATION                 << "3- Buscar elementos"       << endl;
    cout << X_SEPARATION                 << "4- Eliminar elementos"     << endl;
    cout << Y_SEPARATION << X_SEPARATION << "-> Ingresa una opcion : ";
    cin  >> option;
    return option;
}


int main(int argc, char **argv){
    int selected_option;
    print_header();
    selected_option = print_menu();
    return 0;
}

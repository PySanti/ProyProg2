#include <iostream>
#include <cstdlib>

using namespace std;

#define Y_SEPARATION "\n\n\n\n\n\n\n"
#define X_SEPARATION "\t\t\t\t\t"
#define BIGGEST_MENU_OPTION 4
#define SMALLEST_MENU_OPTION 1
#define MENU_OPTION_MAX_SIZE 20
#define BAD_INPUT_MSG "Error, la opcion ingresada no es valida ... \n"

typedef struct Node{
    int element;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;


List *create_list(){
    List *new_list = new List;
    new_list->head = NULL;
    return new_list;
}

Node *create_node(int element){
    Node *new_node = new Node;
    new_node->element = element;
    new_node->next = NULL;
    return new_node;
}

/**
 * Imprimira los elementos de la lista
 */
void print_list(List *main_list){
    Node *current_node = main_list->head;
    while (current_node != NULL){
        cout << current_node->element << ",";
        current_node = current_node->next;
    }
    cout << endl;
}

/**
 * Agrega un elemento a la lista
 */
void append_element(List *main_list, int element){
    Node *current_node = main_list->head;
    Node *last_node = NULL;
    while (current_node != NULL){
        last_node = current_node;
        current_node = current_node->next;
    }
    if (last_node != NULL){
        last_node->next = create_node(element);
    } else {
        main_list->head = create_node(element);
    }
}

/**
 * retornara true si el valor ascii_num es un numero segun ascii
 * false en caso contrario
 */
bool char_is_num(int ascci_num){
    return (57 >= ascci_num) && (ascci_num >= 48);
}


/*
 *  comprueba si la cadena string es completamente un numero
 *  retornara false si consigue un caracter que no sea un numero
 *  true en caso contrario
 * */
bool string_is_num(std::string string){
    for (int i = 0; ((int) string[i]) != 0; i++){
        if (!(char_is_num((int) string[i]))){
            return false;
        }
    }
    return true;
}

/**
 *  Determinara la longitud de la cadena string
 */
int length(std::string string){
    int i = 0;
    while (((int) string[i]) != 0){
        i++;
    }
    return i;
}

/**
 *  convierte una cadena numerica en un numero
 *  retornara -1 si hubo algun error
 *  el numero en concreto en caso contrario
 */
int numbered(std::string string){
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


/*
 *  Retornara true en caso de que el option se encuentre en el rango de max y min
 */
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
    // int selected_option;
    // print_header();
    // selected_option = print_menu();


    List *MAIN_LIST = create_list();
    for (int i = 0; i < 10 ; i ++){
        append_element(MAIN_LIST, i);
    }
    print_list(MAIN_LIST);
    return 0;
}

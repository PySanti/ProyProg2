#include <iostream>
#include <cstdlib>
#include "./dependencies/macros.h"
#include "./dependencies/utils.h"
#include "./dependencies/structs.h"

using namespace std;



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



int main(int argc, char **argv){
    int selected_option;
    print_header();
    selected_option = print_menu();
    return 0;
}

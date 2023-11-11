#include <iostream>
#include <cstdlib>
#include "./dependencies/macros.h"
#include "./dependencies/structs.h"
#include "./dependencies/menus.h"
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
    string options[] = {
        "Artículos",
        "Inventario",
        "Clientes",
        "Descuentos",
        "Vendedores",
        "Comisiones por ventas",
        "Bonos",
        "Facturas"
    };
    int selected_option = print_menu(options, 8, 1, "Menu Inicial");
    switch (selected_option)
    {
        case 1:
            string article_options[] = {
                "Agregar articulo",
                "Modificar articulo",
                "Eliminar articulo",
                "Buscar articulo"
            };
            selected_option = print_menu(article_options, 4, 1, "Menu de Artículos");
            break;
        case 2:
            string stock_options[] = {
                "Agregar inventario",
                "Modificar inventario",
                "Eliminar inventario",
                "Buscar inventario"
            };
            selected_option = print_menu(stock_options, 4, 1, "Menu de Inventario");
            break;
        case 3:
            string client_options[] = {
                "Agregar cliente",
                "Modificar cliente",
                "Eliminar cliente",
                "Buscar cliente"
            };
            selected_option = print_menu(client_options, 4, 1, "Menu de Clientes");
            break;
        case 4:
            string discount_options[] = {
                "-",
                "-",
                "-",
            };
            selected_option = print_menu(discount_options, 3, 1, "Menu de Descuentos");
            break;
        case 5:
            string seller_options[] = {
                "Agregar vendedor",
                "Modificar vendedor",
                "Eliminar vendedor",
                "Buscar vendedor"
            };
            selected_option = print_menu(seller_options, 4, 1, "Menu de Vendedores");
            break;
        case 6:
            string comission_options[] = {
                "-",
            };
            selected_option = print_menu(comission_options, 1, 1, "Menu de comisiones");
            break;
        case 7:
            string bones_options[] = {
                "-",
            };
            selected_option = print_menu(bones_options, 1, 1, "Menu de Bonos");
            break;
    } (selected_option);
    return 0;
}

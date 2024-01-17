#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "./dependencies/macros.h"
#include "./dependencies/menus.h"
#include "./dependencies/options_handling.h"
using namespace std;

string main_options[] = {
    "Artículos",
    "Inventario",
    "Clientes",
    "Descuentos",
    "Vendedores",
    "Comisiones por ventas",
    "Bonos",
    "Facturas",
    "Salir"
};
std::map<std::string, string> articles_pattern_dict = {
    {"nombre",      "_"             },
    {"codigo",      CODE_NUMBER_REGEX},
    {"cantidad" ,   INT_NUMBER_REGEX},
    {"precio" ,     FLOAT_NUMBER_REGEX}
};

std::map<std::string, string> clients_pattern_dict = {
    {"nombre",               "_"},
    {"direccion",            "_"},
    {"numero telefonico" ,   PHONE_NUMBER_REGEX},
};
std::map<std::string, string> sellers_pattern_dict = {
    {"nombre",                  "_"             },
    {"fecha de ingreso",        DATE_REGEX},
    {"cedula",                  INT_NUMBER_REGEX},
    {"comision" ,               FLOAT_NUMBER_REGEX},
};

int main(int argc, char **argv){
    bool exit = false;
    handle_read_articles_from_file("data/articles.txt", articles_pattern_dict, MAIN_ARTICLE_LIST);
    handle_read_clients_from_file("data/clients.txt", clients_pattern_dict, MAIN_CLIENTS_LIST);
    handle_read_sellers_from_file("data/sellers.txt", sellers_pattern_dict, MAIN_SELLERS_LIST);
    while (!exit){
        int selected_option = print_menu(main_options, sizeof(main_options) / sizeof(main_options[0]), "Menu Inicial");
        switch (selected_option)
        {
            case 1:
                handle_articles(articles_pattern_dict);
                break;
            case 2:
                handle_stock();
                break;
            case 3:
                handle_clients(clients_pattern_dict);
                break;
            case 4:
                handle_discounts();
                break;
            case 5:
                handle_sellers(sellers_pattern_dict);
                break;
            case 6:
                handle_comissions();
                break;
            case 7:
                handle_bones();
                break;
            case 8:
                handle_invoices();
                break;
            case 9:
                exit = true;
                break;
        } (selected_option);
    }
    write_sellers_list_in_file("data/sellers.txt", MAIN_SELLERS_LIST);
    write_clients_list_in_file("data/clients.txt", MAIN_CLIENTS_LIST);
    write_articles_list_in_file("data/articles.txt", MAIN_ARTICLE_LIST);

    delete_articles_list();
    delete_clients_list();
    delete_sellers_list();

    return 0;
}

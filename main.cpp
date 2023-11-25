#include <iostream>
#include <cstdlib>
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




int main(int argc, char **argv){
    bool exit = false;
    while (!exit){
        int selected_option = print_menu(main_options, sizeof(main_options) / sizeof(main_options[0]), "Menu Inicial");
        switch (selected_option)
        {
            case 1:
                handle_articles();
                break;
            case 2:
                handle_stock();
                break;
            case 3:
                handle_clients();
                break;
            case 4:
                handle_discounts();
                break;
            case 5:
                handle_sellers();
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
    return 0;
}

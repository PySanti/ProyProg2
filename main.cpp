#include <iostream>
#include <cstdlib>
#include "./dependencies/macros.h"
#include "./dependencies/structs.h"
#include "./dependencies/menus.h"
using namespace std;

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
string article_options[] = {
    "Agregar articulo",
    "Modificar articulo",
    "Eliminar articulo",
    "Buscar articulo"
};
string stock_options[] = {
    "Agregar inventario",
    "Modificar inventario",
    "Eliminar inventario",
    "Buscar inventario"
};
string client_options[] = {
    "Agregar cliente",
    "Modificar cliente",
    "Eliminar cliente",
    "Buscar cliente"
};
string discount_options[] = {
    "-",
    "-",
    "-",
};
string seller_options[] = {
    "Agregar vendedor",
    "Modificar vendedor",
    "Eliminar vendedor",
    "Buscar vendedor"
};
string comission_options[] = {
    "-",
};
string bones_options[] = {
    "-",
};




int main(int argc, char **argv){
    int selected_option = print_menu(options, 8, 1, "Menu Inicial");
    switch (selected_option)
    {
        case 1:
            selected_option = print_menu(article_options, 4, 1, "Menu de Artículos");
            break;
        case 2:

            selected_option = print_menu(stock_options, 4, 1, "Menu de Inventario");
            break;
        case 3:

            selected_option = print_menu(client_options, 4, 1, "Menu de Clientes");
            break;
        case 4:

            selected_option = print_menu(discount_options, 3, 1, "Menu de Descuentos");
            break;
        case 5:
            selected_option = print_menu(seller_options, 4, 1, "Menu de Vendedores");
            break;
        case 6:

            selected_option = print_menu(comission_options, 1, 1, "Menu de comisiones");
            break;
        case 7:
            selected_option = print_menu(bones_options, 1, 1, "Menu de Bonos");
            break;
    } (selected_option);
    return 0;
}

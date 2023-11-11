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
    "Facturas",
    "Salir"
};
string article_options[] = {
    "Agregar articulo",
    "Modificar articulo",
    "Eliminar articulo",
    "Buscar articulo",
    "Volver"
};
string stock_options[] = {
    "Agregar inventario",
    "Modificar inventario",
    "Eliminar inventario",
    "Buscar inventario",
    "Volver"
};
string client_options[] = {
    "Agregar cliente",
    "Modificar cliente",
    "Eliminar cliente",
    "Buscar cliente",
    "Volver"
};
string discount_options[] = {
    "-",
    "-",
    "-",
    "Volver"
};
string seller_options[] = {
    "Agregar vendedor",
    "Modificar vendedor",
    "Eliminar vendedor",
    "Buscar vendedor",
    "Volver"
};
string comission_options[] = {
    "-",
    "Volver",
};
string bones_options[] = {
    "-",
    "Volver"
};
string invoice_options[] = {
    "-",
    "Volver"
};





int main(int argc, char **argv){
    bool exit = false;
    while (!exit){
        int selected_option = print_menu(options, sizeof(options) / sizeof(options[0]), "Menu Inicial");
        switch (selected_option)
        {
            case 1:
                selected_option = print_menu(article_options, sizeof(article_options) / sizeof(article_options[0]), "Menu de Artículos");
                break;
            case 2:
                selected_option = print_menu(stock_options, sizeof(stock_options) / sizeof(stock_options[0]), "Menu de Inventario");
                break;
            case 3:
                selected_option = print_menu(client_options,sizeof(client_options) / sizeof(client_options[0]) , "Menu de Clientes");
                break;
            case 4:
                selected_option = print_menu(discount_options,sizeof(discount_options) / sizeof(discount_options[0]), "Menu de Descuentos");
                break;
            case 5:
                selected_option = print_menu(seller_options,sizeof(seller_options) / sizeof(seller_options[0]) , "Menu de Vendedores");
                break;
            case 6:
                selected_option = print_menu(comission_options, sizeof(comission_options) / sizeof(comission_options[0]), "Menu de comisiones");
                break;
            case 7:
                selected_option = print_menu(bones_options, sizeof(bones_options) / sizeof(bones_options[0]), "Menu de Bonos");
                break;
            case 8:
                selected_option = print_menu(invoice_options, sizeof(invoice_options) / sizeof(invoice_options[0]), "Menu de facturas");
                break;
            case 9:
                exit = true;
                break;
        } (selected_option);
    }
    return 0;
}

#include <iostream>
#include <cstdlib>
#include "./dependencies/macros.h"
#include "./dependencies/structs.h"
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
string article_options[] = {
    "Ver artículos",
    "Agregar articulo",
    "Modificar articulo",
    "Eliminar articulo",
    "Buscar articulo",
    "Volver"
};
string stock_options[] = {
    "Ver inventario",
    "Agregar inventario",
    "Modificar inventario",
    "Eliminar inventario",
    "Buscar inventario",
    "Volver"
};
string client_options[] = {
    "Ver clientes",
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
    "Ver vendedores",
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
        int selected_option = print_menu(main_options, sizeof(main_options) / sizeof(main_options[0]), "Menu Inicial");
        switch (selected_option)
        {
            case 1:
                selected_option = print_menu(article_options, sizeof(article_options) / sizeof(article_options[0]), "Menu de Artículos");
                handle_article_option(selected_option, article_options);
                break;
            case 2:
                selected_option = print_menu(stock_options, sizeof(stock_options) / sizeof(stock_options[0]), "Menu de Inventario");
                handle_stock_option(selected_option, article_options);
                break;
            case 3:
                selected_option = print_menu(client_options,sizeof(client_options) / sizeof(client_options[0]) , "Menu de Clientes");
                handle_client_option(selected_option, client_options);
                break;
            case 4:
                selected_option = print_menu(discount_options,sizeof(discount_options) / sizeof(discount_options[0]), "Menu de Descuentos");
                handle_discount_option(selected_option, client_options);
                break;
            case 5:
                selected_option = print_menu(seller_options,sizeof(seller_options) / sizeof(seller_options[0]) , "Menu de Vendedores");
                handle_seller_option(selected_option, client_options);
                break;
            case 6:
                selected_option = print_menu(comission_options, sizeof(comission_options) / sizeof(comission_options[0]), "Menu de comisiones");
                handle_comission_option(selected_option, client_options);
                break;
            case 7:
                selected_option = print_menu(bones_options, sizeof(bones_options) / sizeof(bones_options[0]), "Menu de Bonos");
                handle_bones_option(selected_option, client_options);
                break;
            case 8:
                selected_option = print_menu(invoice_options, sizeof(invoice_options) / sizeof(invoice_options[0]), "Menu de facturas");
                handle_invoice_option(selected_option, client_options);
                break;
            case 9:
                exit = true;
                break;
        } (selected_option);
    }
    return 0;
}

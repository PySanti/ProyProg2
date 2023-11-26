#include <iostream>
#include "./articles_handling.h"
using namespace std;

bool back_option_selected(string stringed_selected_option){
    return (stringed_selected_option == "volver") ? true : false;
}

bool string_contains(string str, string target){
    return str.find(target) != string::npos;

}

void handle_articles(){
    string article_options[] = {
        "Ver artículos",
        "Agregar articulo",
        "Modificar articulo",
        "Eliminar articulo",
        "Buscar articulo",
        "Borrar la lista de artículos",
        "Volver"
    };
    int selected_option = print_menu(article_options, sizeof(article_options) / sizeof(article_options[0]), "Menu de Artículos");
    ArticleNode *found_article = NULL;
    string stringed_selected_option = to_lower(article_options[selected_option-1]);
    string found_article_code;

    if (back_option_selected(stringed_selected_option))
        return;
    if (string_contains(stringed_selected_option, "agregar")){
        string articles_creation_handling_response = articles_creation_handling();
        if (articles_creation_handling_response != ""){
            success_screen("El producto " + articles_creation_handling_response + " ha sido agregado exitosamente");
        }
    } else if (string_contains(stringed_selected_option, "buscar") || string_contains(stringed_selected_option, "eliminar") || string_contains(stringed_selected_option, "modificar")){
        if (MAIN_ARTICLE_LIST->head == NULL){
            success_screen("No hay artículos en la lista aun !");
        }  else {
            found_article = search_article();
            if (found_article){
                found_article_code = found_article->article.code;
                if (string_contains(stringed_selected_option, "buscar")){
                    system("clear");
                    cout << Y_SEPARATION << X_SEPARATION << "Articulo conseguido !!!" << endl;
                    show_article(found_article->article);
                    pause();
                } else if (string_contains(stringed_selected_option, "modificar")){
                    found_article->article = set_article(found_article->article);
                    success_screen("Articulo " + found_article->article.code + " modificado correctamente !");
                }   else if (string_contains(stringed_selected_option, "eliminar")){
                    if (delete_article_node(MAIN_ARTICLE_LIST, found_article)){
                        success_screen("El articulo " + found_article_code + " ha sido eliminado exitosamente !");
                    } else {
                        success_screen("El articulo " + found_article_code + " no ha podido ser eliminado !");
                    }
                }
            } else {
                success_screen("El articulo no ha sido conseguido !!");
            }
        }
    } else if (string_contains(stringed_selected_option, "ver")){
        if (MAIN_ARTICLE_LIST->head == NULL){
            success_screen("No hay artículos en la lista aun !");
        } else {
            show_articles_list(MAIN_ARTICLE_LIST);
        }
    } else if (string_contains(stringed_selected_option, "borrar")){
        if (MAIN_ARTICLE_LIST->head == NULL){
            success_screen("Aun no hay artículos en la lista !");
        } else {
            delete_articles_list();
            success_screen("Lista de artículos eliminada con éxito !");
        }
    }
    return;
}

void handle_stock(){
    string stock_options[] = {
    "Ver inventario",
    "Agregar inventario",
    "Modificar inventario",
    "Eliminar inventario",
    "Buscar inventario",
    "Volver"
    };
    int selected_option = print_menu(stock_options, sizeof(stock_options) / sizeof(stock_options[0]), "Menu de Inventario");
    return;
}

void handle_clients(){
    string client_options[] = {
        "Ver clientes",
        "Agregar cliente",
        "Modificar cliente",
        "Eliminar cliente",
        "Buscar cliente",
        "Volver"
    };
    int selected_option = print_menu(client_options,sizeof(client_options) / sizeof(client_options[0]) , "Menu de Clientes");
    string stringed_selected_option = to_lower(client_options[selected_option-1]);
    if (back_option_selected(stringed_selected_option))
        return;
    if (stringed_selected_option.find("agregar") != string::npos){
        cout << "Agregar cliente" << endl;
    } else if (stringed_selected_option.find("buscar") != string::npos){
        cout << "Buscar cliente" << endl;
    } else if (stringed_selected_option.find("eliminar") != string::npos){
        cout << "Eliminar eliminar cliente" << endl;
    } else if (stringed_selected_option.find("modificar") != string::npos){
        cout << "Modificar cliente " << endl;
    }  else if (stringed_selected_option.find("ver") != string::npos){
        cout << "Modificar cliente " << endl;
    }
    return;
}

void handle_discounts(){
    string discount_options[] = {
    "-",
    "-",
    "-",
    "Volver"
    };
    int selected_option = print_menu(discount_options,sizeof(discount_options) / sizeof(discount_options[0]), "Menu de Descuentos");
    return;
}


void handle_sellers(){
    string seller_options[] = {
        "Ver vendedores",
        "Agregar vendedor",
        "Modificar vendedor",
        "Eliminar vendedor",
        "Buscar vendedor",
        "Volver"
    };
    int selected_option = print_menu(seller_options,sizeof(seller_options) / sizeof(seller_options[0]) , "Menu de Vendedores");
    string stringed_selected_option = to_lower(seller_options[selected_option-1]);
    if (back_option_selected(stringed_selected_option))
        return;
    if (stringed_selected_option.find("agregar") != string::npos){
        cout << "Agregar vendedor" << endl;
    } else if (stringed_selected_option.find("buscar") != string::npos){
        cout << "Buscar vendedor" << endl;
    } else if (stringed_selected_option.find("eliminar") != string::npos){
        cout << "Eliminar vendedor" << endl;
    } else if (stringed_selected_option.find("modificar") != string::npos){
        cout << "Modificar vendedor " << endl;
    } else if (stringed_selected_option.find("ver") != string::npos){
        cout << "Modificar vendedor " << endl;
    }
    return;
}




void handle_comissions(){
    string comission_options[] = {
        "-",
        "Volver",
    };
    int selected_option = print_menu(comission_options, sizeof(comission_options) / sizeof(comission_options[0]), "Menu de comisiones");
    return;
}

void handle_bones(){
    string bones_options[] = {
        "-",
        "Volver"
    };
    int selected_option = print_menu(bones_options, sizeof(bones_options) / sizeof(bones_options[0]), "Menu de Bonos");
    return;
}

void handle_invoices(){
    string invoice_options[] = {
        "-",
        "Volver"
    };
    int selected_option = print_menu(invoice_options, sizeof(invoice_options) / sizeof(invoice_options[0]), "Menu de facturas");
    return;
}


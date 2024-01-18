#include <iostream>
#include "./articles_handling.h"
#include "./clients_handling.h"
#include "./sellers_handling.h"
#include "./stock_handling.h"
#include "./invoice_handling.h"
using namespace std;

bool back_option_selected(string stringed_selected_option){
    return (stringed_selected_option == "volver") ? true : false;
}



void handle_articles(std::map<std::string, string> pattern_dict){
    ArticleNode *found_article = NULL;

    string found_article_code;
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

    string stringed_selected_option = to_lower(article_options[selected_option-1]);

    if (back_option_selected(stringed_selected_option))
        return;
    if (string_contains(stringed_selected_option, "agregar")){
        string articles_creation_handling_response = articles_creation_handling(pattern_dict);
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
                    found_article->article = set_article(found_article->article, pattern_dict);
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
            if (handle_delete_articles_list()){
                success_screen("Lista de artículos eliminada con éxito !");
            }
        }
    }
    return;
}

void handle_stock(){
    string stock_options[] = {
        "Modificar inventario",
        "Volver"
    };
    string stock_file_reading_response;
    int selected_option = print_menu(stock_options, sizeof(stock_options) / sizeof(stock_options[0]), "Menu de Inventario");
    string stringed_selected_option = to_lower(stock_options[selected_option-1]);
    if (back_option_selected(stringed_selected_option))
        return;
    if (string_contains(stringed_selected_option    , "modificar")){
        stock_file_reading_response = read_stock_from_file("inventario.txt", MAIN_ARTICLE_LIST, CODE_NUMBER_REGEX);
        if (stock_file_reading_response == ""){
            success_screen("Los cambios escritos en el archivo inventario.txt han surtido efecto en el inventario de la tienda!!");
        } else {
            success_screen(stock_file_reading_response);
        }
    }
    return;
}

void handle_clients(std::map<std::string, string> pattern_dict){
    string client_options[] = {
        "Ver clientes",
        "Agregar cliente",
        "Modificar cliente",
        "Eliminar cliente",
        "Buscar cliente",
        "Borrar lista de clientes",
        "Volver"
    };
    ClientNode *found_client;
    string found_client_name;
    int selected_option = print_menu(client_options,sizeof(client_options) / sizeof(client_options[0]) , "Menu de Clientes");
    string stringed_selected_option = to_lower(client_options[selected_option-1]);
    if (back_option_selected(stringed_selected_option))
        return;
    if (string_contains(stringed_selected_option, "agregar")){
        string client_creation_handling_response = clients_creation_handling(pattern_dict);
        if (client_creation_handling_response != ""){
            success_screen("El cliente " + client_creation_handling_response + " ha sido agregado exitosamente");
        }
    } else if (string_contains(stringed_selected_option, "buscar") || string_contains(stringed_selected_option, "eliminar") || string_contains(stringed_selected_option, "modificar")){
        if (MAIN_CLIENTS_LIST->head == NULL){
            success_screen("No hay clientes en la lista aun !");
        }  else {
            found_client = search_client();
            if (found_client){
                found_client_name = found_client->client.name;
                if (string_contains(stringed_selected_option, "buscar")){
                    system("clear");
                    cout << Y_SEPARATION << X_SEPARATION << "Cliente conseguido !!!" << endl;
                    show_client(found_client->client);
                    pause();
                } else if (string_contains(stringed_selected_option, "modificar")){
                    found_client->client = set_client(found_client->client, pattern_dict);
                    success_screen("Cliente " + found_client->client.name + " modificado correctamente !");
                }   else if (string_contains(stringed_selected_option, "eliminar")){
                    if (delete_client_node(MAIN_CLIENTS_LIST, found_client)){
                        success_screen("El cliente " + found_client_name + " ha sido eliminado exitosamente !");
                    } else {
                        success_screen("El articulo " + found_client_name + " no ha podido ser eliminado !");
                    }
                }
            } else {
                success_screen("El cliente no ha sido conseguido !!");
            }
        }
    }  else if (stringed_selected_option.find("ver") != string::npos){
        if (MAIN_CLIENTS_LIST->head == NULL){
            success_screen("No hay clientes en la lista aun !");
        } else {
            show_clients_list(MAIN_CLIENTS_LIST);
        }
    } else if (string_contains(stringed_selected_option, "borrar")){
        if (MAIN_CLIENTS_LIST->head == NULL){
            success_screen("Aun no hay clientes en la lista !");
        } else {
            if (handle_delete_clients_list()){
                success_screen("Lista de clientes eliminada con éxito !");
            }
        }
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


void handle_sellers(std::map<std::string, string> pattern_dict){
    SellerNode *found_seller = NULL;

    string found_seller_name;
    string seller_options[] = {
        "Ver vendedores",
        "Agregar vendedor",
        "Modificar vendedor",
        "Eliminar vendedor",
        "Buscar vendedor",
        "Borrar la lista de vendedores",
        "Volver"
    };
    int selected_option = print_menu(seller_options, sizeof(seller_options) / sizeof(seller_options[0]), "Menu de Vendedores");

    string stringed_selected_option = to_lower(seller_options[selected_option-1]);

    if (back_option_selected(stringed_selected_option))
        return;
    if (string_contains(stringed_selected_option, "agregar")){
        string seller_creation_handling_response = sellers_creation_handling(pattern_dict);
        if (seller_creation_handling_response != ""){
            success_screen("El vendedor " + seller_creation_handling_response + " ha sido agregado exitosamente");
        }
    } else if (string_contains(stringed_selected_option, "buscar") || string_contains(stringed_selected_option, "eliminar") || string_contains(stringed_selected_option, "modificar")){
        if (MAIN_SELLERS_LIST->head == NULL){
            success_screen("No hay vendedores en la lista aun !");
        }  else {
            found_seller = search_seller();
            if (found_seller){
                found_seller_name = found_seller->seller.name;
                if (string_contains(stringed_selected_option, "buscar")){
                    system("clear");
                    cout << Y_SEPARATION << X_SEPARATION << "Vendedor conseguido !!!" << endl;
                    show_seller(found_seller->seller);
                    pause();
                } else if (string_contains(stringed_selected_option, "modificar")){
                    found_seller->seller = set_seller(found_seller->seller, pattern_dict);
                    success_screen("Vendedor " + found_seller->seller.name + " modificado correctamente !");
                }   else if (string_contains(stringed_selected_option, "eliminar")){
                    if (delete_seller_node(MAIN_SELLERS_LIST, found_seller)){
                        success_screen("El vendedor " + found_seller_name + " ha sido eliminado exitosamente !");
                    } else {
                        success_screen("El vendedor " + found_seller_name + " no ha podido ser eliminado !");
                    }
                }
            } else {
                success_screen("El vendedor no ha sido conseguido !!");
            }
        }
    } else if (string_contains(stringed_selected_option, "ver")){
        if (MAIN_SELLERS_LIST->head == NULL){
            success_screen("No hay vendedores en la lista aun !");
        } else {
            show_sellers_list(MAIN_SELLERS_LIST);
        }
    } else if (string_contains(stringed_selected_option, "borrar")){
        if (MAIN_SELLERS_LIST->head == NULL){
            success_screen("Aun no hay vendedores en la lista !");
        } else {
            if (handle_delete_sellers_list()){
                success_screen("Lista de vendedores eliminada con éxito !");
            }
        }
    }
    return;
}






void handle_invoices(){
    string invoice_options[] = {
        "Generar factura",
        "Ver facturas",
        "Volver"
    };
    int selected_option = print_menu(invoice_options, sizeof(invoice_options) / sizeof(invoice_options[0]), "Menu de facturas");
    string stringed_selected_option = to_lower(invoice_options[selected_option-1]);
    string invoice_generation_handling_response;

    if (back_option_selected(stringed_selected_option))
        return;
    if (string_contains(stringed_selected_option, "generar")){
        invoice_generation_handling_response = invoice_generation_handling();
        success_screen(invoice_generation_handling_response);
    }  else if (string_contains(stringed_selected_option, "ver")){
        if (MAIN_INVOICE_LIST->invoice_count == 0){
            success_screen("Aun no hay facturas en la lista");
        } else {
            show_invoice_list();
        }
    }

    return;
}


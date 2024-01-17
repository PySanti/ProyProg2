#include <iostream>
#include <cstdlib>  
#include <ctime> 


using namespace std;

string generate_invoice_code(){
    srand(time(0));
    int num;
    string final_code;
    for (int i = 0; i < 10; i++){
        num = (rand() % (2)) + 1;
        num = num == 1 ? (rand() % (26)) + 65 : (rand() % (10)) + 48;
        final_code  = final_code + (char) num;
    }
    cout << final_code << endl;
    return final_code;
}

string get_product_ammount(string product_code){
    string product_ammount;
    while (1){
        system("clear");
        cout << Y_SEPARATION << X_SEPARATION << "Error, cantidad de unidades invalida !" << endl;
        cout  << X_SEPARATION << "Ingresa la cantidad de unidades del producto " << product_code << " que se venderán : ";
        getline(cin, product_ammount);
        if (string_is_num(product_ammount)){
            return product_ammount;
        }
    }
}

// retornara true en caso de que se haya agregado un nuevo renglon, false en caso contrario
bool add_renglon_to_list(Renglon renglon_list[], Renglon new_renglon, int renglones_number){
    for (int i = 0; i < renglones_number ; i++){
        if (renglon_list[i].article_code == new_renglon.article_code){
            renglon_list[i].article_ammount += new_renglon.article_ammount;
            return false;
        }
    }
    renglon_list[renglones_number] = new_renglon;
    return true;
}

string modify_title_with_renglones_info(Renglon renglon_list[], int renglones_number, string title){
    for (int i = 0; i < renglones_number ; i++){
        title = title + "\n" +X_SEPARATION+renglon_list[i].article_code +" -- " + to_string(renglon_list[i].article_ammount);
    }
    return title;
}

float get_invoice_subtotal(Renglon renglones_list[], int renglones_count){
    Article current_article;
    float subtotal = 0;
    for (int i = 0; i < renglones_count; i++){
        current_article = search_element_in_article_list(MAIN_ARTICLE_LIST, "codigo", renglones_list[i].article_code)->article;
        subtotal += renglones_list[i].article_ammount * current_article.price;
    }
    return subtotal;
}

string invoice_generation_handling(){
    string sellers_names[MAIN_SELLERS_LIST->sellers_count];
    string clients_names[MAIN_CLIENTS_LIST->clients_count];
    string articles_codes[MAIN_ARTICLE_LIST->articles_count+1];
    Invoice new_invoice;
    string selected_client;
    string selected_seller;
    string selected_article_code;
    string product_ammount;
    Renglon renglones_list[MAIN_ARTICLE_LIST->articles_count];
    Renglon current_renglon;
    int current_renglon_number = 0;
    string error_msg = "";
    if (MAIN_SELLERS_LIST->sellers_count == 0){
        return "No hay vendedores, agrega algunos a la lista para poder crear una factura";
    }  else if (MAIN_CLIENTS_LIST->clients_count == 0){
        return "No hay clientes, agrega algunos a la lista para poder crear una factura";
    }  else if (MAIN_ARTICLE_LIST->articles_count == 0){
        return "No hay artículos, agrega algunos a la lista para poder crear una factura";
    } else {
        generate_sellers_names_array(sellers_names);
        generate_clients_names_array(clients_names);
        generate_articles_codes_array(articles_codes);
        articles_codes[MAIN_ARTICLE_LIST->articles_count] = "Continuar";
        selected_seller = sellers_names[print_menu(sellers_names, MAIN_SELLERS_LIST->sellers_count, "Selecciona al vendedor")-1];
        selected_client = clients_names[print_menu(clients_names, MAIN_CLIENTS_LIST->clients_count, "Selecciona al cliente")-1];
        while (1){
            selected_article_code = articles_codes[print_menu(articles_codes, MAIN_ARTICLE_LIST->articles_count+1, modify_title_with_renglones_info(renglones_list, current_renglon_number, "Menu de renglones, selecciona el código del articulo a comprar\n"))-1];
            if (string_contains(selected_article_code, "Continuar")){
                if (current_renglon_number == 0){
                    return "No se han agregado renglones a la factura, abortando operacion !";
                } else {
                    break;
                }
            } else {
                cout << "\n" << X_SEPARATION << "Ingresa la cantidad de unidades del producto " << selected_article_code << " que se venderán : ";
                getline(cin, product_ammount);
                product_ammount = string_is_num(product_ammount) ? product_ammount : get_product_ammount(selected_article_code);
                current_renglon.article_ammount = stoi(product_ammount);
                current_renglon.article_code = selected_article_code;
                current_renglon_number = add_renglon_to_list(renglones_list, current_renglon, current_renglon_number)? current_renglon_number+1 : current_renglon_number;
            }
        }
        new_invoice.id = generate_invoice_code();
        new_invoice.seller_data = search_element_in_seller_list(MAIN_SELLERS_LIST, "nombre", selected_seller)->seller;
        new_invoice.client_data = search_element_in_client_list(MAIN_CLIENTS_LIST, "nombre", selected_client)->client;
        new_invoice.renglones = &renglones_list[0];
        new_invoice.sub_total = get_invoice_subtotal(renglones_list, current_renglon_number);
        new_invoice.discount = 0;
        new_invoice.total = new_invoice.sub_total - (new_invoice.sub_total * new_invoice.discount / 100);
        new_invoice.products_count = current_renglon_number;
    }
}
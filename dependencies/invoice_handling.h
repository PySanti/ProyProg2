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

string invoice_generation_handling(){
    string sellers_names[MAIN_SELLERS_LIST->sellers_count];
    string clients_names[MAIN_CLIENTS_LIST->clients_count];
    Invoice new_invoice;
    string selected_client;
    string selected_seller;
    if (MAIN_SELLERS_LIST->sellers_count == 0){
        return "No hay vendedores, agrega algunos a la lista para poder hacer una factura";
    }  else if (MAIN_CLIENTS_LIST->clients_count == 0){
        return "No hay clientes, agrega algunos a la lista para poder hacer una factura";
    } else {
        generate_sellers_names_array(sellers_names);
        generate_clients_names_array(clients_names);
        selected_seller = sellers_names[print_menu(sellers_names, MAIN_SELLERS_LIST->sellers_count, "Selecciona al vendedor")-1];
        selected_client = clients_names[print_menu(clients_names, MAIN_CLIENTS_LIST->clients_count, "Selecciona al cliente")-1];
        new_invoice.id = generate_invoice_code();
        new_invoice.seller_data = search_element_in_seller_list(MAIN_SELLERS_LIST, "nombre", selected_seller)->seller;
        new_invoice.client_data = search_element_in_client_list(MAIN_CLIENTS_LIST, "nombre", selected_client)->client;
    }
}
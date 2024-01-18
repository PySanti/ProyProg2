#include <iostream>
#include <cstdlib>  
#include <ctime> 
#include <stdlib.h>
#include <fstream>

using namespace std;

typedef struct InvoiceNode {
    Invoice invoice;
    InvoiceNode *next = NULL;
} InvoiceNode;

typedef struct InvoiceList {
    InvoiceNode *head = NULL;
    int invoice_count = 0;
} InvoiceList;

InvoiceList *MAIN_INVOICE_LIST = new InvoiceList;

void add_invoice_to_list(Invoice new_invoice){
    InvoiceNode *current_node = MAIN_INVOICE_LIST->head;
    InvoiceNode *last_node = NULL;
    InvoiceNode *new_invoice_node = new InvoiceNode;
    new_invoice_node->invoice = new_invoice;

    if (MAIN_INVOICE_LIST->head == NULL){
        MAIN_INVOICE_LIST->head = new_invoice_node;
    } else {
        while (current_node != NULL){
            last_node = current_node;
            current_node = current_node->next;
        }
        last_node->next = new_invoice_node;
    }
    MAIN_INVOICE_LIST->invoice_count ++;
}

float discount_calculator(string client_name){
    InvoiceNode *current_node = MAIN_INVOICE_LIST->head;
    int buys_count = 0;
    if (current_node == NULL){
        return 0;
    } else {
        while (current_node != NULL){
            if (current_node->invoice.client_data.name == client_name){
                buys_count++;
            }
            current_node = current_node->next;
        }
    }
    return buys_count*5.2;
}
float commission_calculator(string seller_name){
    InvoiceNode *current_node = MAIN_INVOICE_LIST->head;
    int sells_count = 0;
    if (current_node == NULL){
        return 0;
    } else {
        while (current_node != NULL){
            if (current_node->invoice.seller_data.name == seller_name){
                sells_count++;
            }
            current_node = current_node->next;
        }
    }
    return sells_count*3.7;
}


void show_invoice_list(){
    cls();;
    InvoiceNode *current_node = MAIN_INVOICE_LIST->head;
    Invoice current_invoice;
    while (current_node != NULL){
        current_invoice = current_node->invoice;
        cout << X_SEPARATION << "\t\t[" <<          current_invoice.id << "]\n" << endl;
        cout << X_SEPARATION << "Vendedor                       : " << current_invoice.seller_data.name << endl;
        cout << X_SEPARATION << "Cliente                        : " << current_invoice.client_data.name << endl;
        cout << X_SEPARATION << "Descuento para cliente         : " << current_invoice.discount << "%, " <<current_invoice.sub_total*current_invoice.discount/100 << "$"<< endl;
        cout << X_SEPARATION << "Comision para vendedor         : " << current_invoice.comission << "%, " <<current_invoice.sub_total*current_invoice.comission/100 << "$"<< endl;
        cout << X_SEPARATION << "Subtotal                       : " << current_invoice.sub_total << "$" << endl;
        cout << X_SEPARATION << "Total                          : " << current_invoice.total << "$" << endl << endl;
        cout << X_SEPARATION << "\tRENGLONES      "<< endl << endl;
        for (int i = 0; i < current_invoice.products_count; i++){
            cout << X_SEPARATION << "\t|  " << current_invoice.renglones[i].article_code << " -- " << current_invoice.renglones[i].article_ammount<< endl;
        }
        current_node = current_node->next;
        cout << "\n\n";
    }
    pause();
}


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
        cls();;
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
    title = title + "\n\n\n" + X_SEPARATION + "\t\t" + "Renglones creados" + "\n";
    for (int i = 0; i < renglones_number ; i++){
        title = title + "\n\t\t" +X_SEPARATION+" | "+renglon_list[i].article_code +" -- " + to_string(renglon_list[i].article_ammount);
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
    Renglon *renglones_list = (Renglon *) calloc(MAIN_ARTICLE_LIST->articles_count, sizeof(Renglon));
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
        new_invoice.discount = discount_calculator(new_invoice.client_data.name);
        new_invoice.comission = commission_calculator(new_invoice.seller_data.name);
        new_invoice.total = new_invoice.sub_total - (new_invoice.sub_total * new_invoice.discount / 100);
        new_invoice.products_count = current_renglon_number;
        add_invoice_to_list(new_invoice);
        return "Factura "+ new_invoice.id + " generada con éxito !";
    }
}

void write_invoice_list_in_file(string filename){
    InvoiceNode *current_node = MAIN_INVOICE_LIST->head;
    ofstream file;
    file.open(filename);
    if (MAIN_INVOICE_LIST->head == NULL)
        file << "";
    while (current_node != NULL){
        file << current_node->invoice.id<< endl;
        file << current_node->invoice.seller_data.name << endl;
        file << current_node->invoice.client_data.name << endl;
        file << current_node->invoice.products_count  << endl;
        file << current_node->invoice.sub_total << endl;
        file << current_node->invoice.discount << endl;
        file << current_node->invoice.comission << endl;
        file << current_node->invoice.total << endl;
        for (int i = 0; i < current_node->invoice.products_count; i++){
            file << current_node->invoice.renglones[i].article_code << endl; 
            file << current_node->invoice.renglones[i].article_ammount << endl;
        }
        if (current_node->next)
            file << "~" << endl;    
        current_node = current_node->next;
    }
    file.close();
}


string handle_read_invoices_from_file(string filename){
    std::ifstream file;
    string current_line;
    int current_atribute = 0;
    Renglon *current_renglones_list;   
    Invoice current_invoice;
    file.open(filename);
    if (!file.is_open()){
        return "Error, el archivo "+filename+" no ha podido ser abierto !";
    } else {
        while (file){
            getline(file, current_line);
            cout << current_line << endl;
            if (current_line.length() == 0 && current_atribute == 0){
                return "";
            }
            if (current_atribute == 0){
                current_invoice.id = current_line;
            } else if (current_atribute == 1){
                current_invoice.seller_data = search_element_in_seller_list(MAIN_SELLERS_LIST, "nombre", current_line)->seller;
            } else if (current_atribute == 2){
                current_invoice.client_data = search_element_in_client_list(MAIN_CLIENTS_LIST, "nombre", current_line)->client;
            } else if (current_atribute == 3){
                current_invoice.products_count = stoi(current_line);
                current_renglones_list = (Renglon *) calloc(current_invoice.products_count, sizeof(Renglon));
            }  else if (current_atribute == 4){
                current_invoice.sub_total = stoi(current_line);
            } else if (current_atribute == 5){
                current_invoice.discount = stoi(current_line);
            }  else if (current_atribute == 6){
                current_invoice.comission = stoi(current_line);
            }else if (current_atribute == 7){
                current_invoice.total = stoi(current_line);
            }else{
                for (int j = 0; j < current_invoice.products_count; j++){
                    for (int i =0; i < 2; i++) {
                        if (i == 0){
                            current_renglones_list[j].article_code = current_line;
                        } else {
                            current_renglones_list[j].article_ammount = stoi(current_line);
                        }
                        getline(file, current_line);
                    }
                }
                current_invoice.renglones = current_renglones_list;
                add_invoice_to_list(current_invoice);
                current_atribute = -1;
            }
            current_atribute++;
        }
        file.close();

        return "";
    }

}

void delete_invoices_list(){
    InvoiceNode *current_node = MAIN_INVOICE_LIST->head;
    InvoiceNode *aux_node;
    while (current_node != NULL){
        aux_node = current_node->next;
        current_node->next = NULL;
        delete current_node;
        MAIN_INVOICE_LIST->head = aux_node;
        current_node = MAIN_INVOICE_LIST->head;
    }
}
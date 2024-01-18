#include <iostream>
#include <regex>

using namespace std;

typedef struct SellerNode {
    Seller seller;
    SellerNode *next;
} SellerNode;

typedef struct SellersList {
    int sellers_count = 0;
    SellerNode *head = NULL;
} SellersList;



SellersList *MAIN_SELLERS_LIST = new SellersList;

SellerNode *create_seller_node(Seller seller){
    SellerNode *new_seller_node = new SellerNode;
    new_seller_node->next = NULL;
    new_seller_node->seller = seller;
    return new_seller_node;
}

int last_seller_id(SellersList *main_seller_list){
    return (main_seller_list->head != NULL) ? main_seller_list->head->seller.primary_key : 0;
}

void append_seller_to_sellers_list(SellersList *seller_list, Seller seller){
    SellerNode *new_seller_node = create_seller_node(seller);
    SellerNode *aux_seller_node = NULL;
    if (seller_list->head == NULL){
        seller_list->head = new_seller_node;
    } else {
        aux_seller_node = seller_list->head;
        seller_list->head = new_seller_node;
        seller_list->head->next = aux_seller_node;
    }
    seller_list->sellers_count++;
}


void show_seller(Seller seller){
    cout << X_SEPARATION << "\t\t[" << seller.primary_key << "]\n" << endl;
    cout << X_SEPARATION << "Nombre             : " << seller.name << endl;
    cout << X_SEPARATION << "Fecha de ingreso   : " << seller.entry_date << endl;
    cout << X_SEPARATION << "Comision           : " << seller.comission << "%"  << endl;
    cout << X_SEPARATION << "Cedula             : " << seller.cedula  << endl;
}

void show_sellers_list(SellersList *seller_list){
    SellerNode *current_node = seller_list->head;
    cls();;
    while (current_node != NULL){
        show_seller(current_node->seller);
        current_node = current_node->next;
    }
    pause();
}



Seller create_seller(string name, string entry_date, float comission, int cedula ){
    Seller new_seller;
    new_seller.primary_key = last_seller_id(MAIN_SELLERS_LIST) + 1;
    new_seller.name = name;
    new_seller.entry_date = entry_date;
    new_seller.comission = comission;
    new_seller.cedula = cedula;
    return new_seller;
}
SellerNode *search_seller_node_by_id(SellersList *main_seller_list, int id){
    SellerNode *current_node = main_seller_list->head;
    if (current_node == NULL)
        return NULL;
    else {
        while (current_node != NULL){
            if (current_node->seller.primary_key == id){
                return current_node;
            }
            current_node = current_node->next;
        }
        return NULL;
    }
}

SellerNode *search_element_in_seller_list(SellersList *main_seller_list, string field, string value){
    SellerNode *current_node = main_seller_list->head;
    if (field != "id"){
        while (current_node != NULL){
            if ((field == "nombre" && to_lower(current_node->seller.name) == to_lower(value)) || (field == "cedula" && string_is_num(value) && current_node->seller.cedula == stoi(value)))
                return current_node;
            current_node = current_node->next;
        }
        return NULL;
    } else {
        return string_is_num(value) ? search_seller_node_by_id(main_seller_list, stoi(value)) : NULL;
    }
}

string sellers_creation_handling(std::map<std::string, string> pattern_dict){
    Seller new_seller;
    pattern_dict = validate_form(pattern_dict);
    if (search_element_in_seller_list(MAIN_SELLERS_LIST, "nombre", to_lower(pattern_dict["nombre"])) || search_element_in_seller_list(MAIN_SELLERS_LIST, "cedula", to_lower(pattern_dict["cedula"]))){
        success_screen("Error, ese vendedor ya ha sido agregado a la base de datos (" + pattern_dict["cedula"] +")");
        return "";
    } else {
        new_seller = create_seller(uppercase(pattern_dict["nombre"]), pattern_dict["fecha de ingreso"], stof(pattern_dict["comision"]), stoi(pattern_dict["cedula"]));
        append_seller_to_sellers_list(MAIN_SELLERS_LIST, new_seller);
        return pattern_dict["nombre"];
    }
}




SellerNode *search_seller(){
    string selected_option;
    string value;
    string options[] = {
        "Nombre",
        "Id",
        "Cedula"
    };
    selected_option = to_lower(options[print_menu(options, sizeof(options) / sizeof(options[0]), "MENU DE BÚSQUEDA : Selecciona el parametro de búsqueda")-1]);
    cout << X_SEPARATION << "-> Ingresa el valor del " + selected_option + " para la búsqueda : ";
    getline(cin, value);
    return search_element_in_seller_list(MAIN_SELLERS_LIST, selected_option, value);
}

Seller set_seller(Seller seller, std::map<std::string, string> pattern_dict){
    string current_x_sep = "\t\t\t\t\t\t";
    string value = "";
    string setting_options[] = {
        "Nombre",
        "Fecha De Ingreso",
        "Comision",
    };
    string error_log = "";
    string selected_option = to_lower(setting_options[print_menu(setting_options, sizeof(setting_options) / sizeof(setting_options[0]), "MENU DE CONFIGURACIÓN : Selecciona el parametro de configuración ")-1]);
    regex pattern;
    pattern = pattern_dict[selected_option]; 
    while (true){
        cls();;
        cout << Y_SEPARATION << current_x_sep;
        if (error_log != "")
            cout << error_log << endl << current_x_sep;
        cout << "Ingresa el nuevo valor para " + selected_option + " : ";
        getline(cin,value);
        if ((pattern_dict[selected_option] == "_") || (regex_search(value, pattern)))
            break;
        else
            error_log = "Has ingresado un valor invalido para " + selected_option;
    }
    if (selected_option == "nombre")
        seller.name = uppercase(value);
    if (selected_option == "comision")
        seller.comission = stof(value);
    if (selected_option == "fecha de ingreso")
        seller.entry_date = value;
    return seller;
}

bool delete_seller_node(SellersList *main_seller_list, SellerNode *target_node){
    SellerNode *current_node = main_seller_list->head, *last_node = NULL;
    SellerNode *aux_node = NULL;
    if (main_seller_list->head == NULL){
        return false;
    } else {
        while (current_node != NULL){
            if (current_node->seller.primary_key == target_node->seller.primary_key){
                if (last_node){
                    last_node->next = current_node->next;
                    current_node->next = NULL;
                } else {
                    aux_node = current_node->next;
                    current_node->next = NULL;
                    main_seller_list->head = aux_node;
                }
                delete current_node;
                main_seller_list->sellers_count--;
                return true;
            }
            last_node = current_node;
            current_node = current_node->next;
        }
        return false;
    }
}
void delete_sellers_list(){
    SellerNode *current_node = MAIN_SELLERS_LIST->head;
    SellerNode *aux_node;
    while (current_node != NULL){
        aux_node = current_node->next;
        current_node->next = NULL;
        delete current_node;
        MAIN_SELLERS_LIST->head = aux_node;
        current_node = MAIN_SELLERS_LIST->head;
    }
}
bool handle_delete_sellers_list(){
    string option;
    string error_log = "";
    while (true){
        cls();;
        cout << "\n\n\n\n\n\n\n";
        if (error_log != "")
            cout << "\t\t\t" << error_log << endl;
        cout << "\t\t\tEstas segur@ de que deseas eliminar la lista de articulos en su totalidad ? (s/n) : ";
        getline(cin, option);
        option = to_lower(option);
        if (option != "s" && option != "n")
            error_log = "Ingresa una option valida (s/n) !";
        else
            break;
    }
    if (option == "n")
        return false;
    else{
        delete_sellers_list();
        return true;
    }
}

string read_sellers_from_file(string filename, map<std::string, string> pattern_dict, SellersList *main_sellers_list){
    std::ifstream file;
    string current_line;
    int current_atribute = 0;   
    Seller current_seller;
    regex current_regex;
    file.open(filename);
    if (!file.is_open()){
        return "Error, el archivo " + filename + " no ha podido ser abierto !";
    } else {
        while (file){
            getline(file, current_line);
            if (current_line.length() == 0 && current_atribute == 0){
                return "";
            }
            if (current_atribute == 0){
                current_regex = pattern_dict["cedula"];
                if (pattern_dict["cedula"] == "_" || regex_search(current_line, current_regex)){
                    current_seller.cedula = stoi(current_line);
                } else {
                    return "Error, el valor " + current_line + " no es valido para la cedula.";
                }
            } else if (current_atribute == 1){
                current_regex = pattern_dict["nombre"];
                if (pattern_dict["nombre"] == "_" || regex_search(current_line, current_regex)){
                    current_seller.name = uppercase(current_line);
                } else {
                    return "Error, el valor " + current_line + " no es valido para el nombre.";
                }
            } else if (current_atribute == 2){
                current_regex = pattern_dict["fecha de ingreso"];
                if (pattern_dict["fecha de ingreso"] == "_" || regex_search(current_line, current_regex)){
                    current_seller.entry_date = current_line;
                } else {
                    return "Error, el valor " + current_line + " no es valido para la fecha de ingreso.";
                }
            }   else if (current_atribute == 3){
                current_regex = pattern_dict["comision"];
                if (pattern_dict["comision"] == "_" || regex_search(current_line, current_regex)){
                    current_seller.comission = stof(current_line);
                } else {
                    return "Error, el valor " + current_line + " no es valido para la comision.";
                }
            }  else{ 
                append_seller_to_sellers_list(main_sellers_list, create_seller(current_seller.name, current_seller.entry_date, current_seller.comission, current_seller.cedula));
                current_atribute = -1;
            }
            current_atribute++;
        }
        return "";
    }
    file.close();
}
void handle_read_sellers_from_file(string filename, map<std::string, string> pattern_dict, SellersList *main_sellers_list){
    string sellers_reading_response = read_sellers_from_file(filename, pattern_dict,main_sellers_list); 
    if (sellers_reading_response != ""){
        success_screen(sellers_reading_response);
    }
}

void write_sellers_list_in_file(string filename, SellersList *main_sellers_list){
    SellerNode *current_node = main_sellers_list->head;
    std::ofstream file;
    file.open(filename);
    if (main_sellers_list->head == NULL)
        file << "";
    while (current_node != NULL){
        file << current_node->seller.cedula << endl;
        file << current_node->seller.name << endl;
        file << current_node->seller.entry_date << endl;
        file << current_node->seller.comission << endl;
        if (current_node->next)
            file << "~" << endl;
        current_node = current_node->next;
    }
    file.close();
}

void generate_sellers_names_array(string arr[]){
    SellerNode *current_node = MAIN_SELLERS_LIST->head;
    for (int i = 0; i < MAIN_SELLERS_LIST->sellers_count; i++){
        arr[i] = current_node->seller.name;
        current_node = current_node->next;
    }
}
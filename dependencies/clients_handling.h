#include <iostream>
#include <regex>

using namespace std;

typedef struct ClientNode {
    Client client;
    ClientNode *next;
} ClientNode;

typedef struct ClientsList {
    int clients_count = 0;
    ClientNode *head = NULL;
} ClientsList;

ClientsList *MAIN_CLIENTS_LIST = new ClientsList;

ClientNode *create_client_node(Client client){
    ClientNode *new_client_node = new ClientNode;
    new_client_node->next = NULL;
    new_client_node->client = client;
    return new_client_node;
}

int last_client_id(ClientsList *main_client_list){
    return (main_client_list->head != NULL) ? main_client_list->head->client.primary_key : 0;
}

void append_client_to_client_list(ClientsList *client_list, Client client){
    ClientNode *new_client_node = create_client_node(client);
    ClientNode *aux_client_node = NULL;
    if (client_list->head == NULL){
        client_list->head = new_client_node;
    } else {
        aux_client_node = client_list->head;
        client_list->head = new_client_node;
        client_list->head->next = aux_client_node;
    }
    client_list->clients_count++;
}


void show_client(Client client){
    cout << X_SEPARATION << "\t\t[" << client.primary_key << "]\n" << endl;
    cout << X_SEPARATION << "Nombre                 : " << client.name << endl;
    cout << X_SEPARATION << "Dirección              : " << client.direction << endl;
    cout << X_SEPARATION << "Numero telefónico      : " << client.phone_number  << endl;
}

void show_clients_list(ClientsList *client_list){
    ClientNode *current_node = client_list->head;
    system("clear");
    while (current_node != NULL){
        show_client(current_node->client);
        current_node = current_node->next;
    }
    pause();
}



Client create_client(string name, string direction, string phone_number ){
    Client new_client;
    new_client.primary_key = last_client_id(MAIN_CLIENTS_LIST) + 1;
    new_client.name = name;
    new_client.direction = direction;
    return new_client;
}
ClientNode *search_client_node_by_id(ClientsList *main_client_list, int id){
    ClientNode *current_node = main_client_list->head;
    if (current_node == NULL)
        return NULL;
    else {
        while (current_node != NULL){
            if (current_node->client.primary_key == id){
                return current_node;
            }
            current_node = current_node->next;
        }
        return NULL;
    }
}

ClientNode *search_element_in_client_list(ClientsList *main_client_list, string field, string value){
    ClientNode *current_node = main_client_list->head;
    if (field != "id"){
        while (current_node != NULL){
            if ((field == "nombre" && to_lower(current_node->client.name) == to_lower(value)))
                return current_node;
            current_node = current_node->next;
        }
        return NULL;
    } else {
        return string_is_num(value) ? search_client_node_by_id(main_client_list, stoi(value)) : NULL;
    }
}

string clients_creation_handling(std::map<std::string, string> pattern_dict){
    Client new_client;
    pattern_dict = validate_form(pattern_dict);
    if (search_element_in_client_list(MAIN_CLIENTS_LIST, "nombre", to_lower(pattern_dict["nombre"]))){
        success_screen("Error, ya existe un cliente con el nombre indicado (" + pattern_dict["nombre"] + ")");
        return "";
    } else {
        new_client = create_client(pattern_dict["nombre"], pattern_dict["direccion"], pattern_dict["phone-number"]);
        append_client_to_client_list(MAIN_CLIENTS_LIST, new_client);
        return pattern_dict["nombre"];
    }
}




ClientNode *search_client(){
    string selected_option;
    string value;
    string options[] = {
        "Nombre",
        "Id",
    };
    selected_option = to_lower(options[print_menu(options, sizeof(options) / sizeof(options[0]), "MENU DE BÚSQUEDA : Selecciona el parámetro de búsqueda")-1]);
    cout << X_SEPARATION << "-> Ingresa el valor del " + selected_option + " para la búsqueda : ";
    cin >> value;
    return search_element_in_client_list(MAIN_CLIENTS_LIST, selected_option, value);
}

Client set_client(Client client, std::map<std::string, string> pattern_dict){
    string current_x_sep = "\t\t\t\t\t\t";
    string value = "";
    string setting_options[] = {
        "Nombre",
        "Direccion",
        "Numero telefonico",
    };
    string error_log = "";
    string selected_option = to_lower(setting_options[print_menu(setting_options, sizeof(setting_options) / sizeof(setting_options[0]), "MENU DE CONFIGURACIÓN : Selecciona el parámetro de configuración ")-1]);
    regex pattern;
    pattern = pattern_dict[selected_option]; 
    while (true){
        system("clear");
        cout << Y_SEPARATION << current_x_sep;
        if (error_log != "")
            cout << error_log << endl << current_x_sep;
        cout << "Ingresa el nuevo valor para " + selected_option + " : ";
        cin >> value;
        if ((pattern_dict[selected_option] == "_") || (regex_search(value, pattern)))
            break;
        else
            error_log = "Has ingresado un valor invalido para " + selected_option;
    }
    if (selected_option == "nombre")
        client.name = value;
    if (selected_option == "direccion")
        client.direction = value;
    if (selected_option == "numero telefonico")
        client.phone_number = value;
    return client;
}


bool delete_client_node(ClientsList *main_client_list, ClientNode *target_node){
    ClientNode *current_node = main_client_list->head, *last_node = NULL;
    ClientNode *aux_node = NULL;
    if (main_client_list->head == NULL){
        return false;
    } else {
        while (current_node != NULL){
            if (current_node->client.primary_key == target_node->client.primary_key){
                if (last_node){
                    last_node->next = current_node->next;
                    current_node->next = NULL;
                } else {
                    aux_node = current_node->next;
                    current_node->next = NULL;
                    main_client_list->head = aux_node;
                }
                delete current_node;
                MAIN_CLIENTS_LIST->clients_count--;
                return true;
            }
            last_node = current_node;
            current_node = current_node->next;
        }
        return false;
    }
}
void delete_clients_list(){
    string option;
    string error_log = "";
    ClientNode *current_node = MAIN_CLIENTS_LIST->head;
    ClientNode *aux_node;
    while (true){
        system("clear");
        cout << "\n\n\n\n\n\n\n";
        if (error_log != "")
            cout << "\t\t\t" << error_log << endl;
        cout << "\t\t\tEstas segur@ de que deseas eliminar la lista de artículos en su totalidad ? (s/n) : ";
        cin >> option;
        option = to_lower(option);
        if (option != "s" && option != "n")
            error_log = "Ingresa una option valida (s/n) !";
        else
            break;
    }
    if (option == "n")
        return;
    else{
        while (current_node != NULL){
            aux_node = current_node->next;
            current_node->next = NULL;
            delete current_node;
            MAIN_CLIENTS_LIST->head = aux_node;
            current_node = MAIN_CLIENTS_LIST->head;
        }
        return ;
    }
}
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
    cls();;
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
    new_client.phone_number = phone_number;
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
        new_client = create_client(uppercase(pattern_dict["nombre"]), uppercase(pattern_dict["direccion"]), pattern_dict["numero telefonico"]);
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
    getline(cin, value);
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
        cls();
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
        client.name = uppercase(value);
    if (selected_option == "direccion")
        client.direction = uppercase(value);
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
    ClientNode *current_node = MAIN_CLIENTS_LIST->head;
    ClientNode *aux_node;
    while (current_node != NULL){
        aux_node = current_node->next;
        current_node->next = NULL;
        delete current_node;
        MAIN_CLIENTS_LIST->head = aux_node;
        current_node = MAIN_CLIENTS_LIST->head;
    }
}
bool handle_delete_clients_list(){
    string option;
    string error_log = "";
    while (true){
        cls();;
        cout << "\n\n\n\n\n\n\n";
        if (error_log != "")
            cout << "\t\t\t" << error_log << endl;
        cout << "\t\t\tEstas segur@ de que deseas eliminar la lista de artículos en su totalidad ? (s/n) : ";
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
        delete_clients_list();
        return true;
    }
}

string read_clients_from_file(string filename, map<std::string, string> pattern_dict, ClientsList *main_clients_list){
    std::ifstream file;
    string current_line;
    int current_atribute = 0;   
    Client current_client;
    regex current_regex;
    file.open(filename);
    if (!file.is_open()){
        return "Error, el archivo "+ filename+ " no ha podido ser abierto !";
    } else {
        while (file){
            getline(file, current_line);
            if (current_line.length() == 0 && current_atribute == 0){
                return "";
            }
            if (current_atribute == 0){
                current_regex = pattern_dict["direccion"];
                if (pattern_dict["direccion"] == "_" || regex_search(current_line, current_regex)){
                    current_client.direction = uppercase(current_line);
                } else {
                    return "Error, el valor " + current_line + " no es valido para la dirección.";
                }
            } else if (current_atribute == 1){
                current_regex = pattern_dict["nombre"];
                if (pattern_dict["nombre"] == "_" || regex_search(current_line, current_regex)){
                    current_client.name = uppercase(current_line);
                } else {
                    return "Error, el valor " + current_line + " no es valido para el nombre.";
                }
            } else if (current_atribute == 2){
                current_regex = pattern_dict["numero telefonico"];
                if (pattern_dict["numero telefonico"] == "_" || regex_search(current_line, current_regex)){
                    current_client.phone_number = current_line;
                } else {
                    return "Error, el valor " + current_line + " no es valido para el numero telefonico.";
                }
            } else{ 
                append_client_to_client_list(main_clients_list, create_client(current_client.name, current_client.direction, current_client.phone_number));
                current_atribute = -1;
            }
            current_atribute++;
        }
        return "";
    }
    file.close();
}
void handle_read_clients_from_file(string filename, map<std::string, string> pattern_dict, ClientsList *main_clients_list){
    string clients_reading_response = read_clients_from_file(filename, pattern_dict,main_clients_list); 
    if (clients_reading_response != ""){
        success_screen(clients_reading_response);
    }
}

void write_clients_list_in_file(string filename, ClientsList *main_clients_list){
    ClientNode *current_node = main_clients_list->head;
    std::ofstream file;
    file.open(filename);
    if (main_clients_list->head == NULL)
        file << "";
    while (current_node != NULL){
        file << current_node->client.direction << endl;
        file << current_node->client.name << endl;
        file << current_node->client.phone_number << endl;
        if (current_node->next)
            file << "~" << endl;
        current_node = current_node->next;
    }
    file.close();
}

void generate_clients_names_array(string arr[]){
    ClientNode *current_node = MAIN_CLIENTS_LIST->head;
    for (int i = 0; i < MAIN_CLIENTS_LIST->clients_count; i++){
        arr[i] = current_node->client.name;
        current_node = current_node->next;
    }
}
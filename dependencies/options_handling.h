#include <iostream>

using namespace std;

bool back_option_selected(string stringed_selected_option){
    return (stringed_selected_option == "volver") ? true : false;
}

void handle_article_option(int selected_option, string options_list[]){
    string stringed_selected_option = to_lower(options_list[selected_option-1]);
    if (back_option_selected(stringed_selected_option))
        return;
    if (stringed_selected_option.find("agregar") != string::npos){
        cout << "Agregar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("buscar") != string::npos){
        cout << "Buscar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("eliminar") != string::npos){
        cout << "Eliminar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("modificar") != string::npos){
        cout << "Modificar elemento a la lista de articulos" << endl;
    }
    return;
}

void handle_article_option(int selected_option, string options_list[]){
    string stringed_selected_option = to_lower(options_list[selected_option-1]);
    if (back_option_selected(stringed_selected_option))
        return;
    if (stringed_selected_option.find("agregar") != string::npos){
        cout << "Agregar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("buscar") != string::npos){
        cout << "Buscar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("eliminar") != string::npos){
        cout << "Eliminar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("modificar") != string::npos){
        cout << "Modificar elemento a la lista de articulos" << endl;
    }
    return;
}
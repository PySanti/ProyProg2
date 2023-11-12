#include <iostream>
#include "./articles_handling.h"
using namespace std;

bool back_option_selected(string stringed_selected_option){
    return (stringed_selected_option == "volver") ? true : false;
}

void handle_article_option(int selected_option, string options_list[]){
    string stringed_selected_option = to_lower(options_list[selected_option-1]);
    if (back_option_selected(stringed_selected_option))
        return;
    if (stringed_selected_option.find("agregar") != string::npos){
        articles_creation_handling();
    } else if (stringed_selected_option.find("buscar") != string::npos){
        cout << "Buscar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("eliminar") != string::npos){
        cout << "Eliminar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("modificar") != string::npos){
        cout << "Modificar elemento a la lista de articulos" << endl;
    } else if (stringed_selected_option.find("ver") != string::npos){
        cout << "Ver elemento a la lista de articulos" << endl;
    }
    return;
}

void handle_client_option(int selected_option, string options_list[]){
    string stringed_selected_option = to_lower(options_list[selected_option-1]);
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



void handle_seller_option(int selected_option, string options_list[]){
    string stringed_selected_option = to_lower(options_list[selected_option-1]);
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


void handle_stock_option(int selected_option, string options_list[]){
    return;
}






void handle_comission_option(int selected_option, string options_list[]){
    return;
}

void handle_bones_option(int selected_option, string options_list[]){
    return;
}

void handle_invoice_option(int selected_option, string options_list[]){
    return;
}

void handle_discount_option(int selected_option, string options_list[]){
    return;
}
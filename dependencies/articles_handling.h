#include <iostream>
#include "structs.h"
#include <regex>

using namespace std;

typedef struct ArticleNode {
    Article article;
    ArticleNode *next;
} ArticleNode;

typedef struct ArticlesList {
    int articles_count = 0;
    ArticleNode *head = NULL;
} ArticlesList;

ArticlesList *MAIN_ARTICLE_LIST = new ArticlesList;

ArticleNode *create_article_node(Article article){
    ArticleNode *new_article_node = new ArticleNode;
    new_article_node->next = NULL;
    new_article_node->article = article;
    return new_article_node;
}

int last_article_id(ArticlesList *main_article_list){
    return (main_article_list->head != NULL) ? main_article_list->head->article.primary_key : 0;
}

void append_article_to_article_list(ArticlesList *article_list, Article article){
    ArticleNode *new_article_node = create_article_node(article);
    ArticleNode *aux_article_node = NULL;
    if (article_list->head == NULL){
        article_list->head = new_article_node;
    } else {
        aux_article_node = article_list->head;
        article_list->head = new_article_node;
        article_list->head->next = aux_article_node;
    }
    article_list->articles_count++;
}


void show_article(Article article){
    cout << X_SEPARATION << "\t\t[" << article.primary_key << "]\n" << endl;
    cout << X_SEPARATION << "Codigo     : " << article.code << endl;
    cout << X_SEPARATION << "Nombre     : " << article.name << endl;
    cout << X_SEPARATION << "Cantidad   : " << article.count << endl;
    cout << X_SEPARATION << "Precio     : " << article.price << "$" << endl << endl;
}

void show_articles_list(ArticlesList *article_list){
    ArticleNode *current_node = article_list->head;
    system("clear");
    while (current_node != NULL){
        show_article(current_node->article);
        current_node = current_node->next;
    }
    pause();
}



Article create_article(string code, int count, string name, float price ){
    Article new_article;
    new_article.primary_key = last_article_id(MAIN_ARTICLE_LIST) + 1;
    new_article.code = code; 
    new_article.count = count;
    new_article.name = name;
    new_article.price = price;
    return new_article;
}
ArticleNode *search_article_node_by_id(ArticlesList *main_article_list, int id){
    ArticleNode *current_node = main_article_list->head;
    if (current_node == NULL)
        return NULL;
    else {
        while (current_node != NULL){
            if (current_node->article.primary_key == id){
                return current_node;
            }
            current_node = current_node->next;
        }
        return NULL;
    }
}

ArticleNode *search_element_in_article_list(ArticlesList *main_article_list, string field, string value){
    ArticleNode *current_node = main_article_list->head;
    if (field != "id"){
        while (current_node != NULL){
            if ((field == "codigo" && to_lower(current_node->article.code) == to_lower(value)) || (field == "nombre" && to_lower(current_node->article.name) == to_lower(value)))
                return current_node;
            current_node = current_node->next;
        }
        return NULL;
    } else {
        return string_is_num(value) ? search_article_node_by_id(main_article_list, stoi(value)) : NULL;
    }
}

string articles_creation_handling(){
    Article new_article;
    std::map<std::string, string> pattern_dict = {
        {"nombre",      "_"},
        {"codigo",      CODE_NUMBER_REGEX},
        {"cantidad" ,   INT_NUMBER_REGEX},
        {"precio" ,     FLOAT_NUMBER_REGEX}
    };
    pattern_dict = validate_form(pattern_dict);
    if (search_element_in_article_list(MAIN_ARTICLE_LIST, "codigo", to_lower(pattern_dict["codigo"]))){
        success_screen("Error, ya existe un articulo con el codigo indicado (" + pattern_dict["codigo"] + ")");
        return "";
    } else {
        new_article = create_article(uppercase(pattern_dict["codigo"]), stoi(pattern_dict["cantidad"]), uppercase(pattern_dict["nombre"]), stof(pattern_dict["precio"]));
        append_article_to_article_list(MAIN_ARTICLE_LIST, new_article);
        return uppercase(pattern_dict["codigo"]);
    }
}




ArticleNode *search_article(){
    string selected_option;
    string value;
    string options[] = {
        "Nombre",
        "Id",
        "Codigo",
    };
    selected_option = to_lower(options[print_menu(options, sizeof(options) / sizeof(options[0]), "MENU DE BÚSQUEDA : Selecciona el parámetro de búsqueda")-1]);
    cout << X_SEPARATION << "-> Ingresa el valor del " + selected_option + " para la búsqueda : ";
    cin >> value;
    return search_element_in_article_list(MAIN_ARTICLE_LIST, selected_option, value);
}

Article set_article(Article article){
    string current_x_sep = "\t\t\t\t\t\t";
    std::map<std::string, string> pattern_dict = {
        {"nombre",      "_"},
        {"codigo",      CODE_NUMBER_REGEX},
        {"cantidad" ,   INT_NUMBER_REGEX},
        {"precio" ,     FLOAT_NUMBER_REGEX}
    };
    string value = "";
    string setting_options[] = {
        "Nombre",
        "Codigo",
        "Cantidad",
        "Precio"
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
        article.name = value;
    if (selected_option == "codigo")
        article.code = value;
    if (selected_option == "cantidad")
        article.count = stoi(value);
    if (selected_option == "precio")
        article.price = stof(value);
    return article;
}


bool delete_article_node(ArticlesList *main_article_list, ArticleNode *target_node){
    ArticleNode *current_node = main_article_list->head, *last_node = NULL;
    ArticleNode *aux_node = NULL;
    if (main_article_list->head == NULL){
        return false;
    } else {
        while (current_node != NULL){
            if (current_node->article.primary_key == target_node->article.primary_key){
                if (last_node){
                    last_node->next = current_node->next;
                    current_node->next = NULL;
                } else {
                    aux_node = current_node->next;
                    current_node->next = NULL;
                    main_article_list->head = aux_node;
                }
                delete current_node;
                MAIN_ARTICLE_LIST->articles_count--;
                return true;
            }
            last_node = current_node;
            current_node = current_node->next;
        }
        return false;
    }
}
void delete_articles_list(){
    string option;
    string error_log = "";
    ArticleNode *current_node = MAIN_ARTICLE_LIST->head;
    ArticleNode *aux_node;
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
            MAIN_ARTICLE_LIST->head = aux_node;
            current_node = MAIN_ARTICLE_LIST->head;
        }
        return;
    }
}
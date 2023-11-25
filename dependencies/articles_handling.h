#include <iostream>
#include "structs.h"
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
}


void show_article(Article article){
    cout << "~~ " << article.primary_key << endl;
    cout << "\t\tCodigo : " << article.code << endl;
    cout << "\t\tNombre : " << article.name << endl;
    cout << "\t\tCantidad : " << article.count << endl;
    cout << "\t\tPrecio : " << article.price << endl;
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


string articles_creation_handling(){
    Article new_article;
    std::map<std::string, string> pattern_dict = {
        {"nombre",      "_"},
        {"codigo",      CODE_NUMBER_REGEX},
        {"cantidad" ,   INT_NUMBER_REGEX},
        {"precio" ,     FLOAT_NUMBER_REGEX}
    };
    pattern_dict = validate_form(pattern_dict);
    new_article = create_article(uppercase(pattern_dict["codigo"]), stoi(pattern_dict["cantidad"]), uppercase(pattern_dict["nombre"]), stof(pattern_dict["precio"]));
    append_article_to_article_list(MAIN_ARTICLE_LIST, new_article);
    return uppercase(pattern_dict["codigo"]);
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
    }
    return NULL;
}


ArticleNode *search_article(){
    string selected_option;
    string value;
    string options[] = {
        "Nombre",
        "Id",
        "Codigo",
    };
    selected_option = to_lower(options[print_menu(options, sizeof(options) / sizeof(options[0]), "Selecciona el parámetro de búsqueda")-1]);
    cout << X_SEPARATION << "-> Ingresa el valor del " + selected_option + " para la búsqueda : ";
    cin >> value;
    return search_element_in_article_list(MAIN_ARTICLE_LIST, selected_option, value);
}


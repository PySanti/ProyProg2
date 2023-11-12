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


ArticleNode *create_article_node(Article article){
    ArticleNode *new_article_node = new ArticleNode;
    new_article_node->next = NULL;
    new_article_node->article = article;
    return new_article_node;
}

void append_article_to_article_list(ArticlesList *article_list, Article article){
    ArticleNode *new_article_node = create_article_node(article);
    ArticleNode *current_node = article_list->head;
    ArticleNode *last_node = NULL;
    while (current_node != NULL){
        last_node = current_node;
        current_node = current_node->next;
    }
    if (last_node != NULL){
        last_node->next = new_article_node;
    } else {
        article_list->head = new_article_node;
    }
}

void show_articles_list(ArticlesList *article_list){
    ArticleNode *current_node = article_list->head;
    if (article_list->head == NULL)
        return;
    else{
        while (current_node != NULL){
            cout << current_node->article.name << endl;
            current_node = current_node->next;
        }
    }
}

Article create_article(string code, int count, string name, float price ){
    Article new_article;
    new_article.primary_key = 1;
    new_article.code = code;
    new_article.count = count;
    new_article.name = name;
    new_article.price = price;
    return new_article;
}


void articles_creation_handling(ArticlesList *MAIN_ARTICLES_LIST){
    Article new_article;
    std::map<std::string, string> pattern_dict = {
        {"nombre",      "_"},
        {"codigo",      CODE_NUMBER_REGEX},
        {"cantidad" ,   INT_NUMBER_REGEX},
        {"precio" ,     FLOAT_NUMBER_REGEX}
    };
    pattern_dict = validate_form(pattern_dict);
    new_article = create_article(pattern_dict["code"], stoi(pattern_dict["cantidad"]), pattern_dict["nombre"], stof(pattern_dict["precio"]));
    append_article_to_article_list(MAIN_ARTICLES_LIST, new_article);
}

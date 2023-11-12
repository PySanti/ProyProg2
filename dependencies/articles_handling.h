#include <iostream>
#include "structs.h"
using namespace std;


Article create_article(string code, int count, string name, float price ){
    Article new_article;
    new_article.primary_key = 1;
    new_article.code = code;
    new_article.count = count;
    new_article.name = name;
    new_article.price = price;
    return new_article;
}


void articles_creation_handling(){
    Article new_article;
    std::map<std::string, string> pattern_dict = {
        {"nombre", "_"},
        {"codigo", CODE_NUMBER_REGEX},
        {"cantidad" , INT_NUMBER_REGEX},
        {"precio" , FLOAT_NUMBER_REGEX}
    };
    pattern_dict = validate_form(pattern_dict);
    new_article = create_article(pattern_dict["code"], stoi(pattern_dict["cantidad"]), pattern_dict["nombre"], stof(pattern_dict["precio"]));
}

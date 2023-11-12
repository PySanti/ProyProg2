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
    system("clear");
    std::map<std::string, string> pattern_dict;
    pattern_dict["nombre"] = "_";
    pattern_dict["código"] = "^[A-Za-z][0-9]+$";
    pattern_dict["cantidad"] = "^[0-9]+$";
    pattern_dict["precio"] = "^[+-]?([0-9]+(\\.[0-9]*)?|\\.[0-9]+)([eE][+-]?[0-9]+)?$";
    validate_form(pattern_dict);
    // new_article = create_article(code, count, name, price);
}

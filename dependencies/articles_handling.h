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
    pattern_dict["nombre"] = "-";
    pattern_dict["código"] = "codigo";
    pattern_dict["cantidad"] = "hola";
    pattern_dict["precio"] = "hola";
    validate_form(pattern_dict);
    // new_article = create_article(code, count, name, price);
}

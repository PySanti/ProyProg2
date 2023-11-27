#include <iostream>
#include <fstream>
using namespace std;


string read_stock_from_file(string filename, ArticlesList *main_article_list, string article_code_regex){
    std::ifstream file;
    string current_line;
    int current_atribute = 0;
    string current_value;
    ArticleNode *current_article_node;
    Article current_article;

    file.open(filename);
    if (!file.is_open()){
        return "Error, el archivo no ha podido ser abierto !";
    } else {
        while (file){
            getline(file, current_line);
            if (current_line.length() == 0)
                break;
            cout << current_line << "-" << current_atribute << endl;
            if (current_atribute == 0){
                if (!(validate_field(article_code_regex, current_line))){
                    return "Error, el codigo " + current_line + " es invalido !!";
                } else {
                    current_article_node = search_element_in_article_list(main_article_list, "codigo", current_line);
                    if (current_article_node)
                        current_article = current_article_node->article;
                    else
                        return "Error, articulo con codigo " + current_value + " no ha sido encontrado !";
                }
            } else if (current_atribute == 1){
                if (!string_is_num(current_line)){
                    return "Error, la cantidad "+ current_line + " es invalida !";
                } else {
                    current_article.count += stoi(current_line);
                }
            } else {
                current_atribute = -1;
            }
            current_atribute++;
        }
        pause();
        return "";
    }
    file.close();
}
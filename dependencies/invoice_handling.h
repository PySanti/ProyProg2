#include <iostream>

using namespace std;


string invoice_generation_handling(){
    string *sellers_names;
    sellers_names = generate_sellers_names_array();
    if (sellers_names == NULL){
        return "No hay vendedores";
    } else {
        for (int i = 0; i < MAIN_SELLERS_LIST->sellers_count; i++){
            cout << (sellers_names[i]) << endl;
        }
        exit(-1);
    }
}
#include <iostream>

using namespace std;

typedef struct Article {
    int primary_key;
    string code;
    string name;
    float price;
    int count;
} Article;

typedef struct Client {
    int primary_key;
    string name;
    string direction;
    string phone_number;
} Client;

typedef struct Renglon {
    string article_code;
    int article_ammount;
} Renglon;

typedef struct Seller {
    int primary_key;
    int cedula;
    string name;
    string entry_date;
    float comission;
} Seller;

typedef struct Invoice {
    string id;
    Client client_data;
    Seller seller_data;
    Renglon *renglones;
    int products_count;
    float sub_total;
    float discount;
    float total;
    float comission;
} Invoice;
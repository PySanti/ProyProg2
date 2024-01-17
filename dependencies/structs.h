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
    Article renglones[10];
    float sub_total;
    float discount;
    float total;
} Invoice;
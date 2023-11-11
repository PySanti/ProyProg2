#include <iostream>

using namespace std;

typedef struct Node{
    int element;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct Article {
    int primary_key;
    string code;
    string name;
    float price;
    int count;
} Article;

typedef struct Client {
    int id;
    string name;
    string direction;
    string phone_number;
} Client;

typedef struct Seller {
    int id;
    string name;
    string entry_date;
    float comission;
} Seller;

typedef struct Invoice {
    int id;
    Client client_data;
    Seller seller_data;
    Article renglones[10];
    float sub_total;
    float discount;
    float total;
} Invoice;
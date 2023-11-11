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
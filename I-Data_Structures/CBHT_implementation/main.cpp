#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Node {
    string key;
    string value;
    Node* next;

    Node(const string& input) {
        this->value=input;
        for (auto& ch : input) {
            if (ch>='A' && ch<='Z') this->key+=static_cast<char>(ch+('a'-'A'));
            else this->key+=ch;
        }
        this->next=nullptr;
    }

    ~Node() {}
};

struct HashTable {
    Node** table;
    int capacity;
    int size;

    HashTable() {
        this->size=0;
        this->capacity=1000;
        this->table=new Node*[this->capacity];
    }

    ~HashTable() {
        for (int i=0; i<this->capacity; i++) {
            Node* p=table[i];
            while (p) {
                Node* q=p;
                p=p->next;
                delete q;
            }
        }
        delete [] this->table;
    }
};

void hash_word(HashTable* ht, const string& word, const int& indexT) {
    Node* input=new Node(word);

    int index=0;
    switch(indexT) {
        case 2:
            index=input->key.length()>1 ? ((input->key[0]-'a')*26 + (input->key[1]-'a')) : (input->key[0]-'a');
            break;
        case 3:
            for(int i=0; i<input->key.length(); i++) index+=(input->key[i]-'a');
            break;
        case 4:
            index=input->key.length();
            break;
        default:
            index=(input->key[0]-'a');
            break;
    }

    if (!ht->table[index]) ht->table[index]=input;
    else {
        Node* p=ht->table[index];
        while (p->next) p=p->next;
        p->next=input;
    }

    ht->size++;
}


void write_hash_table(const HashTable& ht, const char* filename) {
    if (ht.size==0) return;

    ofstream out(filename);

    if (!out) {
        cerr << "Can't open file " << filename << endl;
        return;
    }

    for(int i=0; i<ht.capacity; i++) {
        Node* p=ht.table[i];
        if (!p) continue;
        out << i << ": ";
        while (p) {
            out << p->value << "; ";
            p=p->next;
        }
        out << '\n' << '\n';
    }

    out.close();
}


int main() {
    HashTable CBHT1, CBHT2, CBHT3, CBHT4;

    ifstream inputFile("words.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string word;
    while (inputFile >> word) {
        hash_word(&CBHT1, word, 1);
        hash_word(&CBHT2, word, 2);
        hash_word(&CBHT3, word, 3);
        hash_word(&CBHT4, word, 4);
    }

    inputFile.close();

    write_hash_table(CBHT1, "CBHT1.txt");
    write_hash_table(CBHT2, "CBHT2.txt");
    write_hash_table(CBHT3, "CBHT3.txt");
    write_hash_table(CBHT4, "CBHT4.txt");


    return 0;
}

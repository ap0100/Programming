#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct HashTable {
    vector<vector<string>> table;
    int capacity;
    int size;

    HashTable(int cap = 1000) {
        capacity = cap;
        size = 0;
        table.resize(capacity); // initialize vector of vectors
    }

    void hash_word(const string& word, int indexT) {
        string key;
        for (char ch : word) {
            if (ch >= 'A' && ch <= 'Z') key += ch + ('a' - 'A');//to lowercase
            else key += ch;
        }

        int index = 0;
        switch(indexT) {
            case 2:
                index = key.length() > 1 ? ((key[0]-'a')*26 + (key[1]-'a')) : (key[0]-'a');
                break;
            case 3:
                for (char ch : key) index += (ch - 'a');
                break;
            case 4:
                index = key.length();
                break;
            default:
                index = key[0] - 'a';
                break;
        }

        table[index].push_back(word);
        size++;
    }

    void write_hash_table(const string& filename) const {
        if (size == 0) return;

        ofstream out(filename);
        if (!out) {
            cerr << "Can't open file " << filename << endl;
            return;
        }

        for (int i = 0; i < capacity; i++) {
            if (table[i].empty()) continue;
            out << i << ": ";
            for (const auto& word : table[i]) {
                out << word << "; ";
            }
            out << "\n\n";
        }

        out.close();
    }
};


int main() {
    HashTable CBHT1, CBHT2, CBHT3, CBHT4;

    ifstream inputFile("words.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string word;
    while (inputFile >> word) {
        CBHT1.hash_word(word, 1);
        CBHT2.hash_word(word, 2);
        CBHT3.hash_word(word, 3);
        CBHT4.hash_word(word, 4);
    }
    inputFile.close();

    CBHT1.write_hash_table("CBHT1.txt");
    CBHT2.write_hash_table("CBHT2.txt");
    CBHT3.write_hash_table("CBHT3.txt");
    CBHT4.write_hash_table("CBHT4.txt");


    return 0;
}


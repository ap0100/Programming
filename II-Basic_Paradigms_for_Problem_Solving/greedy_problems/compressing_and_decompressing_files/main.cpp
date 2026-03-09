#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int character_encountered_before(vector<pair<unsigned char, int>> &v, unsigned char &c) {
    for (int i=0; i<v.size(); i++)
        if (v[i].first==c) return i;
    return -1;
}

struct Node {
    unsigned char character;
    int frequency;
    Node *left, *right;

    Node(unsigned char c, int f) : character(c), frequency(f), left(nullptr), right(nullptr) {}
    Node(int f, Node* l, Node* r) : character(0), frequency(f), left(l), right(r) {}
};

void generate_codes(Node* node, string code, vector<pair<unsigned char, string>> &codes_list) {
    if (!node) return;

    if (!node->left && !node->right) {
        codes_list.push_back({node->character, (code.empty()? "0" : code)});
        return;
    }

    generate_codes(node->left, code+"0", codes_list);
    generate_codes(node->right, code+"1", codes_list);
}

Node* assign_codes(vector<pair<unsigned char, int>> &v, vector<pair<unsigned char, string>> &codes_list) {
    priority_queue<Node*,vector<Node*>, decltype([](Node* a, Node* b) {
        return a->frequency>b->frequency;
    })> pq;
    for (auto& p:v) pq.push(new Node(p.first, p.second));

    while (pq.size()>1) {
        Node* l=pq.top();
        pq.pop();
        Node* r=pq.top();
        pq.pop();
        pq.push(new Node(l->frequency+r->frequency, l, r));
    }

    Node* root=pq.top();

    generate_codes(root, "", codes_list);
    return root;
}


int main() {
    ifstream input_file("anna_karenina.txt");

    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    vector<pair<unsigned char, int>> frequency_of_character;
    unsigned char character;
    while (input_file.get(reinterpret_cast<istream::char_type &>(character))) {
        int index=character_encountered_before(frequency_of_character, character);
        if (index==-1) frequency_of_character.push_back({character, 1});
        else frequency_of_character[index].second++;
    }

    sort(frequency_of_character.begin(), frequency_of_character.end(), [](auto a, auto b) {
        return a.second > b.second;
    });

    vector<pair<unsigned char, string>> codes_list;
    assign_codes(frequency_of_character, codes_list);

    input_file.clear();
    input_file.seekg(0);

    //-----------------------------compress-----------------------------
    ofstream out("compressed.txt", ios::binary);

    if (!out) {
        cerr << "Can't open file" << '\n';
        return 1;
    }

    out.put(0);

    unsigned char buffer=0;
    int bit_count=0;

    while (input_file.get(reinterpret_cast<istream::char_type &>(character))) {
        for (auto &c: codes_list) {
            if (character==c.first) {
                string &code=c.second;
                for (char &ch: code) {
                    buffer<<=1;
                    if (ch=='1') buffer|=1;
                    bit_count++;

                    if (bit_count==8) {
                        out.put(buffer);
                        buffer=0;
                        bit_count=0;
                    }
                }
                break;
            }
        }
    }

    if (bit_count>0) {
        buffer<<=(8-bit_count);
        out.put(buffer);
    }

    out.seekp(0);
    out.put(bit_count==0 ? 8 : bit_count);

    /*while (input_file.get(reinterpret_cast<istream::char_type &>(character))) {
        for (int i=0; i<codes_list.size(); i++)
            if (character==codes_list[i].first)
                out<<codes_list[i].second;
    }*/

    input_file.close();
    out.close();

    //-----------------------------decompress-----------------------------
    ifstream input_file2("compressed.txt", ios::binary);
    ofstream out2("decompressed.txt", ios::binary);

    if (!input_file2) {
        cerr << "Can't open file" << '\n';
        return 1;
    }

    if (!out2) {
        cerr << "Can't open file" << '\n';
        return 1;
    }

    Node* root=assign_codes(frequency_of_character, codes_list);
    Node* current=root;

    char byte;
    int valid_bits_last=input_file2.get();

    while (input_file2.get(byte)) {
        int bits_to_read=8;

        if (input_file2.peek()==EOF) bits_to_read=valid_bits_last;

        for (int i=7; i>=8-bits_to_read; i--) {
            char bit=((byte>>i)&1) ? '1' : '0';
            current=(bit=='0') ? current->left : current->right;

            if (!current->left && !current->right) {
                out2.put(current->character);
                current=root;
            }
        }
    }

    /*char bit;
    while(input_file2.get(bit)) {
        current=(bit=='0') ? current->left : current->right;
        if(!current->left && !current->right) {
            out2.put(current->character);
            current=root;
        }
    }*/

    input_file2.close();
    out2.close();


    return 0;
}
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;


//-------------------------------------LZW--------------------------------------------------------
vector<unsigned char> lzw_compress(const vector<unsigned char>& data) {
    unordered_map<string, int> dict;
    for (int i=0; i<256; i++) dict[string(1, static_cast<unsigned char>(i))] = i;

    vector<int> codes;
    string current;
    int next_code=256;

    for (unsigned char c: data) {
        string next=current+static_cast<char>(c);
        if (dict.contains(next)) current=next;
        else {
            codes.push_back(dict[current]);
            if (next_code<65536) dict[next]=next_code++;
            current=string(1, static_cast<char>(c));
        }
    }
    if (!current.empty()) codes.push_back(dict[current]);

    vector<unsigned char> output;
    output.reserve(codes.size()*2);
    for (int code: codes) {
        output.push_back((code>>8) & 0xFF);
        output.push_back(code & 0xFF);
    }

    return output;
}

vector<unsigned char> lzw_decompress(const vector<unsigned char>& data) {
    vector<string> dict;
    for (int i=0; i<256; i++) dict.push_back(string(1, static_cast<unsigned char>(i)));

    vector<int> codes;
    for (int i=0; i+1<static_cast<int>(data.size()); i+=2) codes.push_back((static_cast<int>(data[i])<<8) | static_cast<int>(data[i+1]));

    vector<unsigned char> output;
    string current=dict[codes[0]];
    for (unsigned char c: current) output.push_back(c);

    for (int i=1; i<static_cast<int>(codes.size()); i++) {
        int code=codes[i];
        string entry;
        code<static_cast<int>(dict.size()) ? entry=dict[code] : entry=current+current[0];

        for (unsigned char c: entry) output.push_back(c);
        dict.push_back(current+entry[0]);
        current=entry;
    }

    return output;
}

//--------------------------------Huffman-------------------------------------------------------------
int character_encountered_before(const vector<pair<unsigned char, int>> &v, const unsigned char &c) {
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

Node* assign_codes(const vector<pair<unsigned char, int>> &v, vector<pair<unsigned char, string>> &codes_list) {
    priority_queue<Node*,vector<Node*>, decltype([](const Node* a, const Node* b) {
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

//----------------------------------compression and decompression------------------------------------------------------

void compress(ofstream &out, const vector<pair<unsigned char, string>> &codes_list, const vector<unsigned char> &lz_data) {
    unordered_map<unsigned char, string> code_map;
    for (auto& p : codes_list) code_map[p.first] = p.second;

    unsigned char buffer = 0;
    int bit_count = 0;

    for (unsigned char byte: lz_data) {
        for (char bit: code_map[byte]) {
            buffer<<=1;
            if (bit=='1') buffer |= 1;
            bit_count++;
            if (bit_count==8) {
                out.put(buffer);
                buffer=0;
                bit_count=0;
            }
        }
    }

    if (bit_count>0) {
        buffer<<=(8-bit_count);
        out.put(buffer);
    }

    out.seekp(0);
    out.put(bit_count == 0 ? 8 : bit_count);
}

void decompress(ofstream &out2, ifstream &input_file2, vector<pair<unsigned char, string>> &codes_list, const vector<pair<unsigned char, int>> &frequency_of_character) {
    Node* root=assign_codes(frequency_of_character, codes_list);
    Node* current=root;

    vector<unsigned char> huffman_output;

    char byte;
    int valid_bits_last=input_file2.get();

    while (input_file2.get(byte)) {
        int bits_to_read=8;
        if (input_file2.peek()==EOF) bits_to_read=valid_bits_last;

        for (int i=7; i>=8-bits_to_read; i--) {
            char bit=((byte>>i)&1) ? '1' : '0';
            current=(bit=='0') ? current->left : current->right;

            if (!current->left && !current->right) {
                huffman_output.push_back(current->character);
                current=root;
            }
        }
    }

    vector<unsigned char> final_data=lzw_decompress(huffman_output);
    for (auto &c: final_data) out2.put(c);
}

int main() {
    ifstream input_file("anna_karenina.txt");

    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    vector<unsigned char> original;
    unsigned char character;
    while (input_file.get(reinterpret_cast<istream::char_type &>(character))) original.push_back(character);

    input_file.close();

    vector<unsigned char> lz_data=lzw_compress(original);

    unordered_map<unsigned char, int> frequency_of_character;
    for (auto b : lz_data) frequency_of_character[b]++;

    vector<pair<unsigned char, int>> frequencies(frequency_of_character.begin(), frequency_of_character.end());
    sort(frequencies.begin(), frequencies.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    vector<pair<unsigned char,string>> codes_list;
    assign_codes(frequencies, codes_list);

    //-----------------------------compress-------------------------------
    ofstream out("compressed.txt", ios::binary);

    if (!out) {
        cerr << "Can't open file" << '\n';
        return 1;
    }

    out.put(0); // placeholder for bit count
    compress(out, codes_list, lz_data);

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

    decompress(out2, input_file2, codes_list, frequencies);

    input_file2.close();
    out2.close();


   /* cout << "Original size: " << original.size() << " bytes\n";
    cout << "LZW output size: " << lz_data.size() << " bytes\n";
    out.close();
    ifstream check("compressed.txt", ios::binary | ios::ate);
    cout << "Compressed file size: " << check.tellg() << " bytes\n";
    check.close();*/


    return 0;
}
#include <iostream>

struct Node {
    int value;
    Node *next;
};

struct linkedList {
    Node *head;
};

void addNode(Node*, int);
void insertNodeSorted(linkedList&, int);
void outputList(linkedList);

void addNode(Node* node, int val) {
    Node *newNode = new Node();
    newNode->value=val;
    newNode->next=node->next;
    node->next=newNode;
}

void insertNodeSorted(linkedList& l, int val) {
    Node *p = l.head;
    if (val < p->value) {
        Node *newNode = new Node();
        newNode->value=p->value;
        newNode->next=p->next;
        p->next=newNode;
        p->value=val;
        return;
    }
    while (p->next) {
        if (val < p->next->value){
            addNode(p, val);
            return;
        }
        p=p->next;
    }
    addNode(p, val);
}

void outputList(linkedList l) {
    Node *p = l.head;
    while (p) {
        std::cout << p->value << " ";
        p=p->next;
    }
    std::cout << '\n';
}

int main() {
    linkedList List;

    int input;
    std::cout << "Enter list of numbers: " << '\n';
    std::cin >> input;

    List.head = new Node();
    List.head->value=input;
    List.head->next=nullptr;

    while (std::cin>>input) {
        insertNodeSorted(List, input);
    }

    outputList(List);

    return 0;
}
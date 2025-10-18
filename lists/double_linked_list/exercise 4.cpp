#include <iostream>

struct Node {
    int value;
    Node *previous=nullptr, *next=nullptr;//default value for the pointers
};

struct doubleLinkedList {
    Node *head;
    int length=0;
};

void addNode(Node*, int);
void insertNode(doubleLinkedList&, int, int=-1);
void deleteNode(doubleLinkedList&, int);
void searchNode(doubleLinkedList, int);
void outputList(doubleLinkedList);
void inputList(doubleLinkedList&);

//add a new node after the node passed in as a parameter
void addNode(Node *p, int val) {
    Node *newNode = new Node();
    newNode->value=val;
    newNode->previous=p;
    if (p->next) {
        newNode->next=p->next;
        newNode->next->previous=newNode;
    }
    p->next=newNode;
}

void insertNode(doubleLinkedList &l, int val, int pos) {
    Node *p = l.head;
    if (pos == -1) {
        while (p->next) p=p->next;
        addNode(p, val);
    }else if (pos==0) {
        //here p is still equal to l.head, so by adding a different valued element at position 0, the very first element, the head, is being changed
        Node *q=new Node();
        q->value=p->value;
        q->next=p->next;
        q->previous=p;
        p->next=q;
        p->value=val;
    }else {
        for (int i=0; i<pos-1; i++) p=p->next;
        addNode(p, val);
    }
    l.length++;
}

void inputList(doubleLinkedList &l) {
    int input;

    std::cout << "Enter list of numbers: " << '\n';
    std::cin >> input;

    l.head = new Node();
    l.head->value = input;
    l.length++;

    while (std::cin >> input) {
        insertNode(l, input);
    }
    std::cin.clear();
    std::cin.ignore();
}

void deleteNode(doubleLinkedList &l, int pos) {
    Node *p=l.head;
    if (pos == -1) {
        while (p->next) p=p->next;
        if (p->previous) p->previous->next=nullptr;
        delete p;
    }else if (pos==0) {
        //now the new head will be the soon-to-be former second element
        l.head=p->next;
        p->next->previous=nullptr;
        delete p;
    }else {
        for (int i=0; i<pos; i++) {
            p=p->next;
        }
        if (p->previous) p->previous->next=p->next;
        if (p->next) p->next->previous=p->previous;
        delete p;
    }
    l.length--;
}

void searchNode(doubleLinkedList l, int val) {
    Node *p=l.head;
    int pos=0;
    bool found=false;
    std::cout << "value found in position(s): " << " ";
    while (p) {
        if (p->value==val) {
            std::cout << pos << " ";
            found=true;
        }
        p=p->next;
        pos++;
    }
    if (!found) std::cout << "none" << '\n';
}

void outputList(doubleLinkedList l) {
    Node *p=l.head;
    while (p) {
        std::cout << p->value << " ";
        p=p->next;
    }
    std::cout << '\n';
}

int main() {
    doubleLinkedList list;
    inputList(list);

    int input, pos;

    std::cout << "Enter a value you want to add and the position where you want to have it added (-1 to add to the end of the list): " << '\n';
    std::cin >> input >> pos;
    if (pos > list.length) pos=-1;
    insertNode(list, input, pos);
    std::cout << "updated list: " << " ";
    outputList(list);
    std::cout << list.length << '\n';

    std::cout << "Enter the position of the element you want to remove (-1 to remove the last element): " << '\n';
    std::cin >> pos;
    if (pos > list.length) pos=list.length-1;;
    deleteNode(list, pos);
    std::cout << "updated list: " << " ";
    outputList(list);
    std::cout << list.length << '\n';

    std::cout << "Enter a value: " << '\n';
    std::cin >> input;
    searchNode(list, input);

    return 0;
}
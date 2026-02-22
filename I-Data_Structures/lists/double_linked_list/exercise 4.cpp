#include <iostream>

struct Node {
    int value;
    Node *previous=nullptr, *next=nullptr;//default value for the pointers
};

struct doubleLinkedList {
    Node *head=nullptr;
    int length=0;
};

void addNode(Node*, int);
void insertNode(doubleLinkedList&, int, int=-1);
void deleteNode(doubleLinkedList&, int);
Node *searchNode(const doubleLinkedList&, int);
void outputList(const doubleLinkedList&);
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
    if (!l.head) {
        l.head = new Node();
        l.head->value=val;
    }else {
        Node *p = l.head;
        if (pos==0) {
            //here p is still equal to l.head, so by adding a different valued element at position 0, the very first element, the head, is being changed
            Node *q=new Node();
            q->value=p->value;
            q->next=p->next;
            q->previous=p;
            p->next=q;
            p->value=val;
        }else if (pos == -1) {
            while (p->next) p=p->next;
            addNode(p, val);
        }else {
            for (int i=0; i<pos-1; i++) p=p->next;
            addNode(p, val);
        }
    }
    l.length++;
}

void inputList(doubleLinkedList &l) {
    int input;

    std::cout << "Enter list of numbers: " << '\n';
    std::cin >> input;

    if (input) {
        l.head = new Node();
        l.head->value = input;
        l.length++;
    }

    while (std::cin >> input) {
        insertNode(l, input);
    }
    std::cin.clear();
    std::cin.ignore();
}

void deleteNode(doubleLinkedList &l, int pos) {
    if (!l.head) {
        std::cout << "List is empty, there's nothing to delete" << '\n';
        return;
    }
    Node *p=l.head;
    if (pos == -1) {
        while (p->next) p=p->next;
        if (p->previous) p->previous->next=nullptr;
        delete p;
    }else if (pos==0) {
        if (p->next) {
            l.head=p->next;
            p->next->previous=nullptr;
            delete p;
        }else l.head=nullptr;
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

Node *searchNode(const doubleLinkedList &l, int val) {
    if (!l.head) {
        std::cout << "List is empty, there's nothing to search" << '\n';
        return nullptr;
    }
    Node *p=l.head;
    while (p) {
        if (p->value==val) {
            std::cout << "value found in list" << '\n';
            return p;
        }
        p=p->next;
    }
    std::cout << "value not found in list" << '\n';
    return nullptr;
}

void outputList(const doubleLinkedList &l) {
    if (!l.head) {
        std::cout << "List is empty" << '\n';
        return;
    }
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
    if (input) {
        if (pos > list.length) pos=-1;
        insertNode(list, input, pos);
        std::cout << "updated list: " << " ";
        outputList(list);
    }

    std::cin.clear();
    std::cin.ignore();

    std::cout << "Enter the position of the element you want to remove (-1 to remove the last element): " << '\n';
    std::cin >> pos;
    if (pos > list.length) pos=list.length-1;;
    deleteNode(list, pos);
    std::cout << "updated list: " << " ";
    outputList(list);

    std::cin.clear();
    std::cin.ignore();

    std::cout << "Enter a value: " << '\n';
    std::cin >> input;
    if (input) searchNode(list, input);

    return 0;
}
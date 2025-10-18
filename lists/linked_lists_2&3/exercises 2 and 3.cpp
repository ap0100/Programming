#include <iostream>

struct Node {
    int value;
    Node *next;
};

struct linkedList {
    Node *head;
};

void insertionSort(linkedList&);
void bubbleSort(linkedList&);
void insertNode(linkedList&, int);
void inputList(linkedList&);
void outputList(linkedList);
void mergeListsWithoutDuplicates(linkedList&, linkedList&, bool);

void insertionSort(linkedList &l) {
    Node *p=l.head->next, *q;
    while (p) {
        q=l.head;
        while (q && q != p) {
            if (q->value > p->value) {
                int container=q->value;
                q->value=p->value;
                p->value=container;
            }
            q=q->next;
        }
        p=p->next;
    }
}

void bubbleSort(linkedList &l) {
    Node *p=l.head, *q=l.head;
    while (p->next) {
        while (q->next) {
            if (q->value > q->next->value) {
                int container = q->value;
                q->value=q->next->value;
                q->next->value=container;
            }
            q=q->next;
        }
        p=p->next;
        q=l.head;
    }
}

void insertNode(linkedList &l, int val) {
    Node *p=l.head;
    while (p->next) p=p->next;
    Node *newNode = new Node();
    newNode->value=val;
    newNode->next=nullptr;
    p->next=newNode;
}

void inputList(linkedList &l) {
    int input;

    std::cout << "Enter list of numbers (enter any character when you're finished entering the list): " << '\n';
    std::cin >> input;

    l.head = new Node();
    l.head->value = input;
    l.head->next = nullptr;

    while (std::cin >> input) insertNode(l, input);
}

void outputList(linkedList l) {
    Node *p=l.head;
    std::cout << "Final result: " << '\n';
    while (p) {
        std::cout << p->value << " ";
        p=p->next;
    }
    std::cout << '\n';
}

void mergeListsWithoutDuplicates(linkedList &l1, linkedList &l2, bool bubbleSortList) {
    //merge/connect lists
    Node *p1=l1.head, *p2=l2.head;
    while (p1->next) p1=p1->next;
    p1->next=p2;
    bubbleSortList ? bubbleSort(l1) : insertionSort(l1);
    //remove duplicates
    p1=l1.head;
    while (p1->next) {
        while (p1->value == p1->next->value) {
            p2=p1->next->next;
            delete p1->next;
            p1->next=p2;
        }
        p1=p1->next;
    }
}

int main() {
    linkedList List1, List2;

    inputList(List1);
    std::cin.clear();
    std::cin.ignore();
    inputList(List2);

    mergeListsWithoutDuplicates(List1, List2, false);//false to sort with insertionSort, true to sort with bubbleSort
    outputList(List1);

    return 0;
}
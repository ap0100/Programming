#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

//Zad. 3 od testot od '25 - Simple Calculator
/*
struct Node {
    Node *next;
    char value;
};

struct Queue {
    Node *head;
    int size;

    Queue() {
        head=nullptr;
        size=0;
    }

    char top() {
        if (size==0) cout << "Queue is empty" << '\n';
        return head->value;
    }

    void pop() {
        if (size==0) {
            cout << "Queue is empty" << '\n';
            return;
        }

        Node *p=head->next;
        delete head;
        head=p;
        size--;
    }

    void push(char val) {
        Node *newNode=new Node();
        newNode->next=nullptr;
        newNode->value=val;

        if (!head) head=newNode;
        else {
            Node *p=head;
            while (p->next) p=p->next;
            p->next=newNode;
        }

        size++;
    }

    bool empty() {
        return size==0;
    }
};

void processInput(string &input, Queue &s) {
    for (char &c : input) {
        s.push(c);
    }
}

int computeInput(Queue &s) {
    int result=0, lastResult=0;
    char current, sign='/', lastSign='/';// '/' is given as default for sign and lastSign, it's a random character/invalid operation, not + or -

    while (!s.empty()) {
        current=s.top();

       if (current=='+' || current=='-'){
            sign=current;
       }else if (current=='('){
            lastResult=result;
            lastSign=sign;
            result=0;
            sign='/';
       }else if (current==')'){
            lastSign=='-' ? lastResult-=result : lastResult+=result;
            result=lastResult;
            lastResult=0;
            lastSign='/';
            sign='/';
       }else {
            if (sign=='-') result-=static_cast<int>(current)-48;
            else result+=static_cast<int>(current)-48;
       }

       // cout << current << " | " << "result: " << result << " " << lastResult << " sign: " << sign << " lastSign: " << lastSign << '\n';

        s.pop();
    }

    return result;
}

int main() {
    //Da se napravi ednostaven kalkulator:
    //-da operira so ednocifreni (celi) broevi
    //-operacii: +, -, ()
    //-se vnesuva izraz, string (ili specifichno niza od chars)
    //-output e samo rezultatot od presmetaniot izraz, sekako da bide cel broj
    string input;
    Queue s;

    getline(cin, input);
    processInput(input, s);
    cout << computeInput(s);

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------

//Zad. 1 od testot od '24 - Intervals
/*
struct Interval {
    int begin, end;
};

void mergeIntervals(vector<Interval> &intervals, vector<Interval> &result, int i, int index) {
    if (i>=intervals.size()) return;

     if (index>=result.size()) {
        result.push_back(intervals[i]);
        mergeIntervals(intervals, result, i+1, index);
    }

    if (result[index].end < intervals[i].begin) {
        mergeIntervals(intervals, result, i, index+1);
    }else {
        result[index]={min(result[index].begin, intervals[i].begin), max(result[index].end, intervals[i].end)};
        mergeIntervals(intervals, result, i+1, index);
    }
}

void sortIntervals(vector<Interval> &list) {
    for (int i=0; i<list.size()-1; i++) {
        for (int j=i+1; j<list.size(); j++) {
            if (list[i].begin < list[j].begin) {
                Interval temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void outputIntervals(vector<Interval> const &list) {
    for (int i=0; i<list.size(); i++) {
        cout << "{" << list[i].begin << ", " << list[i].end << "}" << ", ";
    }
}

int main()
{
    vector<Interval> intervals = { { 1, 5 }, { 2, 3 }, { 4, 6 }, { 7, 8 },
    { 8, 10 }, {12, 15} };

    vector<Interval> result;

    result.push_back(intervals[0]);

    mergeIntervals(intervals, result, 1, 0);
    sortIntervals(result);
    outputIntervals(result);

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------

//Zad. 2 od testot od '24 - Remove Redundant Nodes
/*
struct Node {
    int x, y;
    Node* next=nullptr;
};
void printList(Node *h);

void push(Node** headRef, int x, int y) {
    Node *newNode=new Node();
    newNode->x=x;
    newNode->y=y;
    newNode->next=*headRef;
    *headRef=newNode;
}

void removeNodes(Node **head) {
    Node *p=*head;
    if (!p || !p->next || !p->next->next) return;

    if ((p->x == p->next->x || p->y == p->next->y) && (p->x == p->next->next->x || p->y == p->next->next->y)) {
        Node *temp=p->next->next;
        delete p->next;
        p->next=temp;
        removeNodes(head);
    }else removeNodes(&p->next);

    // Node *p=*head;
    // while (p->next) {
    //     while (p->next->next && (p->x == p->next->x || p->y == p->next->y) && (p->next->next->x == p->x || p->next->next->y == p->y)) {
    //         Node *n=p->next->next;
    //         delete p->next;
    //         p->next=n;
    //     }
    //     p=p->next;
    // }
}

void printList(Node* head) {
    Node* ptr = head;
    while (ptr) {
        cout<< "(" << ptr->x << ", " << ptr->y << ") -> ";
        ptr = ptr->next;
    }
    printf("NULL\n");
}

int main() {
    // input coordinates
    int keys[][2] = { {0, 1}, {0, 5}, {0, 8},
     {2, 8},
     {5, 8},
     {7, 8}, {7, 10}, {7, 12} };
    int n = sizeof(keys) / sizeof(keys[0]);

    Node* head = NULL;//dummy node
    for (int i = n - 1; i >= 0; i--) {
        push(&head, keys[i][0], keys[i][1]);
    }

    printList(head);
    removeNodes(&head);
    printList(head);

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------

//5) Stack
/*
struct Node {
    int val;
    Node *next=nullptr;
};

struct Stack {
    Node *lead;
    int numOfElements=0;

    Stack() {
        lead = nullptr; //dummy node
    }

    void push(int value) {
        Node *newNode=new Node();
        newNode->next=lead;
        newNode->val=value;
        lead=newNode;
        numOfElements++;
    }

    void pop() {
        if (!lead) return;
        Node *p=lead->next;
        delete lead;
        lead=p;
        numOfElements--;
    }

    int top() {
        if (!lead) return NULL;
        return lead->val;
    }

    int size() {
        return numOfElements;
    }
};

void outputStack(Stack &s) {
    cout << "output:\n";
    int n=s.size();
    for (int i=0; i<n; i++) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << '\n';


    // Node *p=s.lead;
    // cout << "stack: ";
    // while (p->next) {
    //     cout << p->value << " ";
    //     p=p->next;
    // }
    // cout << '\n';
    //
};

int main() {
    int input;
    Stack s;

    cout << "Enter numbers for stack:\n";
    while (cin >> input) {
        s.push(input);
    }
    cin.clear();
    cin.ignore();

    outputStack(s);

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------

//4) Reverse Linked List
/*
struct Node {
    int val;
    Node *next;
    Node() {
        next = nullptr;
    }
};

struct linkedList {
    Node *head;
    int size=0;

    linkedList() {
        head=new Node();
    }
};

void insertNode(linkedList&, int);
void outputList(linkedList&);
void reverseList(linkedList&, int=0, int=-1);

void insertNode(linkedList &l, int value) {
    Node *p=l.head;
    while (p->next) p=p->next;
    Node *q=new Node();
    q->val=value;
    p->next=q;
    l.size++;
}

void outputList(linkedList &l) {
    cout << "result:\n";
    Node *p=l.head->next;
    while (p) {
        cout << p->val << " ";
        p=p->next;
    }
    cout<<'\n';
}

void reverseList(linkedList &l, int start, int end) {
    if (start==end || !l.head) return;
    if (start==0 && end==-1) end=l.size-1;

    Node *previous=l.head;
    for (int i=0; i<start-1; i++) previous=previous->next;

    Node *s=previous->next;
    Node *then=s->next;

    for (int i=0; i<end-start; i++) {
        s->next=then->next;
        then->next=previous->next;
        previous->next=then;
        then=s->next;
    }
}

int main() {
    int input, left, right;
    linkedList list;

    cout << "Enter list:\n";
    while (cin >> input) {
        insertNode(list, input);
    }
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Enter boundary:\n";
    cin >> left >> right;

    reverseList(list, left, right);
    outputList(list);

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------

//3) Merge k Sorted Lists
/*struct Node {
    int value;
    Node *next=nullptr;
};

struct List {
    Node *head;//dummy node
    List() {
        head=new Node();
    }
};

void inputLists(List*, int, int=0);
void addNode(List&, int);
void outputList(List&);
void mergeLists(List*, int);
void bubbleSort(List&);

void inputLists(List *lists, int k, int i) {
    if (k==0) return;

    int input;
    cout << "Enter list: \n";
    while (cin>>input) {
        addNode(*(lists+i), input);
    }

    cin.clear();
    cin.ignore(1000, '\n');

    inputLists(lists, k-1, i+1);
}

void addNode(List &l, int val) {
    Node *p=l.head;
    while (p->next) p=p->next;
    Node *newNode = new Node();
    newNode->value=val;
    p->next=newNode;
}

void outputList(List &list) {
    Node *p=list.head;
    while (p->next) {
        cout << p->next->value <<  " ";
        p=p->next;
    }
    cout << '\n';
}

void mergeLists(List *l, int k) {
    for (int i=0; i<k-1; i++) {
        List &p1=l[i];
        List &p2=l[i+1];
        Node *q=p1.head;
        while (q->next) q=q->next;
        q->next=p2.head->next;
    }
    bubbleSort(l[0]);
}

void bubbleSort(List &l) {
    Node *p=l.head, *q=l.head->next;
    while (p->next) {
        while (q->next) {
            if (q->value > q->next->value) {
                int container=q->value;
                q->value=q->next->value;
                q->next->value=container;
            }
            q=q->next;
        }
        p=p->next;
        q=l.head->next;
    }

    outputList(l);
}

int main() {
    int k;
    cout << "Enter k:\n";
    cin >> k;

    List *lists=new List[k];
    inputLists(lists, k);
    mergeLists(lists, k);

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------

//2) Remove Nth Node from End of the List
/*
struct Node {
    int value;
    Node *next=nullptr;
};

struct List {
    Node *head=nullptr;//dummy node
    int size=0;
};

void inputList(List&);
void outputList(const List&);
void addNode(List&, int);
void deleteNthNodeFromEnd(List&, int);

void inputList(List &list) {
    int input;

    while (cin >> input) {
        addNode(list, input);
        list.size++;
    }

    cin.clear();
    cin.ignore(10000, '\n');
}

void addNode(List &l, int value) {
    if (!l.head) l.head = new Node();
    Node *p=l.head;
    while (p->next) p = p->next;
    Node *newNode = new Node();
    newNode->value = value;
    p->next = newNode;
}

void outputList(List const &list) {
    if (list.size==0) {
        cout << "Empty list\n";
        return;
    }
    Node *p = list.head->next;
    while (p) {
        cout << p->value << " ";
        p = p->next;
    }
    cout << '\n';
}

void deleteNthNodeFromEnd(List &l, int n) {
    Node *p=l.head;
    for (int i=0; i<l.size-n; i++) p = p->next;
    Node *q=p->next->next;
    delete p->next;
    p->next=q;
    l.size--;
}

int main() {
    List l;

    inputList(l);
    deleteNthNodeFromEnd(l, 2);
    outputList(l);

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------

//1) Add Two Numbers
/*
struct Node {
    int value;
    Node *next = nullptr;
};

struct List {
    Node *head = nullptr;
};

int getListNumber(List&);
void inputList(List&);
void addNumbers(List&, List&, List&);
void outputList(const List&);
void addNode(int, List&);

void addNode(int val, List &l) {
    if (l.head==nullptr) {
        l.head = new Node();
        l.head->value = val;
        return;
    }

    Node *p=l.head;
    while (p->next) p=p->next;
    Node *newNode = new Node();
    newNode->value = val;
    p->next = newNode;
}

void inputList(List &list) {
    int input;

    while (cin >> input) {
        addNode(input, list);
    }
    cin.clear();
    cin.ignore(100000, '\n');
}

int getListNumber(List &l) {
    Node *p=l.head;
    int number = 0, exponent=0;

    while (p){
        number+=pow(10, exponent)*(p->value);
        p=p->next;
        exponent++;
    }

    return number;
}

void addNumbers(List &l1, List &l2, List &l) {
    int result=getListNumber(l1) + getListNumber(l2);

    while (result>0) {
        addNode(result%10, l);
        result/=10;
    }
}

void outputList(List &l) {
    Node *p=l.head;
    cout << "resulting list: ";
    while (p) {
        cout << p->value << " ";
        p=p->next;
    }
    cout << '\n';
}

int main() {
    List l1, l2, l;

    inputList(l1);
    inputList(l2);
    addNumbers(l1, l2, l);
    outputList(l);

    return 0;
}
*/
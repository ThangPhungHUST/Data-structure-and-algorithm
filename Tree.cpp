#include <iostream>
using namespace std;

const int MAX = 50;

typedef struct Node {
    char data;
    Node* left, * right;
} Node;

bool isEmpty(Node* T) {
    return T == NULL;
}

Node* newNode(char data) {
    Node* node = new Node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool isOperator(char s) {
    switch (s) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return true;
    default:
        return false;
    }
}

typedef struct stack {
    int Top;
    Node* data[MAX];
} stack;

void init(stack& s) {
    s.Top = 0;
}

bool isempty(stack& s) {
    return s.Top == 0;
}

bool isfull(stack& s) {
    return s.Top == MAX;
}

void push(stack& s, Node* t) {
    if (isfull(s)) {
        cout << "Stack Overflow" << endl;
    }
    else {
        s.data[s.Top++] = t;
    }
}

Node* pop(stack& s) {
    if (isempty(s)) {
        cout << "Stack Underflow" << endl;
    }
    else {
        Node* x = s.data[--s.Top];
        return x;
    }
}

Node* top(stack s) {
    return s.data[s.Top];
}

Node* constructTree(const char* s) {
    stack st;
    init(st);
    Node* t = NULL;
    int i = 0;
    while (s[i]) {
        if (!isOperator(s[i])) {
            t = newNode(s[i]);
            push(st, t);
        }
        else {
            t = newNode(s[i]);
            t->right = pop(st);
            t->left = pop(st);
            push(st, t);
        }
        i++;
    }
    t = pop(st);
    return t;
}

void preorder(Node* T) {
    if (!isEmpty(T)) {
        cout << T->data << " ";
        preorder(T->left);
        preorder(T->right);
    }
}

void inorder(Node* T) {
    if (!isEmpty(T)) {
        inorder(T->left);
        cout << T->data << " ";
        inorder(T->right);
    }
}

void lastorder(Node* T) {
    if (!isEmpty(T)) {
        lastorder(T->left);
        lastorder(T->right);
        cout << T->data << " ";
    }
}

int main() {
    Node* T = constructTree("a5*bc6^d/*-hf-e12/^*+");
    cout << "Tien to: ";
    preorder(T);
    cout << "\n-------\n";
    cout << "Trung to: ";
    inorder(T);
    cout << "\n-------\n";
    cout << "Hau to: ";
    lastorder(T);
    return 0;
}
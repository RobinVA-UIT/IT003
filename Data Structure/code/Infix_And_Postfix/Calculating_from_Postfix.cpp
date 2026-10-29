#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#define db double

using namespace std;

struct node {
    db data;
    node* next;
};

struct stack {
    node* top;
};

void createStack(stack& s) { s.top = nullptr; }

bool isEmpty(stack& s) { return s.top == nullptr; }

void push(stack& s, db input) {
    node* temp = new node();

    temp->data = input;

    if (isEmpty(s)) {
        s.top = temp;
        s.top->next = nullptr;
        return;
    }

    temp->next = s.top;
    s.top = temp;
}

db top(stack& s) {
    if (isEmpty(s)) return 0;

    return s.top->data;
}

void pop(stack& s) {
    if (isEmpty(s)) return;

    node* temp = s.top;
    s.top = s.top->next;

    delete temp;
}

bool isOps(string& token) {
    if (token.size() != 1) return false;

    char ops = token[0];

    if (ops == '+' || ops == '-' || ops == '*' || ops == '/' || ops == '^')
        return true;

    return false;
}

db smallCalc(db x, db y, char ops) {
    switch (ops) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        case '^':
            return pow(x, y);
    }

    return 0;
}

db calculation(string& postfix) {
    stack s;
    createStack(s);

    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        if (!isOps(token)) {
            push(s, stod(token));
        } else {
            db y = top(s);
            pop(s);
            db x = top(s);
            pop(s);

            push(s, smallCalc(x, y, token[0]));
        }
    }

    return top(s);
}

int main() {
    string postfix;
    getline(cin, postfix);

    cout << calculation(postfix);

    return 0;
}

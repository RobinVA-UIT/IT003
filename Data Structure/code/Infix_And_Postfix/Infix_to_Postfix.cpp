#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct node {
    char data;
    node* next;
};

struct stack {
    node* top;
};

void createStack(stack& s) { s.top = nullptr; }

bool isEmpty(stack& s) { return s.top == nullptr; }

void push(stack& s, char c) {
    node* temp = new node();

    temp->data = c;

    if (isEmpty(s)) {
        s.top = temp;
        s.top->next = nullptr;
        return;
    }

    temp->next = s.top;
    s.top = temp;
}

char top(stack& s) {
    if (isEmpty(s)) return '\0';

    return s.top->data;
}

void pop(stack& s) {
    if (isEmpty(s)) return;

    node* temp = s.top;

    s.top = s.top->next;

    delete temp;
}

void cleanStack(stack& s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

bool isOperator(string token) {
    if (token.size() != 1) return false;

    char c = token[0];
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return true;

    return false;
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;

    return 1;
}

string infix_to_postfix(string& infix) {
    string postfix = "";

    stack s;
    createStack(s);

    stringstream ss(infix);
    string token;

    while (ss >> token) {
        if (token[0] == '(') {
            push(s, '(');
            continue;
        } else if (token[0] == ')') {
            while (top(s) != '(' && top(s) != '\0') {
                postfix.push_back(top(s));
                postfix += " ";
                pop(s);
                continue;
            }

            if (isEmpty(s)) {
                cout << "Invalid infix expression.";
                cleanStack(s);
                exit(0);
            }

            pop(s);
        } else if (isOperator(token)) {
            int currLvl = precedence(token[0]);

            // Insert equal or higher precedence tokens to the postfix string
            while (!isEmpty(s) && top(s) != '(' &&
                   precedence(top(s)) >= currLvl) {
                postfix.push_back(top(s));

                postfix += " ";

                pop(s);
            }

            // Finally, push current token to the top of stack
            push(s, token[0]);
        }

        else {
            token += " ";

            postfix += token;
        }
    }

    while (!isEmpty(s)) {
        postfix += top(s);

        postfix += " ";

        pop(s);
    }

    return postfix;
}

int main() {
    string infix;

    getline(cin, infix);

    string postfix = infix_to_postfix(infix);

    cout << postfix;

    return 0;
}

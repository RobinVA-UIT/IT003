# Stack

Last In First Out

Implementation with Linked List:

```cpp
struct node{
	int data;
	node* next;	
};

struct stack{
	node* top;
};

void createStack(stack& s){
	s.top = nullptr;
}
```

## Basic functions

### push

Put an element on top of the stack.

```cpp
void push(stack& s, int data){
	node* newNode;
	newNode->data = data;

	if(top == nullptr){
		s.top = newNode;
		s.top->next = nullptr;
		continue;
	}

	newNode->next = s.top;
	s.top = newNode;
}
```

### top (peek)

Return the value of the top item.

```cpp
int top(stack& s){
	if(s.top == nullptr) return -1;

	return s.top->data;
}
```

### pop

Remove the value of the top item.

```cpp
void pop(stack& s){
	if(s.top == nullptr) return;

	if(s.top->next == nullptr){
		delete s.top;
		s.top = nullptr;

		return;
	}

	node* temp = s.top;
	s.top = s.top->next;
	delete temp;
}
```

### isEmpty

Check if the stack is empty or not.

```cpp
bool isEmpty(stack& s)
{
	return s.top == nullptr;
}
```

# Queue

First In First Out

Linked List implementation:

```cpp
struct node{
	int data;
	node* next;	
};

struct queue{
	node* front;
	node* rear;
};

void createQueue(queue& q){
	q.front = nullptr;
	q.rear = nullptr;
}
```

## Basic functions

### enqueue

Add a new element to the rear of the queue.

```cpp
void enqueue(queue& q, int data){
	node* temp;
	temp->data = data;
	temp->next = nullptr;

	if(q.front == nullptr){
		q.front = temp;
		q.rear = temp;
		return;
	}

	q.rear->next = temp;

	q.rear = temp;
}
```

### dequeue

Remove the front element of the queue, and return the value of that element.

```cpp
int dequeue(queue& q){
	if(q.front == nullptr) return -1;

	int removedData = q.front->data;

	if(q.rear == q.front){
		delete q.front;

		q.front = q.rear = nullptr;
	}
	else{
		node* temp = q.front;
		q.front = q.front->next;

		delete temp;
	}

	return removedData;
}
```

### front (peek)

Return the value at the front position without removing it.

```cpp
int front(queue& q){
	if(q.front == nullptr) return -1;

	return q.front->data;
	
}
```

### isEmpty

```cpp
bool isEmpty(queue& q){
	return q.front == nullptr;
}
```

---

# Problems

## Infix and Postfix

Read more [here](https://www.geeksforgeeks.org/dsa/infix-postfix-prefix-notation/)


### Infix -> Postfix (stack)

For each `x` as an element in the infix expression:

- If `x` is `(`, push it to the stack;

- If `x` is `)`, put all elements in the stack to the result until we reach `(`. Then, 
pop `(`;

- If `x` is an operator, put all operators existing in the stack that have equal or higher 
priority compared to `x`, then push `x`;

- If `x` is a number, put it in the result string.

After iterating the whole infix expression, pop all of the remaining elements in the stack, 
and put them in the result expression.

### Code

```cpp
//Assumed input: Infix expression, each token is separated by spaces
//Token can be a number or an operator

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

//Free memory
void cleanStack(stack& s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

//Check if the token is an operator or not
bool isOperator(string token) {
    if (token.size() != 1) return false;

    char c = token[0];
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return true;

    return false;
}

//Check priority of the current operator
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
    	//If opening parenthesis: push
        if (token[0] == '(') {
            push(s, '(');
            continue;
        }
        //If closing, push back all operators in the stack until reaching '('
        else if (token[0] == ')') {
            while (top(s) != '(' && top(s) != '\0') {
                postfix.push_back(top(s));
                postfix += " ";
                pop(s);
                continue;
            }

			//If empty (without opening), the infix expression is not valid
            if (isEmpty(s)) {
                cout << "Invalid infix expression.";
                cleanStack(s);
                exit(0);
            }

			//Remove the opening parenthesis
            pop(s);
        } 
        //If the token is an operator
        else if (isOperator(token)) {
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

		//If the token is a number, push back
        else {
            token += " ";

            postfix += token;
        }
    }

	//Push back remaining operators
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

```

## Calculating the result from postfix (stack)

For each `t` as a token in the postfix expression:

- If `t` is a number, push it to the stack.

- If `t` is an operator, assume `Y` is the element on top of the stack, and `X` is the one right below `Y`. 
Pop `X` and `Y`, then do `X t Y`, and push the result into the stack.

After reading all tokens, the number left in the stack is the result of the expression.

### Code

```cpp
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
    	//If not an op, it is a number. Push it into the stack
        if (!isOps(token)) {
            push(s, stod(token));
        }
        //When reach an op, start calculating 
        else {
            db y = top(s);
            pop(s);
            db x = top(s);
            pop(s);

            push(s, smallCalc(x, y, token[0]));
        }
    }

	//The top of stack is the final result
    return top(s);
}

int main() {
    string postfix;
    getline(cin, postfix);

    cout << calculation(postfix);

    return 0;
}

```

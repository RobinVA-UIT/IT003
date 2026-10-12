#include <iostream>

using namespace std;

class node {
   public:
    int data;
    node* next;

    node(int x) {
        this->data = x;
        this->next = nullptr;
    }
};

class linked_list {
   public:
    node* head;
    node* tail;

    linked_list() {
        head = nullptr;
        tail = nullptr;
    }

    // Add at tail
    void add_node(int x) {
        if (head == nullptr) {
            head = new node(x);
            tail = head;
        } else {
            node* new_node = new node(x);
            tail->next = new_node;
            tail = new_node;
        }
    }

    //=== NOTE ===
    // The start of the list is indexed as 1

    // Add at custom pos
    void add_node(int x, int pos) {
        if (pos < 1) return;

        node* newNode = new node(x);

        if (pos == 1) {
            newNode->next = head;
            head = newNode;
            return;
        }

        node* replacedNode = this->head;

        // Stop at the node right before the pos
        for (int i = 1; i < pos - 1 && replacedNode != nullptr; ++i) {
            replacedNode = replacedNode->next;
        }

        if (replacedNode == nullptr) return;

        newNode->next = replacedNode->next;

        if (newNode->next == nullptr) tail = newNode;

        replacedNode->next = newNode;

        return;
    }

    void delete_node(int pos) {
        if (pos == 0)
            return;

        else if (pos == 1) {
            node* temp = head;

            // replace head with its next node
            head = head->next;

            delete temp;

            return;
        }

        node* currNode = head;
        for (int i = 1; i < pos - 1 && currNode != nullptr; ++i) {
            currNode = currNode->next;
        }

        if (currNode == nullptr || currNode->next == nullptr) return;

        if (currNode->next == tail) tail = currNode;

        delete currNode->next;

        currNode->next = nullptr;
    }

    void print_list(node* currNode) {
        while (currNode != nullptr) {
            cout << currNode->data;
            currNode = currNode->next;
            if (currNode != nullptr) cout << " -> ";
        }

        cout << "\n";
    }

    void print_headtail() {
        cout << "Head = " << head->data << ", Tail = " << tail->data << '\n';
    }
};

int main() {
    linked_list list;

    int n;
    cin >> n;

    int x;
    while (n > 0) {
        cin >> x;
        list.add_node(x);
        --n;
    }

    list.print_list(list.head);
    list.print_headtail();

    list.add_node(100, 3);

    list.print_list(list.head);
    list.print_headtail();

    list.delete_node(3);
    list.print_list(list.head);
    list.print_headtail();

    list.add_node(200, 1);

    list.print_list(list.head);
    list.print_headtail();

    return 0;
}

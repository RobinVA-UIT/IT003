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

        node* toDelete = currNode->next;
        if (toDelete == tail) {
            tail = currNode;
        }

        currNode->next = toDelete->next;

        delete toDelete;
    }

    void print_list(node* currNode) {
        if (currNode == nullptr) {
            cout << "\nEmpty";
            return;
        }

        while (currNode != nullptr) {
            cout << currNode->data;
            currNode = currNode->next;
            if (currNode != nullptr) cout << " -> ";
        }

        cout << "\n";
    }

    void print_list() { print_list(this->head); }

    void print_headtail() {
        cout << "Head = " << head->data << ", Tail = " << tail->data << '\n';
    }

    void delete_list() {
        node* currNode = head;

        while (currNode != nullptr) {
            // Head will be assigned as nullptr eventually
            head = currNode->next;

            delete currNode;

            currNode = head;
        }

        tail = nullptr;
    }
};

void swap_node(linked_list& list, node* x, node* y) {
    if (x == y) return;

    node* p = list.head;
    node* prev = nullptr;

    // Find prevX
    while (p != nullptr && p != x) {
        prev = p;
        p = p->next;
    }

    node* prevX = prev;

    p = list.head;
    prev = nullptr;

    while (p != nullptr && p != y) {
        prev = p;
        p = p->next;
    }

    node* prevY = prev;

    // NOTE: DO NOT ADJUST PREVS' DATA, ONLY ADJUST PREVS' NEXT NODES
    // Case 1: X is head
    if (prevX == nullptr) {
        // If X is adjacent to Y:
        // X->next will be set to Y->Next
        // Now Y is right before X, so Y->next = X
        if (x->next == y) {
            x->next = y->next;
            y->next = x;
        }
        // If not adjacent:
        // Swap X and Y's next nodes
        // prevY->next now points to X
        else {
            node* temp = y->next;
            y->next = x->next;
            x->next = temp;

            prevY->next = x;
        }
        // Update head
        list.head = y;
    }
    // Case 2: Y is head
    else if (prevY == nullptr) {
        // If Y is adjacent to X:
        // Y->next = X->next
        // Now X is right before Y, so X->next = Y
        if (y->next == x) {
            y->next = x->next;
            x->next = y;
        }
        // Else
        // Swap X and Y's next nodes
        // prevX->next now points to Y
        else {
            node* temp = y->next;
            y->next = x->next;
            x->next = temp;

            prevX->next = y;
        }

        // New head
        list.head = x;

    }  // Case 3: Normal
    // Just swap next node of X, Y and their prevs
    else {
        node* temp = prevX->next;
        prevX->next = prevY->next;
        prevY->next = temp;

        temp = x->next;
        x->next = y->next;
        y->next = temp;
    }

    // Update tail if needed
    if (x->next == nullptr) {
        list.tail = x;
    } else if (y->next == nullptr) {
        list.tail = y;
    }
}

// Ascending
void selection_sort(linked_list& list) {
    // If n <= 1, return
    if (list.head == nullptr || (list.head == list.tail)) return;

    node *currNode, *selectingNode, *min, *temp;

    currNode = list.head;

    while (currNode != nullptr) {
        min = currNode;

        selectingNode = currNode->next;

        while (selectingNode != nullptr) {
            if (min->data > selectingNode->data) min = selectingNode;

            selectingNode = selectingNode->next;
        }

        if (min != currNode) {
            swap_node(list, min, currNode);

            // If swapped, our old curr is now swapped to the other end, so we
            // need to update
            currNode = min;
        }

        currNode = currNode->next;
    }
}

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

    selection_sort(list);
    list.print_list();

    list.delete_list();
    list.print_list();

    return 0;
}

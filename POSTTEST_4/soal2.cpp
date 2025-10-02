#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char nilai = temp->data;
    top = top->next;
    delete temp;
    return nilai;
}

// fungsi untuk mengecek apakah pasangan kurung sesuai
bool isMatchingPair(char buka, char tutup) {
    return (buka == '(' && tutup == ')') ||
           (buka == '{' && tutup == '}') ||
           (buka == '[' && tutup == ']');
}

bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (stackTop == nullptr) return false;
            char atas = pop(stackTop);
            if (!isMatchingPair(atas, c)) return false;
        }
    }

    return (stackTop == nullptr);
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}
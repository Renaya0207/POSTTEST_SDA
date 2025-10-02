#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// fungsi push: menambahkan data ke atas stack
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

// fungsi pop: mengeluarkan data paling atas dari stack
char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char nilai = temp->data;
    top = top->next;
    delete temp;
    return nilai;
}

// fungsi untuk membalik string menggunakan stack
string reverseString(string s) {
    Node* stackTop = nullptr;
    string hasil = "";

    // masukkan setiap karakter ke stack
    for (char c : s) {
        push(stackTop, c);
    }

    // ambil kembali karakter dari stack (otomatis terbalik)
    while (stackTop != nullptr) {
        hasil += pop(stackTop);
    }

    return hasil;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl;
    return 0;
}
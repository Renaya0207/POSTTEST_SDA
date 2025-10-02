#include <iostream>
#include <string>
using namespace std;

struct Node {
    string dokumen;
    Node* next;
};

// menambahkan dokumen ke antrian (enqueue)
void enqueue(Node*& front, Node*& rear, string dokumen) {
    Node* newNode = new Node{dokumen, nullptr};

    if (front == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// mengambil dokumen dari antrian (dequeue)
string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return "";

    Node* temp = front;
    string doc = temp->dokumen;
    front = front->next;

    if (front == nullptr) rear = nullptr;

    delete temp;
    return doc;
}

// memproses semua dokumen di antrian
void processAllDocuments(Node*& front, Node*& rear) {
    while (front != nullptr) {
        string doc = dequeue(front, rear);
        cout << "Memproses: " << doc << endl;
    }
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    return 0;
}
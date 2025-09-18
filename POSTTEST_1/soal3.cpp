#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    Mahasiswa mhs[4];

    cout << "Input 4 Mahasiswa:\n";
    for (int i = 0; i < 4; i++) {
        cout << "Mahasiswa ke-" << i + 1 << endl;
        cout << "Nama : "; cin >> mhs[i].nama;
        cout << "NIM  : "; cin >> mhs[i].nim;
        cout << "IPK  : "; cin >> mhs[i].ipk;
    }

    // urutkan berdasarkan IPK 
    sort(mhs, mhs + 4, [](Mahasiswa a, Mahasiswa b) {
        return a.ipk < b.ipk;
    });

    cout << "\nData Mahasiswa setelah diurutkan (IPK ascending):\n";
    for (int i = 0; i < 4; i++) {
        cout << mhs[i].nama << " | " << mhs[i].nim << " | " << mhs[i].ipk << endl;
    }

    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int matriks[3][3];
    int angka = 1;

    // matriks 3x3 dengan angka 1–9
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriks[i][j] = angka++;
        }
    }

    // hitung jumlah baris genap (baris ke-2 = index 1)
    int jumlah = 0;
    for (int j = 0; j < 3; j++) {
        jumlah += matriks[1][j];
    }

    cout << "Matriks 3x3:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Jumlah elemen baris genap (baris ke-2): " << jumlah << endl;

    return 0;
}
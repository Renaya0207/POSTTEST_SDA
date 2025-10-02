#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Node {
    int id;
    string namaItem;
    int jumlah;
    string tipe;
    Node *next;
    Node *prev;
};

Node *head = NULL;
Node *tail = NULL;
int jumlahAwal = 1;
int posisiSisip = 1;
int autoID = 1;

// Membuat node baru
Node* buatNode(string nama, string tipe) {
    Node *baru = new Node;
    baru->id = autoID++;
    baru->namaItem = nama;
    baru->tipe = tipe;
    baru->jumlah = jumlahAwal;
    baru->next = NULL;
    baru->prev = NULL;
    return baru;
}

// Tambah di akhir
void tambahItem(string nama, string tipe) {
    Node *baru = buatNode(nama, tipe);
    if (head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
}

// Sisip di posisi tertentu
void sisipItem(string nama, string tipe) {
    Node *baru = buatNode(nama, tipe);

    if (head == NULL || posisiSisip == 1) {
        baru->next = head;
        if (head != NULL) head->prev = baru;
        head = baru;
        if (tail == NULL) tail = baru;
    } else {
        Node *bantu = head;
        int i = 1;
        while (i < posisiSisip - 1 && bantu->next != NULL) {
            bantu = bantu->next;
            i++;
        }
        baru->next = bantu->next;
        baru->prev = bantu;
        if (bantu->next != NULL) {
            bantu->next->prev = baru;
        } else {
            tail = baru;
        }
        bantu->next = baru;
    }
}

// Hapus item terakhir
void hapusItemTerakhir() {
    if (tail == NULL) {
        cout << "Inventory kosong!\n";
        return;
    }
    Node *hapus = tail;
    if (head == tail) {
        head = tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = NULL;
    }
    delete hapus;
    cout << "Item terakhir berhasil dihapus!\n";
}

// Gunakan item
void gunakanItem(string nama) {
    if (head == NULL) {
        cout << "Inventory kosong!\n";
        return;
    }

    Node *bantu = head;
    while (bantu != NULL && bantu->namaItem != nama) {
        bantu = bantu->next;
    }

    if (bantu == NULL) {
        cout << "Item tidak ditemukan!\n";
    } else {
        bantu->jumlah--;
        if (bantu->jumlah <= 0) {
            cout << bantu->namaItem << " habis, dihapus dari inventory.\n";
            if (bantu == head) {
                head = bantu->next;
                if (head != NULL) head->prev = NULL;
            } else if (bantu == tail) {
                tail = bantu->prev;
                if (tail != NULL) tail->next = NULL;
            } else {
                bantu->prev->next = bantu->next;
                bantu->next->prev = bantu->prev;
            }
            delete bantu;
        } else {
            cout << "Berhasil menggunakan " << nama 
                 << ". Sisa: " << bantu->jumlah << endl;
        }
    }
}

// Cetak header tabel
void cetakHeader() {
    cout << "+-----+-----------------+--------+---------------+\n";
    cout << "| ID  | Nama Item       | Jumlah | Tipe          |\n";
    cout << "+-----+-----------------+--------+---------------+\n";
}

// Cetak baris tabel
void cetakBaris(Node *n) {
    cout << "| " << setw(3) << n->id
         << " | " << left << setw(15) << n->namaItem
         << " | " << setw(6) << n->jumlah
         << " | " << setw(13) << n->tipe << " |\n";
}

// Traversal dari depan
void tampilkanInventory() {
    if (head == NULL) {
        cout << "Inventory kosong!\n";
        return;
    }
    cout << "\n=== Daftar Inventory (Depan -> Belakang) ===\n";
    cetakHeader();
    Node *bantu = head;
    while (bantu != NULL) {
        cetakBaris(bantu);
        bantu = bantu->next;
    }
    cout << "+-----+-----------------+--------+---------------+\n";
}

// Traversal dari belakang
void tampilkanInventoryBelakang() {
    if (tail == NULL) {
        cout << "Inventory kosong!\n";
        return;
    }
    cout << "\n=== Daftar Inventory (Belakang -> Depan) ===\n";
    cetakHeader();
    Node *bantu = tail;
    while (bantu != NULL) {
        cetakBaris(bantu);
        bantu = bantu->prev;
    }
    cout << "+-----+-----------------+--------+---------------+\n";
}

// Cari detail berdasarkan ID
void detailItem(int idCari) {
    Node *bantu = head;
    while (bantu != NULL && bantu->id != idCari) {
        bantu = bantu->next;
    }
    if (bantu == NULL) {
        cout << "Data dengan ID " << idCari << " tidak ditemukan!\n";
    } else {
        cout << "\n=== Detail Item ===\n";
        cout << "ID     : " << bantu->id << endl;
        cout << "Nama   : " << bantu->namaItem << endl;
        cout << "Jumlah : " << bantu->jumlah << endl;
        cout << "Tipe   : " << bantu->tipe << endl;
        cout << "===================\n";
    }
}

// MAIN PROGRAM
int main() {
    string nama, nim;
    cout << "Masukkan Nama: ";
    getline(cin, nama);
    cout << "Masukkan NIM: ";
    getline(cin, nim);

    for (auto &c : nama) c = toupper(c);

    if (nim.size() >= 2) {
        jumlahAwal = stoi(nim.substr(nim.size() - 2));
    } else {
        jumlahAwal = stoi(nim);
    }
    posisiSisip = (nim.back() - '0') + 1;

    int pilih;
    do {
        cout << "\n+-------------------------------------------------+\n";
        cout << "|        GAME INVENTORY MANAGEMENT (DLL)          |\n";
        cout << "|        [ " << nama << " - " << nim << " ]\n";
        cout << "+-------------------------------------------------+\n";
        cout << "1. Tambah Item Baru\n";
        cout << "2. Sisipkan Item\n";
        cout << "3. Hapus Item Terakhir\n";
        cout << "4. Gunakan Item\n";
        cout << "5. Tampilkan Inventory (Depan -> Belakang)\n";
        cout << "6. Tampilkan Inventory (Belakang -> Depan)\n";
        cout << "7. Detail Item (berdasarkan ID)\n";
        cout << "0. Keluar\n";
        cout << "+-------------------------------------------------+\n";
        cout << "Pilih menu: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            string item, tipe;
            cout << "Masukkan nama item : ";
            getline(cin, item);
            cout << "Masukkan tipe item : ";
            getline(cin, tipe);
            tambahItem(item, tipe);
        }
        else if (pilih == 2) {
            string item, tipe;
            cout << "Masukkan nama item : ";
            getline(cin, item);
            cout << "Masukkan tipe item : ";
            getline(cin, tipe);
            sisipItem(item, tipe);
        }
        else if (pilih == 3) {
            hapusItemTerakhir();
        }
        else if (pilih == 4) {
            string item;
            cout << "Masukkan nama item yang digunakan: ";
            getline(cin, item);
            gunakanItem(item);
        }
        else if (pilih == 5) {
            tampilkanInventory();
        }
        else if (pilih == 6) {
            tampilkanInventoryBelakang();
        }
        else if (pilih == 7) {
            int idCari;
            cout << "Masukkan ID item: ";
            cin >> idCari;
            detailItem(idCari);
        }
    } while (pilih != 0);

    return 0;
}
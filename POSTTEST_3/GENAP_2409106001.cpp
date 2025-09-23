#include <iostream>
#include <string>
using namespace std;

struct Flight {
    string kodePenerbangan;
    string tujuan;
    string status;
    Flight *next;
    Flight *prev;
};

Flight *head = nullptr;
Flight *tail = nullptr;
int counter = 0;

// kode penerbangan berdasarkan NIM
string generateKode() {
    if (counter == 0) {
        counter++;
        return "JT-002"; // 3 digit terakhir NIM
    } else {
        return "JT-002-" + to_string(counter++);
    }
}

// tambah jadwal di akhir
void addLast(string tujuan, string status) {
    Flight *nodeBaru = new Flight;
    nodeBaru->kodePenerbangan = generateKode();
    nodeBaru->tujuan = tujuan;
    nodeBaru->status = status;
    nodeBaru->next = nullptr;
    nodeBaru->prev = tail;

    if (head == nullptr) {
        head = tail = nodeBaru;
    } else {
        tail->next = nodeBaru;
        tail = nodeBaru;
    }
    cout << ">> Jadwal berhasil ditambahkan di akhir.\n";
}

// sisipkan jadwal pada posisi tertentu (digit terakhir NIM + 1)
void addSpecific(string tujuan, string status) {
    int posisi = 2 + 1; // karena NIM berakhir 2 → posisi = 3
    Flight *nodeBaru = new Flight;
    nodeBaru->kodePenerbangan = generateKode();
    nodeBaru->tujuan = tujuan;
    nodeBaru->status = status;

    if (head == nullptr || posisi <= 1) {
        nodeBaru->next = head;
        nodeBaru->prev = nullptr;
        if (head != nullptr) head->prev = nodeBaru;
        head = nodeBaru;
        if (tail == nullptr) tail = nodeBaru;
        cout << ">> Jadwal berhasil disisipkan di awal.\n";
        return;
    }

    Flight *temp = head;
    int hitung = 1;
    while (temp->next != nullptr && hitung < posisi - 1) {
        temp = temp->next;
        hitung++;
    }

    nodeBaru->next = temp->next;
    nodeBaru->prev = temp;
    if (temp->next != nullptr) temp->next->prev = nodeBaru;
    temp->next = nodeBaru;
    if (nodeBaru->next == nullptr) tail = nodeBaru;

    cout << ">> Jadwal berhasil disisipkan pada posisi " << posisi << ".\n";
}

// hapus jadwal paling awal
void deleteFirst() {
    if (head == nullptr) {
        cout << ">> Jadwal masih kosong <<\n";
        return;
    }
    Flight *hapus = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr; // jika list jadi kosong
    }
    cout << "Jadwal " << hapus->kodePenerbangan << " dihapus.\n";
    delete hapus;
}

// update status penerbangan
void updateStatus(string kode) {
    if (head == nullptr) {
        cout << ">> Jadwal masih kosong <<\n";
        return;
    }
    Flight *temp = head;
    while (temp != nullptr) {
        if (temp->kodePenerbangan == kode) {
            cout << "Status lama: " << temp->status << endl;
            cout << "Masukkan status baru: ";
            string newStatus;
            getline(cin >> ws, newStatus);
            temp->status = newStatus;
            cout << "Status penerbangan " << kode << " berhasil diperbarui.\n";
            return;
        }
        temp = temp->next;
    }
    cout << ">> Kode penerbangan tidak ditemukan <<\n";
}

// tampilkan semua jadwal dari depan
void display() {
    if (head == nullptr) {
        cout << ">> Tidak ada jadwal penerbangan <<\n";
        return;
    }
    Flight *temp = head;
    cout << "\n==== DAFTAR JADWAL PENERBANGAN (DEPAN) ====\n";
    while (temp != nullptr) {
        cout << "Kode   : " << temp->kodePenerbangan << endl;
        cout << "Tujuan : " << temp->tujuan << endl;
        cout << "Status : " << temp->status << endl;
        cout << "-----------------------------\n";
        temp = temp->next;
    }
}

// tampilkan semua jadwal dari belakang
void displayReverse() {
    if (tail == nullptr) {
        cout << ">> Tidak ada jadwal penerbangan <<\n";
        return;
    }
    Flight *temp = tail;
    cout << "\n==== DAFTAR JADWAL PENERBANGAN (BELAKANG) ====\n";
    while (temp != nullptr) {
        cout << "Kode   : " << temp->kodePenerbangan << endl;
        cout << "Tujuan : " << temp->tujuan << endl;
        cout << "Status : " << temp->status << endl;
        cout << "-----------------------------\n";
        temp = temp->prev;
    }
}

// tampilkan detail jadwal berdasarkan kode
void detailByKode(string kode) {
    Flight *temp = head;
    while (temp != nullptr) {
        if (temp->kodePenerbangan == kode) {
            cout << "\n==== DETAIL JADWAL ====\n";
            cout << "Kode   : " << temp->kodePenerbangan << endl;
            cout << "Tujuan : " << temp->tujuan << endl;
            cout << "Status : " << temp->status << endl;
            return;
        }
        temp = temp->next;
    }
    cout << ">> Kode penerbangan tidak ditemukan <<\n";
}

int main() {
    int pilihan;
    string tujuan, status, kode;

    do {
        cout << "\n+------------------------------------------------------------+\n";
        cout << "|              FLIGHT SCHEDULE SYSTEM (DLL)                  |\n";
        cout << "|       [ Renaya Putri Alika - 2409106002 ]                  |\n";
        cout << "+------------------------------------------------------------+\n";
        cout << "| 1. Tambah Jadwal Penerbangan (Akhir)                       |\n";
        cout << "| 2. Sisipkan Jadwal Penerbangan (Posisi NIM+1)              |\n";
        cout << "| 3. Hapus Jadwal Paling Awal                                |\n";
        cout << "| 4. Update Status Penerbangan                               |\n";
        cout << "| 5. Tampilkan Semua Jadwal (Depan)                          |\n";
        cout << "| 6. Tampilkan Semua Jadwal (Belakang)                       |\n";
        cout << "| 7. Cari Detail Jadwal (berdasarkan Kode)                   |\n";
        cout << "| 0. Keluar                                                  |\n";
        cout << "+------------------------------------------------------------+\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cout << "Masukkan tujuan: ";
            getline(cin >> ws, tujuan);
            cout << "Masukkan status: ";
            getline(cin >> ws, status);
            addLast(tujuan, status);
            break;
        case 2:
            cout << "Masukkan tujuan: ";
            getline(cin >> ws, tujuan);
            cout << "Masukkan status: ";
            getline(cin >> ws, status);
            addSpecific(tujuan, status);
            break;
        case 3:
            deleteFirst();
            break;
        case 4:
            cout << "Masukkan kode penerbangan: ";
            cin >> kode;
            updateStatus(kode);
            break;
        case 5:
            display();
            break;
        case 6:
            displayReverse();
            break;
        case 7:
            cout << "Masukkan kode penerbangan: ";
            cin >> kode;
            detailByKode(kode);
            break;
        case 0:
            cout << "Keluar dari program...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}

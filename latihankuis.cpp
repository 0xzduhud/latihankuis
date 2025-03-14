#include <iostream>
#include <cstdio>

using namespace std;

struct Penduduk {
    int nik;
    char nama[50];
    char alamat[100];
    char jenis_kelamin;
};

// fungsi untuk tambah dataa
void inputData() {
    FILE *file = fopen("data_penduduk.txt", "a");
    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }

    Penduduk p;
    cout << "Masukkan NIK: ";
    cin >> p.nik;
    cin.ignore();
    cout << "Masukkan Nama: ";
    cin.getline(p.nama, 50);
    cout << "Masukkan Alamat: ";
    cin.getline(p.alamat, 100);
    cout << "Masukkan Jenis Kelamin (L/P): ";
    cin >> p.jenis_kelamin;
    cin.ignore();

    fprintf(file, "%d|%s|%s|%c\n", p.nik, p.nama, p.alamat, p.jenis_kelamin);
    fclose(file);
        cout << "Data berhasil ditambahkan!\n";
}

// fungsi untk menampilkan data
void tampilkanData() {
    FILE *file = fopen("data_penduduk.txt", "r");
    if (!file) {
        cout << "Belum ada data tersimpan.\n";
        return;
    }

    Penduduk dataPenduduk[100]; 
    int jumlah = 0;

    
     while (fscanf(file, "%d|%49[^|]|%99[^|]|%c\n", &dataPenduduk[jumlah].nik, 
                  dataPenduduk[jumlah].nama, dataPenduduk[jumlah].alamat, 
                  &dataPenduduk[jumlah].jenis_kelamin) != EOF) {
        jumlah++;
    }
    fclose(file); 

    if (jumlah == 0) {
        cout << "Tidak ada data untuk ditampilkan.\n";
        return;
    }

    
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (dataPenduduk[j].nik > dataPenduduk[j + 1].nik) {
                Penduduk temp = dataPenduduk[j];
                dataPenduduk[j] = dataPenduduk[j + 1];
                dataPenduduk[j + 1] = temp;
            }
        }
    }

   
    cout << "=======================================\n";
    cout << "NIK\tNama\tAlamat\tJenis Kelamin\n";
    cout << "=======================================\n";

    for (int i = 0; i < jumlah; i++) {
        cout << dataPenduduk[i].nik << "\t" << dataPenduduk[i].nama << "\t" 
             << dataPenduduk[i].alamat << "\t" << dataPenduduk[i].jenis_kelamin << endl;
    }
}


// fungsi cari data
void cariData() {

    FILE *file = fopen("data_penduduk.txt", "r");
    if (!file) {
        cout << "Belum ada data tersimpan.\n";
        return;
    }

    int cariNik;
    cout << "Masukkan NIK yang dicari: ";
         cin >> cariNik;

    Penduduk p;
    bool ditemukan = false;

  

    while (fscanf(file, "%d|%49[^|]|%99[^|]| %c\n", &p.nik, p.nama, p.alamat, &p.jenis_kelamin) != EOF) {
        if (p.nik == cariNik) {
            cout << "\nData ditemukan!\n";
            cout << "NIK: " << p.nik << "\nNama: " << p.nama
                 << "\nAlamat: " << p.alamat << "\nJenis Kelamin: " << p.jenis_kelamin << "\n";
            ditemukan = true;
            break;
        }
    }

    fclose(file);

    if (!ditemukan) {
        cout << "Data tidak ditemukan.\n";
    }
}
// untuk mengedit data 
void editData() {
    FILE *file = fopen("data_penduduk.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        cout << "Gagal membuka file!\n";
        return;
    }

    int nikEdit;
    cout << "Masukkan NIK yang ingin diedit: ";
    cin >> nikEdit;
    cin.ignore();

    Penduduk p;
    bool found = false;

    while (fscanf(file, "%d|%49[^|]|%99[^|]|%c\n", &p.nik, p.nama, p.alamat, &p.jenis_kelamin) != EOF) {
        if (p.nik == nikEdit) {
            found = true;
            cout << "Masukkan Alamat baru: ";
            cin.getline(p.alamat, 100);
        }
        fprintf(temp, "%d|%s|%s|%c\n", p.nik, p.nama, p.alamat, p.jenis_kelamin);
    }

    fclose(file);
    fclose(temp);
    remove("data_penduduk.txt");
    rename("temp.txt", "data_penduduk.txt");

    if (found) {
        cout << "Data berhasil diperbarui!\n";
    } else {
        cout << "Data tidak ditemukan!\n";
    }
}

// fungsi untk menghapus dta
void hapusData() {
    FILE *file = fopen("data_penduduk.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        cout << "Gagal membuka file!\n";
        return;
    }

    int nikHapus;
    cout << "Masukkan nik yang ingin dihapus: ";
    cin >> nikHapus;

    Penduduk p;
    bool found = false;

    while (fscanf(file, "%d|%49[^|]|%99[^|]|%c\n", &p.nik, p.nama, p.alamat, &p.jenis_kelamin) != EOF) {
        if (p.nik != nikHapus) {
            fprintf(temp, "%d|%s|%s|%c\n", p.nik, p.nama, p.alamat, p.jenis_kelamin);
        } else {
            found = true;
        }
    }

        fclose(file);
    fclose(temp);
    remove("data_penduduk.txt");
    rename("temp.txt", "data_penduduk.txt");

    if (found) {
        cout << "Data berhasil dihapus!\n";
    } else {
        cout << "Data tidak ditemukan!\n";
    }
}


int main() {
    int pilihan;
    do {
        cout << "\nPilih Menu:\n";
        cout << "=======================================\n";
        cout << "1. Input Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Data\n";
        cout << "4. Edit Data\n";
     cout << "5. Hapus Data\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: inputData(); break;
            case 2: tampilkanData(); break;
            case 3: cariData(); break;
            case 4: editData(); break;
            case 5: hapusData(); break;
            case 6: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 6);

    return 0;
}

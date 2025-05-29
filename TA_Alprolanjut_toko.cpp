#include <iostream>  // Output-Input 
#include <iomanip>   // Rapi (setw)
#include <string>    // Manipulasi data 
#include <algorithm> // Untuk gedekecil
using namespace std;

#define jmlbar 3 // batas max kml barang
#define jmlgud 3 // batas max jml gudang
#define USERNAME "toko"
#define PASSWORD "1234"
#define max_transaksi 100 // batas max transaksi

// nama file dlm program
const char* TOKOTA = "TOKO TA.txt";
const char* STOKTA = "STOK TA.txt";

// simpan barang pake STRUCT
struct barang { //POINTER
    string nama;
    float harga;
};

// simpan transaksi pake STRUCT
struct transaksi {
    string namapembeli;
    string tanggalbeli;
    string namabarang;
    int jumlah;
    float totalharga;
    int gudang;
};

// item barang dgn pointer
barang* dafbar = new barang[jmlbar]{
    {"Laptop", 5000},
    {"Keyboard", 1800},
    {"Mouse", 250}
};

// ARRAY multidim untuk stok barang/ gudang
int stokbarang[jmlbar][jmlgud] = {
    {10, 5, 7},
    {11, 6, 9},
    {8, 12, 15}
};

// Deklar konversi huruf besar kecil
string huruf(string str) {
    for (char &c : str)  //cek
    c = tolower(c); //ubah
    return str; 
}

// simpan all transaksi ARRAY
transaksi daftartransaksi[max_transaksi];
int jumlahtransaksi = 0;

//simpan transaksi sek cuma sesi 1x login AARRAY
transaksi transaksiSesi[max_transaksi];
int jmltransasisesi = 0;

//simpan tgl biar disimpen ke file AARAY
string tanggalStok[jmlbar];

// hapus tampilanlogin
void hilang() {
    system("cls");
}

// login pake fungsi rekursi
bool login(int percobaan = 3) {
    if (percobaan == 0) {
        cout << "Percobaan mencapai batas. Program berakhir.\n";
        return false;
    }
    string username, password;
    cout << "Masukkan Username: ";
    cin >> username;
    cout << "Masukkan Password: ";
    cin >> password;

    if (username == USERNAME && password == PASSWORD) { //login berhasil
        hilang();
        cout << "Selamat Datang di Toko\n";
        return true;
    } else {
        cout << "! Login gagal, Sisa percobaan " << percobaan - 1 << " kali !\n";
        return login(percobaan - 1); //login gagal dan percobban-1
    }
}

// fungsi tampilkan stok barang (menu2)
void stokgudang() {
    cout << "===================================================================\n";
    cout << "| No |     Nama      |   Harga   | Gudang 1 | Gudang 2 | Gudang 3 |\n";
    cout << "===================================================================\n";
    for (int i = 0; i < jmlbar; i++) {
        cout << "| " << setw(2) << right << i + 1 << " "
             << "| " << setw(12) << left << dafbar[i].nama << " "
             << "| Rp" << setw(8) << right << dafbar[i].harga << " "
             << "| " << setw(8) << stokbarang[i][0] << " "
             << "| " << setw(8) << stokbarang[i][1] << " "
             << "| " << setw(8) << stokbarang[i][2] << " |\n";
    }
    cout << "===================================================================\n";
}

// simpan stok barang ke file
void simpanstokfile(const char* namafile) { //FILE
    FILE* file = fopen(namafile, "w"); 

    if (!file) {
        printf("Gagal menyimpan stok ke file.\n"); //ga iso di buka, dapet pesan
        return;
    }
    for (int i = 0; i < jmlbar; i++) {
        fprintf(file, "%d,%d,%d,%s\n",
            stokbarang[i][0], stokbarang[i][1], stokbarang[i][2], tanggalStok[i].c_str());
    }
    fclose(file);
}

// baca stok dari file
void bacastokfile(const char* namafile) { //FILE
    FILE* file = fopen(namafile, "r");
    if (!file) return;
    int i = 0;
    char tanggal[18];
    while (i < jmlbar && fscanf(file, "%d,%d,%d,%18[^\n]\n", //max 18 klo digabung
        &stokbarang[i][0], &stokbarang[i][1], &stokbarang[i][2], tanggal) == 4) {
        tanggalStok[i] = tanggal;
        i++;
    }
    fclose(file);
}

// fungsi tampilkan data transsaksi (menu)
void tampildatatransaksi() { //POINTER
    transaksi* ptr = daftartransaksi; //pointer ke transaksi
    cout << "====================================================================================\n";
    cout << "| No |   Nama Pembeli   |      Tanggal       |   Nama Barang   | Jumlah |   Total  |\n";
    cout << "====================================================================================\n";
    for (int i = 0; i < jumlahtransaksi; i++) {
        cout << "| " << setw(2) << i + 1 << " "
             << "| " << setw(16) << left << (ptr + i)->namapembeli << " "
             << "| " << setw(18) << left << (ptr + i)->tanggalbeli << " "
             << "| " << setw(15) << left << (ptr + i)->namabarang << " "
             << "| " << setw(6) << right << (ptr + i)->jumlah << " "
             << "| ";
        if ((int)(ptr + i)->totalharga == (ptr + i)->totalharga) 
            cout << setw(8) << right << (int)(ptr + i)->totalharga << " |\n"; 
        else
            cout << setw(8) << right << fixed << setprecision(2) << (ptr + i)->totalharga << " |\n";
    }
    cout << "====================================================================================\n";
}

//tampilkan transaksi saat 1x login itu juga
void tampildatatransaksisesi() { //POINTER
    transaksi* ptr = transaksiSesi;
    cout << "====================================================================================\n";
    cout << "| No |   Nama Pembeli   |      Tanggal       |   Nama Barang   | Jumlah |   Total  |\n";
    cout << "====================================================================================\n";
    for (int i = 0; i < jmltransasisesi; i++) {
        cout << "| " << setw(2) << i + 1 << " "
             << "| " << setw(16) << left << (ptr + i)->namapembeli << " "
             << "| " << setw(18) << left << (ptr + i)->tanggalbeli << " "
             << "| " << setw(15) << left << (ptr + i)->namabarang << " "
             << "| " << setw(6) << right << (ptr + i)->jumlah << " "
             << "| ";

        if ((int)(ptr + i)->totalharga == (ptr + i)->totalharga)
            cout << setw(8) << right << (int)(ptr + i)->totalharga << " |\n";
        else
            cout << setw(8) << right << fixed << setprecision(2) << (ptr + i)->totalharga << " |\n";
    }
    cout << "====================================================================================\n";
    if (jmltransasisesi == 0)
        cout << "Belum ada transaksi pada sesi ini.\n";
}

// fungsi tambah stok barang (menu1)
void tambahstok() {
    int idxBarang, idxGudang, jumlahTambah;
    stokgudang();
    cout << "Masukkan nomor barang yang ingin ditambah stoknya: ";
    cin >> idxBarang;

    if (idxBarang < 1 || idxBarang > jmlbar) {
        cout << "Nomor barang tidak valid!\n";
        return;
    }

    cout << "Pilih gudang (1-3): ";
    cin >> idxGudang;
    if (idxGudang < 1 || idxGudang > jmlgud) {
        cout << "Nomor gudang tidak valid!\n";
        return;
    }

    cout << "Masukkan jumlah stok yang ingin ditambah: ";
    cin >> jumlahTambah;
    if (jumlahTambah < 1) {
        cout << "Jumlah harus lebih dari 0!\n";
        return;
    }
    stokbarang[idxBarang - 1][idxGudang - 1] += jumlahTambah;

    // Input tanggal tambah stok
    int tgl, thn;
    string bln;
    cout << "Tanggal stok ditambah\n";
    cout << "Tanggal (angka): ";
    cin >> tgl;
    cout << "Bulan (huruf): ";
    cin >> bln;
    cout << "Tahun (angka): ";
    cin >> thn;
    tanggalStok[idxBarang - 1] = to_string(tgl) + " " + bln + " " + to_string(thn);

    cout << "Stok berhasil ditambah.\n";
    simpanstokfile(STOKTA);
    stokgudang();
}

// fungsi cari nama dan gudang (menu4) SEARCH
void caridata() {
    while (true) { 
        char opsi;
        cout << "\n========= SUB MENU CARI =========\n";
        cout << "a. Cari berdasarkan Nama Barang\n";
        cout << "b. Cari berdasarkan Gudang\n";
        cout << "c. Kembali ke Menu Utama\n";
          cout << "===============================\n";
        cout << "Pilihan (a/b/c): ";
        cin >> opsi;
        opsi = tolower(opsi); //besar kecil oke

        if (opsi == 'a') {
            cout << endl;
            string keyword;
            bool statuscari = false;

            // Validasi input nama barang harus huruf 
            do {
                cout << "Masukkan nama barang yang ingin dicari: ";
                cin.ignore();
                getline(cin, keyword);
                bool valid = !keyword.empty();
                for (char c : keyword) {
                    if (!isalpha(c) && c != ' ') {
                        valid = false;
                        break;
                    }
                }
                if (!valid) {
                    cout << "Input hanya boleh huruf, silakan ulangi!\n";
                }
                if (valid) break;
            } while (true);

            cout << "Hasil Pencarian '" << keyword << "':\n";
            cout << "===================================================================\n";
            cout << "| No |     Nama     |    Harga   | Gudang 1 | Gudang 2 | Gudang 3 |\n";
            cout << "===================================================================\n";

            for (int i = 0; i < jmlbar; i++) {
                if (huruf(dafbar[i].nama).find(huruf(keyword)) != string::npos) {
                    cout << "| " << setw(2) << right << i + 1 << " "
                         << "| " << setw(12) << left << dafbar[i].nama << " "
                         << "| Rp" << setw(8) << right << dafbar[i].harga << " "
                         << "| " << setw(8) << stokbarang[i][0] << " "
                         << "| " << setw(8) << stokbarang[i][1] << " "
                         << "| " << setw(8) << stokbarang[i][2] << " |\n";
                    statuscari = true;
                }
            }
            if (!statuscari) cout << "Barang tidak ditemukan.\n";
            cout << "===================================================================\n";
        } else if (opsi == 'b') {
            cout << endl;
            int gudang;
            bool statuscari = false;

            // Validasi input nomor gudang harus angka 1-3
            while (true) {
                cout << "Masukkan nomor gudang (1-3): ";
                cin >> gudang;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Input harus berupa angka antara 1-3!\n";
                    continue;
                }
                if (gudang < 1 || gudang > 3) {
                    cout << "Gudang tidak valid! Masukkan angka 1-3.\n";
                    continue;
                }
                break;
            }

            cout << "Barang yang tersedia di gudang " << gudang << ":\n";
            cout << "=============================================\n";
            cout << "| No |     Nama     |    Harga   | Gudang " << gudang << " |\n";
            cout << "=============================================\n";

            for (int i = 0; i < jmlbar; i++) {
                if (stokbarang[i][gudang - 1] > 0) {
                    cout << "| " << setw(2) << right << i + 1 << " "
                         << "| " << setw(12) << left << dafbar[i].nama << " "
                         << "| Rp" << setw(8) << right << dafbar[i].harga << " "
                         << "| " << setw(8) << stokbarang[i][gudang - 1] << " |\n";
                    statuscari = true;
                }
            }
            if (!statuscari) cout << "Tidak ada barang di gudang " << gudang << "\n";
            cout << "=============================================\n";
        } else if (opsi == 'c') {
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}

// buat itung total harga
float hitungtotalharga() {
    float total = 0;
    for (int i = 0; i < jumlahtransaksi; i++) {
        total += daftartransaksi[i].totalharga;
    }
    return total;
}

// simpan transaksi ke file
void simpantransaksifile(const char* namafile) { //FILE
    FILE* file = fopen(namafile, "w");

    if (!file) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }
    for (int i = 0; i < jumlahtransaksi; i++) {
        fprintf(file, "%s,%s,%s,%d,%.2f,%d\n",
            daftartransaksi[i].namapembeli.c_str(),
            daftartransaksi[i].tanggalbeli.c_str(),
            daftartransaksi[i].namabarang.c_str(),
            daftartransaksi[i].jumlah,
            daftartransaksi[i].totalharga,
            daftartransaksi[i].gudang
        );
    }
    fclose(file);
    printf("Transaksi berhasil disimpan ke file.\n");
}

//baca transaksi dari file toko 
void ambiltransaksifile(const char* namafile) { //FILE
    FILE* file = fopen(namafile, "r");
    if (!file) return;
    jumlahtransaksi = 0;
    char namapembeli[20], tanggalbeli[18], namabarang[10];
    int jumlah, gudang;
    float totalharga;
    while (jumlahtransaksi < max_transaksi &&
        fscanf(file, "%18[^,],%18[^,],%18[^,],%d,%f,%d\n",
            namapembeli, tanggalbeli, namabarang, &jumlah, &totalharga, &gudang) == 6) {
        daftartransaksi[jumlahtransaksi].namapembeli = namapembeli;
        daftartransaksi[jumlahtransaksi].tanggalbeli = tanggalbeli;
        daftartransaksi[jumlahtransaksi].namabarang = namabarang;
        daftartransaksi[jumlahtransaksi].jumlah = jumlah;
        daftartransaksi[jumlahtransaksi].totalharga = totalharga;
        daftartransaksi[jumlahtransaksi].gudang = gudang;
        jumlahtransaksi++;
    }
    fclose(file);
}

//validasi nama hanya huruf spasi
bool validNama(const string& nama) {
    for (char c : nama) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return !nama.empty();
}

// fungsi beli barang dgn input data (menu5)
void belibarang() {
    int pilihan, jumlah, gudang;
    char lanjut;
    string namapembeli, tanggalbeli;

    // Input nama pembeli hanya sekali di awal transaksi
    do {
        cout << "Masukkan nama pembeli: ";
        cin.ignore();
        getline(cin, namapembeli);
        if (!validNama(namapembeli)) {
            cout << "Nama hanya boleh huruf dan spasi, tidak boleh kosong!\n";
        }
    } while (!validNama(namapembeli));

    int tgl, thn;
    string bln;
    cout << "Tanggal beli\n";
    cout << "Tanggal (angka): ";
    cin >> tgl;
    cout << "Bulan (huruf): ";
    cin >> bln;
    cout << "Tahun (angka): ";
    cin >> thn;
    tanggalbeli = to_string(tgl) + " " + bln + " " + to_string(thn); // disambung 

    do {
        stokgudang();
        cout << "Masukkan nomor barang yang ingin dibeli: ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > jmlbar) { // ga valid
            cout << "Pilihan tidak valid!\n";
            continue;
        }

        cout << "Pilih gudang (1-3): ";
        cin >> gudang;
        if (gudang < 1 || gudang > 3) {
            cout << "Gudang tidak valid!\n";
            continue;
        }

        cout << "Masukkan jumlah yang ingin dibeli: ";
        cin >> jumlah;

        if (jumlah > stokbarang[pilihan - 1][gudang - 1]) { // stok kurang
            cout << "Stok tidak mencukupi di gudang " << gudang << "!\n";
        } else {
            stokbarang[pilihan - 1][gudang - 1] -= jumlah; 
            float hargabarang = jumlah * dafbar[pilihan - 1].harga; 

            if (jumlahtransaksi < max_transaksi) { // cek jlm transaksi
                transaksi t = {namapembeli, tanggalbeli, dafbar[pilihan - 1].nama, jumlah, hargabarang, gudang - 1};
                daftartransaksi[jumlahtransaksi++] = t;

                // Tambahkan ke array transaksi sesi
                if (jmltransasisesi < max_transaksi)
                    transaksiSesi[jmltransasisesi++] = t;
            } else {
                cout << "Batas maksimal transaksi! Tidak bisa menambahkan transaksi baru.\n";
            }
        }

        cout << "Ingin membeli barang lain? (y/n): ";
        cin >> lanjut;
        cout << endl;

    } while (lanjut == 'y' || lanjut == 'Y'); //gede kecil ga ngaruh
    cout << "------------------------------------------\n";
    cout << "Pembelian berhasil!\n";
    cout << "Total yang harus dibayar: Rp" << hitungtotalharga() << "\n"; //input lebih dari 1x tetep bisa
    cout << "------------------------------------------\n";
    simpantransaksifile(TOKOTA); // simpen ke file
    simpanstokfile(STOKTA); 
}

// tuker posisi klo dah dibandingkan pake bubble
void posisi(transaksi &a, transaksi &b) {
    transaksi simpansementara = a; //disimpan
    a = b; //a diganti b
    b = simpansementara; // b diisi a
}

// cara pengurutan pake bubble = dibandingkan SORTING
void bubblesort(int mode) {
    for (int i = 0; i < jumlahtransaksi - 1; i++) {
        for (int j = 0; j < jumlahtransaksi - i - 1; j++) {
            bool tukar = false;
            if (mode == 1 && daftartransaksi[j].jumlah > daftartransaksi[j + 1].jumlah) //kecil ke besar
                tukar = true;
            else if (mode == 2 && daftartransaksi[j].totalharga < daftartransaksi[j + 1].totalharga) //besar ke kecil
                tukar = true;
            else if (mode == 3 && daftartransaksi[j].namabarang > daftartransaksi[j + 1].namabarang) //a-z
                tukar = true;
            if (tukar)
                posisi(daftartransaksi[j], daftartransaksi[j + 1]);
        }
    }
}

// fungsi urutkan pake bubble dari jumlah beli, total beli, nama barang (menu6)
void urutkandata() {
    while (true) {
        ambiltransaksifile(TOKOTA); // ambil data terbaru
        if (jumlahtransaksi == 0) { 
            cout << "Belum ada transaksi yang tercatat.\n";
            return;
        }

        char opsi;
        cout << "\n===== SUB MENU URUTKAN =====\n";
        cout << "a. Jumlah Pembelian (asc)\n";
        cout << "b. Total Transaksi (des)\n";
        cout << "c. Nama Barang (abjad)\n";
        cout << "d. Kembali ke Menu Utama\n";
         cout << "===========================\n";
        cout << "Opsi (a/b/c/d): ";
        cin >> opsi;
        opsi = tolower(opsi);

        if (opsi == 'a') {
            bubblesort(1);
            cout << "Data setelah diurutkan berdasarkan jumlah pembelian (asc):\n";
            tampildatatransaksi();
        } else if (opsi == 'b') {
            bubblesort(2);
            cout << "Data setelah diurutkan berdasarkan total transaksi (des):\n";
            tampildatatransaksi();
        } else if (opsi == 'c') {
            bubblesort(3);
            cout << "Data setelah diurutkan berdasarkan nama barang (A-Z):\n";
            tampildatatransaksi();
        } else if (opsi == 'd') {
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}

// fungsi edit nama pembeli dan tanggal beli (menu7)
void edittransaksi() { //POINTER
    if (jumlahtransaksi == 0) {
        cout << "Belum ada transaksi untuk diedit.\n";
        return;
    }

    int no;
    tampildatatransaksi();
    cout << "Masukkan nomor transaksi yang ingin diedit: ";
    cin >> no;
    if (no < 1 || no > jumlahtransaksi) { 
        cout << "Nomor transaksi tidak valid!\n";
        return;
    }

    transaksi* t = & daftartransaksi[no - 1]; //pointer ke transaksi

    cin.ignore();
    cout << "Nama Pembeli lama   : " << t-> namapembeli << endl;
    cout << "Nama Pembeli baru   : ";
    getline(cin, t->namapembeli);

    cout << "Tanggal lama        : " << t-> tanggalbeli << endl;
    cout << "Tanggal baru (d-m-y): ";
    getline(cin, t->tanggalbeli);

    cout << "Data transaksi berhasil diedit.\n";
    simpantransaksifile(TOKOTA);
    tampildatatransaksi();
}

// fungsi hapus transaksi dgn pilih no (menu8)
void hapustransaksi() {
    if (jumlahtransaksi == 0) {
        cout << "Belum ada transaksi untuk dihapus.\n";
        return;
    }
    int no;
    tampildatatransaksi();
    cout << "Masukkan nomor transaksi yang ingin dihapus: ";
    cin >> no;

    if (no < 1 || no > jumlahtransaksi) {
        cout << "Nomor transaksi tidak valid!\n";
        return;
    }

    transaksi t = daftartransaksi[no - 1]; //ambil data
    int idxBarang = -1; //cari
    for (int i = 0; i < jmlbar; i++) { 
        if (dafbar[i].nama == t.namabarang) { // cek
            idxBarang = i; 
            break;
        }
    }

    if (idxBarang != -1) {
        stokbarang[idxBarang][t.gudang] += t.jumlah; // pake gudang asal
        simpanstokfile(STOKTA);
    }

    for (int i = no - 1; i < jumlahtransaksi - 1; i++) { 
        daftartransaksi[i] = daftartransaksi[i + 1]; 
    }
    jumlahtransaksi--; // hapus yg dipilih
    cout << "Transaksi berhasil dibatalkan dan stok barang kembali/bertambah sesuai yang dibeli.\n";
    simpantransaksifile(TOKOTA); // simpen 
    tampildatatransaksi();
}

// untuk baca file transaksi
void bacafiletransaksi(const char* namafile) { //FILE
    FILE* file = fopen(namafile, "r");
    if (!file) {
        printf("File transaksi tidak ditemukan.\n");
        return;
    }

    int no = 1;
    char namapembeli[20], tanggalbeli[18], namabarang[10];
    int jumlah, gudang;
    float total;
    printf("================================================================================\n");
    printf("| No |   Nama Pembeli   |    Tanggal     |   Nama Barang   | Jumlah |   Total  |\n");
    printf("================================================================================\n");
    while (fscanf(file, "%18[^,],%18[^,],%18[^,],%d,%f,%d\n",
        namapembeli, tanggalbeli, namabarang, &jumlah, &total, &gudang) == 6) {
        printf("| %2d | %-16s | %-14s | %-15s | %6d | %8.2f |\n", //ukuran tabel
            no++, namapembeli, tanggalbeli, namabarang, jumlah, total);
    }
    printf("================================================================================\n");
    fclose(file);
}

// untuk tampilkan isi file stok
void bacaFileStok(const char* namafile) { //FILE
    FILE* file = fopen(namafile, "r");
    if (!file) {
        printf("File stok tidak ditemukan.\n");
        return;
    }
    int no = 1, s1, s2, s3;
    char tgl[18];
    printf("=========================================================================\n");
    printf("| No |     Nama     | Gudang 1 | Gudang 2 | Gudang 3 |  Tanggal Tambah  |\n");
    printf("=========================================================================\n");
    while (no <= jmlbar && fscanf(file, "%d,%d,%d,%18[^\n]\n", &s1, &s2, &s3, tgl) == 4) {
        printf("| %2d | %-12s | %8d | %8d | %8d | %-16s |\n",
            no, dafbar[no-1].nama.c_str(), s1, s2, s3, tgl);
        no++;
    }
    printf("=========================================================================\n");
    fclose(file);
}

// fungsi buka file toko dan stok (menu9)
void bukafile() {
    while (true) {
        char opsi;
        cout << "\n======= SUB MENU BACA FILE =======\n";
        cout << "a. Lihat TOKO TA.txt (Transaksi)\n";
        cout << "b. Lihat STOK TA.txt (Stok Barang)\n";
        cout << "c. Kembali ke Menu Utama\n";
        cout << "==================================\n";
        cout << "Pilihan (a/b/c): ";
        cin >> opsi;
        opsi = tolower(opsi);
        if (opsi == 'a') {
            bacafiletransaksi(TOKOTA);
        } else if (opsi == 'b') {
            bacaFileStok(STOKTA);  
        } else if (opsi == 'c') {
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
}

// menu utama
int main() {
    bacastokfile(STOKTA); 
    ambiltransaksifile(TOKOTA); //ambil data

    if (!login()) return 0;
    jmltransasisesi = 0; // reset transaksi sesi

    int pilihan;
    do {
        cout << "\n===================================\n";
        cout << "|           MENU UTAMA            |\n";
        cout << "===================================\n";
        cout << "| 1. Tambah Stok Barang           |\n";
        cout << "| 2. Tampilkan Stok Barang        |\n";
        cout << "| 3. Tampilkan Transaksi Sesi Ini |\n";
        cout << "| 4. Cari Data                    |\n";
        cout << "| 5. Beli Barang                  |\n";
        cout << "| 6. Urutkan Transaksi            |\n";
        cout << "| 7. Edit Data Transaksi          |\n";
        cout << "| 8. Hapus Data Transaksi         |\n";
        cout << "| 9. Baca/Buka File Transaksi     |\n";
        cout << "| 10. Keluar                      |\n";
        cout << "===================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahstok(); break;
            case 2: stokgudang(); break;
            case 3: tampildatatransaksisesi(); break;
            case 4: caridata(); break;
            case 5: belibarang(); break;
            case 6: urutkandata(); break;
            case 7: edittransaksi(); break;
            case 8: hapustransaksi(); break;
            case 9: bukafile(); break;
            case 10: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 10);

    return 0;
}

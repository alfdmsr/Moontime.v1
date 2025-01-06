#include <stdio.h>
#include <string.h>
#include "1_inputData.h"

#define MAX_DATA 100

typedef struct {
    int id;
    char namaPengguna[50];
    char tanggalAwal[11];
    char tanggalAkhir[11];
} Menstruasi;

Menstruasi siklus[MAX_DATA];
int count = 0;

// Deklarasi fungsi
void inputDataMenu();
void tambahkanDataSiklus();
void lihatDataSiklus();
void sortSiklusDariId();
void simpanSiklusPadaFile();
void bacaSiklusDariFile();
void perbaruiDataSiklus();
void hapusDataSiklus();
void cariSiklusMelaluiId();

// Fungsi untuk menambahkan data
void tambahkanDataSiklus() {
    if (count >= MAX_DATA) {
        printf("Data penuh!\n");
        return;
    }

    printf("Masukkan ID: ");
    scanf("%d", &siklus[count].id);
    printf("Masukkan Nama Pengguna: ");
    scanf("%s", siklus[count].namaPengguna);
    printf("Masukkan Tanggal Mulai (YYYY-MM-DD): ");
    scanf("%s", siklus[count].tanggalAwal);
    printf("Masukkan Tanggal Selesai (YYYY-MM-DD): ");
    scanf("%s", siklus[count].tanggalAkhir);

    count++;
    printf("Data berhasil ditambahkan!\n");
    simpanSiklusPadaFile(); // Simpan data setelah menambah
}

// Fungsi untuk menampilkan data
void lihatDataSiklus() {
    if (count == 0) {
        printf("Tidak ada data siklus.\n");
        return;
    }

    sortSiklusDariId(); // Urutkan data sebelum ditampilkan
    printf("Data Siklus Menstruasi:\n");
    printf("ID\tNama Pengguna\tTanggal Mulai\tTanggal Selesai\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%s\t%s\n", siklus[i].id, siklus[i].namaPengguna, siklus[i].tanggalAwal, siklus[i].tanggalAkhir);
    }
}

// Fungsi untuk mengurutkan data berdasarkan ID
void sortSiklusDariId() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (siklus[j].id > siklus[j + 1].id) {
                Menstruasi temp = siklus[j];
                siklus[j] = siklus[j + 1];
                siklus[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk mencari data berdasarkan ID
void cariSiklusMelaluiId() {
    int id, found = 0;
    printf("Masukkan ID yang dicari: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (siklus[i].id == id) {
            printf("Data ditemukan:\n");
            printf("ID: %d\n", siklus[i].id);
            printf("Nama Pengguna: %s\n", siklus[i].namaPengguna);
            printf("Tanggal Mulai: %s\n", siklus[i].tanggalAwal);
            printf("Tanggal Selesai: %s\n", siklus[i].tanggalAkhir);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi untuk menyimpan data ke file
void simpanSiklusPadaFile() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "ID: %d\n", siklus[i].id);
        fprintf(file, "Nama Pengguna: %s\n", siklus[i].namaPengguna);
        fprintf(file, "Tanggal Mulai: %s\n", siklus[i].tanggalAwal);
        fprintf(file, "Tanggal Selesai: %s\n", siklus[i].tanggalAkhir);
        fprintf(file, "\n");
    }

    fclose(file);
}

// Fungsi untuk membaca data dari file
void bacaSiklusDariFile() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca!\n");
        return;
    }

    count = 0;
    while (fscanf(file, "ID: %d\n", &siklus[count].id) != EOF) {
        fscanf(file, "Nama Pengguna: %s\n", siklus[count].namaPengguna);
        fscanf(file, "Tanggal Mulai: %s\n", siklus[count].tanggalAwal);
        fscanf(file, "Tanggal Selesai: %s\n", siklus[count].tanggalAkhir);
        fscanf(file, "\n");
        count++;
    }

    fclose(file);
}

// Fungsi untuk memperbarui data
void perbaruiDataSiklus() {
    int id, found = 0;
    printf("Masukkan ID yang akan diupdate: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (siklus[i].id == id) {
            printf("Masukkan Tanggal Mulai baru (YYYY-MM-DD): ");
            scanf("%s", siklus[i].tanggalAwal);
            printf("Masukkan Tanggal Selesai baru (YYYY-MM-DD): ");
            scanf("%s", siklus[i].tanggalAkhir);
            printf("Data berhasil diupdate.\n");
            found = 1;
            simpanSiklusPadaFile(); // Simpan data setelah mengupdate
            break;
        }
    }

    if (!found) {
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi untuk menghapus data
void hapusDataSiklus() {
    int id, found = 0;
    printf("Masukkan ID yang akan dihapus: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (siklus[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                siklus[j] = siklus[j + 1];
            }
            count--;
            printf("Data berhasil dihapus.\n");
            found = 1;
            simpanSiklusPadaFile(); // Simpan data setelah menghapus
            break;
        }
    }

    if (!found) {
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi utama
void inputDataMenu() {
    int choice;

    bacaSiklusDariFile(); // Baca data dari file saat aplikasi dimulai

    do {
        printf("\n+-------------------------------------------+\n");
        printf("|     Menu Pemantauan Siklus Menstruasi     |\n");
        printf("|===========================================|\n");
        printf("| 1. Tambah Data Siklus Menstruasi          |\n");
        printf("| 2. Lihat Data Siklus Menstruasi           |\n");
        printf("| 3. Cari Data Siklus Menstruasi            |\n");
        printf("| 4. Ubah Data Siklus Menstruasi            |\n");
        printf("| 5. Hapus Data Siklus Mentruasi            |\n");
        printf("| 0. Keluar                                 |\n");
        printf("+-------------------------------------------+\n");
        printf("Pilihan Anda (0-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                tambahkanDataSiklus();
                break;
            case 2:
                lihatDataSiklus();
                break;
            case 3:
                cariSiklusMelaluiId();
                break;
            case 4:
                perbaruiDataSiklus();
                break;
            case 5:
                hapusDataSiklus();
                break;
            case 0:
                printf("==== Keluar dari Menu Pemnatauan Siklus Mentruasi ====.\n");
                break;
            default:
                printf("Pilihan tidak valid! Silakan pilih lagi!\n");
        }
    } while (choice != 0);
}
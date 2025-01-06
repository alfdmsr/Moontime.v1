#include <stdio.h>
#include <string.h>
#include "3_prediksiPeriodeSelanjutnya.h"

#define MAX_DATA 100

typedef struct {
    int id;
    char startDate[11];
    char endDate[11];
    int duration; // Durasi siklus dalam hari
} PrediksiPeriode;

PrediksiPeriode siklus[MAX_DATA];
int jumlahDataPeriode = 0;

// Deklarasi fungsi
void prediksiPeriodeMenu();
void tambahPrediksiPeriode();
void lihatPrediksiPeriode();
void urutkanPrediksiPeriodeBerdasarkanID();
void simpanPrediksiPeriodeKeFile();
void bacaPrediksiPeriodeDariFile();
void ubahPrediksiPeriode();
void hapusPrediksiPeriode();
float hitungRataRataDurasi();
void prediksiPeriodeSelanjutnya();


// Fungsi untuk menambahkan data prediksi periode
void tambahPrediksiPeriode() {
    if (jumlahDataPeriode >= MAX_DATA) {
        printf("Data penuh! Tidak dapat menambahkan data baru.\n");
        return;
    }

    printf("Masukkan ID siklus:");
    scanf("%d", &siklus[jumlahDataPeriode].id);
    printf("Masukkan Tanggal Mulai Siklus (YYYY-MM-DD): ");
    scanf("%s", siklus[jumlahDataPeriode].startDate);
    printf("Masukkan Tanggal Selesai Siklus (YYYY-MM-DD): ");
    scanf("%s", siklus[jumlahDataPeriode].endDate);
    printf("Masukkan Durasi Siklus (dalam hari): ");
    scanf("%d", &siklus[jumlahDataPeriode].duration);

    jumlahDataPeriode++;
    simpanPrediksiPeriodeKeFile();
    printf("Data berhasil ditambahkan!\n");
}

// Fungsi untuk melihat semua data siklus meenstruasi
void lihatPrediksiPeriode() {
    if (jumlahDataPeriode == 0) {
        printf("Tidak ada data siklus menstruasi.\n");
        return;
    }

    urutkanPrediksiPeriodeBerdasarkanID();
    printf("Data Siklus Menstruasi:\n");
    for (int i = 0; i < jumlahDataPeriode; i++) {
        printf("ID: %d\n", siklus[i].id);
        printf("Tanggal Mulai: %s\n", siklus[i].startDate);
        printf("Tanggal Selesai: %s\n", siklus[i].endDate);
        printf("Durasi: %d\n", siklus[i].duration);
        printf("\n");
    }
}

// Fungsi untuk mengurutkan data siklus berdasarkan ID (bubble sort)
void urutkanPrediksiPeriodeBerdasarkanID() {
    for (int i = 0; i < jumlahDataPeriode - 1; i++) {
        for (int j = 0; j < jumlahDataPeriode - i - 1; j++) {
            if (siklus[j].id > siklus[j + 1].id) {
                PrediksiPeriode temp = siklus[j];
                siklus[j] = siklus[j + 1];
                siklus[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk menghitung rata-rata durasi siklus
float hitungRataRataDurasi() {
    if (jumlahDataPeriode == 0) return 0;

    int totalDurasi = 0;
    for (int i = 0; i < jumlahDataPeriode; i++) {
        totalDurasi += siklus[i].duration;
    }
    return (float)totalDurasi / jumlahDataPeriode;
}

// Fungsi untuk memprediksi periode menstruasi selanjutnya
void prediksiPeriodeSelanjutnya() {
    if (jumlahDataPeriode == 0) {
        printf("Tidak ada data untuk memprediksi.\n");
        return;
    }

    float rataRataDurasi = hitungRataRataDurasi();
    printf("Rata-rata durasi siklus: %.2f hari\n", rataRataDurasi);
    printf("Prediksi periode berikutnya berdasarkan data terbaru: +%.0f hari dari siklus terakhir.\n", rataRataDurasi);
}

// Fungsi untuk menyimpan data siklus ke file
void simpanPrediksiPeriodeKeFile() {
    FILE *file = fopen("prediksi_periode.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    for (int i = 0; i < jumlahDataPeriode; i++) {
        fprintf(file, "ID: %d\n", siklus[i].id);
        fprintf(file, "Tanggal Mulai: %s\n", siklus[i].startDate);
        fprintf(file, "Tanggal Selesai: %s\n", siklus[i].endDate);
        fprintf(file, "Durasi: %d\n", siklus[i].duration);
        fprintf(file, "\n");
    }

    fclose(file);
}

// Fungsi untuk membaca data siklus dari file
void bacaPrediksiPeriodeDariFile() {
    FILE *file = fopen("prediksi_periode.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca data!\n");
        return;
    }

    jumlahDataPeriode = 0;
    while (fscanf(file, "ID: %d\n", &siklus[jumlahDataPeriode].id) != EOF) {
        fscanf(file, "Tanggal Mulai: %s\n", siklus[jumlahDataPeriode].startDate);
        fscanf(file, "Tanggal Selesai: %s\n", siklus[jumlahDataPeriode].endDate);
        fscanf(file, "Durasi: %d\n", &siklus[jumlahDataPeriode].duration);
        jumlahDataPeriode++;
    }

    fclose(file);
}

// Fungsi untuk memperbarui data siklus 
void ubahPrediksiPeriode() {
    int id, ditemukan = 0;
    printf("Masukkan ID data yang ingin diubah: ");
    scanf("%d", &id);

    for (int i = 0; i < jumlahDataPeriode; i++) {
        if (siklus[i].id == id) {
            printf("Masukkan Tanggal Mulai Baru (YYYY-MM-DD): ");
            scanf("%s", siklus[i].startDate);
            printf("Masukkan Tanggal Selesai Baru (YYYY-MM-DD): ");
            scanf("%s", siklus[i].endDate);
            printf("Masukkan Durasi Baru (dalam hari): ");
            scanf("%d", &siklus[i].duration);
            printf("Data berhasil diperbarui!\n");
            ditemukan = 1;
            simpanPrediksiPeriodeKeFile(); // Simpan data setelah mengubah data
            break;
        }
    }
    if (!ditemukan) {
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi untuk menghapus data siklus
void hapusPrediksiPeriode() {
    int id, ditemukan = 0;
    printf("Masukkan ID data yang ingin dihapus: ");
    scanf("%d", &id);

    for (int i = 0; i < jumlahDataPeriode; i++) {
        if (siklus[i].id == id) {
            for (int j = i; j < jumlahDataPeriode - 1; j++) {
                siklus[j] = siklus[j + 1];
            }
            jumlahDataPeriode--;
            printf("Data berhasil dihapus!\n");
            ditemukan = 1;
            simpanPrediksiPeriodeKeFile(); // Simpan data setelah menghapus data
            break;
        }
    }
    if (!ditemukan) {
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi utama
void prediksiPeriodeMenu() {
    int choice;

    bacaPrediksiPeriodeDariFile(); // Baca data dari file saat aplikasi dimulai
    do {
        printf("\n+------------------------------------------+\n");
        printf("|     Menu Prediksi Periode Menstruasi     |\n");
        printf("|------------------------------------------|\n");
        printf("| 1. Tambah Data Siklus                    |\n");
        printf("| 2. Lihat Semua Data Siklus               |\n");
        printf("| 3. Prediksi Periode Berikutnya           |\n");
        printf("| 4. Ubah Data Siklus                      |\n");
        printf("| 5. Hapus Data Siklus                     |\n");
        printf("| 0. Keluar                                |\n");
        printf("+------------------------------------------+\n");
        printf("Pilihan Anda (0-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                tambahPrediksiPeriode();
                break;
            case 2:
                lihatPrediksiPeriode();
                break;
            case 3:
                prediksiPeriodeSelanjutnya();
                break;
            case 4:
                ubahPrediksiPeriode();
                break;
            case 5:
                hapusPrediksiPeriode();
                break;
            case 0:
                printf("==== Keluar dari Menu Prediksi Periode Selanjutnya! ====\n");
                break;
            default:
                printf("Pilihan tidak valid! Silakan pilih lagi!\n");
        }
    } while (choice != 0);
}

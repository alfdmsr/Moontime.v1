#include <stdio.h>
#include <string.h>
#include "5_statistik.h"

#define MAX_DATA 100

typedef struct {
    int id;
    char startDate[11];
    char endDate[11];
    int duration; // Durasi siklus dalam hari
} Menstruation;

Menstruation cycles[MAX_DATA];
int dataStatistik = 0;

// Deklarasi fungsi
void tambahSiklus();
void lihatSiklus();
void urutkanSiklusDenganId();
void lihatStatistics();
void simpanStatsToFile();
void readStatsFromFile();
void ubahSiklus();
void hapusSiklus();

// Fungsi untuk menambahkan data
void tambahSiklus() {
    if (dataStatistik >= MAX_DATA) {
        printf("Data penuh!\n");
        return;
    }

    printf("Masukkan ID: ");
    scanf("%d", &cycles[dataStatistik].id);
    printf("Masukkan Tanggal Mulai (YYYY-MM-DD): ");
    scanf("%s", cycles[dataStatistik].startDate);
    printf("Masukkan Tanggal Selesai (YYYY-MM-DD): ");
    scanf("%s", cycles[dataStatistik].endDate);
    printf("Masukkan Durasi Siklus (dalam hari): ");
    scanf("%d", &cycles[dataStatistik].duration);

    dataStatistik++;
    simpanStatsToFile();
    printf("Data berhasil ditambahkan!\n");
}

// Fungsi untuk menampilkan statistik siklus menstruasi
void lihatStatistics() {
    if (dataStatistik == 0) {
        printf("Tidak ada data siklus untuk ditampilkan.\n");
        return;
    }

    int totalDuration = 0, minDuration = cycles[0].duration, maxDuration = cycles[0].duration;

    for (int i = 0; i < dataStatistik; i++) {
        totalDuration += cycles[i].duration;
        if (cycles[i].duration < minDuration) {
            minDuration = cycles[i].duration;
        }
        if (cycles[i].duration > maxDuration) {
            maxDuration = cycles[i].duration;
        }
    }

    float averageDuration = (float)totalDuration / dataStatistik;

    printf("\nStatistik Siklus Menstruasi:\n");
    printf("Jumlah Siklus: %d\n", dataStatistik);
    printf("Durasi Siklus Terpendek: %d hari\n", minDuration);
    printf("Durasi Siklus Terpanjang: %d hari\n", maxDuration);
    printf("Rata-rata Durasi Siklus: %.2f hari\n", averageDuration);
}

// Fungsi untuk melihat data siklus
void lihatSiklus() {
    if (dataStatistik == 0) {
        printf("Tidak ada data siklus.\n");
        return;
    }

    urutkanSiklusDenganId();
    printf("Data Siklus Menstruasi:\n");
    printf("ID\tTanggal Mulai\tTanggal Selesai\tDurasi (hari)\n");
    for (int i = 0; i < dataStatistik; i++) {
        printf("%d\t%s\t%s\t%d\n", cycles[i].id, cycles[i].startDate, cycles[i].endDate, cycles[i].duration);
    }
}

// Fungsi untuk mengurutkan data berdasarkan ID
void urutkanSiklusDenganId() {
    for (int i = 0; i < dataStatistik - 1; i++) {
        for (int j = 0; j < dataStatistik - i - 1; j++) {
            if (cycles[j].id > cycles[j + 1].id) {
                Menstruation temp = cycles[j];
                cycles[j] = cycles[j + 1];
                cycles[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk menyimpan data ke file
void simpanStatsToFile() {
    FILE *file = fopen("statistik.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    for (int i = 0; i < dataStatistik; i++) {
        fprintf(file, "ID: %d\n", cycles[i].id);
        fprintf(file, "Tanggal Mulai: %s\n", cycles[i].startDate);
        fprintf(file, "Tanggal Selesai: %s\n", cycles[i].endDate);
        fprintf(file, "Durasi: %d\n", cycles[i].duration);
        fprintf(file, "\n");
    }

    fclose(file);
}

// Fungsi untuk membaca data dari file
void readStatsFromFile() {
    FILE *file = fopen("statistik.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca!\n");
        return;
    }

    dataStatistik = 0;
    while (fscanf(file, "ID: %d\n", &cycles[dataStatistik].id) != EOF) {
        fscanf(file, "Tanggal Mulai: %s\n", cycles[dataStatistik].startDate);
        fscanf(file, "Tanggal Selesai: %s\n", cycles[dataStatistik].endDate);
        fscanf(file, "Durasi: %d\n", &cycles[dataStatistik].duration);
        dataStatistik++;
    }

    fclose(file);
}

// Fungsi untuk memperbarui data
void ubahSiklus() {
    int id, found = 0;
    printf("Masukkan ID yang akan diupdate: ");
    scanf("%d", &id);

    for (int i = 0; i < dataStatistik; i++) {
        if (cycles[i].id == id) {
            printf("Masukkan Tanggal Mulai baru (YYYY-MM-DD): ");
            scanf("%s", cycles[i].startDate);
            printf("Masukkan Tanggal Selesai baru (YYYY-MM-DD): ");
            scanf("%s", cycles[i].endDate);
            printf("Masukkan Durasi baru (dalam hari): ");
            scanf("%d", &cycles[i].duration);
            printf("Data berhasil diupdate.\n");
            found = 1;
            simpanStatsToFile(); // Simpan data setelah mengupdate
            break;
        }
    }

    if (!found) {
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi untuk menghapus data
void hapusSiklus() {
    int id, found = 0;
    printf("Masukkan ID yang akan dihapus: ");
    scanf("%d", &id);

    for (int i = 0; i < dataStatistik; i++) {
        if (cycles[i].id == id) {
            for (int j = i; j < dataStatistik - 1; j++) {
                cycles[j] = cycles[j + 1];
            }
            dataStatistik--;
            printf("Data berhasil dihapus.\n");
            found = 1;
            simpanStatsToFile(); // Simpan data setelah menghapus
            break;
        }
    }

    if (!found) {
        printf("Data dengan ID %d tidak ditemukan.\n", id);
    }
}

// Fungsi utama9
void statistikMenu() {
    int choice;

    do {
        printf("\n+------------------------------------------+\n");
        printf("|     Menu Statistik Siklus Menstruasi     |\n");
        printf("|==========================================|\n");
        printf("| 1. Tambah Data Siklus                    |\n");
        printf("| 2. Lihat Data Siklus                     |\n");
        printf("| 3. Lihat Statistik Siklus                |\n");
        printf("| 4. Ubah Data Siklus                      |\n");
        printf("| 5. Hapus Data Siklus                     |\n");
        printf("| 0. Keluar                                |\n");
        printf("+------------------------------------------+\n");
        printf("Pilihan Anda (0-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                tambahSiklus();
                break;
            case 2:
                lihatSiklus();
                break;
            case 3:
                lihatStatistics();
                break;
            case 4:
                ubahSiklus();
                break;
            case 5:
                hapusSiklus();
                break;
            case 0:
                printf("==== Keluar dari Menu Statistik ====.\n");
            default:
                printf("Pilihan tidak valid! Silakan pilih lagi!\n");
        }
    } while (choice != 0);
}

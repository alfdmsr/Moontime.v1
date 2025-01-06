#include <stdio.h>
#include <string.h>
#include "2_catatanGejala.h"

#define MAX_DATA 100

typedef struct {
    int id ;
  char tanggalMulai[11]; // Format: YYYY-MM-DD
  char tanggalSelesai[11]; // Format: YYYY-MM-DD
  int durasi; // Durasi siklus dalam hari
  char gejala[255]; // Catatan gejala yang dialami
} catatanGejala;

catatanGejala data[MAX_DATA];
int jumlahData = 0;

// Deklarasi fungsi
void catatanGejalaMenu();
void tambahCatatanGejala();
void simpanCatatanGejalaKeFile();
void bacaCatatanGejalaDariFile();
void urutkanCatatanGejalaBerdasarkanID();
void lihatCatatanGejala();
void CatatanGejalaBerdasarkanTanggal();
void ubahCatatanGejala();
void hapusCatatanGejala();


// Fungsi untuk menambahkan catatan gejala menstruasi
void tambahCatatanGejala() {
    if (jumlahData >= MAX_DATA) {
        printf("Data penuh! Tidak dapat menambahkan catatan gejala baru.\n");
        return;
    }

    printf("Masukkan ID Siklus: ");
    scanf("%d", &data[jumlahData].id);
    printf("Masukkan Tanggal Mulai (YYYY-MM-DD): ");
    scanf("%s", data[jumlahData].tanggalMulai);
    printf("Masukkan Tanggal Selesai (YYYY-MM-DD): ");
    scanf("%s", data[jumlahData].tanggalSelesai);
    printf("Masukkan Durasi Siklus (dalam hari): ");
    scanf("%d", &data[jumlahData].durasi);
    getchar(); // Menangani newline setelah memasukkan durasi
    printf("Masukkan Catatan Gejala yang Dialami: ");
    fgets(data[jumlahData].gejala, 255, stdin);
    data[jumlahData].gejala[strcspn(data[jumlahData].gejala, "\n")] = 0;  // Menghapus baris baru

    jumlahData++;
    simpanCatatanGejalaKeFile(); // Simpan data setelah menambahkan
    printf("Catatan gejala berhasil ditambahkan!\n");
}

// Fungsi untuk melihat daftar catatan gejala menstruasi
void lihatCatatanGejala() {
    if (jumlahData == 0) {
        printf("Tidak ada data catatan gejala.\n");
        return;
    }

    urutkanCatatanGejalaBerdasarkanID(); // Urutkan data sebelum ditampilkan
    printf("\n==== Daftar Catatan Gejala Menstruasi ====\n");
    printf("ID\tTanggal Mulai\tTanggal Selesai\tDurasi (hari)\tGejala\n");
    for (int i = 0; i < jumlahData; i++) {
        printf("%d\t%s\t%s\t%d\t%s\n", data[i].id, data[i].tanggalMulai, data[i].tanggalSelesai,
               data[i].durasi, data[i].gejala);
    }
}

// Fungsi untuk menyimpan data catatan gejala ke file
void simpanCatatanGejalaKeFile() {
    FILE *file = fopen("catatanGejalaMenstruasi.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        fprintf(file, "ID: %d\n", data[i].id);
        fprintf(file, "Tanggal Mulai: %s\n", data[i].tanggalMulai);
        fprintf(file, "Tanggal Selesai: %s\n", data[i].tanggalSelesai);
        fprintf(file, "Durasi: %d\n", data[i].durasi);
        fprintf(file, "Gejala: %s\n", data[i].gejala);
        fprintf(file, "\n");
    }

    fclose(file);
}

// Fungsi untuk membaca data dari file
void bacaCatatanGejalaDariFile() {
    FILE *file = fopen("catatanGejalaMenstruasi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca!\n");
        return;
    }

    jumlahData = 0;
    while (fscanf(file, "ID: %d\n", &data[jumlahData].id) != EOF) {
        fscanf(file, "Tanggal Mulai: %s\n", data[jumlahData].tanggalMulai);
        fscanf(file, "Tanggal Selesai: %s\n", data[jumlahData].tanggalSelesai);
        fscanf(file, "Durasi: %d\n", &data[jumlahData].durasi);
        fscanf(file, "Gejala: %[^\n]\n", data[jumlahData].gejala);
        jumlahData++;
    }

    fclose(file);
}

// Fungsi untuk mengurutkan catatan gejala berdasarkan ID
void urutkanCatatanGejalaBerdasarkanID() {
  for (int i = 0; i < jumlahData - 1; i++) {
    for (int j = 0; j < jumlahData - i - 1; j++) {
      if (data[j].id > data[j + 1].id) {
        catatanGejala temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
}

// Fungsi untuk mencari catatan gejala berdasarkan Tanggal (linear search)
void CatatanGejalaBerdasarkanTanggal() {
  char tanggalMulai[11], tanggalSelesai[11];
  printf("Masukkan Tanggal Mulai Siklus (YYYY-MM-DD): ");
  scanf("%s", tanggalMulai);
  printf("Masukkan Tanggal Selesai Siklus (YYYY-MM-DD): ");
  scanf("%s", tanggalSelesai);

  int ditemukanTanggal = 0;
  printf("Catatan ditemukan:\n");
  for (int i = 0; i < jumlahData; i++) {
    if (strcmp(data[i].tanggalMulai, tanggalMulai) >= 0 && strcmp(data[i].tanggalSelesai, tanggalSelesai) <= 0) {
      printf("ID: %d\n", data[i].id);
      printf("Tanggal Mulai: %s\n", data[i].tanggalMulai);
      printf("Tanggal Selesai: %s\n", data[i].tanggalSelesai);
      printf("Durasi: %d\n", data[i].durasi);
      printf("Gejala: %s\n", data[i].gejala);
      printf("\n");
      ditemukanTanggal = 1;
    }
  }

  if (!ditemukanTanggal) {
    printf("Tidak ada catatan gejala yang ditemukan dalam rentang tanggal tersebut.\n");
  }
}

// Fungsi untuk mengupdate catatan gejala berdasarkan ID
void ubahCatatanGejala() {
  int id;
  printf("Masukkan ID Siklus yang ingin anda ubah:");
  scanf("%d", &id);

  // mencari catatan berdasarkan ID
  int ditemukanId = 0;
  for (int i = 0; i < jumlahData; i++) {
    if (data[i].id == id) {
      ditemukanId = 1;
      printf("Catatan ditemukan. Masukkan data baru:\n");
      printf("Masukkan Tanggal Mulai Siklus (YYYY-MM-DD): ");
      scanf("%s", data[i].tanggalMulai);
      printf("Masukkan Tanggal Selesai Siklus (YYYY-MM-DD): ");
      scanf("%s", data[i].tanggalSelesai);
      printf("Masukkan Durasi Siklus (dalam hari): ");
      scanf("%d", &data[i].durasi);
      getchar(); // menangani baris baru setelah memasukkan durasi
      printf("Masukkan Catatan Gejala yang Dialami: ");
      fgets(data[i].gejala, 255, stdin);
      data[i].gejala[strcspn(data[i].gejala, "\n")] = 0; // untuk menghapus baris baru

      printf("Catatan gejala dengan ID %d berhasil diubah!\n", id);
      simpanCatatanGejalaKeFile(); // simpan data setelah berhasil diubah
      break;
    }
  }

  if (!ditemukanId) {
    printf("ID Siklus tidak ditemukan!\n");
  }
}


// Fungsi untuk menghapus catatan gejala berdasarkan ID
void hapusCatatanGejala() {
  int id;
  printf("Masukkan ID Siklus yang ingin anda hapus: ");
  scanf("%d", &id);

  // mencari catatan berdasarkan ID
  int ditemukanId = 0;
  for (int i = 0; i < jumlahData; i++) {
    if (data[i].id == id) {
      ditemukanId = 1;
      // Geser data setelah catatan yang dihapus
      for (int j = i; j < jumlahData - 1; j++) {
        data[j] = data[j + 1];
      }
      jumlahData--; // mengurangi jumlah catatan
      printf("Catatan gejala dengan ID %d berhasil dihapus!\n", id);
      simpanCatatanGejalaKeFile(); // simpan data setelah berhasil dihapus
      break;
    }
  }

  if (!ditemukanId) {
    printf("ID Siklus tidak ditemukan!");
  }
}

// Fungsi utama
void catatanGejalaMenu() {
    int choice;

    bacaCatatanGejalaDariFile(); // Membaca data dari file sebelum menu dimulai

    do {
        printf("\n+-----------------------------------------------------+\n");
        printf("|           Menu Catatan Gejala Menstruasi            |\n");
        printf("|=====================================================|\n");
        printf("| 1. Tambah Catatan Gejala                            |\n");
        printf("| 2. Lihat Daftar Catatan Gejala                      |\n");
        printf("| 3. Ubah Catatan Gejala                              |\n");
        printf("| 4. Cari Catatan Gejala Berdasarkan Rentang Tanggal  |\n");
        printf("| 5. Hapus Catatan Gejala                             |\n");
        printf("| 0. Keluar                                           |\n");
        printf("+-----------------------------------------------------+\n");
        printf("Pilihan Anda (0-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                tambahCatatanGejala();
                break;
            case 2:
                lihatCatatanGejala();
                break;
            case 3:
                ubahCatatanGejala();
                break;
            case 4:
                CatatanGejalaBerdasarkanTanggal();
                break;
            case 5:
                hapusCatatanGejala();
                break;
            case 0:
                printf("==== Keluar dari Menu Catatan Gejala Menstruasi. ====\n");
                break;
            default:
                printf("Pilihan tidak valid! Silakan pilih lagi!\n");
        }
    } while (choice != 0);
}

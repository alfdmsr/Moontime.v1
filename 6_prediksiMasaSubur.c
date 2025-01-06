#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "6_prediksiMasaSubur.h"

#define MAX_RECORDS 100

typedef struct{
    int id;
    char TanggalMulaisiklus[11];
    int siklusTerpendek;
    int siklusTerpanjang;
} CatatanKesuburan;

CatatanKesuburan catatan[MAX_RECORDS];
int recordCount = 0;

//Deklarasi Fungsi
void prediksiMasaSuburMenu();
void addCatatanKesuburan();
void displayCatatanKesuburan();
void sortCatatanKesuburan();
void updateCatatanKesuburan();
void predictCatatanKesuburan();
void deleteCatatanKesuburan();
void saveCatatanKesuburanToFile();
void loadCatatanKesuburanFromFile();
void searchByid();
void searchByDate();

// Fungsi untuk menyimpan data ke dalam file
void saveCatatanKesuburanToFile() {
    FILE *file = fopen ("dataMasaSubur.txt","w");
    if(file == NULL){
        printf("Tidak dapat membuka file untuk menulis data.\n");
        return;
    }
    for (int i = 0; i < recordCount; i++){
         fprintf(file, "%d %s %d %d\n", catatan[i].id, catatan[i].TanggalMulaisiklus, catatan[i].siklusTerpendek, catatan[i].siklusTerpanjang);
    }
    fclose(file);
}

// Fungsi untuk membaca data dari file
void loadCatatanKesuburanFromFile() {
    FILE *file = fopen("dataMasaSubur.txt", "r");
    if (file == NULL) {
        printf("Tidak ada data yang tersimpan.\n");
        return;
    }
    recordCount = 0;
   while (fscanf(file, "%d %s %d %d", &catatan[recordCount].id, catatan[recordCount].TanggalMulaisiklus,
                   &catatan[recordCount].siklusTerpendek, &catatan[recordCount].siklusTerpanjang) != EOF) {
        recordCount++;
    }
    fclose(file);
}

//Fungsi untuk menambahkan data prediksi masa subur
void addCatatanKesuburan() {
    if (recordCount >= MAX_RECORDS) {
        printf("Data Sudah penuh. Tidak dapat menambah data lagi.\n");
        return;
    }
    CatatanKesuburan newRecord;
    newRecord.id = recordCount + 1;
    printf("Masukkan tanggal mulai siklus (YYYY-MM-DD):");
    scanf("%s", newRecord.TanggalMulaisiklus);
    printf("Masukkan siklus terpendek (dalam hari): ");
    scanf("%d", &newRecord.siklusTerpendek);
    printf("Masukkan siklus terpanjang (dalam hari):");
    scanf("%d", &newRecord.siklusTerpanjang);
    
    catatan[recordCount++] = newRecord;
    saveCatatanKesuburanToFile();
    printf("Data berhasil ditambahkan.\n");
}    

// Fungsi untuk menampilkan semua data
    void displayCatatanKesuburan(){
        if (recordCount == 0) {
            printf("Tidak ada Data.\n");
            return;
        }
        sortCatatanKesuburan();
        printf("\nData Prediksi Masa Subur:\n");
        for (int i = 0; i < recordCount; i++) {
          printf("ID: %d\nTanggal Mulai Siklus: %s\nSiklus Terpendek: %d hari\nSiklus Terpanjang: %d hari\n", 
        catatan[i].id, 
        catatan[i].TanggalMulaisiklus, 
        catatan[i].siklusTerpendek, 
        catatan[i].siklusTerpanjang);

        }
    }
    
// Fungsi untuk memprediksi masa subur
void predictCatatanKesuburan() {
    int id;
    printf("Masukkan ID data yang ingin di prediksi:");
    scanf("%d", &id);
    
    for (int i = 0; i < recordCount; i++){
        if (catatan[i].id == id) {
            int averageCycle = (catatan[i].siklusTerpendek + catatan[i].siklusTerpanjang) / 2;
            printf("Prediksi masa subur untuk siklus ini adalah %d hari setelah tanggal %s.\n", averageCycle, catatan[i].TanggalMulaisiklus);
            return;
        }
    }
    printf("Data dengan ID %d tidak dapat ditemukan.\n", id);
}

//Fungsi untuk mengurutkan data berdasarkan ID
void sortCatatanKesuburan() {
    for (int i= 0; i < recordCount - 1; i++) {
        for (int j = 0; j < recordCount - i - 1; j++){
            if (catatan [j].id > catatan[j+1].id){
                CatatanKesuburan temp = catatan[j];
                catatan[j] = catatan[j+1];
                catatan[j + 1] = temp;
            }
        }
    }
}

//Fungsi untuk mengupdate data berdasarkan ID
void updateCatatanKesuburan() {
    int id;
    printf("Masukkan ID yang ingin di update:");
    scanf("%d", &id);
    
    for (int i = 0; i < recordCount; i++) {
        if (catatan[i].id == id) {
            printf("Masukkan tanggal mulai siklus baru (YYYY-MM-DD):");
            scanf("%s", catatan[i].TanggalMulaisiklus);
            printf("Masukkan siklus terpendek baru (dalam hari):");
            scanf("%d", &catatan[i].siklusTerpendek);
            printf("Masukkan siklus terpanjang baru (dalam hari):");
            scanf("%d", &catatan[i].siklusTerpanjang);
            
            saveCatatanKesuburanToFile();
            printf("Data berhasil di update.\n");
            return;
        }
    }
}

//Fungsi mencari data berdasarkan ID
void searchByid() {
    int id;
    printf("Masukkan ID yang di cari:");
    scanf("%d", &id);
    
    for(int i = 0; i < recordCount; i++){
        if (catatan[i].id == id) {
            printf("Data ditemukan:\n");
           printf("ID: %d\nTanggal Mulai Siklus: %s\nSiklus Terpendek: %d hari\nSiklus Terpanjang: %d hari\n",
               catatan[i].id,
               catatan[i].TanggalMulaisiklus,
               catatan[i].siklusTerpendek,
               catatan[i].siklusTerpanjang);
                return;
        }
    }
    printf("Data dengan ID %d tidak dapat ditemukan.\n",id);
}

//Fungsi mencari data berdasarkan Tanggal
void searchByDate() {
    char date[11];
    printf("Masukkan tanggal yang dicari (YYYY-MM-DD): ");
    scanf("%s", date);
    
    int found = 0;
    for (int i = 0; i< recordCount; i++) {
        if (strcmp(catatan[i].TanggalMulaisiklus, date) == 0){
            printf("Data ditemukan:\n");
            printf("ID: %d\nTanggalMulaisiklus: %s\nsiklusTerpendek: %d hari\nsiklusTerpanjang: %d hari\n",
                catatan[i].id,
                catatan[i].TanggalMulaisiklus,
                catatan[i].siklusTerpendek,
                catatan[i].siklusTerpanjang);
                found = 1;
        }
    }
    if (!found) {
        printf("Data dengan Tanggal %s tidak dapat ditemukan.\n",date);
    }
}

// Fungsi untuk menghapus data berdasarkan ID
void deleteCatatanKesuburan() {
    int id;
    printf("Masukkan ID yang akan dihapus:");
    scanf("%d", &id);
    
    int index = -1;
    for (int i = 0; i < recordCount; i++) {
        if (catatan[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Data dengan ID %d tidak dapat ditemukan.\n", id);
        return;
    }
    for (int i = index; i < recordCount - 1; i++) {
        catatan[i] = catatan[i + 1];
    }
    recordCount--;
    saveCatatanKesuburanToFile();
    printf("Data berhasil dihapus.\n");
}

// Menu utama fitur prediksi masa subur
void prediksiMasaSuburMenu() {
    int choice;

    loadCatatanKesuburanFromFile();
    do {
        printf("\n+----------------------------------+\n");
        printf("|     Menu Prediksi Masa Subur     |\n");
        printf("|==================================|\n");
        printf("| 1. Tambah Data Prediksi          |\n");
        printf("| 2. Tampilkan Semua Data          |\n");
        printf("| 3. Prediksi Masa Subur           |\n");
        printf("| 4. Update Data                   |\n");
        printf("| 5. Cari Data Berdasarkan id      |\n");
        printf("| 6. Cari Data Berdasarkan Tanggal |\n");
        printf("| 7. Hapus Data                    |\n");
        printf("| 0. Keluar                        |\n");
        printf("+----------------------------------+\n");
        printf("Pilihan Anda (0-7):");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addCatatanKesuburan();
                break;
            case 2:
                displayCatatanKesuburan();
                break;
            case 3:
                predictCatatanKesuburan();
                break;
            case 4:
                updateCatatanKesuburan();
                break;
            case 5:
                searchByid();
                break;
            case 6:
                searchByDate();
                break;
            case 7:
                deleteCatatanKesuburan();
                break;
            case 0:
                printf("==== Keluar dari fitur Prediksi Masa Subur. ====\n");
                break;
            default:
                printf ("Pilihan tidak valid! Silakan pilih lagi!\n");
        }
    } while (choice != 0);

}
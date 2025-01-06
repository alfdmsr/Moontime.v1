#include <stdio.h>
#include <string.h>
#include "4_reminder.h"

#define MAX_REMINDERS 100
#define MAX_LENGTH 100

typedef struct {
    int id;
    char description[255];
    char date[11]; // Format: YYYY-MM-DD
    char title[255];
} Reminder;

Reminder reminders[MAX_REMINDERS];
int reminderCount = 0;

// Deklarasi fungsi
void addReminder();
void sortRemindersById();
void saveReminderToFile();
void readReminderFromFile();
void viewReminders();
void updateReminder();
void deleteReminder();
void searchReminder(const char *keyword);

// Fungsi untuk menambahkan pengingat
void addReminder() {
    if (reminderCount >= MAX_REMINDERS){
            printf("Jumlah pengingat sudah penuh!\n");
            return;
    }

    printf("Masukkan ID Pengingat: ");
    scanf("%d", &reminders[reminderCount].id);
    getchar(); // Menangani newline setelah memasukkan ID
    printf("Masukkan Deskripsi Pengingat: ");
    fgets(reminders[reminderCount].description, 255, stdin);
    reminders[reminderCount].description[strcspn(reminders[reminderCount].description, "\n")] = 0; // Menghapus newline
    printf("Masukkan Tanggal Pengingat (YYYY-MM-DD): ");
    scanf ("%s",reminders[reminderCount].date);

    reminderCount++;
    printf("Pengingat berhasil ditambahkan!\n");
    saveReminderToFile(); // Simpan data setelah menambahkan
}


// Fungsi untuk melihat semua pengingat
void viewReminders() {
    if (reminderCount == 0) {
            printf("Tidak ada pengingat.\n");
            return;
    }

    sortRemindersById(); // Urutkan pengingat sebelum ditampilkan
    printf("daftar pengingat:\n");
    printf("ID \t deskripsi \t tanggal \n");
    for (int i = 0; i < reminderCount; i++) {
        printf("%d\t%s\t%s\n", reminders[i].id, reminders[i].description, reminders[i].date);
    }
}

// Fungsi untuk menyimpan data ke file
void saveReminderToFile(){
    FILE *file = fopen("reminders.txt", "w");
    if (file == NULL) {
        printf("gagal membuka file untuk menulis!\n");
        return;
    }

    for (int i = 0; i < reminderCount; i++) {
        fprintf(file, "ID: %d\n", reminders[i].id);
        fprintf(file, "deskripsi : %s\n", reminders[i].description);
        fprintf(file, "tanggal : %s\n", reminders[i].date);
        fprintf(file, "\n");
    }

    fclose(file);
}

// Fungsi untuk membaca data dari file
void readReminderFromFile() {
    FILE *file = fopen("reminders.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca!\n");
        return;
    }

    reminderCount = 0;
    while (fscanf(file, "ID: %d\n", &reminders[reminderCount].id) != EOF) {
        fscanf(file, "Deskripsi: %[^\n]\n", reminders[reminderCount].description);
        fscanf(file, "Tanggal: %s\n", reminders[reminderCount].date);
        fscanf(file, "\n");
        reminderCount++;
    }

    fclose(file);
}

// fungsi untuk mengurutkan pengingat berdasarkan ID
void sortRemindersById() {
    for (int i = 0; i < reminderCount - 1; i++) {
        for (int j = 0; j < reminderCount - i - 1; j++) {
            if (reminders[j].id > reminders[j + 1].id) {
                Reminder temp = reminders[j];
                reminders[j] = reminders[j + 1];
                reminders[j = 1] = temp;
            }
        }
    }
}

// fungsi untuk memperbarui pengingat
void updateReminder() {
    int id, found = 0;
    printf("Masukkan ID pengingat yang ingin diperbarui: ");
    scanf("%d", &id);

    for (int i = 0; i < reminderCount; i++) {
        if (reminders[i].id == id) {
            getchar(); // menangani newline setelah memasukkan ID
            printf("masukkan deskripsi Baru: ");
            fgets(reminders[i].description, 255, stdin);
            reminders[i].description[strcspn(reminders[i].description, "\n")] = 0; //  menghapus newline
            printf("Masukkan tanggal Baru (YYYY-MM-DD): ");
            scanf("%s", reminders[i].date);
            printf("Pengingat berhasil diperbarui!\n");
            found = 1;
            saveReminderToFile(); // simpan data setelah mengupdate
            break;
        }
    }
    if (!found) {
        printf("pengingat dengan ID %d tidak ditemukan. \n", id);
    }
}

// fungsi untuk menghapus pengingat
 void deleteReminder() {
     int id, found = 0;
     printf("Masukkan ID pengingat yang ingin dihapus: ");
     scanf("%d", &id);

     for (int i = 0; i < reminderCount; i++) {
        if (reminders[i].id == id){
            for (int j = i; j < reminderCount - 1; j++) {
                reminders[j] = reminders[j + 1];
            }
            reminderCount--;
            printf("Pengingat berhasil dihapus!\n");
            found = 1;
            saveReminderToFile(); // simpan data setelah menghapus
            break;
        }
     }
     if (!found) {
        printf("Pengingat dengan ID %d tidak ditemukan.\n", id);
     }
 }

 void searchReminder( const char *keyword)
 {
    int found = 0;
     printf("Mencari pengingat yang berisi '%s'... \n", keyword);
     for (int i = 0; i < reminderCount; i++) {
        if (strstr(reminders[i].title, keyword) || strstr(reminders[i].description, keyword)) {
            printf("%d. Deskripsi:%s\n  Tanggal:%s\n",i + 1, reminders[i].description, reminders[i].date);
            found = 1;
        }
    }
    if (!found) {
        printf(" Hasil tidak ditemukan '%s'.\n", keyword);
    }
 }


// Fungsi utama
void reminderMenu() {
    int choice;
    char keyword[MAX_LENGTH];

    readReminderFromFile();
    do {
        printf("\n+-----------------------------------+\n");
        printf("|     Menu Pengingat Menstruasi     |\n");
        printf("|===================================|\n");
        printf("| 1. Tambah Pengingat               |\n");
        printf("| 2. Lihat Pengingat                |\n");
        printf("| 3. Ubah Pengingat                 |\n");
        printf("| 4. Hapus Pengingat                |\n");
        printf("| 5. Cari Pengingat                 |\n");
        printf("| 0. Keluar                         |\n");
        printf("+-----------------------------------+\n");
        printf("Pilihan Anda (0-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addReminder();
                break;
            case 2:
                viewReminders();
                break;
            case 3:
                updateReminder();
                break;
            case 4:
                deleteReminder();
                break;
            case 5:
                printf("Masukkan kata kunci: ");
                scanf("%s", keyword);
                searchReminder(keyword);
                break;
            case 0:
                printf("==== Keluar dari Menu Pengingat Menstruasi. ====\n");
                break;
            default:
                printf("Pilihan tidak valid! Silakan pilih lagi!\n");
        }
    } while (choice != 0);
}

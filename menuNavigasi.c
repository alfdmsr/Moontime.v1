#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1_inputData.h"
#include "2_catatanGejala.h"
#include "3_prediksiPeriodeSelanjutnya.h"
#include "4_reminder.h"
#include "5_statistik.h"
#include "6_prediksiMasaSubur.h"
#include "7_rekomendasiNutrisi.h"

int main() {
  int choice;
  printf("Program Dimulai!");
  
  do {
    printf("\n==============================================\n");
    printf("|   Moontime - Aplikasi Pelacak Menstruasi   |\n");
    printf("|--------------------------------------------|\n");
    printf("| 1. Masukkan Data Siklus Menstruasi         |\n");
    printf("| 2. Catatan Gejala Menstruasi               |\n");
    printf("| 3. Prediksi Periode Selanjutnya            |\n");
    printf("| 4. Prediksi Masa Subur                     |\n");
    printf("| 5. Reminder                                |\n");
    printf("| 6. Rekomendasi Nutrisi                     |\n");
    printf("| 7. Statistik                               |\n");
    printf("| 0. Keluar                                  |\n");
    printf("==============================================\n");
    printf("Pilih fitur (0-7): ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        inputDataMenu();
        break;
      case 2:
        catatanGejalaMenu();
        break;
      case 3:
        prediksiPeriodeMenu();
        break;
      case 4:
        prediksiMasaSuburMenu();
        break;
      case 5:
        reminderMenu();
        break;
      case 6:
        rekomendasiNutrisiMenu();
        break;
      case 7:
        statistikMenu();
        break;
      case 0:
        printf("Keluar dari aplikasi Moontime.\n");
        printf("=== Terima kasih telah menggunakan aplikasi Moontime. ===\n");
        break;
    }
  } while (choice != 0);

  printf("Program selesai!\n");
  return 0;
}
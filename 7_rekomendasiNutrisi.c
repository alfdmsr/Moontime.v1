#include <stdio.h>
#include <string.h>
#include "7_rekomendasiNutrisi.h"

#define max_nutrisi 100
#define file_name "Nutrisi.txt"

// Deklarasi fungsi
void rekomendasiNutrisiMenu();
void addNutrisi();
void viewNutrisi();
void updateNutrisi();
void deleteNutrisi();

void rekomendasiBerdasarkanKondisi();
void rekomendasiBerdasarkanKondisiDanFase();
void searchingBerdasarkanFase(int faseTarget, int fase[], char nutrisi[][256], int jumlahNutrisi);

int readNutrisiDariFile(char nutrisi[][256], int fase[]);
void writeNutrisiKeFile(char nutrisi[][256], int fase[], int count);

// Fungsi Utama 
void rekomendasiNutrisiMenu(){
    int pilihan;
    do
    {
        printf("\n+--------------------------------------------+\n");
        printf("|          Menu Rekomendasi Nutrisi          |\n");
        printf("|============================================|\n");
        printf("| 1. Tambah Rekomendasi Nutrisi              |\n");
        printf("| 2. Lihat Rekomendasi Nutrisi               |\n");
        printf("| 3. Update Rekomendasi Nutrisi              |\n");
        printf("| 4. Hapus Rekomendasi Nutrisi               |\n");
        printf("| 5. Rekomendasi Berdasarkan Gejala/Kondisi  |\n");
        printf("| 6. Rekomendasi Berdasarkan Fase            |\n");
        printf("| 7. Cari Berdasarkan Fase                   |\n");
        printf("| 0. Keluar                                  |\n");
        printf("+--------------------------------------------+\n");
        printf("Pilihan Anda (0-7): ");
        scanf("%d", &pilihan);

        switch (pilihan){
        case 1: addNutrisi();
            break;
        case 2: viewNutrisi();
            break;
        case 3: updateNutrisi();
            break;
        case 4: deleteNutrisi();
            break;
        case 5: rekomendasiBerdasarkanKondisi();
            break;
        case 6: rekomendasiBerdasarkanKondisiDanFase();
            break;
        case 7: {
            int faseTarget;
            int fase[max_nutrisi];
            char nutrisi[max_nutrisi][256];
            int jumlah_nutrisi = readNutrisiDariFile(nutrisi, fase);

            printf("Masukkan fase yang ingin dicari : \n");
            printf("1. Pra-Menstruasi\n");
            printf("2. Menstruasi\n");
            printf("3. Pasca-Menstruasi\n");
            printf("Pilihan anda (1-3) : ");
            scanf("%d", &faseTarget);

            if (faseTarget >= 1 && faseTarget <= 3) {
                searchingBerdasarkanFase(faseTarget, fase, nutrisi, jumlah_nutrisi);
            } else {
                printf("Fase tidak valid! Masukkan hanya 1, 2, atau 3.\n");
            }
            break;
        }

        case 0: printf("==== Keluar dari Menu Rekomendasi Nutrisi. ====\n");
            break;
        default: printf("Pilihan tidak valid! Silakan pilih lagi!.\n");
        }

    } while (pilihan != 0);

}

void rekomendasiBerdasarkanKondisi(){
    int kondisi;
    printf("\n=== Rekomendasi Nutrisi Berdasarkan Kondisi ===\n");
    printf("Pilih kondisi yang dialami :\n");
    printf("1. Kram atau Nyeri Perut\n");
    printf("2. Kelelahan\n");
    printf("3. Mood Buruk atau Stres\n");
    printf("4. Jerawat Hormonal\n");
    printf("5. Perut Kembung\n");
    printf("Masukkan Pilihan : ");
    scanf("%d", &kondisi);

    switch (kondisi){
    case 1:
        printf("\nRekomendasi untuk Kram atau Nyeri Perut :\n");
        printf("- Pisang (Kaya Magnesium untuk relaksasi otot)\n");
        printf("- Almond (magnesium dan vitamin B6 untuk keseimbangan hormon)\n");
        printf("- Bayam (mengandung zat besi dan magnesium)\n");
        break;
    case 2:
        printf("\nRekomendasi untuk Kelelahan:\n");
        printf("- Kacang-kacangan (protein untuk energi)\n");
        printf("- Roti gandum (karbohidrat kompleks untuk energi tahan lama)\n");
        printf("- Buah jeruk (vitamin C untuk meningkatkan energi)\n");
        break;
    case 3:
        printf("\nRekomendasi untuk Mood Buruk atau Stres:\n");
        printf("- Coklat hitam (mengandung tryptophan untuk meningkatkan serotonin)\n");
        printf("- Pisang (meningkatkan hormon serotonin secara alami)\n");
        printf("- Teh chamomile (efek relaksasi untuk mengurangi stres)\n");
        break;
    case 4:
        printf("\nRekomendasi untuk Jerawat Hormonal:\n");
        printf("- Sayuran Hijau (antioksidan untuk melawan radikal bebas)\n");
        printf("- Salom (omega-3 untuk mengurangi inflamasi)\n");
        printf("- Almond (Vitamin E membantu regenerasi)\n");
        break;
    case 5:
        printf("\nRekomendasi untuk Perut Kembung:\n");
        printf("- Jahe (membantu pencernaan dan mengurangi kembung)\n");
        printf("- Pepaya (enzim alami untuk melancarkan pencernaan)\n");
        printf("- Yogurt (probiotik untuk kesehatan usus)\n");
        break;
    default:
        printf("Pilihan tidak valid.\n");
        break;
    }
}

void rekomendasiBerdasarkanKondisiDanFase(){
    int fase;
    printf("\n+-----------------------+\n"); 
    printf("|      Fase Siklus      |\n"); 
    printf("|=======================|\n");  
    printf("| 1. Pra-Menstruasi     |\n");
    printf("| 2. Menstruasi         |\n");
    printf("| 3. Pasca-Menstruasi   |\n");
    printf("+-----------------------+\n"); 
    printf("Pilih Fase : ");
    scanf("%d", &fase);

    switch (fase){
    case 1:
        printf("\n+-------------- Rekomendasi Berdasarkan Fase --------------+\n");
        printf("| Fase Pra-Menstruasi:                                     |\n");
        printf("|..........................................................|\n");
        printf("| - Hindari makan tinggi garam untuk mencegah kembung.     |\n");
        printf("| - Konsumsi buah-buahan segar.                            |\n");
        printf("| - Perbanyak magnesium seperti almond atau pisang.        |\n");
        printf("+----------------------------------------------------------+\n");
        break;
    case 2:
        printf("\n+--------------- Rekomendasi Berdasarkan Fase ---------------+\n");
        printf("| Fase Menstruasi:                                           |\n");
        printf("|............................................................|\n");
        printf("| - Konsumsi makanan tinggi zat besi seperti bayam.          |\n");
        printf("| - Minum air putih yang cukup untuk menghindari dehidrasi.  |\n");
        printf("| - Perbanyak karbohidrat kompleks untuk menjaga energi.     |\n");
        printf("+------------------------------------------------------------+\n");
        break;
    case 3:
        printf("\n+--------------------- Rekomendasi Berdasarkan Fase ---------------------+\n");
        printf("| Fase Pasca-Menstruasi:                                                 |\n");
        printf("|........................................................................|\n");
        printf("| - Fokus pada protein seperti ayam atau tahu untuk pemulihan tubuh.     |\n");
        printf("| - Makanan kaya vitamin C seperti jeruk untuk meningkatkan imun.        |\n");
        printf("+------------------------------------------------------------------------+\n");
        break;
    default:
        printf("Fase tidak valid.\n");
    }
}

void addNutrisi(){
    char newNutrisi[256];
    int fase;
    char nutrisi[max_nutrisi][256];
    int fases[max_nutrisi];
    int count;

    count = readNutrisiDariFile(nutrisi, fases);

    if (count >= max_nutrisi) {
        printf("Data nutrisi sudah penuh.\n");
        return;
    }

    do{
        printf("Masukkan Fase siklus :\n");
        printf("1. Pra-menstruasi\n");
        printf("2. Menstruasi\n");
        printf("3. Pasca-Menstruasi\n");
        if (scanf("%d", &fase) != 1 || fase < 1 || fase > 3){
                printf("Input tidak valid. Harap masukkan angka 1, 2, atau 3.\n");
                while(getchar() != '\n');
        }else{
            break;
        }
        
    } while (1);
    getchar();

    do{
        printf("Masukkan rekomendasi nutrisi: ");
        fgets(newNutrisi, 256,stdin);
        newNutrisi[strcspn(newNutrisi, "\n")] = 0;

        if (strlen(newNutrisi) == 0){
            printf("Rekomendasi nutrisi tidak boleh kosong.\n");
        }else{
            break;
        }
    } while (1);
    
    strcpy(nutrisi[count], newNutrisi);
    fases[count] = fase;

    writeNutrisiKeFile(nutrisi, fases, count + 1);
    printf("Rekomendasi nutrisi berhasil ditambahkan.\n");
}

void viewNutrisi(){
    char nutrisi[max_nutrisi][256];
    int fases[max_nutrisi];
    int count = readNutrisiDariFile(nutrisi, fases);

    if (count == 0){
        printf("Belum ada data rekomendasi nutrisi.\n");
        return;
    }

    printf("\n=== Rekomendasi Nutrisi ===\n");
    for (int i = 0; i < count; i++){
        printf("\nID : %d.\n", i + 1);
        printf("Fase : ");
        switch (fases[i]){
        case 1:
            printf("Pra-Menstruasi\n");
            break;
        case 2:
            printf("Menstruasi\n");
            break;
        case 3:
            printf("Pasca-Menstruasi\n");
            break;
        default:
            printf("Fase tidak valid\n");
            break;
        }
        printf("Rekomendasi: %s\n", nutrisi[i]);
    }
}
void updateNutrisi(){
    char nutrisi[max_nutrisi][256];
    int fases[max_nutrisi];
    int count = readNutrisiDariFile(nutrisi, fases);
    int index, fase;
    char newNutrisi[256];
    
    if (count == 0){
        printf("Belum ada data Rekomendasi yang ingin di update");
        return;
    }
    viewNutrisi();
    printf("Masukkan nomor rekomendasi yang ingin di update : ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= count){
        printf("Nomer rekomendasi tidak valid.\n");
        return;
    }

    printf("Masukkan fase siklus :\n");
    printf("1. Pra-Menstruasi\n");
    printf("2. Menstruasi\n");
    printf("3. Pasca-Menstruasi\n");
    printf("Pilihan Anda (1-3) : \n");
    scanf("%d", &fase);
    getchar();

    printf("Masukkan rekomendasi nutrisi baru : ");
    fgets(newNutrisi, 256, stdin);
    newNutrisi[strcspn(newNutrisi, "\n")] = 0;

    strcpy(nutrisi[index], newNutrisi);
    fases[index] = fase;

    writeNutrisiKeFile(nutrisi, fases, count);
    printf("Rekomendasi nutrisi berhasil di update.\n");

}


void deleteNutrisi(){
    char nutrisi[max_nutrisi][256];
    int fases[max_nutrisi];
    int count = readNutrisiDariFile(nutrisi,fases);
    int index;

    if (count == 0){
        printf("Belum ada data rekomendasi nutrisi untuk dihapus.\n");
        return;
    }

    viewNutrisi();
    printf("Masukkan nomor rekomendasi yang ingin dihapus: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= count){
        printf("Nomer rekomendasi tidak valid.\n");
        return;
    }

    for (int i = index; i < count - 1; i++){
        strcpy(nutrisi[i], nutrisi[i+1]);
        fases[i] = fases[i + 1];
    }

    writeNutrisiKeFile(nutrisi, fases, count - 1);
    printf("Rekomendasi nutrisi berhasil di hapus.\n");
    
}

void searchingBerdasarkanFase(int faseTarget, int fase[], char nutrisi[][256], int jumlahNutrisi){
   
    int found = 0;
    printf("Mencari rekomendasi nutrisi berdasarkan fase %d.\n", faseTarget);
    for (int i = 0; i < jumlahNutrisi; i++){
        if (fase[i] == faseTarget){
            printf("- %s\n", nutrisi[i]);
            found = 1;
        }   
    }
    if (!found) {
        printf("Tidak ada rekomendasi nutrisi untuk fase %d.\n", faseTarget);
    }
}

int readNutrisiDariFile(char nutrisi[][256], int fase[]){
    FILE *file =fopen(file_name, "r");
    int count = 0;

    if(file == NULL){
        return 0;
    }

    while(fscanf(file, "%d\n", &fase[count]) != EOF && count < max_nutrisi){
        fgets(nutrisi[count], 256, file);
        nutrisi[count][strcspn(nutrisi[count], "\n")] =0;
        count++; 
    }
    fclose(file);
    return count;
}

void writeNutrisiKeFile(char nutrisi[][256], int fase[], int count){
    FILE*file = fopen(file_name, "w");

    if (file == NULL) {
        printf("Gagal menyimpan data ke file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", fase[i]);
        fprintf(file, "%s\n", nutrisi[i]);
    }

    fclose(file);
}
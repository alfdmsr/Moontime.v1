#ifndef _7_REKOMENDASINUTRISI_H
#define _7_REKOMENDASINUTRISI_H

// Deklarasi Fungsi
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

#endif
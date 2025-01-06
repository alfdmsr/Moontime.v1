# Moontime.v1
Project ini merupakan tugas UAS Semester 1 Mata Kuliah Algoritma &amp; Pemograman 

# Moontime - Aplikasi Pelacak Menstruasi

Moontime adalah aplikasi pelacak menstruasi yang membantu pengguna untuk mencatat siklus menstruasi, gejala, dan memberikan prediksi serta rekomendasi terkait kesehatan menstruasi.

## Fitur Aplikasi

- **Masukkan Data Siklus Menstruasi**: Mencatat data siklus menstruasi pengguna.
- **Catatan Gejala Menstruasi**: Mencatat gejala yang dialami selama menstruasi.
- **Prediksi Periode Selanjutnya**: Memberikan prediksi periode menstruasi berikutnya.
- **Prediksi Masa Subur**: Memberikan prediksi masa subur pengguna.
- **Reminder**: Mengatur pengingat terkait siklus menstruasi.
- **Rekomendasi Nutrisi**: Memberikan rekomendasi nutrisi yang sesuai.
- **Statistik**: Menampilkan statistik terkait siklus menstruasi pengguna.

## Cara Meng-compile dan Menjalankan Aplikasi

1. **Pastikan Anda memiliki compiler C** (misalnya, minGW(GCC), atau lainnya) terinstal di komputer Anda.
2. **Clone repository ini:**
   ```sh
   git clone https://github.com/alfdmsr/Moontime.v1.git
3. **Masuk ke direktori repository:**
   ```sh
   cd Moontime.v1
5. **Compile semua file .c:**
   ```sh
   gcc -o moontime menuNavigasi.c 1_inputData.c 2_catatanGejala.c 3_prediksiPeriodeSelanjutnya.c 4_reminder.c 5_statistik.c 6_prediksiMasaSubur.c 7_rekomendasiNutrisi.c
7. **Jalankan aplikasi:**
   ```sh
   ./moontime

## Struktur Direktori
Pastikan struktur direktori Anda seperti berikut:
```sh
repository-name/
├── 1_inputData.c
├── 2_catatanGejala.c
├── 3_prediksiPeriodeSelanjutnya.c
├── 4_reminder.c
├── 5_statistik.c
├── 6_prediksiMasaSubur.c
├── 7_rekomendasiNutrisi.c
├── menuNavigasi.c
├── 1_inputData.h
├── 2_catatanGejala.h
├── 3_prediksiPeriodeSelanjutnya.h
├── 4_reminder.h
├── 5_statistik.h
├── 6_prediksiMasaSubur.h
├── 7_rekomendasiNutrisi.h
└── README.md
```

## Kontribusi
Jika Anda ingin berkontribusi pada proyek ini, silakan fork repository ini, buat branch baru untuk fitur atau perbaikan Anda, dan buat pull request. Kami akan meninjau perubahan Anda secepat mungkin.

   

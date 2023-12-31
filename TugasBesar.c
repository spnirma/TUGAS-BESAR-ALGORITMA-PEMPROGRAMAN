#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//fungsi untuk melanjutkan antrian yang sudah dilakukan sebelum nya
void antrian_lanjut(int *antrian, int *nomor){
    FILE *antrian_sebelum;
    int i = 0;

    antrian_sebelum = fopen("antrian kapal.txt", "r");
    while(fscanf(antrian_sebelum, "%i", &antrian[i]) == 1 ){
        i++;
    }
    *nomor = i;
}
// fungsi yang menghitung jumlah nomor kapal yang sama, yg jumlah nya di inputkan dalam file "jumlah masuk perkapal.txt"
void data_nomor(int *nomor_kapal){
    FILE *data_kapal;
    int jumlah = 0;
    data_kapal = fopen("daftar kapal urut.txt", "r");
    while(fscanf(data_kapal, "%i", &nomor_kapal[jumlah])){
        jumlah++;
        if(jumlah > 100){
            jumlah = 100;
            break;
        }
    }
    fclose(data_kapal);
}

void total_masuk(int nomor){
    FILE *jumlah_total;
    int nomor_kapal[100];
    int satuan_nomor[100];
    int total[100];
    data_nomor(nomor_kapal);
    int kapal = 0;
    for(int i = 0; i < nomor; i++){
        int jumlah = 1;
            if(nomor_kapal[i] > 0){
                kapal++;
                satuan_nomor[kapal-1] = nomor_kapal[i];
                for(int j = i+1; j < nomor; j++){
                    if(nomor_kapal[i] == nomor_kapal[j]){
                    nomor_kapal[j] = 0;
                    jumlah++;
                    }
                }
                total[kapal-1] = jumlah;   
            } 
    }
    jumlah_total = fopen("Jumlah masuk perkapal.txt", "w");
    for(int i = 0; i < kapal; i++){
        fprintf(jumlah_total, "%i\t: %i\n", satuan_nomor[i], total[i]);
    }
    fclose(jumlah_total);
}
//fungsi untuk menukar dua angka yang dipakai pada fungsi quicksort
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//fungsi yang mengurutkan nomor kapal dari yang terkecil sampai yang terbesar menggunakan algoritma quick_sort
void quick_sort(int x, int y, int *z){
    int kecil, besar, pivot, temp;
    kecil = x;
    besar = y;
    pivot = y;

    if (kecil <= besar)
    {
        while (kecil < besar)
        {
            while (z[kecil] <= z[pivot]){
                kecil++;
            }
            while (z[besar] > z[pivot]){
                besar--;
            }
            if (kecil < besar){
                swap(&z[besar], &z[kecil]);
            }
        }
        swap(&z[pivot], &z[besar]);

        quick_sort(x, besar - 1, z);
        quick_sort(besar + 1, y, z);
    }
}
// fungsi yang berguna untuk menginputkan array yang berisi nomor kapal yang sudah terurut kedalam file "daftar kapal urut.txt"
void file_urutan(int *array, int size){
    FILE *data_urut;
    data_urut = fopen("daftar kapal urut.txt", "w");
    if(data_urut == NULL){
        printf("EROR!");
        exit(1);
    } else {
        for(int i = 0; i < size; i++){
            fprintf(data_urut, "%i\n", array[i]); //penginputan array ke dalam file "daftar kapal urut.txt"
        }
    }
    fclose(data_urut);
}
//fungsi yang menginputkan data-data nomor kapal dari file "daftar kapal.txt" kedalam array "data_kapal"
void daftar_nomor(int *data_kapal){
    FILE *nomor_kapal;
    nomor_kapal = fopen("daftar kapal.txt", "r"); //membuka file
    int i = 0;
    if(nomor_kapal == NULL){
        printf("EROR!"); //jika file tidak di temukan maka output "EROR", dan akan langsung keluar
        exit(1);
    } else{
        while(fscanf(nomor_kapal, "%i", &data_kapal[i]) == 1){ //perulangan yang menginputkan isi file ke dalam array "data_kapal"
            i++;
        }
    }
    fclose(nomor_kapal); //menutup file
}
// fungsi untuk mengubah, status = 1,menjadi, status = 0, jika yang di inputkan == "keluar"
void antrian_keluar(int *status){
    printf("Kapal keluar: \n"); //menginfokan apakah ada kapal yang keluar dari dermaga atau tidak
    for(int i = 0; i < 4; i++){
        char keluar[7];
        if(status[i] == 1){
            printf("dermaga %i: ", i +1);
            scanf("%s", keluar); //input == "keluar", jika ingin mengubah status menjadi 0 / kosong
            if(strcmp(keluar, "keluar") == 0){ //jika inputan == "keluar" -->
                status[i] = 0; // maka status dermaga tersebut = 0;
            }
        }
    }
}
//fungsi untuk mengubah status dermaga menjadi = 1, dengan antrian yang sudah teratur
void antrian_masuk(int nomor, int *antrian, int *status){
    for(int i = 0; i < nomor; i++){
        if(antrian[i] > 0){ //jika antrian(nomor kapal) > 0, maka masuk dalam percabangan, karena antrian == 0, adalah antrian yang sudah masuk
            for(int j = 0; j < 4; j++){
                int nmr = j; // untuk mengetahui nomer dermaga
                if(status[j] == 0){
                    if(antrian[i] % 2 == 1 && j % 2 == 0 ){ // nomor kapal ganjil == dermaga nomor ganjil
                        status[j] = 1;
                        antrian[i] = 0; //antrian tersebut menjadi 0, karena sudah masuk dermaga, dan agar tidak masuk lagi kedalam percabangan
                        break; 
                        
                    } else if(antrian[i] % 2 == 0 && j % 2 == 1 ){ // nomor kapal genap == dermaga nomor genap
                        status[j] = 1;
                        antrian[i] = 0; //antrian tersebut menjadi 0, karena sudah masuk dermaga, dan agar tidak masuk lagi kedalam percabangan
                        break; 
                    }
                    
                }
            }
        }
    }
}

void file_antrian(int *antrian, int size){
    FILE *data_antrian;

    data_antrian = fopen("antrian kapal.txt", "w"); //menginputkan data nomer antrian dan nomor kapal kedalam file "antrian kapal.txt"
    if(data_antrian == NULL){
        printf("EROR!");
        exit(1);
    } else{
        for(int i = 0; i < size; i++){ //perulangan untuk menginputkan antrian ke dalam file
            fprintf(data_antrian, "\t%i\n", antrian[i]);
        }
    }
    fclose(data_antrian);
}

// fungsi untuk print antrian kapal yang sedang berlangsung, dan juga menginput nya kedalam file
void cek_antrian(int size, int *antrian){
    FILE *data_antrian;
    printf("No antri\tNo kapal\n"); //print nomor antrian disertai nomor kapal
    for(int i = 0; i < size; i++){
        printf("%i\t\t%i\n", i+1, antrian[i]);
    }
}
// fungsi untuk mengecek status dermaga saat pertama kali kode di jalankan, input adalah hanya 1 atau 0
void cek_status_dermaga(int *status){
    for(int i = 0; i < 4; i++){
        printf(" Status dermaga %i: ", i+1);
        scanf("%i", &status[i]);
    }
}
// fungsi untuk menampilkan status dermaga, status == 0 berarti kosong, status == 1 berarti isi
void status_dermaga(int *status){
    for(int i = 0; i < 4; i++){
        printf(" Status dermaga %i: %i\n", i+1, status[i]);
    }
}
//fungsi utama 

int main(){
    int antrian[100], data_kapal[100], nomor = 0;
    int status[4];
    bool pelabuhan = true;
    bool kapal_masuk = true;
    char oprasional[15];
    FILE *daftar_kapal;
    int input_nomor;

    cek_status_dermaga(status);

    while(pelabuhan == true){
        printf("\n1. Kapal Masuk\n");
        printf("2. Cek Antrian\n");
        printf("3. Simpan data\n");
        printf("4. Status Dermaga\n");
        printf("5. kapal keluar\n");
        printf("6. program selesai\n");
        printf("\nMasukkan nomor: ");
        scanf("%i", &input_nomor);
        printf("\n");
        switch(input_nomor){
            case 1:
                if(nomor == 0){
                    antrian_lanjut(antrian, &nomor);
                }

                daftar_kapal = fopen("daftar kapal.txt", "a");
                if(daftar_kapal == NULL){
                    printf("EROR");
                    return 1;
                } else{
                    while(kapal_masuk == true){
                        char masuk[6];
                        printf("\nMasukkan nomor kapal: ");
                        scanf("%i", &antrian[nomor]);
                        fprintf(daftar_kapal, "%i\n", antrian[nomor]);
                        nomor++;
                        printf("\nApakah ada lagi? ");
                        scanf("%s", masuk);
                        if(strcmp(masuk, "ada") == 0){
                            kapal_masuk = true;
                        } else {
                        kapal_masuk = false;
                        }

                    }
                }
                fclose(daftar_kapal);
                kapal_masuk = true;
                antrian_masuk(nomor, antrian, status); printf("\n");
                break;

            case 2:
                if(nomor == 0){
                    antrian_lanjut(antrian, &nomor);
                }

                if(nomor == 0){
                    printf("Antrian masih kosong\n");
                } else {
                    cek_antrian(nomor, antrian); printf("\n");
                }
                break;

            case 3:
                file_antrian(antrian, nomor);
                daftar_nomor(data_kapal);
                quick_sort(0, nomor - 1, data_kapal);
                file_urutan(data_kapal, nomor);
                total_masuk(nomor);
                printf("data telah tersimpan\n");
                break;

            case 4:
                status_dermaga(status); printf("\n");
                break;

            case 5:
                antrian_keluar(status); printf("\n");
                antrian_masuk(nomor, antrian, status); printf("\n");
                break;

            case 6:
                file_antrian(antrian, nomor);
                daftar_nomor(data_kapal);
                quick_sort(0, nomor - 1, data_kapal);
                file_urutan(data_kapal, nomor);
                total_masuk(nomor);
                printf("data telah tersimpan\n");
                pelabuhan = false;
                break;

            default:
                break;
        }
    } 

    return 0;
}

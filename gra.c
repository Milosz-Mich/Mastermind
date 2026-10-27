#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "gra.h"
#include "interfejs.h"


void plansza(int** zgadniecia, int aktualna_proba, int wyniki[N][2], int n){
    czyszczenie_ekranu();
    printf("====== MASTERMIND ======\n");
    printf("=PODAJ PRÓBĘ DŁUGOŚCI %d=\n", n);
    printf("%s1-● %s2-● %s3-● %s4-● %s5-● %s6-●\n" RESET, kolor(1), kolor(2), kolor(3), kolor(4), kolor(5), kolor(6));
    dzwieki(3);
    for(int i = 0; i < aktualna_proba; ++i){
        for(int j = 0; j < n; ++j){
            printf("%s● " RESET, kolor(zgadniecia[i][j]));
        }
        printf("| ");
        for(int j = 0; j < wyniki[i][0]; ++j){
            printf("%s● " RESET, kolor(-1)); //wypisanie czarnych
        }
        for(int j = 0; j < wyniki[i][1]; ++j){
            printf("%s● " RESET, kolor(0)); //wypisanie bialych
        }
        printf("\n");
    }
    if(aktualna_proba > 0){
        printf("========================\n");
    }
}

void koniec_gry(int* kod, int wygrana, int aktualna_proba, int n, int** zgadniecia, int wyniki[N][2], int zapis){
    if(wygrana){
        dzwieki(2);
        printf("%sGratulacje! Udalo ci sie zgadnac kod w %d probach!\n" RESET, kolor(6), aktualna_proba + 1);
        zapisywanie_wynikow(kod, aktualna_proba + 1, n, wygrana, zgadniecia, wyniki, n, zapis);
    }
    else{
        dzwieki(1);
        printf("\n%sKONIEC GRY! POPRAWNY KOD TO: " RESET, kolor(1));
        Sleep(150);
        for(int i = 0; i < n; ++i){
            Beep(1000 + kod[i] * 200, 150);
            printf("%s● " RESET, kolor(kod[i]));
            Sleep(150);
        }
        printf("\n");
        zapisywanie_wynikow(kod, aktualna_proba, n, wygrana, zgadniecia, wyniki, n, zapis);
    }
}

void wczytaj_kod(int* kod, int n){
    dzwieki(0);
    while(1){
        int udane_wczytanie = 1;
        czyszczenie_ekranu();
        printf("==== WITAJ W GRZE MASTERMIND ====\n====PODAJ KOD DO ZGADYWANIA====\n");
        printf("%s1-● %s2-● %s3-● %s4-● %s5-● %s6-●\n" RESET, kolor(1), kolor(2), kolor(3), kolor(4), kolor(5), kolor(6));
        for(int i = 0; i < n; ++i){
            if(scanf_s("%d", &kod[i]) < 1 || ferror(stdin) || kod[i] < 1 || kod[i] > 6){
                printf("Nieprawidłowy format kodu. Dostępne kolory to 1-6. Proszę spróbować ponownie\n");
                udane_wczytanie = 0;
                Sleep(1500);
                break;
            }
        }
        if(udane_wczytanie) break;
        czyszczenie_bufora();
        czyszczenie_ekranu();
    }
}

void losowy_kod(int* kod, int n){
    for(int i = 0; i < n; ++i){
        kod[i] = (rand()%6) + 1;
    }
    printf("==== WITAJ W GRZE MASTERMIND ====\n ==== KOD ZOSTAL WYGENEROWANY LOSOWO ====\n");
    dzwieki(0);
}

void tryb_gry(int* kod, int n){
    int wybor;
    printf("Wybierz tryb gry: \n1. Wprowadź kod samodzielnie\n2. Wygeneruj losowy kod\n");
    while(1){
        if(scanf_s("%d", &wybor) < 1 || ferror(stdin) || (wybor != 1 && wybor != 2)){
            printf("Nieprawidłowy wybór trybu, Wybierz 1 lub 2\n");
            czyszczenie_bufora();
            continue;
        }
        break;
    }
    if(wybor == 1){
        wczytaj_kod(kod, n);
    }
    else{
        losowy_kod(kod, n);
    }
}

int wczytaj_probe(int* proba, int n){
    for(int j = 0; j < n; ++j){
        if(scanf_s("%d", &proba[j]) < 1 || ferror(stdin) || proba[j] < 1 || proba[j] > 6){
            printf("Dostępne kolory to 1-6\n");
            _getch();
            return 0;
        }
    }
    return 1;
}

void ocen_probe(int* proba, int* kod, int* wynik, int n){
    int* kod_kopia = (int*)calloc(n, sizeof(int));
    int* proba_kopia = (int*)calloc(n, sizeof(int));
    if(kod_kopia == NULL || proba_kopia == NULL){
        free(kod_kopia);
        free(proba_kopia);
        return;
    }
    for(int j = 0; j < n; ++j){
        if(proba[j] == kod[j]){
           ++wynik[0];
            kod_kopia[j] = 1;
            proba_kopia[j] = 1;
        }
    }

    for(int j = 0; j < n; ++j){
        if(proba_kopia[j] == 1){
            continue;
        }
        for(int k = 0; k < n; ++k){
            if(kod_kopia[k] == 0 && proba[j] == kod[k]){
                ++wynik[1];
                kod_kopia[k] = 1;
                proba_kopia[j] = 1;
                break;
            }
        }
    }
    free(kod_kopia);
    free(proba_kopia);
}

int poziom_trudnosci() {
    int wybor;
    printf("Wybierz poziom trudności:\n1. Łatwy (4 grzybki)\n2. Średni (5 Grzybkow)\n3. Trudny (6 Grzybkow)\n4. Powrót do menu\n");
    while (1) {
        if (scanf_s("%d", &wybor) < 1 || ferror(stdin) || wybor < 1 || wybor > 4) {
            printf("Nieprawidłowy wybór, Wybierz 1, 2 lub 3\n");
            czyszczenie_bufora();
            continue;
        }
        break;
    }
    if (wybor == 1) {
        return 4;
    }
    else if (wybor == 2) {
        return 5;
    }
    else if (wybor == 3){
        return 6;
    }
    return 0; // Zwracamy 0 zeby sie cofnac do menu
}

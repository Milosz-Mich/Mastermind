#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "interfejs.h"

const char* kolor(int n){
    switch(n){
        case 1: return RED;
        case 2: return GREEN;
        case 3: return YELLOW;
        case 4: return BLUE;
        case 5: return PURPLE;
        case 6: return CYAN;
        case 0: return WHITE;
        case -1: return GRAY;
        default: return RESET;
    }
}

const char* kolor_do_pliku(int n){
    switch(n){
        case 1: return "Czerwony";
        case 2: return "Zielony";
        case 3: return "Zółty";
        case 4: return "Niebieski";
        case 5: return "Fioletowy";
        case 6: return "Cyjan";
        case 0: return "Biały";
        case -1: return "Czarny";
        default: return "Nieznany";
    }
}

void dzwieki(int n){
    switch (n){
        //Dzwiek na poczatek gry
        case 0:{
            // Rosnący pasaż (Arpeggio C-dur: C4, E4, G4, C5)
            Beep(261, 150); // C4
            Beep(329, 150); // E4
            Beep(392, 150); // G4
            Beep(523, 400); // C5
            break;
        }
        //Dzwiek na koniec gry (przegrana)
        case 1:{
            Beep(392, 400);  // G4
            Sleep(50);       // Krótka pauza zapobiegająca zlaniu się dźwięków
            Beep(370, 400);  // F#4
            Sleep(50);       
            Beep(349, 400);  // F4
            Sleep(50);       
            Beep(330, 1200); // E4
            break;
        }
        //Dzwiek na koniec gry (wygrana)
        case 2:{
            Beep(523, 200); // C5
            Beep(659, 200); // E5
            Beep(784, 200); // G5
            Beep(1047, 400); // High C6
            Sleep(100);
            Beep(784, 150); // G5
            Beep(1047, 400); // High C6
            break;
        }
        //Dzwiek na poczatek nowej rundy
        default:{
            Beep(750, 120);
            break;
        }
    }
}

void instrukcja() {
    FILE* plik;
    if (fopen_s(&plik, "instrukcja.txt", "r") != 0 || plik == NULL) {
        printf("Nie znaleziono pliku instrukcja.txt!\n");
        return;
    }
    int znak;
    while((znak = fgetc(plik)) != EOF){
        printf("%c", znak);
    }
    fclose(plik);
}

void zapisywanie_wynikow(int* kod, int aktualna_proba, int n, int wygrana, int** zgadniecia, int wyniki[N][2], int poziom_trudnosci, int zapis){
    if(zapis == 3){
        return; // Brak zapisu, koniec funkcji
    }
    FILE* plik;
    if(zapis == 2){
        czyszczenie_pliku();
    }
    if(fopen_s(&plik, "wyniki.txt", "a") != 0 || plik == NULL){
        return;
    }
    fprintf(plik, "======================================= WYNIK ROZGRYWKI===================================\n");
    fprintf(plik, "Gra rozegrana na %s poziomie trudności\n", (poziom_trudnosci == 4) ? "Łatwym" : (poziom_trudnosci == 5) ? "Średnim" : "Trudnym");
    fprintf(plik, "Kod: ");
    for(int i = 0; i < n; ++i){
        fprintf(plik, "●%s  ", kolor_do_pliku(kod[i]));
    }
    fprintf(plik, "\n");
    if(wygrana){
        fprintf(plik, "Wygrana w %d próbach\n", aktualna_proba);
    }
    else{
        fprintf(plik, "Przegrana\n");
    }
    fprintf(plik, "Próby:\n");
    for(int i = 0; i < aktualna_proba; ++i){
        for(int j = 0; j < n; ++j){
            fprintf(plik, "●%s  ", kolor_do_pliku(zgadniecia[i][j]));
        }
        fprintf(plik, "| ");
        for(int j = 0; j < wyniki[i][0]; ++j){
            fprintf(plik, "●%s  ", kolor_do_pliku(-1)); //czarny
        }
        for(int j = 0; j < wyniki[i][1]; ++j){
            fprintf(plik,"●%s  ", kolor_do_pliku(0)); //bialy
        }
        fprintf(plik, "\n");
    }
    fprintf(plik, "==========================================================================================\n\n");
    fclose(plik);
}

void czyszczenie_pliku(){
    FILE* plik;
    if(fopen_s(&plik, "wyniki.txt", "w") == 0 && plik != NULL){
        fclose(plik);
    }
    return;
}

int tryb_zapisu(){
    int wybor;
    while(1){
        czyszczenie_ekranu();
        printf("Czy chcesz dodać wynik do poprzedniej historii gier, czy zacząć nową historię? \n1. Dodaj\n2. Nowa historia\n3. Nie chce zapisywać\n");
        if(scanf_s("%d", &wybor) < 1 || ferror(stdin) || (wybor < 1 || wybor > 3)){
            printf("Nieprawidłowy wybór, Wybierz 1, 2 lub 3\n");
            czyszczenie_bufora();
            _getch();
            continue;
        }
        break;
    }
    return wybor;
}

void czyszczenie_ekranu(){
    printf("\033[H\033[J");
}

void czyszczenie_bufora(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int ekran_startowy() {
    int wybor;
    while (1) {
        czyszczenie_ekranu();
        printf("====== MASTERMIND ======\n\n");
        printf("1. Graj\n2. Instrukcja\n3. Autorzy\n4. Zakończ\n");
        if (scanf_s("%d", &wybor) < 1 || ferror(stdin) || wybor < 1 || wybor > 4) {
            printf("Nieprawidłowy wybór, Wybierz 1, 2, 3 lub 4\n");
            czyszczenie_bufora();
            _getch(); // Zatrzymanie ekranu do wcisniecia klawisza, zeby przeczytac blad
            continue;
        }
        if (wybor == 1) {

            return 1;
        }
        else if (wybor == 2) {
            czyszczenie_ekranu();
            instrukcja();
            printf("\nNaciśnij dowolny przycisk aby wrócić\n");
            _getch(); // Czekanie na dowolny klawisz bez ENTERU
            czyszczenie_ekranu();
        }
        else if (wybor == 3) {
            czyszczenie_ekranu();
            printf("Milosz Koziel\nMilosz Michalowski\n:3\n\n");
            printf("\nNaciśnij dowolny przycisk aby wrócić\n");
            _getch(); // Czekanie na dowolny klawisz bez ENTERU
            czyszczenie_ekranu();
        }
        else {
            czyszczenie_ekranu();
            exit(0);
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "gra.h"
#include "interfejs.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned int)time(NULL));
    while(1){
        int opcja = ekran_startowy();
        czyszczenie_ekranu();
        if (opcja == 1) {
            int n = poziom_trudnosci();
            if(n == 0){
                continue; // Cofamy do menu
            }
            int* kod = (int*)malloc(n * sizeof(int));
            if (kod == NULL) return  1;
            int wyniki[N][2] = { 0 };
            int** zgadniecia = (int**)malloc(N * sizeof(int*));
            if (zgadniecia == NULL) {
                free(kod);
                return 1;
            }
            for (int i = 0; i < N; ++i) {
                zgadniecia[i] = (int*)malloc(n * sizeof(int));
                if (zgadniecia[i] == NULL){
                    for(int j = 0; j < i; ++j){
                        free(zgadniecia[j]);
                    }
                    free(zgadniecia);
                    free(kod);
                    return 1;
                }
            }
            czyszczenie_ekranu();
            int zapis = tryb_zapisu();
            czyszczenie_ekranu();
            tryb_gry(kod, n);
            czyszczenie_ekranu();

            int aktualna_proba = 0;
            while (aktualna_proba < N) {
                plansza(zgadniecia, aktualna_proba, wyniki, n);
                if (!wczytaj_probe(zgadniecia[aktualna_proba], n)) {
                    czyszczenie_bufora();
                    czyszczenie_ekranu();
                    continue;
                }

                ocen_probe(zgadniecia[aktualna_proba], kod, wyniki[aktualna_proba], n);

                if (wyniki[aktualna_proba][0] == n) {
                    koniec_gry(kod, 1, aktualna_proba, n, zgadniecia, wyniki, zapis);
                    break;
                }
                ++aktualna_proba;
            }
            if (aktualna_proba == N) {
                koniec_gry(kod, 0, aktualna_proba, n, zgadniecia, wyniki, zapis);
            }
            for (int i = 0; i < N; ++i) {
                free(zgadniecia[i]);
            }
            free(zgadniecia);
            free(kod);
            printf("Naciśnij dowolny przycisk aby wrócić do menu...\n");
            _getch();
        }
    }
    return 0;
}
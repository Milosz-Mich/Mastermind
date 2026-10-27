#pragma once
#define N 10
void plansza(int** zgadniecia, int aktualna_proba, int wyniki[N][2], int n);
void koniec_gry(int* kod, int wygrana, int aktualna_proba, int n, int** zgadniecia, int wyniki[N][2], int zapis);
void ocen_probe(int* proba, int* kod, int* wynik, int n);
int wczytaj_probe(int* proba, int n);
void wczytaj_kod(int* kod, int n);
void tryb_gry(int* kod, int n);
void losowy_kod(int* kod, int n);
int poziom_trudnosci();

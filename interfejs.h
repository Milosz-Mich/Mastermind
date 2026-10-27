#pragma once
#include "gra.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define PURPLE "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BLACK  "\033[30m"
#define GRAY "\033[90m"
void czyszczenie_pliku();
void zapisywanie_wynikow(int* kod, int aktualna_proba, int n, int wygrana, int** zgadniecia, int wyniki[N][2], int poziom_trudnosci, int zapis);
void instrukcja();
void dzwieki(int n);
const char* kolor_do_pliku(int n);
const char* kolor(int n);
int tryb_zapisu();
int ekran_startowy();
void czyszczenie_ekranu();
void czyszczenie_bufora();

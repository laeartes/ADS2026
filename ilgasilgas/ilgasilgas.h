#ifndef ILGASILGAS_H
#define ILGASILGAS_H

#include <stdint.h>

typedef struct skaitmensMazgas {
    uint8_t skaitmuo;           
    struct skaitmensMazgas *kitas;  
} skaitmensMazgas;

typedef struct IlgasIlgas {
    skaitmensMazgas *galva;  
    int dydis;         
    int zenklas;         
} IlgasIlgas;

// Konstruktoriai / destruktoriai
IlgasIlgas* Sukurti();
void Naikinti(IlgasIlgas *n);

// Pagalbinės funkcijos
void PridetSkaitmena(IlgasIlgas *n, uint8_t d);
int GautDydi(IlgasIlgas *n);
void SpausdintIlgaIlga(IlgasIlgas *n);

// Matematinės operacijos
IlgasIlgas* Sudeti(IlgasIlgas *a, IlgasIlgas *b);
IlgasIlgas* Atimti(IlgasIlgas *a, IlgasIlgas *b);

// Papildomos pagalbinės
IlgasIlgas* Kopijuoti(IlgasIlgas *n);
int Palyginti(IlgasIlgas *a, IlgasIlgas *b); // 1 jei a>b, 0 jei lygus, -1 jei a<b
void PasalintiNereikalingusNulius(IlgasIlgas *n);

// sitos tai rimtos
IlgasIlgas* Dauginti(IlgasIlgas *a, IlgasIlgas *b);
IlgasIlgas* Dalyti(IlgasIlgas *a, IlgasIlgas *b);
IlgasIlgas* Liekana(IlgasIlgas *a, IlgasIlgas *b);

#endif
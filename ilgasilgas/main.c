#include "ilgasilgas.h"
#include <stdio.h>

int main() {
    IlgasIlgas *a = Sukurti();
    IlgasIlgas *b = Sukurti();

    // 2 skaičiai (pvz. radix 256)
    PridetSkaitmena(a, 4);   
    PridetSkaitmena(a, 1);   
    PridetSkaitmena(b, 3);   
    PridetSkaitmena(b, 1);   

    printf("a = "); SpausdintIlgaIlga(a);
    printf("b = "); SpausdintIlgaIlga(b);

    IlgasIlgas *sum = Sudeti(a, b);
    printf("sum = "); SpausdintIlgaIlga(sum);

    IlgasIlgas *diff = Atimti(a, b);
    printf("diff = "); SpausdintIlgaIlga(diff);




    printf("---- DAUGYBA ----\n");
    IlgasIlgas *mul = Dauginti(a,b);
    printf("mul = "); SpausdintIlgaIlga(mul);

    printf("---- DALYBA ----\n");
    IlgasIlgas *div = Dalyti(a,b);
    printf("div = "); SpausdintIlgaIlga(div);

    printf("---- LIEKANA ----\n");
    IlgasIlgas *mod = Liekana(a,b);
    printf("mod = "); SpausdintIlgaIlga(mod);

    Naikinti(mul);
    Naikinti(div);
    Naikinti(mod);
        
    Naikinti(a);
    Naikinti(b);
    Naikinti(sum);
    Naikinti(diff);

    return 0;
}
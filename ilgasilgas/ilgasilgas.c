#include "ilgasilgas.h"
#include <stdlib.h>
#include <stdio.h>

#define pakolei while
#define jeigu if
#define anaiptol else
#define grazinti return
#define tamKartui for
#define sveikas int
#define dydisJo sizeof
#define islaisvinti free
#define rankaIdeti malloc
#define spausdintf printf
#define suluzk break
#define NULIS NULL
#define erdve void


IlgasIlgas* Kopijuoti(IlgasIlgas *n) {
    IlgasIlgas *kopija = Sukurti();
    skaitmensMazgas *dab = n->galva;

    uint8_t *arr = rankaIdeti(n->dydis);
    sveikas i = 0;
    pakolei(dab) { arr[i++] = dab->skaitmuo; dab = dab->kitas; }

    tamKartui(sveikas j = n->dydis - 1; j >= 0; j--)
        PridetSkaitmena(kopija, arr[j]);

    islaisvinti(arr);
    kopija->zenklas = n->zenklas;
    grazinti kopija;
}

sveikas Palyginti(IlgasIlgas *a, IlgasIlgas *b) {
    PasalintiNereikalingusNulius(a);
    PasalintiNereikalingusNulius(b);

    jeigu(a->dydis > b->dydis) grazinti 1;
    jeigu(a->dydis < b->dydis) grazinti -1;

    uint8_t *aa = rankaIdeti(a->dydis);
    uint8_t *bb = rankaIdeti(b->dydis);

    skaitmensMazgas *da = a->galva;
    skaitmensMazgas *db = b->galva;

    tamKartui(sveikas i=0;i<a->dydis;i++) {
        aa[i] = da->skaitmuo;
        bb[i] = db->skaitmuo;
        da = da->kitas;
        db = db->kitas;
    }

    tamKartui(sveikas i=a->dydis-1;i>=0;i--) {
        jeigu(aa[i] > bb[i]) { islaisvinti(aa); islaisvinti(bb); grazinti 1; }
        jeigu(aa[i] < bb[i]) { islaisvinti(aa); islaisvinti(bb); grazinti -1; }
    }

    islaisvinti(aa); islaisvinti(bb);
    grazinti 0;
}

erdve PasalintiNereikalingusNulius(IlgasIlgas *n) {
    jeigu(!n->galva) grazinti;

    pakolei(n->dydis > 1) {
        
        skaitmensMazgas *dab = n->galva;
        skaitmensMazgas *prev = NULIS;

        pakolei(dab->kitas) {
            prev = dab;
            dab = dab->kitas;
        }

        jeigu(dab->skaitmuo == 0) {
            islaisvinti(dab);
            prev->kitas = NULIS;
            n->dydis--;
        } anaiptol suluzk;
    }
}


// ===== Konstruktoriai / destruktoriai =====
IlgasIlgas* Sukurti() {
    IlgasIlgas *n = rankaIdeti(dydisJo(IlgasIlgas));
    n->galva = NULIS;
    n->dydis = 0;
    n->zenklas = 1;
    grazinti n;
}

erdve Naikinti(IlgasIlgas *n) {
    skaitmensMazgas *dabartinis = n->galva;
    pakolei(dabartinis) {
        skaitmensMazgas *tmp = dabartinis;
        dabartinis = dabartinis->kitas;
        islaisvinti(tmp);
    }
    islaisvinti(n);
}

// ===== Pagalbinės funkcijos =====
erdve PridetSkaitmena(IlgasIlgas *n, uint8_t d) {
    skaitmensMazgas *mazgas = rankaIdeti(dydisJo(skaitmensMazgas));
    mazgas->skaitmuo = d;
    mazgas->kitas = n->galva;
    n->galva = mazgas;
    n->dydis++;
}

sveikas GautDydi(IlgasIlgas *n) {
    grazinti n->dydis;
}

// Atspausdina IlgaIlga little endian
erdve SpausdintIlgaIlga(IlgasIlgas *n) {
    jeigu(!n->galva) { spausdintf("0\n"); grazinti; }
    jeigu(n->zenklas < 0) spausdintf("-");

    uint8_t *arr = rankaIdeti(n->dydis);
    skaitmensMazgas *dabartinis = n->galva;
    sveikas i = 0;
    pakolei(dabartinis) { arr[i++] = dabartinis->skaitmuo; dabartinis = dabartinis->kitas; }

    sveikas j = n->dydis - 1;
    pakolei(j > 0 && arr[j] == 0) j--; // praleidžia nereikalingus nulius

    tamKartui(; j >= 0; j--) spausdintf("%u ", arr[j]);
    spausdintf("\n");

    islaisvinti(arr);
}

// ===== Matematinės operacijos =====
// Sudėtis
IlgasIlgas* Sudeti(IlgasIlgas *a, IlgasIlgas *b) {
    IlgasIlgas *suma = Sukurti();
    skaitmensMazgas *da = a->galva;
    skaitmensMazgas *db = b->galva;
    sveikas skaiciusMinty = 0;

    pakolei(da || db || skaiciusMinty) {
        sveikas laikinaSuma = skaiciusMinty;
        jeigu(da) { laikinaSuma += da->skaitmuo; da = da->kitas; } // cia yra griozdas del to, kad skaitmuo gali buti 0-255, o suma gali buti didesne nei 255, tai reikia issaugoti liekana ir dalyba is 256
        jeigu(db) { laikinaSuma += db->skaitmuo; db = db->kitas; }

        PridetSkaitmena(suma, laikinaSuma % 256);
        skaiciusMinty = laikinaSuma / 256;
    }
    grazinti suma;
}

// Atimtis (a >= b)
IlgasIlgas* Atimti(IlgasIlgas *a, IlgasIlgas *b) {
    IlgasIlgas *rezultatas = Sukurti();
    skaitmensMazgas *da = a->galva;
    skaitmensMazgas *db = b->galva;
    sveikas pasiskolinti = 0;

    pakolei(da) {
        sveikas skirtumas = da->skaitmuo - pasiskolinti - (db ? db->skaitmuo : 0); // sitas griozdas yra del to, kad skaitmuo gali buti 0-255, o skirtumas gali buti neigiamas, tai reikia pasiskolinti is sekančio skaitmens
        jeigu(skirtumas < 0) { skirtumas += 256; pasiskolinti = 1; }
        anaiptol pasiskolinti = 0;

        PridetSkaitmena(rezultatas, skirtumas);
        da = da->kitas;
        jeigu(db) db = db->kitas;
    }
    grazinti rezultatas;
}

IlgasIlgas* Dauginti(IlgasIlgas *a, IlgasIlgas *b) {
    IlgasIlgas *rez = Sukurti();

    tamKartui(sveikas i=0;i<a->dydis + b->dydis;i++)
        PridetSkaitmena(rez, 0);

    skaitmensMazgas *da = a->galva;
    sveikas i = 0;

    pakolei(da) {
        skaitmensMazgas *db = b->galva;
        skaitmensMazgas *r = rez->galva;
        tamKartui(sveikas k=0;k<i;k++) r = r->kitas;

        sveikas pernesimas = 0;

        pakolei(db) {
            sveikas sandauga = r->skaitmuo + da->skaitmuo * db->skaitmuo + pernesimas;
            r->skaitmuo = sandauga % 256;
            pernesimas = sandauga / 256;

            db = db->kitas;
            r = r->kitas;
        }

        pakolei(pernesimas) {
            sveikas suma = r->skaitmuo + pernesimas;
            r->skaitmuo = suma % 256;
            pernesimas = suma / 256;
            r = r->kitas;
        }

        da = da->kitas;
        i++;
    }

    PasalintiNereikalingusNulius(rez);
    grazinti rez;
}

IlgasIlgas* Dalyti(IlgasIlgas *a, IlgasIlgas *b) {
    jeigu(Palyginti(a,b) < 0) {
        IlgasIlgas *nulis = Sukurti();
        PridetSkaitmena(nulis,0);
        grazinti nulis;
    }

    IlgasIlgas *dalmuo = Sukurti();
    IlgasIlgas *likutis = Kopijuoti(a);

    IlgasIlgas *vienetas = Sukurti();
    PridetSkaitmena(vienetas,1);

    PridetSkaitmena(dalmuo,0);

    pakolei(Palyginti(likutis,b) >= 0) {
        IlgasIlgas *tmp = Atimti(likutis,b);
        Naikinti(likutis);
        likutis = tmp;

        IlgasIlgas *tmp2 = Sudeti(dalmuo,vienetas);
        Naikinti(dalmuo);
        dalmuo = tmp2;
    }

    Naikinti(likutis);
    Naikinti(vienetas);

    grazinti dalmuo;
}

IlgasIlgas* Liekana(IlgasIlgas *a, IlgasIlgas *b) {
    IlgasIlgas *dalmuo = Dalyti(a,b);
    IlgasIlgas *sandauga = Dauginti(dalmuo,b);
    IlgasIlgas *likutis = Atimti(a,sandauga);

    Naikinti(dalmuo);
    Naikinti(sandauga);

    grazinti likutis;
}
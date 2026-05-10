#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "priemimoKomisija.h"

static void trim(char *s) {
    char *p = s;
    // left
    while (*p == ' ' || *p == '\t') p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    // right
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == ' ' || s[len-1] == '\t' || s[len-1] == '\r' || s[len-1] == '\n')) {
        s[len-1] = '\0';
        len--;
    }
}

static int load_config(const char *path, int *g1, int *g2, double *prob, int *priemimoLaikas, int *sim_time) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '#' || *p == ';' || *p == '\n' || *p == '\0') continue;
        char *eq = strchr(p, '=');
        if (!eq) continue;
        *eq = '\0';
        char *key = p;
        char *val = eq + 1;
        trim(key);
        trim(val);
        if (strcmp(key, "darbuotoja1Greitis") == 0) *g1 = atoi(val);
        else if (strcmp(key, "darbuotoja2Greitis") == 0) *g2 = atoi(val);
        else if (strcmp(key, "atvykimoTikimybe") == 0) *prob = atof(val);
        else if (strcmp(key, "priemimoLaikas") == 0) *priemimoLaikas = atoi(val);
        else if (strcmp(key, "simuliacijosLaikas") == 0) *sim_time = atoi(val);
    }
    fclose(f);
    return 1;
}

int main(int argc, char **argv) {
    const char *cfg = "params.cfg"; // default
    if (argc > 1) cfg = argv[1];

    int darbuotoja1Greitis = 5;
    int darbuotoja2Greitis = 3;
    double atvykimoTikimybe = 0.5;
    int priemimoLaikas = 1;
    int simuliacijosLaikas = 1000;

    if (load_config(cfg, &darbuotoja1Greitis, &darbuotoja2Greitis, &atvykimoTikimybe, &priemimoLaikas, &simuliacijosLaikas)) {
        printf("Kraunu config iš %s\n", cfg);
    } else {
        printf("Naudoju numatytąsias reikšmes (konfigūracijos failas nerastas %s)\n", cfg);
    }

    srand((unsigned)time(NULL));
    simulate(darbuotoja1Greitis, darbuotoja2Greitis, atvykimoTikimybe, priemimoLaikas, simuliacijosLaikas);
    return 0;
}

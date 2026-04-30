
# 2 laboratorinis darbas

## Variantas

15 – triangular N-queens problem

## Aprašymas

Programa randa maksimalų nesikertančių valdovių skaičių trikampėje lentoje, naudojant perrinkimą (backtracking).

Palaikomi režimai:

* `fullSearch`
* `firstMatchSearch`
* `heuristic` – nerealizuota

Galimas darbo nutraukimas pagal laiką (`-timeout`).

## Paleidimas

```bash
PgmName.exe [-|failas] [-mode fullSearch|firstMatchSearch|heuristic n] [-timeout ms]
```

Pavyzdžiai:

```bash
PgmName.exe data.txt > result.txt
PgmName.exe - < data.txt > result.txt
```

## Įvedimas

Vienas skaičius:

```
N
```

## Išvedimas

* įvesties duomenys
* maksimalus valdovių skaičius
* lenta
* būsenos informacija (timeout / completed)

## Testai

Naudoti:

```
N = 3, 4, 5, 6, 7, 8, 9, 10
```


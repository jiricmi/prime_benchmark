# Prvočísla v C++
Milan Jiříček (jiricmi1) COMMIT (172a35b8)
## Zadání
 - Vytvořte program, který bude rozkládat čísla na prvočísla.
 - Porovnejte mezi sebou metodu Eratosthenova síta a Miller-Rabinova testu.
 - Porovnejte mezi sebou metodu hledání prvočísel a Pollardova Rho algoritmu.
## Ovládání programu
CMake generuje program s názvem `PrimeNumber`.
Tento program je možné spustit argumenty, či bez argumentů.
Pokud program spustíme bez argumentů, tak se spustí interaktivní mód pomocí konzole, kde se program vyptává.
Pokud program spustíme s argumenty, tak se vstup bere pomocí souboru.
Více k nalezení v nápovědě programu.
### Vlastnosti
- Program umí načítat vstup ze souboru, ale také z konzole.
- Program umí výsledky zapisovat do souboru, ale také na konzoli.
- Je možné si vybrat, které algoritmy se mají použít.
## Popis použitých algoritmů
### Eratosthenovo síto
Eratosthenovo síto je algoritmus pro hledání prvočísel.
Tento algoritmus se nám hodí pro nalezení všech prvočísel v daném intervalu a následném hledání prvočíselného rozkladu. 
#### Popis algoritmu
- Vytvoříme si pole o velikosti n+1, kde n je horní hranice intervalu.
- Všechny prvky pole nastavíme na true.
- Nastavíme si proměnnou i na 2.
- Dále budeme procházet pole pres všechny prvky od 2 do n.
  - pokud je prvek na pozici i nastaven na true, tak procházíme všechny násobky čísla i a nastavíme je na false.
  - pokud je prvek na pozici i nastaven na false, tak se posuneme na další prvek.
- Výsledkem je pole, kde jsou na pozicích prvočísla nastavena na true a ostatní na false.

### Miller-Rabinův test
Miller-Rabinův test je pravděpodobnostní test prvočíselnosti.
Pokud algoritmus určí, že číslo neni prvočíslo, tak je to jistě pravda.
Pokud algoritmus určí, že číslo je prvočíslo, tak je to pravděpodobně pravda.
Nicméně existují čísla, která jsou složená, ale algoritmus je považuje za prvočísla. Tento jev se dá omezit opakováním testu.
#### Popis algoritmu
- Nejdříve si musíme zvolit číslo k, které bude určovat, kolikrát se bude test opakovat.
- Číslo n rozložíme na tvar n-1 = 2^s * d, kde d je liché číslo.
- Vypočítáme si a^d mod n, kde a je náhodné číslo z intervalu <2, n-2>.
- Pokud výsledek je roven 1 nebo existuje číslo r z intervalu <0, s-1>, pro které platí a^(2^r * d) mod n = n-1, tak číslo n pravděpodobně je prvočíslo.
- Pokud výsledek není roven 1 ani neexistuje číslo r, tak číslo n není prvočíslo.
Implementací jsem se inspiroval na [wikipedii](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Miller%E2%80%93Rabin_test).
#### Paralelizace
Paralelizace je možná, jelikož každý test je nezávislý na ostatních. V tomto případě je to možné protože testujeme kazdé číslo zvlášť.
Proto jsem se rozhodl vytvořit vlákna, které budou testovat čísla zvlášť a následně se spojí.  
- Vlákna mají přístup k proměnné, která funguje jako index, které číslo se bude testovat
  - Pokud je index vetší než horní hranice intervalu, tak vlákno skončí.
  - Pro předcházaní kolizí je použit mutex, který se zamkne před kontrolou indexu a odemkne se po zvýšení indexu.
- Následně se provede Miller-Rabinův test pro konkrétní číslo.
- Pokud je číslo prvočíslo, tak se výsledek uloží do pole.
  - Z důvodu kolizí je použit mutex, který se zamkne před zápisem do pole a odemkne se po zápisu.
- Pokud je číslo složené, tak se pokračuje na další číslo.

### Standardní metoda rozkladu na prvočísla
Standardní metoda rozkladu na prvočísla je algoritmus, který postupně dělí číslo n prvočísly od 2 do n.
#### Popis algoritmu
- Nejdříve si musíme najít všechna prvočísla v intervalu <2, n>.
- Následně od nejmenšího prvočísla dělíme číslo n až do doby dokud je to možné.
- Výsledkem je pole prvočísel, které jsme našli.
### Pollardův Rho algoritmus
Pollardův Rho algoritmus je algoritmus pro rozklad čísla na prvočísla.
Tento algoritmus se nám hodí pro rozklad čísla na prvočísla, ale ne vždy se nám podaří číslo rozložit.
Existují čísla, které čistě tímto algoritmem nelze rozložit, například číslo 8 či 25 a další. Záleží na zvolené náhodné funkci.
#### Popis algoritmu
- Zvolíme si náhodnou funkci, která bude generovat posloupnost čísel. V tomto případě jsem zvolil funkci x^2 + 1 mod n, dle doporučení z [wikipedie](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm).
- Následně si zvolíme čísla x a y a následně je budeme postupně vkládat do funkce (y budeme vkládat 2x).
- Pokud najdeme společného dělitele čísla n, tak jsme našli člen prvočíselného rozkladu.
- Pokud společný dělitel je n samotné, tak jsme nerozložili číslo.
Implementací jsem se inspiroval na [wikipedii](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm).

## Vysledky měření
### Porovnání Eratosthenova síta a Miller-Rabinova testu
Z měření je vidět, že Eratosthenovo síto je rychlejší než Miller-Rabinův test. Sice síto je velice naivní algoritmus, ale Miller-Rabinův test je dobrý pro testování jednoho čísla.
Nicméně výhodou Miller-Rabinova testu je, že je možné ho paralelizovat.
#### Tabulka a graf
| Řád       | Eratosthenovo síto | Miller-Rabinův test K=20 | Miller-Rabinův test K=10 | Miller-Rabinův test K=5 | Miller-Rabinův test K=3 | Miller-Rabinův test K=1 |
|-----------|--------------------|--------------------------|--------------------------|-------------------------|-------------------------|-------------------------|
| 10        | 3.00E-06           | 1.70E-05                 | 1.00E-06                 | 1.00E-06                | 0                       | 0                       |
| 50        | 0                  | 1.90E-05                 | 1.10E-05                 | 7.00E-06                | 5.00E-06                | 3.00E-06                |
| 100       | 0                  | 3.80E-05                 | 2.30E-05                 | 1.40E-05                | 1.10E-05                | 8.00E-06                |
| 500       | 2.00E-06           | 0.000212                 | 0.000133                 | 9.20E-05                | 7.50E-05                | 5.70E-05                |
| 1000      | 5.00E-06           | 0.000439                 | 0.000277                 | 0.000204                | 0.000162                | 0.000125                |
| 5000      | 2.20E-05           | 0.002299                 | 0.001513                 | 0.001152                | 0.000972                | 0.000755                |
| 10000     | 4.30E-05           | 0.004677                 | 0.003124                 | 0.002277                | 0.001936                | 0.001664                |
| 50000     | 0.000216           | 0.024313                 | 0.016481                 | 0.012782                | 0.010873                | 0.009141                |
| 100000    | 0.000413           | 0.051042                 | 0.033382                 | 0.0257                  | 0.02225                 | 0.018925                |
| 500000    | 0.002054           | 0.251013                 | 0.17566                  | 0.142037                | 0.121079                | 0.104101                |
| 1000000   | 0.004119           | 0.505121                 | 0.356843                 | 0.281968                | 0.250487                | 0.219417                |
| 5000000   | 0.022052           | 2.63618                  | 1.88808                  | 1.51157                 | 1.35889                 | 1.20401                 |
| 10000000  | 0.050678           | 5.32541                  | 3.84619                  | 3.09472                 | 2.78539                 | 2.47364                 |
| 50000000  | 0.401962           | 27.5259                  | 20.2881                  | 16.5269                 | 15.0477                 | 13.5034                 |
| 100000000 | 0.851974           | 57.0717                  | 42.3483                  | 38.9574                 | 32.7669                 | 29.0042                 |


![miller.png](pictures%2Fmiller.png)

### Porovnání Eratosthenova síta a Miller-Rabinova testu s paralelizací
Po výsledcích měření můžeme vidět, že paralelizace zrychlila Miller-Rabinův test, ale stále je pomalejší než Eratosthenovo síto.
Paralelizace 

#### Tabulka a graf
| Řád       | Miller-Rabinův test K=3 | Miller-Rabinův test K=3 paralelizace |
|-----------|-------------------------|--------------------------------------|
| 10        | 1e-06                   | 0.000347                             |
| 50        | 1.2e-05                 | 0.000141                             |
| 100       | 2.4e-05                 | 0.000143                             |
| 500       | 0.000135                | 0.000219                             |
| 1000      | 0.000279                | 0.000303                             |
| 5000      | 0.00151                 | 0.001224                             |
| 10000     | 0.003372                | 0.002372                             |
| 50000     | 0.016342                | 0.011732                             |
| 100000    | 0.033993                | 0.023789                             |
| 500000    | 0.179824                | 0.11453                              |
| 1000000   | 0.366422                | 0.230072                             |
| 5000000   | 1.94108                 | 1.16062                              |
| 10000000  | 4.03203                 | 2.31858                              |
| 50000000  | 21.166                  | 12.6395                              |
| 100000000 | 44.4489                 | 26.3836                              |

![parallel.png](pictures%2Fparallel.png)
### Porovnání hledání prvočísel a Pollardova Rho algoritmu
Z měření můžeme vidět, že standardní metoda a Pollardův Rho algoritmus mají podobnou rychlost až do velikosti řádu 1000000.
Při standardní metodě si nejprve najdu prvočísla pomocí Eratosthenova síta.  
Poté se rychlost standardní metody zpomaluje až na 0.623631s pro 100000000. Takže pro větší čísla je výhodnější použít Pollardův Rho algoritmus.  
Nicméně při Pollardově Rho algoritmu existují čísla, která nejsou schopna rozložit. například číslo 8 či 25 a další, tzn. udělá se rozklad pouze částečně.
V tomto měření to bylo 49.5 % čísel, které se podařilo rozložit pouze částečně.
Při standardní metodě se nám vždy podaří číslo rozložit, ale je pomalejší, protože musíme procházet všechna čísla od 2 do n.

V dalším testování jsem vyzkoušel tento problém vyřešit tak, že použiji Pollardův Rho algoritmus a poté zkontroluji, zda všechna čísla v rozkladu jsou prvočísla.
Pokud ne, tak použiji standardní metodu.
Tímto způsobem se mi podařilo rozložit všechna čísla, ale rychlost se zpomalila. Nicméně jelikož standartní metoda pracuje s menšimi čísly, tak jsme dokázali najít kompromis.
#### Tabulka a graf
| Řád       | Standardní metoda | Pollardův Rho algoritmus | Pollardův Rho algoritmus s opravou |
|-----------|-------------------|--------------------------|------------------------------------|
| 50        | 5.00E-08          | 0                        | 5.10E-07                           |
| 100       | 0                 | 1.00E-08                 | 8.20E-07                           |
| 500       | 5.70E-07          | 2.00E-07                 | 1.65E-06                           |
| 1000      | 2.07E-06          | 7.50E-07                 | 3.09E-06                           |
| 5000      | 1.04E-05          | 8.20E-07                 | 6.72E-06                           |
| 10000     | 2.62E-05          | 2.46E-06                 | 9.81E-06                           |
| 50000     | 9.23E-05          | 3.80E-06                 | 3.60E-05                           |
| 100000    | 2.63E-04          | 5.71E-06                 | 5.48E-05                           |
| 500000    | 1.07E-03          | 1.29E-05                 | 1.46E-04                           |
| 1000000   | 2.89E-03          | 3.06E-05                 | 3.63E-04                           |
| 5000000   | 1.25E-02          | 3.50E-05                 | 1.32E-03                           |
| 10000000  | 3.49E-02          | 6.49E-05                 | 3.34E-03                           |
| 50000000  | 2.05E-01          | 9.57E-05                 | 2.47E-02                           |
| 100000000 | 6.21E-01          | 2.36E-04                 | 7.34E-02                           |
  

![mes_stand_pollard.png](pictures%2Fmes_stand_pollard.png)
![me_fix.png](pictures%2Fme_fix.png)

## Závěr

### Eratosthenovo síto a Miller-Rabinův test
Z výsledků měření je zřejmé, že Eratosthenovo síto je rychlejší než Miller-Rabinův test. Je to z důvodu, že Miller-Rabinův test je pravděpodobnostní test, který je dobrý pro testování jednoho čísla.
Nicméně výhodou Miller-Rabinova testu je, že je možné ho paralelizovat, což zrychlí testování, nicméně na mém setupu paralelizace nepomohla, ale rychlost se dostala na polovinu při velkých číslech.
### Hledání prvočísel a Pollardův Rho algoritmus
Z výsledků měření můžeme vidět, že pro malá čísla (do 50) je výhodnější použít standardní metodu, jelikož je rychlejší.
Pro větší čísla je výhodnější použít Pollardův Rho algoritmus, jelikož je rychlejší, ale ne vždy se nám podaří číslo rozložit.
Nejlepší výsledky jsme dosáhli při použití Pollardova Rho algoritmu a následném použití standardní metody pro čísla, která se nám nepodařilo rozložit.

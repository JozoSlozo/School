
# Zadání čislo 2
## Minimální cena přepravy zboží
### Problém
V tomto zadání máte za úkol optimalizovat cenu přepravy zboží v logistické síti mezi městy, která
je reprezentována jako neorientovaný vážený graf. Města představují vrcholy grafu, cesty jsou re-
prezentovány neorientovanými váženými hranami, kde váha představuje cenu přepravy zboží mezi
těmito městy. Vaším úkolem je nalézt trasu s minimální cenou přepravy zboží z města 𝐴 do města
𝐵 a to:
• v původní logistické síti a
• v pozměněné logistické síti – na jednu libovolnou hranu grafu můžete aplikovat 50% slevu na
cenu přepravy.
### Řešení
Problém řešíme použitím Dijkstrova algoritmu pro hledání nejkratší cesty mezi vrcholy grafu. Dijkstrův algorytmus upravíme, pro vyhledávání cesty se slevou a to tak že si pro každý vrchol pamatujeme cenu beze slevy a cenu ze slevou. Protože chceme aby sleva byla použita jenom jednou musíme vždy přičitat neslevněnou cestu se slevněnou. Počítáni se slevou by nemělo změnit časovou náročnost algorytmu.
### Kompilace
```
g++ ./main.cpp DijkstraAlgorythm.cpp -o main
```
### Github
[https://github.com/JozoSlozo/school/tree/main/AGLII/projekt](https://github.com/JozoSlozo/school/tree/main/AGLII/projekt)

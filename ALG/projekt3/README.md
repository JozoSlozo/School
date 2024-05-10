# Projekt ALG zadání 3

## Zadání 
### Problém
Předmětem tohoto zadání jsou polynomy, v češtině nazývané též mnohočleny. Takovým polynomem
je například výraz 3𝑥2 − 7𝑥 + 5. Čísla 3, -7 a 5 se nazývají koeficienty polynomu. Nejvyšší mocninu
s nenulovým koeficientem nazýváme stupeň polynomu, v našem případě je to 2. Obecně můžeme
polynom 𝑛-tého stupně zapsat jako


$`P(x) = a_{n}x^{n} + a_{n-1}x^{n-1} + ... + a_{2}x^{2} + a_{1}x^{1} + a_{0}x^{0}`$

Další příklady asi není nutné uvádět, neboť se jedná o středoškolskou matematiku, kterou jistě ovlá-
dáte. Jinak vše potřebné najdete například na Wikipedii, https://cs.wikipedia.org/wiki/
Polynom, nebo v angličtině https://en.wikipedia.org/wiki/Polynomial, a samozřejmě
v učebnicích matematiky pro střední a vysoké školy.

Polynom 𝑃(𝑥) je jednoznačně zadán stupněm 𝑛 a 𝑛 + 1 koeficienty 𝑎𝑛, 𝑎𝑛−1, … , 𝑎2, 𝑎1, 𝑎0.
Vaším úkolem je navrhnout vhodnou reprezentaci polynomu a implementovat následující ope-
race s polynomy:

1. vytvoření polynomu z daného pole nebo vektoru A, kde prvku pole či vektoru A[i] odpovídá
koeficient 𝑎𝑖,
2. vytvoření polynomu z jednoho čísla a, které bude reprezentovat koeficient 𝑎0 polynomu nul-
tého stupně,
3. výpis polynomu na standardní výstup,
4. stupeň polynomu,
5. hodnotu polynomu v daném bodě 𝑥0,
6. součet dvou polynomů,
7. rozdíl dvou polynomů,
8. součin dvou polynomů,
9. derivaci polynomu a
10. primitivní funkci k danému polynomu.

### Ukázkový příklad
Mějme dáno pole double A[] = {4, 5, −1, 7, 0, 3}; . Tomuto poli odpovídá polynom

𝑃(𝑥) = 3𝑥5 + 7𝑥3 − 𝑥2 + 5𝑥 + 4

Dále například číslu −2 odpovídá polynom nultého stupně −2𝑥0 = −2. Například hodnota polynomu
pro 𝑥0 = 5 je

𝑃(5) = 3 ⋅ 55 + 7 ⋅ 53 − 52 + 5 ⋅ 5 + 4

= 3 ⋅ 3125 + 7 ⋅ 125 − 25 + 25 + 4

= 9375 + 875 − 25 + 25 + 4

= 10254

### Poznámky

• Přestože v příkladech jsou koeficienty polynomu celá čísla, implementace by měla používat
čísla s plovoucí řádovou čárkou.

• Řešení zadání musí obsahovat i testovací aplikaci, která postupně zavolá všechny implemen-
tované funkce bez interakce s uživatelem, tj. bez toho, aby uživatel vybíral jakou akci chce
s polynomy provést, zadával polynomy ze standardního vstupu. Testovací polynomy budou
zadány jako konstanty ve zdrojovém kódu.


## Kompilace
doxygen
```console
x@y:~/school/ALG/projekt3$ doxygen dconfig
```
program
```console
x@y:~/school/ALG/projekt3$ g++ main.cpp utils.cpp polynomial.cpp -o main
x@y:~/school/ALG/projekt3$ ./main
```
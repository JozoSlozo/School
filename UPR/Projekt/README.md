Epidemiologické modelování

Program simuluje vývoj epidemie pomocí SIR modelu.

argumenty:
--real_data <cesta k souboru> - cesta k CSV souboru s daty o průběhu pandemie, musí mít příponu .csv
--infectious_days <celé číslo> - počet dnů, během kterých je jedinec nakažlivý, musí být číslo větší než nula
--infections_per_day <desetinné číslo> - počet lidí, které nakažený člověk nakazí za jeden den, musí být číslo větší než mula
--output <cesta k souboru> - cesta k výstupnímu souboru s vizualizací predikce a reálných dat, musí obsahovat nějakou příponu

Výstupem programu je SVG graf v HTML stránce, který zobrazuje vývoj epidemie v průběhu 100 dní.

Program se překládá pomocí CMakeLists.txt pomocí příkazů
$ mkdir build
$ cd build
$ cmake ..
$ make

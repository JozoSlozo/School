#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using std::vector, std::pair;

/**
 * @brief Struktura pro data vrcholů.
 */
struct dijsktraVertex
{
    /**
     * @brief Index vrcholu.
     */
    int index;
    /**
     * @brief Cena od počátečního vrcholu.
     */
    double cost;
    /**
     * @brief Cena od počátečního vrcholu se slevou.
     */
    double cost_discounted;

    dijsktraVertex(int i, double c, double cs){
        index = i;
        cost = c;
        cost_discounted = cs;
    }
    dijsktraVertex(int i){
        index = i;
        cost = std::numeric_limits<double>::max();
        cost_discounted = std::numeric_limits<double>::max();
    }
    dijsktraVertex(){
        index = 0;
        cost = 0;
        cost_discounted = 0;
    }
    /**
     * @brief Funkce pro nalezení nejmenší ceny do tohoto vrcholu.
     */
    double getMinDistance(){
        return std::min(cost, cost_discounted);
    }
};

/**
 * @brief Pomocná struktura pro správné porovnání vrcholů v prioritní frontě.
 * 
 * Tato struktura definuje podmínku pro porovnávání dvou vrcholů typu `dijsktraVertex` podle jejich minimální vzdálenosti.
 */
struct compareDijsktraVertex{
    bool operator()(dijsktraVertex &a, dijsktraVertex &b){
        return a.getMinDistance() > b.getMinDistance();
    }
};

/**
 * @class dijkstraAlgorythm
 * @brief Třída pro hledání nejlevnější cesty mezi vrcholy.
 */
class dijkstraAlgorythm {
private:
    /**
     * @brief Vrchol, ve kterém začínáme.
     */
    int start_vertex;
    /**
     * @brief Vrchol, do kterého se snažíme dostat.
     */
    int end_vertex;
    /**
     * @brief Velikost matice sousednosti.
     */
    int size;
    /**
     * @brief Matice sousednosti.
     */
    vector<vector<double>> adjacency_matrix;
    /**
     * @brief Cena od počátečního vrcholu k vrcholu daném indexem ve vektoru.
     */
    vector<dijsktraVertex> cost_to_vertex;
    /**
     * @brief Předchozí vrchol k vrcholu danému indexem ve vektoru.
     * První int v pairu je bez slevy, druhý je se slevou.
     */
    vector<pair<int, int>> parent_vertex;
    /**
     * @brief Prioritní fronta, která ukládá vrcholy s nejmenší vzdáleností bez ohledu na to, zda jsou se slevou nebo bez.
     */
    std::priority_queue<dijsktraVertex, std::vector<dijsktraVertex>, compareDijsktraVertex> dijkstra_queue;
    /**
     * @brief Funkce pro vytvoření cesty z počátečního vrcholu do cílového.
     * 
     * Prochází vektor `parent` dokud nedorazí na počáteční vrchol a poté otočí finální vektor a uloží do `final_path` nebo `final_path_discounted`.
     */
    int constructFinalPath();

    vector<int> constructPath(int first_or_second);

    /**
     * @brief Funkce pro hledání nejlevnější cesty mezi počátečním a cílovým vrcholem.
     * 
     * Funkce používá Dijkstrův algoritmus pro nalezení nejlevnější cesty a ukládá výsledky do `final_cost` a `final_cost_discounted`.
     */
    int solveDijkstra();

public:
    /**
     * @brief Cesta z počátečního vrcholu do cílového vrcholu.
     */
    vector<int> final_path;

    /**
     * @brief Nejlevnější cena cesty.
     */
    double final_cost;

    /**
     * @brief Cesta z počátečního vrcholu do cílového vrcholu se slevou na jednu cenu hrany.
     */
    vector<int> final_path_discounted;

    /**
     * @brief Nejlevnější cena cesty se slevou na jednu cenu hrany.
     */
    double final_cost_discounted;

    /**
     * @brief Konstruktor třídy, který spouští Dijkstrův algoritmus.
     * 
     * @param adjacency_matrix_input Matice sousednosti.
     * @param start_vertex_input Vrchol, ve kterém začínáme.
     * @param end_vertex_input Vrchol, do kterého se snažíme dostat.
     * @param adjacency_matrix_size Velikost matice sousednosti.
     */
    dijkstraAlgorythm(vector<vector<double>> adjacency_matrix_input, int start_vertex_input, int end_vertex_input, int adjacency_matrix_size);
};

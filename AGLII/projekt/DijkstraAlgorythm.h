#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using std::vector, std::pair;

/**
 * @class dijkstraAlgorythm
 * @brief Třída která hledá nejlevnější cestu mezi vercholy
 */
class dijkstraAlgorythm {
private:
    /**
     * @brief Vrchol ve kterém začínáme.
     */
    int start_vertex;

    /**
     * @brief Vrchol do kterého se snaíme dostat.
     */
    int end_vertex;

    /**
     * @brief Velikost matice sousednosti.
     */
    int size;

    /**
     * @brief Matice sousednosti
     */
    vector<vector<double>> adjacency_matrix;

    /**
     * @brief Vzdálenost od začátečního vrcholu k vrcholu daném indexem ve vectoru.
     */
    vector<double> distance_to_vertex;

    /**
     * @brief Předchozí vrchol k vrcholu daného indexem ve vektoru.
     */
    vector<int> parent_vertex;

    /**
     * @brief Prioritní fronta, která ukládá vrchol s nejmenší vzdáleností.
     */
    std::priority_queue<pair<double, int>, std::vector<pair<double, int>>, std::greater<>> dijkstra_queue;

    /**
     * @brief Funkce vytvoří cestu ze začátečního vrcholu do konečného.
     * 
     * Prochází vektor parent dokud nedorazí na začátek a potom finální vektor otočí.
     * 
     * @return Vektor intů kde každý int je číslo vrcholu
     */
    vector<int> constructFinalPath();

    /**
     * @brief Funkce hledající nejlevnější cestu mezi začátečním a konečným vrcholem
     * 
     * Funkce používá Dijkstrův algoritmus. 
     * 
     * @param input_adjacency_matrix Matice sousednosti.
     * @return Nejlevnější cena cesty.
     */
    double solveDijkstra(const vector<vector<double>>& input_adjacency_matrix);

    /**
     * @brief Hledá nejlevnější cestu po zlevnění jedné hrany
     * 
     * Prochází každou hranu a zlevní ji o 50%, potom použije Dijkstrův algoritmus a zvolí nejlevnější možnost.
     */
    void getDiscounted();

public:
    /**
     * @brief Cesta z počátečního vrcholu do koncového vrcholu.
     */
    vector<int> final_path;

    /**
     * @brief Nejlevnější cena cesty.
     */
    double final_cost;

    /**
     * @brief Cesta z počátečního vrcholu do koncového vrcholu po slevě jedné ceny hrany.
     */
    vector<int> final_path_discounted;

    /**
     * @brief Nejlevnější cena cesty po slevě jedné ceny hrany.
     */
    double final_cost_discounted;

    /**
     * @brief Konstruktor třídy, spouští se zde funkce řešící algoritmus.
     * 
     * @param adjacency_matrix_input Matice sousednosti.
     * @param start_vertex_input Vrchol ve kterém začínáme.
     * @param end_vertex_input Vrchol do kterého se snažíme dostat.
     * @param adjacency_matrix_size Velikost matice.
     */
    dijkstraAlgorythm(vector<vector<double>> adjacency_matrix_input, int start_vertex_input, int end_vertex_input, int adjacency_matrix_size);
};

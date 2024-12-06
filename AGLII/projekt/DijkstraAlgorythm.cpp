#include "DijkstraAlgorythm.h"
#include <algorithm>
#include <limits>

using std::vector;
using std::pair;

typedef pair<double, int> vertex;

/**
 * @brief Funkce vytvoří cestu ze začátečního vrcholu do konečného
 */
vector<int> dijkstraAlgorythm::constructFinalPath() {
    vector<int> final_path_vector;
    int current_vertex = end_vertex;
    final_path_vector.push_back(current_vertex);
    while (current_vertex != start_vertex) {
        current_vertex = parent_vertex[current_vertex];
        final_path_vector.push_back(current_vertex);
    }
    std::reverse(final_path_vector.begin(), final_path_vector.end());
    return final_path_vector;
}

/**
 * @brief Funkce hledající nejlevnější cestu mezi začátečním a konečným vrcholem
 */
double dijkstraAlgorythm::solveDijkstra(const vector<vector<double>>& input_adjacency_matrix) {
    distance_to_vertex[start_vertex] = 0;
    dijkstra_queue.push({0, start_vertex});
    while (!dijkstra_queue.empty()) {
        vertex current_vertex = dijkstra_queue.top();
        dijkstra_queue.pop();
        if (current_vertex.first > distance_to_vertex[current_vertex.second]) {
            continue;
        }
        if (current_vertex.second == end_vertex) {
            return distance_to_vertex[end_vertex] == std::numeric_limits<double>::max() ? -1 : distance_to_vertex[end_vertex];
        }

        for (int end_vertex = 0; end_vertex < size; end_vertex++) {
            double current_cost = input_adjacency_matrix[current_vertex.second][end_vertex];
            if (current_cost <= 0) {//if is valid 
                continue;
            }
            double new_distance = distance_to_vertex[current_vertex.second] + current_cost;
            if (new_distance < distance_to_vertex[end_vertex]) {
                distance_to_vertex[end_vertex] = new_distance;
                parent_vertex[end_vertex] = current_vertex.second;
                dijkstra_queue.push({new_distance, end_vertex});
            }
        }
    }
    return distance_to_vertex[end_vertex] == std::numeric_limits<double>::max() ? -1 : distance_to_vertex[end_vertex];
}

/**
 * @brief Hledá nejlevnější cestu po zlevnění jedné hrany
 */
void dijkstraAlgorythm::getDiscounted() {
    double min_cost = std::numeric_limits<double>::max();
    vector<int> best_path;
     
    for (int row = 0; row < size; ++row) {
        for (int column = row + 1; column < size; ++column) {
            if (adjacency_matrix[row][column] > 0) {
                auto originalCost = adjacency_matrix[row][column];
                adjacency_matrix[row][column] *= 0.5;
                adjacency_matrix[column][row] *= 0.5;

                double current_cost = solveDijkstra(adjacency_matrix);
                if (current_cost != -1 && current_cost < min_cost) {
                    min_cost = current_cost;
                    best_path = constructFinalPath();
                }

                adjacency_matrix[row][column] = originalCost;
                adjacency_matrix[column][row] = originalCost;
            }
        }
    }
    final_cost_discounted = min_cost;
    final_path_discounted = best_path;
}

/**
 * @brief Konstruktor funkce, spouští se zde funkce řešící algoritmus
 */
dijkstraAlgorythm::dijkstraAlgorythm(vector<vector<double>> adjacency_matrix_input, int start_vertex_input, int end_vertex_input, int adjacency_matrix_size) {
    this->size = adjacency_matrix_size;
    this->distance_to_vertex = vector<double>(this->size, std::numeric_limits<double>::max());
    this->parent_vertex = vector<int>(this->size, -1);
    this->start_vertex = start_vertex_input;
    this->end_vertex = end_vertex_input;
    this->adjacency_matrix = adjacency_matrix_input;
    final_cost = solveDijkstra(adjacency_matrix);
    final_path = constructFinalPath();
    getDiscounted();
}

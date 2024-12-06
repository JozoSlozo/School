#include "DijkstraAlgorythm.h"
#include <algorithm>
#include <limits>

using std::vector;
using std::pair;

vector<int> dijkstraAlgorythm::constructPath(int first_or_second){
    vector<int> path;
    int current_vertex = end_vertex;
    path.push_back(current_vertex);
    while (current_vertex != start_vertex) {
        current_vertex = first_or_second == 0 ? parent_vertex[current_vertex].first : parent_vertex[current_vertex].second;
        path.push_back(current_vertex);
    }
    std::reverse(path.begin(), path.end()); 
    return path;
}

/**
 * @brief Vytvoří cestu z počátečního vrcholu do cílového.
 */
int dijkstraAlgorythm::constructFinalPath() {
    final_path = constructPath(0);
    final_path_discounted = constructPath(1);
    return 0;
}

/**
 * @brief Hledá nejlevnější cestu mezi počátečním a cílovým vrcholem pomocí Dijkstrova algoritmu.
 */
int dijkstraAlgorythm::solveDijkstra() {

    //set starting vertex distance to 0
    cost_to_vertex[start_vertex].cost = 0;
    cost_to_vertex[start_vertex].cost_discounted = 0;

    dijkstra_queue.push(dijsktraVertex(start_vertex, 0, 0));

    while (!dijkstra_queue.empty()) {
        dijsktraVertex current_vertex = dijkstra_queue.top(); //top is always the cheapest vertex to get to
        dijkstra_queue.pop();

        if (current_vertex.getMinDistance() > cost_to_vertex[current_vertex.index].getMinDistance()) {
            continue;
        }
        
        if (current_vertex.index == end_vertex) { //if end reached
            if (cost_to_vertex[end_vertex].cost == std::numeric_limits<double>::max() || cost_to_vertex[end_vertex].cost_discounted == std::numeric_limits<double>::max())
            {
                final_cost = -1;
                final_cost_discounted = -1;
                return 1;
            }
            final_cost = cost_to_vertex[end_vertex].cost;
            final_cost_discounted = cost_to_vertex[end_vertex].cost_discounted;
            return 0;
        }

        for (int end_vertex = 0; end_vertex < size; end_vertex++) {

            double current_cost = adjacency_matrix[current_vertex.index][end_vertex]; //gets cost of current edge
            
            if (current_cost <= 0) { //if the edge is not valid
                continue;
            }
            
            double new_cost = cost_to_vertex[current_vertex.index].cost + current_cost; //not discounted cost
            //discounted cost, we cant add 2 discounted paths together
            double new_cost_discounted = std::min(cost_to_vertex[current_vertex.index].cost_discounted + current_cost, cost_to_vertex[current_vertex.index].cost + (current_cost / 2));
            
            dijsktraVertex temp = dijsktraVertex(end_vertex, cost_to_vertex[end_vertex].cost, cost_to_vertex[end_vertex].cost_discounted);
            int changed = 0;

            if (new_cost < cost_to_vertex[end_vertex].cost) {
                cost_to_vertex[end_vertex].cost = new_cost;
                parent_vertex[end_vertex].first = current_vertex.index;
                temp.cost = new_cost;
                changed = 1;
            }
            if (new_cost_discounted < cost_to_vertex[end_vertex].cost_discounted) {
                cost_to_vertex[end_vertex].cost_discounted = new_cost_discounted;
                parent_vertex[end_vertex].second = current_vertex.index;
                temp.cost_discounted = new_cost_discounted;
                changed = 1;
            }
            if (changed) {
                dijkstra_queue.push(temp);
            }
            
        }
    }
    if (cost_to_vertex[end_vertex].cost == std::numeric_limits<double>::max() || cost_to_vertex[end_vertex].cost_discounted == std::numeric_limits<double>::max())
    {
        final_cost = -1;
        final_cost_discounted = -1;
        return 1;
    }
    final_cost = cost_to_vertex[end_vertex].cost;
    final_cost_discounted = cost_to_vertex[end_vertex].cost_discounted;
    return 0;
}

/**
 * @brief Konstruktor třídy, který spouští Dijkstrovu algoritmus pro hledání nejkratší cesty.
 */
dijkstraAlgorythm::dijkstraAlgorythm(vector<vector<double>> adjacency_matrix_input, int start_vertex_input, int end_vertex_input, int adjacency_matrix_size) {
    this->size = adjacency_matrix_size;
    this->cost_to_vertex = vector<dijsktraVertex>(this->size, dijsktraVertex(-1));
    this->parent_vertex = vector<pair<int, int>>(this->size, {-1, -1});
    this->start_vertex = start_vertex_input;
    this->end_vertex = end_vertex_input;
    this->adjacency_matrix = adjacency_matrix_input;
    if (!solveDijkstra())
    {
        constructFinalPath();
    }
}
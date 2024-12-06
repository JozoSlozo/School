#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "DijkstraAlgorythm.h"

using std::vector, std::string, std::cout, std::cerr, std::endl, std::pair;

/**
 * @brief Pomocná funkce pro čtení souboru
 * 
 */
int readFile(const string& file_name, vector<vector<double>>& final_matrix, int& size, int& start, int& end) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        return 0;
    }
    string line;
    std::getline(file, line);
    size = std::stoi(line);
    for (int i = 0; i < size; i++) {
        std::getline(file, line);
        std::stringstream line_as_atream(line);
        double num;
        vector<double> temp_vector;
        while (line_as_atream >> num) {
            temp_vector.push_back(num);
        }
        final_matrix.push_back(temp_vector);
    }
    std::getline(file, line);
    start = std::stoi(line);
    std::getline(file, line);
    end = std::stoi(line);
    file.close();
    return 1;
}

int main(int argc, char* argv[]) {
    (void)argc;
    int start;
    int end;
    int size;
    vector<vector<double>> temp;
    if (!readFile(argv[1], temp, size, start, end)) {
        cerr << "Unable to open file " << argv[1] << endl;
        return -1;
    }

    dijkstraAlgorythm da = dijkstraAlgorythm(temp, start, end, size);

    cout << std::fixed << std::setprecision(2);

    cout << "Nejlevnější cena cesty: " << da.final_cost  << "\nNejlevnější cesta: ";

    for (int i : da.final_path) {
        cout << i << ", ";
    }
    cout << "\n";
    cout << "Nejlevnější cena cesty se slevou: " << da.final_cost_discounted  << "\nNejlevnější cesta se slevou: ";

    for (int i : da.final_path_discounted) {
        cout << i << ", ";
    }
    cout << "\n";
    return 0;
}

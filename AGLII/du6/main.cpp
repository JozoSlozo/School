#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::vector, std::string, std::cout;

vector<vector<int>> readIntegersFromFile(const string& file_name) {
    std::ifstream file(file_name);
    vector<vector<int>> final_vector;

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << file_name << std::endl;
        return final_vector;
    }

    string line;
    size_t index = 0;

    while (std::getline(file, line)) {

        std::stringstream line_as_atream(line);
        int num;
        vector<int> temp_vector;

        while (line_as_atream >> num) {
            temp_vector.push_back(num);
        }
        index++;
        final_vector.push_back(temp_vector);
    }

    file.close();
    return final_vector;
}

vector<vector<int>> solveTransitiveClosure(vector<vector<int>> input_matrix){
    if (input_matrix.size() != input_matrix[0].size())
    {
        std::cerr << "Invalid matrix size" << std::endl;
        return input_matrix;
    }
    size_t size = input_matrix.size();
    for (size_t iter = 0; iter < size; iter++)
    {
        vector<vector<int>> temp_vector = input_matrix;
        for (size_t row = 0; row < size; row++)
        {
            for (size_t column = 0; column < size; column++)
            {
                input_matrix[row][column] = temp_vector[row][column] || (temp_vector[row][iter] && temp_vector[iter][column]);
            }
        }
    }
    return input_matrix;
}

int main(int argc, char* argv[]){
    vector<vector<int>> matrix = solveTransitiveClosure(readIntegersFromFile(argv[1]));
    size_t size = matrix.size();
    (void)argc;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
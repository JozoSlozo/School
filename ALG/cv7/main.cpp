#include <vector>
#include <iostream>
#include <cmath>
#include <stack>
#include <unordered_map>
using namespace std;

int bruteForceBatoh(const vector<int>& values, const vector<int>& weogths, const int limit){
    int items = values.size();
    int k;
    int mini_mask;
    int index;
    int sum_of_values;
    int sum_of_weigths;
    int max_value = -1;

    for (int i = 0; i < pow(2, items); i++)
    {
        k = i;
        index = 0;
        sum_of_values = 0;
        sum_of_weigths = 0;
        while (k > 0)
        {
            mini_mask = k % 2;
            k /= 2;
            index++;
            sum_of_values += mini_mask * values[index];
            sum_of_weigths += mini_mask * weogths[index];
        }
        if (sum_of_weigths < limit)
        {
            max_value = max(max_value, sum_of_values);
        }
    }
    return max_value;
}

struct Graph
{
    unordered_map<int, vector<int>> adjacency_list;
    unordered_map<int, int> label_to_index;
    int num_of_vertices;
};

void CreateLabelToIndex(Graph& g){
    unordered_map<int, int> label_to_index;
    int index = 0;
    for (const auto& [vertex, friends] : g.adjacency_list)
    {
        label_to_index[vertex] = index;
        index++;
    }
    g.label_to_index = label_to_index;
}

vector<vector<int>> CreateAdjacencyMatrix(const Graph& g){
    int n = g.num_of_vertices;
    vector<vector<int>> m(n, vector<int>(n, 0));
    for (const auto& [vertex, friends] : g.adjacency_list)
    {
        for (int friend_ : friends){
            m[g.label_to_index.at(vertex)][g.label_to_index.at(friend_)] = 1;
            m[g.label_to_index.at(friend_)][g.label_to_index.at(vertex)] = 1;
        }
    }
    return m;
}

void MatrixPP(const vector<vector<int>> m){
    for (vector<int> line : m)
    {
        for(int num : line){
            cout << num << " ";
        }
        cout << endl;
    }
    
}

int main(){
    Graph g;
    g.adjacency_list[5] = {7};
    g.adjacency_list[7] = {5,8,1};
    g.adjacency_list[8] = {7,4};
    g.adjacency_list[1] = {7,5};
    g.adjacency_list[4] = {1,8};
    g.num_of_vertices = 5;
    CreateLabelToIndex(g);
    vector<vector<int>> temp = CreateAdjacencyMatrix(g);
    MatrixPP(temp);
    return 0;
}
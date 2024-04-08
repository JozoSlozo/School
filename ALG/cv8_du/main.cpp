using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Graph {
    unordered_map <int, vector<int>> adjacency_list; 
    unordered_map<int, int> vertex_to_mat_index;
    int no_of_vertices;
    int no_of_edges;
};

void printGraph (const Graph & graph) {
    std::cout << "Graph: \n";
    for (const auto&[vertex, neighbours] : graph.adjacency_list) { 
        std::cout << vertex << ": ";
        for(int neighbour : neighbours) {
            std::cout << neighbour << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

bool isIn(vector<int> searchIn, int searching){
    auto found = find(searchIn.begin(), searchIn.end(), searching);
    if (found == searchIn.end())
    {
        return 0;
    }
    return 1;
}

Graph readGraphFromFile (const string & filename) {
    Graph graph;
    string line;
    ifstream file(filename);

    while (getline(file, line))
    {
        vector<int> vertexes;
        stringstream lineStream(line);
        int vertex;
        char separator;

        while(lineStream >> vertex) {
            lineStream >> separator;//loads characters to separator, basically skips char
            vertexes.push_back(vertex);//puts intigers into vertexes
        }

        for (int i = 1; i < vertexes.size(); i++)
        {
            if (!isIn(graph.adjacency_list[vertexes[0]], vertexes[i]))//checks for any repeating vertexes
            {
                graph.adjacency_list[vertexes[0]].emplace_back(vertexes[i]);//puts neighbors into the vertex
            }

            if (!isIn(graph.adjacency_list[vertexes[i]], vertexes[0]))//checks for any repeating vertexes
            {
                graph.adjacency_list[vertexes[i]].emplace_back(vertexes[0]);//puts neighbots into vertex so its two way
            }
        }
        
    }
    graph.no_of_vertices = graph.adjacency_list.size();
    file.close();
    return graph;
}

vector<vector<int>> createAdjacencyMatrix (const Graph & graph) {
    int n = graph.no_of_vertices;
    vector<vector<int>> matrix (n, vector<int>(n, 0));
    for (const auto& [vertex, friends] : graph.adjacency_list)
    {
        for (int friend_ : friends){
            matrix[graph.vertex_to_mat_index.at(vertex)][graph.vertex_to_mat_index.at(friend_)] = 1;
            matrix[graph.vertex_to_mat_index.at(friend_)][graph.vertex_to_mat_index.at(vertex)] = 1;
        }
    }
    return matrix;
}
void constructIndexingMap (Graph& graph) {
    int index = 0;
    unordered_map<int, int > res;
    for (const auto& kv: graph.adjacency_list) { 
        res[kv.first] = index;
        index += 1;
    }
    graph.vertex_to_mat_index = res;
}

void printGraphIndexingMap (const Graph & graph) {
    std::cout << "Graph vertex to index map (vertex, index):\n";
    for (const auto&[vertex, index] : graph.vertex_to_mat_index) { 
        std::cout << vertex << ": " << index << ", ";
    }
    std::cout << std::endl;
}

int seachByValue(unordered_map<int, int> map, int val){
    for (auto&[f, s] : map)
    {
        if (s == val)
        {
            return f;
        }
    }
    return 0;
}

void printAdjacencyMatrix (const Graph& graph) {
    int index = 0;
    cout << "Graph adjacency matrix:\nx ";
    for (int i = 0; i < graph.no_of_vertices; i++)
    {
        cout << seachByValue(graph.vertex_to_mat_index, i) << " ";
    }
    cout << endl;
    for (auto& line: createAdjacencyMatrix(graph)) {
        cout << seachByValue(graph.vertex_to_mat_index, index) << " ";
        for (int val: line) {
            std::cout << val << " ";
        }
        index++;
        std::cout << "\n";
    }
}
int main(){
    Graph mainGraph;
    string file = "testfile.txt";
    mainGraph = readGraphFromFile(file);
    constructIndexingMap(mainGraph);
    printGraph(mainGraph);
    printGraphIndexingMap(mainGraph);
    printAdjacencyMatrix(mainGraph);
    return 0;
}
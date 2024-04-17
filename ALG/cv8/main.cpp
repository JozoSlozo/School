using namespace std;
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <random>

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
unordered_map<int, std::vector<int>> generateRandomGraph(int number_of_vertices, double edge_probability, unsigned int seed) {
    std::unordered_map<int, std::vector<int>> adj_list;

    // Explicit seed
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Iterate over all pairs of vertices and add edges with probability edge_probability
    for (int i = 0; i < number_of_vertices; ++i) {
        for (int j = i + 1; j < number_of_vertices; ++j) {
            if (dis(gen) < edge_probability) {
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }
    }

    return adj_list;
}
unordered_set<int> projit(const Graph& graph, int starting_point){
    unordered_set<int> isDone;
    stack<int> st;
    
    st.push(starting_point);
    isDone.insert(starting_point);

    while (!st.empty())
    {
        int current = st.top();
        st.pop();

        isDone.insert(current);
        vector<int> neighbours = graph.adjacency_list.at(current);
        for (int vertex : neighbours)
        {
            if(isDone.find(vertex) == isDone.end()){
                st.push(vertex);
                isDone.insert(vertex);
            }
            
        }       
    }
    return isDone;
}
int numberOfComponents(const Graph& graph, int starting_point){
    int number = 1;
    unordered_set<int> proslo;
    int point = starting_point;

    while (proslo.size() != graph.adjacency_list.size())
    {
        for (int i : projit(graph, point))
        {
            proslo.insert(i);
        }
        for (const auto& [vertex, neighbour] : graph.adjacency_list)
        {
            if(proslo.find(vertex) == proslo.end()){
                point = vertex;
                number+=1;
                break;
            }
        }
    }
    return number;
    
}

int main(){
    Graph mainGraph;
    string file = "testfile.txt";
    mainGraph = readGraphFromFile(file);
    printGraph(mainGraph);
    cout << numberOfComponents(mainGraph, 1) << endl;
}
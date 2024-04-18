using namespace std;
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

vector<int> InsertionSort(vector<int> vec){
    int v;
    int j;
    for (int i = 1; i < vec.size(); i++)
    {
        v = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > v)
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = v;
    }
    return vec;
}

struct orientedGraph
{
    unordered_map<int, vector<int>> adj_list;
};

void addEdge(orientedGraph& graph, pair<int, int> edge){
    graph.adj_list[edge.first].push_back(edge.second);
}
void deleteEdge(orientedGraph& graph, pair<int, int> edge){
    for (int i = 0; i < graph.adj_list[edge.first].size(); i++)
    {
        if (graph.adj_list[edge.first][i] == edge.second)
        {
            graph.adj_list[edge.first].erase(graph.adj_list[edge.first].begin() + i);
            break;
        }
    }
}
void deleteLeaf(orientedGraph& graph, int edge){
    graph.adj_list.erase(edge);
}
void printGraph(const orientedGraph g){
    for (auto& [vertex, neighbours] : g.adj_list)
    {
        cout <<  vertex << ": ";
        for (int neighbour : neighbours)
        {
            cout << neighbour << " ";
        }
        cout << endl;
    }
    
}

bool isIn(vector<int> searchIn, int searching){
    auto found = find(searchIn.begin(), searchIn.end(), searching);
    if (found == searchIn.end())
    {
        return 0;
    }
    return 1;
}

vector<int> topologicalSort(orientedGraph& graph,vector<int> sorted_list){

    if (graph.adj_list.empty())
    {
        return sorted_list;
    }
    
    int candidate;
    for(const auto&[candidate, _] : graph.adj_list){
        bool temp = 0;
        for(const auto[vertex, neighbours] : graph.adj_list){
            if (isIn(neighbours, candidate))
            {
                temp = 1;
                break;
            }
        }
        if (temp)
        {
            break;
        }
    }
    sorted_list.push_back(candidate);
    return sorted_list;
}

int main(){
    vector<int> temp = {1,5,4,7,8,2,3,5,4,7,9,6,3,1,4};
    for (int i : InsertionSort(temp))
    {
        cout << i << ", ";
    }
    cout << endl;

    orientedGraph g;
    addEdge(g, {1,3});
    addEdge(g, {2,3});
    addEdge(g, {3,4});
    addEdge(g, {3,5});
    addEdge(g, {4,5});
    printGraph(g);
    vector<int> v;
    for (int i : topologicalSort(g, v))
    {
        cout << i << ", ";
    }
    cout << endl;
    return 0;
}
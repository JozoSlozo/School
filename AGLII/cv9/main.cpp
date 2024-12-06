#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <optional>
#include <limits>
using std::vector, std::map;

class unionBySize
{
    private:
        map<int, int> parent;
        map<int, int> sizes;
    public:
        void makeSet(int x){
            if (parent.find(x) != parent.end())
            {
                return;
            }
            parent[x] = x;
            sizes[x] = 1;
        }
        void oneUnion(int x, int y){
            int rootx = find(x);
            int rooty = find(y);

            if (sizes[rootx] < sizes[rooty])
            {
                std::swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            parent[rootx] += sizes[rooty];
            
        }
        int find(int x){
            if (parent[x] != x)
            {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        bool isInTheSamePartition(int x, int y){
            return find(x) == find(y);
        }
};
using weightedEdge = std::pair<int, std::pair<int, int>>;

class Graph{
    public:
    vector<weightedEdge> edge;
    map<int, vector<weightedEdge>> vertextoEdges;
    map<int, vector<int>> vertextoNeighbours;
    vector<int> vertices;
};
void naiveDijkstra(Graph graph, int initialVertex){
    std::priority_queue<weightedEdge, vector<weightedEdge>, std::less<>> dijkstraQ;
    std::unordered_map<int, int> distance;
    std::unordered_map<int, std::optional<int>> entryPoints;
    for(auto vertex : graph.vertices){
        distance[vertex] = std::numeric_limits<int>::max();
        entryPoints[vertex] = std::nullopt;
    }
    for (auto edge : graph.edge)
    {
        dijkstraQ.push(edge);
    }
    
    distance[initialVertex] = 0;
    for (int i = 0; i < graph.vertices.size() - 1; i++)
    {
        /* code */
    }
    
}

int main(){
    unionBySize myUnion;
    vector<int> inputdata = {1,2,3,4};
    for (auto item : inputdata)
    {
        myUnion.makeSet(item);
    }
    myUnion.oneUnion(1,2);
    std::cout << myUnion.isInTheSamePartition(1,2) << "\n";
    myUnion.oneUnion(1,3);
    std::cout << myUnion.isInTheSamePartition(1,3) << "\n";
        
    return 0;
}
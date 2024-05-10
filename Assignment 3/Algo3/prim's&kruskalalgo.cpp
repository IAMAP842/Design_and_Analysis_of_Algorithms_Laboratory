#include <bits/stdc++.h>
using namespace std;
struct Edge
{
    int src, dest, weight;
};
class Graph
{
public:
    int V;
    vector<Edge> edges;
    Graph(int V) : V(V) {}
    void addEdge(int src, int dest, int weight)
    {
        edges.push_back({src, dest, weight});
    }
};
class UnionFind
{
public:
    vector<int> parent, rank;
    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
                swap(rootX, rootY);
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY])
                rank[rootX]++;
        }
    }
};
struct CompareWeight
{
    bool operator()(const Edge &e1, const Edge &e2)
    {
        return e1.weight > e2.weight;
    }
};
vector<Edge> kruskalMST(Graph &graph)
{   vector<Edge> MST;
    sort(graph.edges.begin(), graph.edges.end(), CompareWeight());
    UnionFind uf(graph.V);
    for (const auto &edge : graph.edges)
    {
        int src = edge.src;
        int dest = edge.dest;
        if (uf.find(src) != uf.find(dest))
        {
            MST.push_back(edge);
            uf.unite(src, dest);
        }
    }
    return MST;
}
vector<Edge> primMST(Graph &graph)
{   vector<Edge> MST;
    vector<bool> visited(graph.V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    while (!pq.empty())
    {
        pair<int, int> minEdge = pq.top();
        pq.pop();
        int weight = minEdge.first;
        int vertex = minEdge.second;
        if (visited[vertex])
            continue;
        visited[vertex] = true;
        for (const auto &edge : graph.edges)
        {
            if (edge.src == vertex && !visited[edge.dest])
                pq.push({edge.weight, edge.dest});
            else if (edge.dest == vertex && !visited[edge.src])
                pq.push({edge.weight, edge.src});
        }
        if (!MST.empty() || visited[vertex])
        {
            for (const auto &edge : graph.edges)
            {
                if ((edge.src == vertex && visited[edge.dest]) ||
                    (edge.dest == vertex && visited[edge.src]))
                    MST.push_back(edge);
            }
        }
    }
    return MST;
}
void printMST(const vector<Edge> &MST)
{
    int totalWeight = 0;
    for (const auto &edge : MST)
    {
        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight of MST: " << totalWeight << endl;
}
int main()
{   Graph graph(4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);
    cout << "Kruskal's MST:" << endl;
    auto kruskal_result = kruskalMST(graph);
    printMST(kruskal_result);
    cout << "\nPrim's MST:" << endl;
    auto prim_result = primMST(graph);
    printMST(prim_result);
    return 0;
}
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// In color
// "b" stands for "black"
// "g" stands for "grey"
// "w" stands for "white"

typedef struct nodestr{
    vector<int> adj;
    char color;
    int pi;
    int number;
} Node;

vector<vector<int>> graph;

vector<Node> dfsGraph;

vector<int> sources;

int maxNumber = 1;

int readGraph()
{
    int n, m;
    int counter = 0;

    scanf("%d %d", &n, &m);

    graph = vector<vector<int>>(n, vector<int>());
    vector<int> isSource = vector<int>(n, 1);

    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u - 1].push_back(v);
        isSource[v - 1] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (isSource[i] == 1)
        {
            sources.push_back(i + 1);
            counter++;
        }
    }
    return counter;
}

void DFSVisit(int i, int counter)
{
    dfsGraph[i].color = 'g';

    printf("counter: %d\n", counter);

    for (int j = 0; j < dfsGraph[i].adj.size(); j++)
    {
        Node node = dfsGraph[dfsGraph[i].adj[j] - 1];
        if (node.color == 'w')
        {
            node.pi = i + 1;
            counter++;
            DFSVisit(node.number, counter);
        }
    }
}

void DFS(int n)
{
    dfsGraph = vector<Node>(graph.size());
    for (int i = 0; i < graph.size(); i++)
    {
        dfsGraph[i].color = 'w';
        dfsGraph[i].pi = -1;
        dfsGraph[i].adj = graph[i];
        dfsGraph[i].number = i + 1;
    }
    
    if(dfsGraph[n].color == 'w')
    {
        DFSVisit(n, 0);
    }
}

int main()
{

    int min = readGraph();

    DFS(3);

    return 0;
}
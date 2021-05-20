#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define VERTIX_X 0
#define VERTIX_Y 1

using namespace std;


typedef struct edgeStruct{
    int vertex;
    int capacity;
} Edge;

vector<vector<Edge>> graph;

//buildGraph will fill nVertices with the graphs number of vertices
vector<vector<Edge>> buildGraph(int* nVertices)
{
    int n, k;
    int xBuffer, yBuffer;
    int capacity, processA, processB;
    vector<vector<Edge>> graph = vector<vector<Edge>>();
    scanf("%d %d", &n, &k);

    *nVertices = n + 2;

    //Processor X
    graph.push_back(vector<Edge>());
    //Processor Y
    graph.push_back(vector<Edge>());

    for (int i = 2; i < n + 2; i++)
    {
        Edge edgeX, edgeY;
        Edge edgeXT, edgeYT;
        scanf("%d %d", &xBuffer, &yBuffer);

        graph.push_back(vector<Edge>());

        //X connects to processes
        edgeX.vertex = i;
        edgeX.capacity = xBuffer;
        graph[VERTIX_X].push_back(edgeX);

        //Processes connect to Y
        edgeY.vertex = VERTIX_Y;
        edgeY.capacity = yBuffer;
        graph.back().push_back(edgeY);

        //Processes connect to X (residual)
        edgeXT.vertex = VERTIX_X;
        edgeXT.capacity = 0;
        graph.back().push_back(edgeXT);

        //Y connects to processes (residual)
        edgeYT.vertex = i;
        edgeYT.capacity = 0;
        graph[VERTIX_Y].push_back(edgeYT);
    }

    for (int i = 2; i < k + 2; i++)
    {
        //Cost represent the conections between processes
        //The edges between these are not directed
        Edge edgeA, edgeB;
        scanf("%d %d %d", &processA, &processB, &capacity);

        edgeA.vertex = processB + 1;
        edgeA.capacity = capacity;
        graph[processA + 1].push_back(edgeA);

        edgeB.vertex =  processA + 1;
        edgeB.capacity = capacity;
        graph[processB + 1].push_back(edgeB);
    }

    return graph;
}

bool bfs(int* path, int nVertices)
{
    bool visited[nVertices];
    queue<int> queue;
    memset(visited, false, sizeof(visited));

    queue.push(VERTIX_X);
    path[VERTIX_X] = 0; //VERTIX_X is the source, so it has no path parent
    visited[VERTIX_X] = true;

    while (!queue.empty())
    {
        int son;
        int parent = queue.front();
        queue.pop();
        for (long unsigned int i = 0; i < graph[parent].size(); i++)
        {
            son = graph[parent][i].vertex;
            if (!visited[son] && graph[parent][i].capacity > 0)
            {
                if (son == VERTIX_Y)
                {
                    path[son] = parent;
                    return true;
                }
                queue.push(son);
                path[son] = parent;
                visited[son] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(int nVertices)
{
    int v;

    //Getting filled by BFS
    int path[nVertices];
    int maxFlow = 0;
    int uIndex = 0;
    int iIndex = 0;

    while (bfs(path, nVertices))
    {
        int currentFlow = __INT_MAX__;
        for (int i = VERTIX_Y; i != VERTIX_X; i = path[i])
        {
            v = path[i];
            for (long unsigned int j = 0; j < graph[v].size(); j++)
            {
                if (graph[v][j].vertex == i)
                {
                    uIndex = j;
                    break;
                }
            }
            currentFlow = min(graph[v][uIndex].capacity, currentFlow);
        }
        
        for (int i = VERTIX_Y; i != VERTIX_X; i = path[i])
        {
            v = path[i];
            for (long unsigned int j = 0; j < graph[v].size(); j++)
            {
                if (graph[v][j].vertex == i)
                {
                    uIndex = j;
                    break;
                }
            }
            for (long unsigned int j = 0; j < graph[i].size(); j++)
            {
                if (graph[i][j].vertex == v)
                {
                    iIndex = j;
                    break;
                }
            }
            
            //If its a path envolving X or Y, behave normally
            if (i == VERTIX_X || i == VERTIX_Y || v == VERTIX_X || v == VERTIX_Y)
            {
                graph[i][iIndex].capacity += currentFlow;
                graph[v][uIndex].capacity -= currentFlow;
            }
            //If its a path between processes, its residual edge will be affected in the same manner as its normal edge (instead of simetrical)
            else
            {
                graph[i][iIndex].capacity -= currentFlow;
                graph[v][uIndex].capacity -= currentFlow;
            }
        }
        maxFlow += currentFlow;
    }
    return maxFlow;
}

int main()
{
    int nVertices;

    //nVertices will be filled by buildGraph
    graph = buildGraph(&nVertices);

    printf("%d\n", fordFulkerson(nVertices));

    return 0;
}
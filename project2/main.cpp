#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define VERTIX_X 0
#define VERTIX_Y 1
#define INT_MAX 2147483647

using namespace std;

typedef struct edgeStruct{
    int vertex;
    int capacity;
} Edge;

//Prints the graph
void graphPrinter(vector<vector<Edge>> graph)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            char strint[10];
            char first[10];
            char last[10];
            sprintf(strint, "%d", i - 1);
            strcpy(first, (i == 0) ? "X" : (i == 1) ? "Y" : strint);
            sprintf(strint, "%d", graph[i][j].vertex - 1);
            strcpy(last, (graph[i][j].vertex == 0) ? "X" : (graph[i][j].vertex == 1) ? "Y" : strint);
            printf("%s connects to %s with a capacity of %d\n", first , last, graph[i][j].capacity);
        }
    }
}

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

bool bfs(vector<vector<Edge>> graph, int* path, int nVertices)
{
    bool visited[nVertices];
    memset(visited, false, sizeof(visited));

    queue<int> q;
    q.push(VERTIX_X);
    visited[VERTIX_X] = true;
    path[VERTIX_X] = -1;

    while (!q.empty())
    {
        int son;
        int parent = q.front();
        q.pop();
        //printf("PARENT: %d\n", parent);
        for (int i = 0; i < graph[parent].size(); i++)
        {
            son = graph[parent][i].vertex;
            if (!visited[son] && graph[parent][i].capacity > 0)
            {
                if (son == VERTIX_Y)
                {
                    path[son] = parent;
                    //printf("SON: %d\nFINISHED!\n", son);
                    return true;
                }
                q.push(son);
                //printf("SON: %d\n", son);
                path[son] = parent;
                visited[son] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<Edge>> graph, int nVertices)
{
    printf("hello");

    vector<vector<Edge>> newGraph = vector<vector<Edge>>();

    int u;

    for (int i = 0; i < nVertices; i++)
    {
        newGraph.push_back(vector<Edge>());
        for (int j = 0; j < graph[i].size(); j++)
        {
            Edge edge;
            edge.vertex = graph[i][j].vertex;
            edge.capacity = graph[i][j].capacity;
            newGraph[i].push_back(edge);
        }   
    }

    //Getting filled by BFS
    int path[nVertices];
    int maxFlow = 0;

    while (bfs(newGraph, path, nVertices))
    {
        int pathFlow = INT_MAX;
        for (int i = VERTIX_Y; i != VERTIX_X; i++)
        {
            u = path[i];
            pathFlow = min(pathFlow, newGraph[u][i].capacity);
        }
        
        for (int i = VERTIX_Y; i != VERTIX_X; i++)
        {
            u = path[i];
            if (i == VERTIX_X || i == VERTIX_Y || u == VERTIX_X || u == VERTIX_Y)
            {
                newGraph[u][i].capacity -= pathFlow;
                newGraph[u][i].capacity += pathFlow;
                printf("case1\n");
            }
            else
            {
                newGraph[u][i].capacity -= pathFlow;
                newGraph[u][i].capacity -= pathFlow;
                printf("case2\n");
            }
            maxFlow += pathFlow;
        }
    }
    return maxFlow;
}

int main()
{
    int nVertices;

    vector<vector<Edge>> graph = buildGraph(&nVertices);

    graphPrinter(graph);

    printf("%d\n", fordFulkerson(graph, nVertices));

    return 0;
}
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

vector<vector<Edge>> graph;


//Prints the graph
/*void graphPrinter(vector<vector<Edge>> graph)
{
    for (int i = 0; i < 6; i++)
    {
        for (long unsigned int j = 0; j < graph[i].size(); j++)
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
}*/

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

        //Processes connect to X
        edgeXT.vertex = VERTIX_X;
        edgeXT.capacity = 0;
        graph.back().push_back(edgeXT);

        //Y connects to processes
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
        for (long unsigned int i = 0; i < graph[parent].size(); i++)
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

int fordFulkerson(int nVertices)
{
    int u;

    /*for (int i = 0; i < nVertices; i++)
    {
        graph.push_back(vector<Edge>());
        for (long unsigned int j = 0; j < graph[i].size(); j++)
        {
            Edge edge;
            edge.vertex = graph[i][j].vertex;
            edge.capacity = graph[i][j].capacity;
            newGraph[i].push_back(edge);
        }   
    }*/

    //Getting filled by BFS
    int path[nVertices];
    int maxFlow = 0;
    int uIndex = 0;
    int iIndex = 0;

    while (bfs(path, nVertices))
    {
        int pathFlow = INT_MAX;
        for (int i = VERTIX_Y; i != VERTIX_X; i = path[i])
        {
            u = path[i];
            for (long unsigned int j = 0; j < graph[u].size(); j++)
            {
                if (graph[u][j].vertex == i)
                {
                    uIndex = j;
                    break;
                }
            }
            pathFlow = min(pathFlow, graph[u][uIndex].capacity);
        }
        
        for (int i = VERTIX_Y; i != VERTIX_X; i = path[i])
        {
            u = path[i];
            for (long unsigned int j = 0; j < graph[u].size(); j++)
            {
                if (graph[u][j].vertex == i)
                {
                    uIndex = j;
                    break;
                }
            }
            for (long unsigned int j = 0; j < graph[i].size(); j++)
            {
                if (graph[i][j].vertex == u)
                {
                    iIndex = j;
                    break;
                }
            }
            
            if (i == VERTIX_X || i == VERTIX_Y || u == VERTIX_X || u == VERTIX_Y)
            {
                graph[u][uIndex].capacity -= pathFlow;
                graph[i][iIndex].capacity += pathFlow;
                //printf("CASE 1:\n");
                //printf("Capacity from %d to %d is now %d\n", u, i, newGraph[u][uIndex].capacity);
                //printf("Capacity from %d to %d is now %d\n", i, u, newGraph[i][iIndex].capacity);
                //printf("Pathflow is %d\n", pathFlow);
                //printf("Maxflow is %d\n", maxFlow);
                //printf("----------------------------------------------\n");

            }
            else
            {
                graph[u][uIndex].capacity -= pathFlow;
                graph[i][iIndex].capacity -= pathFlow;
                //printf("CASE 2:\n");
                //printf("Capacity from %d to %d is now %d\n", u, i, newGraph[u][uIndex].capacity);
                //printf("Capacity from %d to %d is now %d\n", i, u, newGraph[i][iIndex].capacity);
                //printf("Pathflow is %d\n", pathFlow);
                //printf("Maxflow is %d\n", maxFlow);
                //printf("----------------------------------------------\n");
            }
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main()
{
    int nVertices;

    graph = buildGraph(&nVertices);

    //graphPrinter(graph);

    printf("%d\n", fordFulkerson(nVertices));

    return 0;
}
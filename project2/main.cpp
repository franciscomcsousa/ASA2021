#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

typedef struct edgeStruct{
    int vertex;
    int capacity;
} Edge;

vector<vector<Edge>> graph;


void buildGraph()
{
    //Code
    int n, k;
    int xBuffer, yBuffer;
    int capacity, processA, processB;
    graph = vector<vector<Edge>>();
    scanf("%d %d", &n, &k);

    //Processor X
    graph.push_back(vector<Edge>());
    //Processor Y
    graph.push_back(vector<Edge>());

    
    for (int i = 2; i < n + 2; i++)
    {
        Edge edgeX, edgeY;
        scanf("%d %d", &xBuffer, &yBuffer);

        graph.push_back(vector<Edge>());

        edgeX.vertex = i;
        edgeX.capacity = xBuffer;
        graph[0].push_back(edgeX);

        edgeY.vertex = i;
        edgeY.capacity = yBuffer;
        graph[1].push_back(edgeY);
    }

    for (int i = 2; i < k + 2; i++)
    {
        Edge edgeA, edgeB;
        scanf("%d %d %d", &processA, &processB, &capacity);

        edgeA.vertex = processB + 1;
        edgeA.capacity = capacity;
        graph[processA + 1].push_back(edgeA);

        edgeB.vertex =  processA + 1;
        edgeB.capacity = capacity;
        graph[processB + 1].push_back(edgeB);
    }
}


int main()
{
    buildGraph();

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            printf("%d connects to %d with a capacity of %d\n", i, graph[i][j].vertex, graph[i][j].capacity);
        }
    } 

    return 0;
}
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> graph;

int readGraph(){
    int n, m;
    int counter = 0;

    scanf("%d %d", &n, &m);

    graph = vector<vector<int>>(n + 1, vector<int>());
    vector<int> isSource = vector<int>(n + 1, 1);

    for(int i = 1; i < m + 1; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        isSource[v] = 0;
    }
    
    for (int i = 1; i < n + 1; i++)
    {
        if (isSource[i] == 1)
        {
            counter++;
        }
    }
    return counter;
}

void dfs(int* distances, bool* visited, int i){

    vector<int> queue = vector<int>(graph.size(), -1);
    queue.push_back(i);
    vector<int> lastChild = vector<int>(graph.size(), 0);

    while (!queue.empty())
    {
        if (visited[queue.back()])
        {
            queue.pop_back();
            if(queue.back() == -1){
                break;
            }
        }

        visited[queue.back()] = true;

        int vert = queue.back();

        for (int j = lastChild[vert]; j < (int) graph[vert].size(); j++)
        {
            int child = graph[vert][j];

            if (!visited[child])
            {
                queue.push_back(child);
                lastChild[vert] = j;
                break;
            }
            distances[vert] = max(distances[vert], distances[child] + 1);
        }
    }
}

int main(){

    int min = readGraph();

    int* distances = new int[graph.size() + 1];
    bool* visited = new bool[graph.size() + 1];

    for (int i = 0; i < (int) graph.size(); i++)
    {
        distances[i] = 0; visited[i] = false;
    }
    

    for (int i = 1; i < (int) graph.size(); i++)
    {
        if(!visited[i]){
            dfs(distances, visited, i);
        }
    }

    int maxValue = 0;

    for (int i = 0; i < (int) graph.size(); i++)
    {
        maxValue = max(maxValue, distances[i]);
    }
    
    printf("%d %d\n", min, maxValue + 1);

    return 0;
}
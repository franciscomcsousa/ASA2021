#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;


vector<vector<int>> graph;

int maxNumber = 1;


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

/*void dfs(int* distances, bool* visited, int i){

    if(visited[i]){
        return;
    }

    visited[i] = true;

    if(graph[i].size() == 0){
        distances[i] = 1;
    }

    for (int j = 0; j < (int) graph[i].size(); j++)
    {
        int child = graph[i][j];

        if(!visited[child])
        {
            dfs(distances, visited, child);
        }

        distances[i] = max(distances[i], distances[child] + 1);
    }

}*/

void dfs(int* distances, bool* visited, int i){

    vector<int> queue = vector<int>(graph.size());
    queue.push_back(i);
    
    while (queue.size() != 0)
    {
        if (visited[queue.back()])
        {
            queue.pop_back();
        }

        visited[queue.back()] = true;

        int vert = queue.back();

        for (int j = 0; j < graph[vert].size(); j++)
        {
            int child = graph[vert][j];

            if (!visited[child])
            {
                queue.push_back(child);
                break;
            }
            distances[vert] = max(distances[vert], distances[child] + 1);
        }
        
    }
}



int main(){

    int min = readGraph();

    int distances[graph.size()];
    bool visited[graph.size()];

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
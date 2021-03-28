#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> graph;

void readGraph(){
    int n,m;
    scanf("%d %d", &n, &m);
    graph = vector<vector<int>>(n+1, vector<int>());
    for(int i=0; i<m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);        
    }
}

int minPieces(vector<vector<int>> graph){
    vector<int> v = vector<int>(graph.size());
    int counter = 0;

    for (int i = 1; i < graph.size(); i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            v[graph[i][j]] = 1;
        }
    }
    
    for (int i = 1; i < v.size(); i++)
    {
        if(v[i]==0)
        {
            counter++;
            printf("%d\n", i);
        }
    }
    
    return counter;

}

int main(){
    readGraph();

    int min = minPieces(graph);

    printf("%d\n", min);

    return 0;
}
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int>> graph;

vector<int> parents;

int maxNumber = 1;

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
    parents = vector<int>(graph.size());

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
            parents.push_back(i);
            counter++;
            printf("%d\n", i);
        }
    }
    
    return counter;

}

void maxSequence(int parent, int counter){

    int maxProgress = counter;
    maxProgress++;

    if(graph[parent].size() == 0){
        if(maxProgress > maxNumber){
            maxNumber = maxProgress;
        }
    }
    else{
        for(int i = 0; i < graph[parent].size(); i++){
            maxSequence(graph[parent][i], maxProgress);
        }
    }
}

void computeParents(){
    for(int i = 0; i < parents.size(); i++){
        maxSequence(graph, parents[i], 0);
    }
}

int main(){

    readGraph();

    int min = minPieces(graph);

    computeParents();

    printf("%d %d\n", min, maxNumber);

    return 0;
}

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define WHITE 0 
#define RED 1 
#define BLUE 2
#define BLACK 3
int V;
int **aux;
int *cont_parents;
int *node_colours;
vector<int>res(0);
vector<int>sol(0);
int *visited;
int *check;

int check2() , has_cycle(int i);
void DFS(int v, int colour),find_LCA(int ancestor,int check);



int main(int argc , char** argv) {
    int cont=0,res_size=0,sol_size=0,edges,a,b,v1,v2,check=0;
    int in=scanf("%d %d %d %d",&v1,&v2,&V,&edges);
    if (in!=4) {
        printf("0\n");
        return 0;
    }
    
    cont_parents=(int*)malloc(V * sizeof(int*));
    node_colours=(int*)malloc(V * sizeof(int*));
    aux = (int**)malloc(V * sizeof(int*));

    for(int i = 0; i < V; i++){
        aux[i] = (int*)malloc(2*sizeof(int));
       
        aux[i][0] = 0;
        aux[i][1] = 0;
        node_colours[i]=WHITE; 
        cont_parents[i]=0;
    }

    while (cont!= edges) {
        cont++; 
        in=scanf("%d %d",&a,&b);
        if (in!=2) {
            printf("0\n");
            return 0;
        }
        if (cont_parents[b-1]>=2) {
            printf("0\n");
            return 0;
        }
        aux[b-1][cont_parents[b-1]]=a;
        cont_parents[b-1]++;
    }

    check = check2();
    if (check == 1 ){
        printf("0\n");
        return 0;
    }
    
    if(v1 == v2){
        printf("%d \n",v1);
        return 0;
    }    
    node_colours[v1-1]=RED;
    DFS(v1,RED);
    
    
    if (node_colours[v2-1]==RED){
        node_colours[v2-1]= BLACK;}
    else if (node_colours[v2-1]!= BLACK) {
        node_colours[v2-1]= BLUE;}
    
    DFS(v2,BLUE);
    

    
    for(int i=0;i<V;i++){
        if(node_colours[i] == BLACK){
            res.push_back(i+1);
            res_size++;
           
        }
    }

    if (res_size==1) {
        printf("%d \n",res[0]);
        return 0;
    }

    for (int i=0 ; i< res_size ; i++) {
        find_LCA(res[i],0);
    }

    for (int i=0 ; i< V ; i++) {
        if (node_colours[i]==BLACK) {
            sol.push_back(i+1);
            sol_size++;
        }
    }
    if (sol_size==0) {
        printf("-\n");
        return 0;
    }
    sort(sol.begin(), sol.end());
    for (int i=0 ; i<sol_size; i++) {
        printf("%d ",sol[i]);
    }
    printf("\n");
    return 0;

}


int check2(){
    visited=(int*) malloc(V * sizeof(int*));
    check=(int*) malloc(V * sizeof(int*));

    
    for(int i=0; i < V ; i++){
        visited[i]=0; 
        check[i]=0;
    }

    for (int i = 0  ; i < V ; i++){
        if (has_cycle(i) == 1 ){
            return 1;
        }
    }
    return 0;  
}

int has_cycle(int v){
    if (visited[v] == 0 ){
        visited[v] = 1;
        check[v] = 1;
        

        for(int i=0; i< 2; i++ ){
            if(aux[v][i] == 0){
                break;
            }
            if ((visited[aux[v][i]-1] == 0 && has_cycle(aux[v][i]-1)) || check[aux[v][i]-1] == 1){
                return 1;
            }
        } 
    }
    check[v] = 0; 
    return 0 ; 
}

void DFS(int v,int colour) {
    for (int i=0 ; i<2 ; i++) {
        if (aux[v-1][i]!=0) {
            if (node_colours[aux[v-1][i]-1]==RED  && colour!=RED) {
                node_colours[aux[v-1][i]-1]=BLACK;
            }
            else if (node_colours[aux[v-1][i]-1]!=BLACK) {
                node_colours[aux[v-1][i]-1] = colour;
            }
            DFS(aux[v-1][i],colour);
        }
    }
}

void find_LCA(int ancestor,int check) {
    if (ancestor!=0) {
        if (find(res.begin(),res.end(),ancestor)!=res.end() && check==1 ) {  
            node_colours[ancestor-1]=WHITE;
        }
        else {
            for (int i=0 ; i<2 ; i++) {
                find_LCA(aux[ancestor-1][i],1);
            }
        }
    }
}




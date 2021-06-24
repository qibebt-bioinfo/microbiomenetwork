

#pragma once


#include<iostream>
#include<string>
#include<map> 
#include<vector>
#include<limits.h>
#include <algorithm>
#include <queue>


using namespace std;

#define VertexData unsigned int
#define INFINITE 0xFFFFFFFF 

struct Dis {
    string path;
    double value;
    bool visit;
    Dis() {
        visit = false;
        value = 0;
        path = "";
    }
};

typedef struct 
{
    VertexData u;
    VertexData v;
    double cost;
}Arc; 


bool compare(Arc  A, Arc  B)
{
    return A.cost < B.cost ? true : false;
}

bool FindTree(VertexData u, VertexData v,vector<vector<VertexData> > &Tree)
{
    unsigned int index_u = INFINITE;
    unsigned int index_v = INFINITE;
    for (unsigned int i = 0; i < Tree.size();i++) 
    {
        if (find(Tree[i].begin(), Tree[i].end(), u) != Tree[i].end())
            index_u = i;
        if (find(Tree[i].begin(), Tree[i].end(), v) != Tree[i].end())
            index_v = i;
    }

    if (index_u != index_v) 
    {
        for (unsigned int i = 0; i < Tree[index_v].size();i++)
        {
            Tree[index_u].push_back(Tree[index_v][i]);
        }
        Tree[index_v].clear();
        return true;
    }
    return false;
}

class Graph_DG {
private:
    int vexnum;   
    int edge;     
   	double **arc;  
    Dis * dis; 
public:
    
    Graph_DG(int vexnum, int edge);
    
    ~Graph_DG();
    
    bool check_edge_value(int start, int end, int weight);
 
    void createGraph();
 
    map<int,string> createGraph(const char * infilename);
 
    
    void MiniSpanTree_Kruskal(const char * outfile_name);

	void ReadArc(vector<Arc> &vertexArc);


	
	 
    void print();
    
    void print(string outfilename,map<int,string> map_intid,map<string,string> map_meta);
  
    void Dijkstra(int begin);
    void Dijkstra(int begin,map<int,string> map_intid);

    void print_path(int);
    void print_path(int begin,string outfilename,map<int,string> map_intid);
    void print_path(string outfilename_graph, vector< vector<string> > &matrix_path, map<int,string> map_intid);
};

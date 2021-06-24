#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;
#define INFINITE 0xFFFFFFFF   
#define VertexData unsigned int  
#define UINT  unsigned int
#define vexCounts 24  
vector<string> vec_type;

string infile_name,outfile_name;

struct node 
{
    VertexData data;
    double lowestcost;
}closedge[vexCounts]; 
typedef struct 
{
    VertexData u;
    VertexData v;
    double cost;  
}Arc;  

void Print_help(){
	 cout <<"\t Minispantree for group level:" << endl; 
	 cout << "\t-i Input file name [Required, the sample level mst result]" << endl;
     cout << "\t-o Output file name [Required, the group level mst result]" << endl;
     cout << endl;
 }



void Para_args(int argc, char * argv[]){

    int i = 1;

    if (argc ==1)
                Print_help();

    while(i < argc){
         if (argv[i][0] != '-') {
                           printf("Argument # %d Error : Arguments must start with -\n", i);
                           exit(0);
                           };
         switch(argv[i][1]){
                            case 'i':
                                      infile_name = argv[i+1];
                                      
                                      break; //input


                            case 'o': outfile_name = argv[i+1]; break; 
                            
                            case 'h': Print_help(); break;
                            
                            default: printf("Unrec argument %s\n", argv[i]); Print_help(); break;
                        }
            i+=2;
        }
}




void AdjMatrix(double adjMat[][vexCounts])
{
    for (int i = 0; i < vexCounts; i++)   
        for (int j = 0; j < vexCounts; j++)
        {
            adjMat[i][j] = INFINITE;
        }
    //string infile_name="group_trans_1stepmst.txt";
    ifstream infile(infile_name.c_str(),ios::in);
    if(!infile){
    	cout<<"cant open the file "<<infile_name<<endl;
	exit(0);
	}
	string node_source,node_target,buffer,node_value;
	map<string,int> map_type;
	map<string,int> :: iterator map_it;
	int count_type=0;
	while(getline(infile,buffer)){
		stringstream str_buf(buffer);
		str_buf>>node_source>>node_target;
		map_it=map_type.find(node_source);
		if(map_it==map_type.end()){
			map_type[node_source]=count_type;
			vec_type.push_back(node_source);
			count_type++;
		}
		map_it=map_type.find(node_target);
		if(map_it==map_type.end()){
			map_type[node_target]=count_type;
			vec_type.push_back(node_target);
			count_type++;
		}
	}
	infile.close();
	ifstream infile2(infile_name.c_str(),ios::in);
    if(!infile2){
    	cout<<"cant open the file "<<infile_name<<endl;
	}
	while(getline(infile2,buffer)){
		stringstream str_buf2(buffer);
		str_buf2>>node_source>>node_target>>node_value;
		adjMat[map_type[node_source]][map_type[node_target]]=atof(node_value.c_str());
	}
	//cout<<"map_size:\t"<<map_type.size()<<endl;
	for(int i=0;i<map_type.size();i++)
		adjMat[i][i] = INFINITE;
}
int Minmum(struct node * closedge)
{
    double min = INFINITE;
    int index = -1;
    for (int i = 0; i < vexCounts;i++)
    {
        if (closedge[i].lowestcost < min && closedge[i].lowestcost !=0)
        {
            min = closedge[i].lowestcost;
            index = i;
        }
    }
    return index;
}
void MiniSpanTree_Prim(double adjMat[][vexCounts], VertexData s)
{
    for (int i = 0; i < vexCounts;i++)
    {
        closedge[i].lowestcost = INFINITE;
    }      
    closedge[s].data = s; 
    closedge[s].lowestcost = 0;
    for (int i = 0; i < vexCounts;i++)
    {
        if (i != s)
        {
            closedge[i].data = s;
            closedge[i].lowestcost = adjMat[s][i];
        }
    }
    for (int e = 1; e <= vexCounts -1; e++)
    {
        int k = Minmum(closedge);
        closedge[k].lowestcost = 0;
        for (int i = 0; i < vexCounts;i++)
        {
            if ( adjMat[k][i] < closedge[i].lowestcost)
            {
                closedge[i].data = k;
                closedge[i].lowestcost = adjMat[k][i];
            }
        }
    }
}
void ReadArc(double  adjMat[][vexCounts],vector<Arc> &vertexArc)
{
    Arc * temp = NULL;
    for (unsigned int i = 0; i < vexCounts;i++)
    {
        for (unsigned int j = 0; j < i; j++)
        {
            if (adjMat[i][j]!=INFINITE)
            {
                temp = new Arc;
                temp->u = i;
                temp->v = j;
                temp->cost = adjMat[i][j];
                vertexArc.push_back(*temp);
            }
        }
    }
}
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
void MiniSpanTree_Kruskal(double adjMat[][vexCounts])
{
    //string outfile_name="boxplotgroup_trans_2step_mst.result";
    ofstream outfile(outfile_name.c_str(),ios::out);
	if(!outfile){
        cout<<"cant open the file "<<outfile_name<<endl;
        exit(0);
        } 
	vector<Arc> vertexArc;
    ReadArc(adjMat, vertexArc);
    sort(vertexArc.begin(), vertexArc.end(), compare);
    vector<vector<VertexData> > Tree(vexCounts);
    for (unsigned int i = 0; i < vexCounts; i++)
    {
        Tree[i].push_back(i);
    }
    for (unsigned int i = 0; i < vertexArc.size(); i++)
    {
        VertexData u = vertexArc[i].u;  
        VertexData v = vertexArc[i].v;
        if (FindTree(u, v, Tree))
        {
            outfile << vec_type[u] << "\t" << vec_type[v] << "\t" << adjMat[u][v] << endl;
        }   
    }
    outfile.close();
}

int main(int argc, char * argv[])
{
    Para_args(argc, argv);
    double  adjMat[vexCounts][vexCounts] = { 0 };
    AdjMatrix(adjMat);
    MiniSpanTree_Kruskal(adjMat);
    cout<<"Finished!"<<endl;
    return 0;
}


#include"Kruskal.h"
#include <stdlib.h>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#define INFINITE 0xFFFFFFFF  


Graph_DG::Graph_DG(int vexnum, int edge) {

    this->vexnum = vexnum;
    this->edge = edge;
    
    arc = new double*[this->vexnum];
    dis = new Dis[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        arc[i] = new double[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            
                arc[i][k] = INT_MAX;
        }
    }
}

Graph_DG::~Graph_DG() {
    delete[] dis;
    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
    }
    delete arc;
}


bool Graph_DG::check_edge_value(int start, int end, int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG::createGraph() {
    cout << "Please input the start node & end node of each edge and the weight" << endl;
    int start;
    int end;
    double weight;
    int count = 0;
    while (count != this->edge) {
        cin >> start >> end >> weight;
        
        while (!this->check_edge_value(start, end, weight)) {
            cout << "The input is wrong, please input it again!" << endl;
            cin >> start >> end >> weight;
        }
        
        arc[start - 1][end - 1] = weight;
        
        ++count;
    }
}

void Graph_DG::MiniSpanTree_Kruskal(const char * outfile_name)
{
    ofstream outfile(outfile_name,ios::out);
    if(!outfile){
    	cout<<"Cant open the file "<<outfile_name<<endl;
    	exit(0);
	}
    
	vector<Arc> vertexArc;
    ReadArc(vertexArc);
    sort(vertexArc.begin(), vertexArc.end(), compare);
    vector<vector<VertexData> > Tree(this->vexnum); 
    for (unsigned int i = 0; i < this->vexnum; i++)
    {
        Tree[i].push_back(i);  
    }
    for (unsigned int i = 0; i < vertexArc.size(); i++)
    {
        VertexData u = vertexArc[i].u;  
        VertexData v = vertexArc[i].v;
        {
            outfile << u << "\t" << v <<"\t"<< vertexArc[i].cost <<endl;
        }   
    }
}



void Graph_DG::ReadArc(vector<Arc> &vertexArc) 
{
    Arc * temp = NULL;
    for (unsigned int i = 0; i < this->vexnum;i++)
    {
        for (unsigned int j = 0; j < this->vexnum; j++)
        {
            if (arc[i][j]!=INT_MAX)
            {
                temp = new Arc;
                temp->u = i;
                temp->v = j;
                temp->cost = arc[i][j];
                vertexArc.push_back(*temp);
            }
        }
    }
}


map<int,string> Graph_DG::createGraph(const char * infile_name) {
	ifstream infile(infile_name,ios::in);
	if(!infile){
    	cout<<"Can`t open the file "<<infile_name<<endl;
    	exit(0);
	}
	string buffer;
	map<string,int> map_id;
	map<int,string> map_intid;
	map<string,int> :: iterator map_it;
	int count=0;
	while(getline(infile,buffer)){
		stringstream str_buffer(buffer);
		string node_source,node_target,edge_weight,tmp_query;
		str_buffer>>tmp_query>>node_source;
		map_it=map_id.find(node_source);
		if(map_it==map_id.end()){
			map_id[node_source]=count;
			map_intid[count]=node_source;
			count++;
		}
		while(str_buffer>>node_target>>edge_weight){
			double edge_weight_d=stod(edge_weight);
			map_it=map_id.find(node_target);
			if(map_it==map_id.end()){
				map_id[node_target]=count;
				map_intid[count]=node_target;
				count++;
			}
			if(edge_weight_d>=0.870)
				arc[map_id[node_source]][map_id[node_target]] = 1.00-edge_weight_d;
			else
				arc[map_id[node_source]][map_id[node_target]] = INT_MAX;
		}
		
	}
    infile.close();
    return map_intid;
}

void Graph_DG::print() {
    cout << "The adjacency matrix of the graph is" << endl;
    int count_row = 0; 
    int count_col = 0; 
   
    while (count_row != this->vexnum) {
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                cout << "¡Þ" << " ";
            else
            cout << arc[count_row][count_col] << " ";
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}

void Graph_DG::print(string outfilename,map<int,string> map_intid,map<string,string> map_meta) {
    
    ofstream outfile(outfilename.c_str(),ios::out);
    outfile<<" "<<"\t";
	for(int i=0;i<this->vexnum;i++){
		outfile<<map_meta[map_intid[i]]<<"\t";
	}
    outfile<<endl;
    int count_row = 0; 
    int count_col = 0; 
    
    while (count_row != this->vexnum) {
    	outfile<<map_meta[map_intid[count_row]]<<"\t";
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                outfile << "oo" << "\t";
            else
            outfile << arc[count_row][count_col] << "\t";
            ++count_col;
        }
        outfile << endl;
        ++count_row;
    }
}


void Graph_DG::Dijkstra(int begin){
    
    
    int i;
    for (i = 0; i < this->vexnum; i++) {
        
        dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
        dis[i].value = arc[begin - 1][i];
    }
    
    dis[begin - 1].value = 0;
    dis[begin - 1].visit = true;

    int count = 1;
    
    while (count != this->vexnum) {
        
        int temp=0;
        int min = INT_MAX;
        for (i = 0; i < this->vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        
        dis[temp].visit = true;
        ++count;
        
        for (i = 0; i < this->vexnum; i++) {
        	 
            
            if (!dis[i].visit && arc[temp][i]!=INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
                
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
            }
        }
    }
    

}

void Graph_DG::Dijkstra(int begin,map<int,string> map_intid){
    cout<<"The "<<begin<<" th node Dijkstra begin!"<<endl;
    Dis *dis = new Dis[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        
        dis[i].path = map_intid[begin-1] + "->" + map_intid[i];
        dis[i].value = arc[begin - 1][i];
        dis[i].visit = false;
    }
    
    dis[begin - 1].value = 0;
    dis[begin - 1].visit = true;
	
    int count = 1;

    
    while (count != this->vexnum) {
        
        int temp=0;
        int min = INT_MAX;
        for (int i = 0; i < this->vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        
        dis[temp].visit = true;
        ++count;
     
        for (int i = 0; i < this->vexnum; i++) {
        	
            
            if (!dis[i].visit && arc[temp][i]!=INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
                
                dis[i].value = dis[temp].value + arc[temp][i];
                dis[i].path = dis[temp].path + "->" + map_intid[i];
                
            }
            
        }

    }
    string outfilename=to_string((begin-1)%10)+"/"+map_intid[begin-1]+".txt";
    ofstream outfile(outfilename.c_str(),ios::out);
    if(!outfile){
    	cout<<"Can`t open the file "<<outfilename<<endl;
    	exit(0);
	}
    outfile << map_intid[begin-1] << "\t";  
    for (int i = 0; i < this->vexnum; i++) {
		if(dis[i].value!=INT_MAX)
        outfile << dis[i].path << "=" << dis[i].value << "\t";
        else {
            outfile << "oo" << "\t";
        }
	}
	outfile.close();
	/*for (int i = 0; i < this->vexnum; i++) {
		if(dis[i].value!=INT_MAX)
        matrix_path[begin-1][i] = dis[i].path + "=" + to_string(dis[i].value);
        else {
             matrix_path[begin-1][i] = "oo";
        }
	}*/
    delete[] dis;
 	cout<<"The "<<begin<<" th node Dijkstra completed!"<<endl;
    

}


void Graph_DG::print_path(int begin) {
    string str;
    str = "v" + to_string(begin);
    cout << "the node "<<str<<" shortest path is:" << endl;
    for (int i = 0; i < this->vexnum; i++) {
    	
        if(dis[i].value!=INT_MAX)
        cout << dis[i].path << "=" << dis[i].value << "\t";
        else {
            cout << dis[i].path << "has no shortest path" << endl;
        }
    }
}



void Graph_DG::print_path(int begin,string outfilename,map<int,string> map_intid) {
    ofstream outfile(outfilename.c_str(),ios::app);
	string str;
    
    outfile<<map_intid[begin-1]<<"\t";
    for (int i = 0; i != this->vexnum; i++) {
    	
        if(dis[i].value!=INT_MAX)
        outfile << dis[i].path << "=" << dis[i].value << "\t";
        else {
            outfile << "oo" << "\t";
        }
    }
    outfile<<endl;
}


void Graph_DG::print_path(string outfilename_graph,vector<vector<string> > &matrix_path,map<int,string> map_intid) {

   ofstream outfile(outfilename_graph.c_str(),ios::app);
	
	
   for (int i = 0; i != this->vexnum; i++) {
   	
   		outfile << map_intid[i] << "\t"; 
    	
    	for (int j = 0; j != this->vexnum; j++) {
    		
    		outfile<<matrix_path[i][j]<<"\t"; 
    		
		} 
		
		outfile << endl;
        

    }
    
    outfile.close();
}

#include"Dijkstra.cpp"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <omp.h>


bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}

vector <int> find_vex_edge(string infilename){
	
	ifstream infile(infilename.c_str(),ios::in);
	if(!infile){
    	cout<<"Can`t open the file "<<infilename<<endl;
    	exit(0);
	}
	string buffer,node_target,node_source,tmp_weight;
	map<string,int> map_id;
	int vexnum=0,edge=0;
	map<string,int> :: iterator map_it;
	while(getline(infile,buffer)){
		stringstream str_buf(buffer);
		str_buf>>tmp_weight>>node_source;
		map_it=map_id.find(node_source);
		if(map_it==map_id.end()){
			map_id[node_source]=vexnum++;
			
		}
		while(str_buf>>node_target>>tmp_weight){
			map_it=map_id.find(node_target);
			if(map_it==map_id.end()){
				map_id[node_target]=vexnum++;
				edge++;
			}
			else{
				edge++;
			}
		}
	}
	vector<int> vec_vex_edge;

	vec_vex_edge.push_back(vexnum);
	vec_vex_edge.push_back(edge);
	infile.close();
	string outfile_name="node.list";
	ofstream outfile(outfile_name.c_str(),ios::out);
	for(map_it=map_id.begin();map_it!=map_id.end();map_it++)
		outfile<<map_it->first<<"\t"<<map_it->second<<endl;
	outfile.close();
	return vec_vex_edge;
	
}

map<string,string> gene_meta(string infile_name){
	ifstream infile(infile_name.c_str(),ios::in);
	map<string,string> map_meta;
	string buffer,id,meta;
	while(getline(infile,buffer)){
		stringstream str_buffer(buffer);
		str_buffer>>id>>meta;
		map_meta[id]=meta;
	}
	infile.close();
	return map_meta; 
}

map<string,int> gene_map_comp(string infile_name){
	ifstream infile(infile_name.c_str(),ios::in);
	if(!infile){
    	cout<<"Can`t open the file "<<infile_name<<endl;
    	exit(0);
	}
	map<string,int> map_com;
	string buffer;
	int count=1;
	while(getline(infile,buffer)){
		map_com[buffer]=count++;
	}
	infile.close();
	return map_com;
} 

int main() {

	string buf_infile="all.query.out";
	string minispantree_name="query_mst2.txt";
	
	vector<int> vec_vex_edge;
	vec_vex_edge=find_vex_edge(buf_infile); 
	
    
	Graph_DG graph(vec_vex_edge[0],vec_vex_edge[1]);
   	cout<<"Now the graph init completed!"<<endl;
    
    
    map<int,string> map_intid;
    map_intid=graph.createGraph(buf_infile);
	cout<<"Now the graph create completed!"<<endl;
	graph.MiniSpanTree_Kruskal(minispantree_name);
    /* 
    string infile_comp="complete.list"; 
    map<string,int> map_com;
    map_com=gene_map_comp(infile_comp);
   
    #pragma omp parallel for num_threads(61)
    for(int i=1;i<=vec_vex_edge[0];i++){
    	map<string,int>::iterator map_it;
    	map_it=map_com.find(map_intid[i-1]);
    	if(map_it!=map_com.end()){

    		continue;
	}
    	else
    		graph.Dijkstra(i,map_intid);
	}
	cout<<"Now the Dijkstra for everynode complete!"<<endl;
	*/ 
    
    system("pause");
    return 0;
}

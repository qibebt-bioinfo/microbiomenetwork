#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <stdlib.h>

using namespace std;

float sim_t = 0.9;
int max_depth = 0;

struct _match{       
       string id;
       vector <string> res;
       vector <float> sim;
       };

vector <_match> Matches;
map <string, int> Id_order;

class _group{
      public: friend class _group_library;
      
             _group(int id){
                      gid = id;
                      }
                      
             int Add(string sid){
                  if (samples.count(sid) != 0) return -1;
                  samples.insert(sid);
                  return 0;
                  } 
             
      private:
              int gid;
              set <string> samples;
      };

class _group_library{
      public:
             _group_library(){
                              giter = 0;
                              gcount = 0;
                              }
                              
             int New_group(){
                 int gid = giter;                  
                  _group * a_group = new _group (gid);
                  groups[gid] = a_group;
                  giter++;
                  gcount ++;
                  return gid;
                  }
             
             int New_group(string sid){
                 
                 int gid = New_group();
                 Add_sample(sid, gid);
                 return gid;
                 }
                  
             void Add_sample(string sid, int gid){
                  groups[gid]->Add(sid);
                  sid_group[sid] = gid;
                  }
             
             int Combine_groups(int gid_1, int gid_2){
                  int master_gid = 0;
                  int slave_gid = 0;
                  if (groups[gid_1]->samples.size() < groups[gid_2]->samples.size()){
                                                    master_gid = gid_1;
                                                    slave_gid = gid_2;
                                                    }
                  else{
                       master_gid = gid_2;
                       slave_gid = gid_1;
                       }
                  
                  _group * master_group = groups[master_gid];
                  _group * slave_group = groups[slave_gid];
                  
                  for (set <string> ::iterator siter = slave_group->samples.begin(); siter != slave_group->samples.end(); siter ++)
                      Add_sample(*siter, master_group->gid);
                                    
                  delete slave_group;
                  groups[slave_gid] = NULL;
                  
                  gcount--;
                  return master_gid;
                  }
             
             int Get_gid(string sid){
                 if (sid_group.count(sid) != 0) return sid_group[sid];
                 return -1;
                 }
             
             int Get_group_count(){
                 
                 return gcount;
                 }
             
      private:
              int giter;
              map <int, _group * > groups;
              map <string, int> sid_group;
              int gcount;
      };

_group_library Group_library;

int Read(const char * infilename){
    
    ifstream infile(infilename, ios::in);
    if (!infile){
                 cerr << "Error: Cannot open input file: " << infilename<< endl;
                 return 0;
                 }
    
    string buffer;
    int iter = 0;
    while(getline(infile, buffer)){
                          
                          string id;
                          string res;
                          float sim;
                          string temp;
                          stringstream strin(buffer);
                          strin >> temp >> id;
                          _match a_match;
                          a_match.id = id;
                          
                          while(strin >> res){
                                      
                                      if (res == "No-Hit") break;                                                                                                                 
                                      strin >> sim;                                      
                                      if (sim < sim_t) break;                                      
                                      a_match.res.push_back(res);
                                      a_match.sim.push_back(sim);
                                      
                                      }                          
                          
                          if (Id_order.count(id) != 0) continue;
                          
                          Id_order[id] = iter;
                          iter ++;                                                     
                          Matches.push_back(a_match);
                          }
    
    infile.close();
    infile.clear();
    
    return iter;
    }

void Closure(string sid, int depth){
    
    int order = Id_order[sid];
        
    //debug
    //cout << depth << endl;
    if (depth > max_depth) max_depth = depth;
    
    for (int i = 0; i < Matches[order].res.size(); i ++){
        
        int gid = Group_library.Get_gid(sid);
        
        string res_sid = Matches[order].res[i];
        if (res_sid == sid) continue;
        
        int res_gid = Group_library.Get_gid(res_sid);      
        if (res_gid == -1){                                                   
                                        //debug
                                        //cout << "res_id: " << res_sid << endl;
                                        //add
                                        Group_library.Add_sample(res_sid, gid);
                                        //recursive
                                        Closure(res_sid, depth + 1);
                                        }
                                        
        else if (gid != res_gid)//combine
             Group_library.Combine_groups(gid, res_gid);
        
        else if (gid == res_gid) //continue
             continue;
        }
    
    }

void Process(){
    
    for (int i = 0; i < Matches.size(); i ++){
        
        string sid = Matches[i].id;
        //debug
        //cout << "sid: " << sid << endl;
        
        if (Group_library.Get_gid(sid) == -1){                                                                                                                   
                                         Group_library.New_group(sid);                                          
                                         Closure(sid, 0);
                                         }
        
        }
    
    }

void Print(const char * outfilename){
     
     ofstream outfile(outfilename, ios::out);
     if (!outfile){
                   cerr << "Error: Cannot open output file: " << outfilename << endl;
                   return;
                   }
     
     cout << Group_library.Get_group_count() << " groups" << endl;
     
     for (int i = 0; i < Matches.size(); i ++){
         
         string sid = Matches[i].id;
         int gid = Group_library.Get_gid(sid);
         
         outfile << sid << "\t" << gid << endl;
         }
     
     outfile.close();
     outfile.clear();
     }

int main(int argc, char * argv[]){
    
    sim_t = atof(argv[3]);
    
    cout << "sim_t = " << sim_t << endl;
    
    cout << Read(argv[1]) << " samples loaded" << endl;
    Process();
    Print(argv[2]);
    
    cout << "max_depth = " << max_depth << endl;
    //system("pause");
    return 0;
    }

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std ;

struct node {
    node(){ visited = false; }
    int visit(int h,int now = opentime){
        if( !visited && now>=opentime && now<=closetime )
            { visited = false; return h + happy; }
        else return h;
    }
    string name;
    int happy;
    int opentime;
    int closetime;
    bool visited;
};
struct path_info{
    int happy;
    int costtime;
    pair<int,set<int>> to;
};
typedef pair<int,set<int>> Situation;
typedef map<situation,path_info> Table;

vector <int> path ;
vector <int> begint ;
vector <int> endt ;

void print(int **A,int n){
    for(int i=0;i<n;i++) { for(int j=0;j<n;j++) cout<<A[i][j]<<" "; cout<<endl; }
}

#define g(sol) func(table,sol,dist,pi,place,n,time)
path_info func(Table &table,Situation sit,int **dist,int **pi,node *place,int n,int time){
    Table::iterator it = table.find(sit)
    if(it!=table.end()) return it->second;

    set<int> S;

    S = sit->second;
}

int dp(int **dist,int **pi,node *place,int n,int time,int start_time){
    int start_point = 0;
    int happy = node[start_point].visit(0);
    int cur = start_point, in = start_time, out = start_time;
    int i,j,k,all[n];

    for(i=0;i<n;i++) all[i] = i;
    set<int> S(all); S.erase(start_point);
    Situation sit(start_point,S);
    Table table;
/*
    for(i=0;i<n;i++) com[i] = i; --com[n-1];
    while(com[0]<(m-n)){
        for(i=n-1;i>=0;i--) if(com[i]<m+i-n){
            com[i]++; for(j=i+1;j<n;++j) com[j]=com[i]+j-i; break;
        }
        for(i=0;i<n;i++) cout<<com[i]+1<<'\t'; cout<<endl;
    }
    */
    g(sit);

}

int pb1(int **dist,int **pi,node *place,int n,int time,int start_time){
    if(n<20) return dp(dist,pi,place,n,time,start_time);

    int start_point = 0;
    int happy = node[start_point].visit(0);
    int cur = start_point, in = start_time, out = start_time;
    int i,j,k,to[n];



    return happy;
}

int main(int argc,char* argv[]) {
    if (argc != 2) return 1 ;

    string str(argv[1]) ;
    fstream fin,fout1,fout2;
    fin.open("./"+str+"/tp.data",ios::in) ;
    fout1.open("./"+str+"/ans1.txt",ios::out) ;
    fout2.open("./"+str+"/ans2.txt",ios::out) ;

    int n,m,time,start_time;

    string name1,name2;
    int i,j,k,*tmp_d,*tmp_p;
    int **dist,**pi;

    fin>>n>>m>>time>>start_time;
    if(time+start_time>1440) time = 1440-start_time;

    node place[n];

    dist = new int*[n];
    tmp_d = new int[n*n];
    for(i=0;i<n;i++) dist[i] = tmp_d + n*i;
    for(i=0;i<n;i++) for(j=0;j<n;j++) dist[i][j] = -1;
    pi = new int*[n];
    tmp_p = new int[n*n];
    for(i=0;i<n;i++) pi[i] = tmp_p + n*i;
    for(i=0;i<n;i++) for(j=0;j<n;j++) pi[i][j] = i;

    for(i=0;i<n;i++)
        fin>> place[i].name >> place[i].happy >> place[i].opentime >> place[i].closetime;
    for(i=0;i<m;i++) {
        fin>>name1>>name2;
        for(j=0;j<n;j++) if( name1==place[j].name ) break;
        for(k=0;k<n;k++) if( name2==place[k].name ) break;
        fin>>dist[j][k]; dist[k][j] = dist[j][k];
    }

    fin.close();

    for(i=0;i<n;i++) dist[i][i] = 0;
    for(k=0;k<n;k++) for(i=0;i<n;i++) for(j=0;j<n;j++)
        if( dist[i][k]!=-1 && dist[k][j]!=-1 && ( dist[i][j]>dist[i][k]+dist[k][j] || dist[i][j]==-1 ) ) {
            dist[i][j] = dist[i][k] + dist[k][j] ;
            pi[i][j] = pi[k][j];
        }

    /*
    fout1<<total<<endl;
    for(i=0;i<path.size();i++)
        fout1<<node[path[i]].name<<" "<<begint[i]<<" "<<endt[i]<<endl;
    fout1.close();
    */

    delete [] tmp_d;
    delete [] tmp_p;
    delete [] dist;
    delete [] pi;

    return 0 ;
}


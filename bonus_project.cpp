#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
using namespace std ;
typedef vector<int> int_arr;

struct node {
    node(){ visited = false; }
    int try_visit(int h,int now = -1){
        if( !visited && ( ( now>=opentime && now<=closetime ) || now==-1 ) ) return h + happy;
        else return h;
    }
    void visit(){visited = true;}
    string name;
    int happy;
    int opentime;
    int closetime;
    bool visited;
};

void print(int **A,int n){
    for(int i=0;i<n;i++) { for(int j=0;j<n;j++) cout<<A[i][j]<<" "; cout<<endl; } cout<<endl;
}
void print(int *A,int n){
    for(int i=0;i<n;i++) cout<<A[i]<<" "; cout<<endl<<endl;
}

void pb(int **dist,int **pi,node *place,int n,int time,int start_time,
        int_arr &path,int_arr &begint,int_arr &endt,int &happy,int &costtime,bool strict){
    int i,j,start_point = 0;
    int cur,in,out,lefttime;
    happy = -1;
    for(i=0;i<n;i++) {
        int wow = strict ? place[i].try_visit(0,start_time) : place[i].try_visit(0);
        if( happy<wow ) { happy = wow; start_point = i; }
    }
    out = start_time;
    if(happy==0){
        for(i=0;i<n;i++) if( out<place[i].opentime )
            { out = place[i].opentime; start_point = i; }
    }
    cur = start_point; in = start_time; lefttime = time - (out - in);
    place[cur].visit();
    path.push_back(cur) ; begint.push_back(in) ; endt.push_back(out) ;

    int maximum,next,to[n];
    stack<int> stk;

    while(1) {
        for(i=0;i<path.size();i++) cout<<path[i]<<" "; cout<<endl;
        for(i=0;i<path.size();i++) cout<<begint[i]<<" "; cout<<endl;
        for(i=0;i<path.size();i++) cout<<endt[i]<<" "; cout<<endl<<endl;
        //find total happy
        for(i=0;i<n;i++) {
            to[i]=0;
            if( i!=cur && dist[cur][i]!=-1 && dist[cur][i]+dist[i][start_point]<=lefttime) {
                j = i;
                to[i] = strict ? place[j].try_visit(to[i],out+dist[cur][j]) :
                                 place[j].try_visit(to[i]);
                while(pi[cur][j]!=cur){
                    j = pi[cur][j];
                    to[i] = strict ? place[j].try_visit(to[i],out+dist[cur][j]) :
                                     place[j].try_visit(to[i]);
                }
            }
        }
        print(to,n);
        //find best
        maximum = to[0]; next = 0;
        for(i=1;i<n;i++) if( maximum<to[i] ) { maximum = to[i]; next = i; }
        if(maximum==0) {
            if(cur==start_point) break;
            else next = start_point;
        }
        lefttime -= dist[cur][next];
        //find path
        happy += to[next];
        place[next].visit();
        while(pi[cur][next]!=cur){
            stk.push(next);
            next = pi[cur][next];
            place[next].visit();
        }
        //doing output
        in = out = out + dist[cur][next];
        path.push_back(next) ; begint.push_back(in) ; endt.push_back(out) ;
        cur = next;
        while(!stk.empty()) {
            next = stk.top();
            in = out = out + dist[cur][next];
            path.push_back(next) ; begint.push_back(in) ; endt.push_back(out) ;
            cur = next;
            stk.pop();
        }
    }
    costtime = time - lefttime;
    return ;
}

int main(int argc,char* argv[]) {
    string str(argv[1]) ;
    fstream fin,fout1,fout2;
    fin.open("./"+str+"/tp.data",ios::in);
    fout1.open("./"+str+"/ans1.txt",ios::out);
    fout2.open("./"+str+"/ans2.txt",ios::out);

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

    if(start_time>1440) {
        fout1<<0<<" "<<0<<endl;
        fout2<<0<<" "<<0<<endl;
        fout1.close(); fout2.close();
    }

    for(i=0;i<n;i++) dist[i][i] = 0;
    for(k=0;k<n;k++) for(i=0;i<n;i++) for(j=0;j<n;j++)
        if( dist[i][k]!=-1 && dist[k][j]!=-1 && ( dist[i][j]>dist[i][k]+dist[k][j] || dist[i][j]==-1 ) ) {
            dist[i][j] = dist[i][k] + dist[k][j] ;
            pi[i][j] = pi[k][j];
        }

    int happy1,happy2,costtime1,costtime2;
    int_arr path1,begint1,endt1,path2,begint2,endt2;

    pb(dist,pi,place,n,time,start_time,path1,begint1,endt1,happy1,costtime1,false);
    fout1<<happy1<<" "<<costtime1<<endl;
    for(i=0;i<path1.size();i++)
        fout1<<place[path1[i]].name<<" "<<begint1[i]<<" "<<endt1[i]<<endl;
    fout1.close();

    for(i=0;i<n;i++) place[i].visited = false;
    pb(dist,pi,place,n,time,start_time,path2,begint2,endt2,happy2,costtime2,true);
    fout2<<happy2<<" "<<costtime2<<endl;
    for(i=0;i<path2.size();i++)
        fout1<<place[path2[i]].name<<" "<<begint2[i]<<" "<<endt2[i]<<endl;
    fout2.close();

    delete [] tmp_d;
    delete [] tmp_p;
    delete [] dist;
    delete [] pi;

    return 0 ;
}


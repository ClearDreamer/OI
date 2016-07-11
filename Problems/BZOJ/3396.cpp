#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=1000,INF=0x3f3f3f3f;
struct edge{
	int v,nxt,c;
	edge(int v,int nxt,int c):v(v),nxt(nxt),c(c){}
	edge(){}
}es[3*700+3];
int n,etot=1,ans;
int head[MAXN+3],d[MAXN+3],S,T;
queue<int> q;
void _addedge(int u,int v,int c){
	etot++;
	es[etot]=edge(v,head[u],c);
	head[u]=etot;
}
void addedge(int u,int v,int c){_addedge(u,v,c);_addedge(v,u,0);}
bool bfs(){
    memset(d,-1,sizeof(d));
    q.push(S);d[S]=0;
    while(!q.empty()){
    	int u=q.front();q.pop();
    	for(int i=head[u];i;i=es[i].nxt){
    		int v=es[i].v;
    		if(d[v]!=-1 || es[i].c==0)continue;
    		d[v]=d[u]+1;q.push(v);
    	}
    }
    return d[T]!=-1;
}
int dfs(int u,int a){  
    if (u==T||a==0) return a;
    int flow=0,f;
    for(int i=head[u];i;i=es[i].nxt){  
        int v=es[i].v;
        if(d[v]==d[u]+1 && (f=dfs(v,min(a,es[i].c)))>0){
        	flow+=f;
        	es[i].c-=f;es[i^1].c+=f;
        	a-=f;
        	if(a==0)break;
        }
    }
	if(flow==0)d[u]=-1; 
    return flow;
}
int maxflow(){
	int ans=0;
	while(bfs())ans+=dfs(S,INF);
	return ans;
}
#define id(x) (x-'A'+1)
int main(){
	cin>>n;
	S=id('A'),T=id('Z');
	for (int i=1;i<=n;i++){
		char a,b;int c;
		cin>>a>>b>>c;
		addedge(id(a),id(b),c);
	}
	cout<<maxflow()<<endl;
	return 0;
}
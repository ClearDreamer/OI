#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=500,MAXM=2*MAXN*MAXN,INF=0x3f3f3f3f;
struct edge{
	int u,v,c,nxt;
	edge(int u,int v,int c,int nxt):u(u),v(v),c(c),nxt(nxt){}
	edge(){}
}es[MAXM+3];
int head[MAXN+3],etot=1;
void _addedge(int u,int v,int c){
	etot++;
	es[etot]=edge(u,v,c,head[u]);
	head[u]=etot;
}
void addedge(int u,int v,int c){
	_addedge(u,v,c);
	_addedge(v,u,0);
}
int d[MAXN+3],S,T;
queue<int> q;
bool bfs(){
	memset(d,-1,sizeof(d));
	q.push(S);d[S]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=es[i].nxt){
			int v=es[i].v;
			if(d[v]!=-1 || es[i].c==0)continue;
			d[v]=d[u]+1;
			q.push(v);
		}
	}
	return d[T]!=-1;
}
int cur[MAXN+3];
int dfs(int u,int a){
	if(u==T || a==0)return a;
	int flow=0,f;
	for(int &i=cur[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(d[v]==d[u]+1 && (f=dfs(v,min(a,es[i].c)))>0){
			es[i].c-=f;
			es[i^1].c+=f;
			flow+=f;
			a-=f;
			if(a==0)break;
		}
	}
	if(flow==0)d[u]=-1;
	return flow;
}
int maxflow(){
	int ans=0;
	while(bfs()){
		for(int i=1;i<=T;i++)cur[i]=head[i];
		ans+=dfs(S,INF);
	}
	return ans;
}
int N,F,D;
int in[MAXN+3],out[MAXN+3],tot=0;
int main(){
	scanf("%d%d%d",&N,&F,&D);
	for(int i=1;i<=N;i++){
		in[i]=++tot;
		out[i]=++tot;
		addedge(in[i],out[i],1);
	}
	S=tot+F+D+1,T=S+1;
	for(int i=1;i<=F;i++)addedge(S,tot+i,1);
	for(int i=1;i<=D;i++)addedge(tot+F+i,T,1);
	for(int i=1,f,d;i<=N;i++){
		scanf("%d%d",&f,&d);
		for(int j=1,x;j<=f;j++){
			scanf("%d",&x);
			addedge(x+tot,in[i],1);
		}
		for(int j=1,x;j<=d;j++){
			scanf("%d",&x);
			addedge(out[i],x+tot+F,1);
		}
	}
	printf("%d\n",maxflow());
	return 0;
}
#include<queue>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN=40000,MAXE=2*MAXN;
struct edge{
	int v,w,nxt;
}es[MAXE+3];
int n,m;
int etot=0,head[MAXN+3];
void addedge(int u,int v,int w){
	etot++;
	es[etot].v=v;es[etot].w=w;es[etot].nxt=head[u];
	head[u]=etot;
}
int dep[MAXN+3],d[MAXN+3],pa[18][MAXN+3];
void dfs(int u,int f){
	dep[u]=dep[f]+1;pa[0][u]=f;
	for(int i=1;i<18;i++)pa[i][u]=pa[i-1][pa[i-1][u]];
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(v==f)continue;
		d[v]=d[u]+es[i].w;
		dfs(v,u);
	}
}
int lca(int a,int b){
	if(dep[a]<dep[b])swap(a,b);
	int h=dep[a]-dep[b];
	for(int i=0;i<18;i++)if(h>>i&1)a=pa[i][a];
	for(int i=17;i>=0;i--)
		if(pa[i][a]!=pa[i][b])a=pa[i][a],b=pa[i][b];
	return a==b?a:pa[0][a];
}
int len(int a,int b){
	return d[a]+d[b]-2*d[lca(a,b)];
}
int main(){
	char c;
	scanf("%d%d",&n,&m);
	while(m--){
		int a,b,w;scanf("%d %d %d %c",&a,&b,&w,&c);
		addedge(a,b,w);addedge(b,a,w);
	}
	dfs(1,0);
	int q;scanf("%d",&q);
	for(int i=1,u,v;i<=q;i++){
		scanf("%d%d",&u,&v);
		printf("%d\n",len(u,v));
	}
	return 0;
}
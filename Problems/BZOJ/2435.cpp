#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
typedef long long LL;
const int MAXN=1000000;
struct edge{
	int u,v,w,nxt;
}es[2*MAXN+3];
int head[MAXN+3],tot=0;
void addedge(int u,int v,int w){
	tot++;
	es[tot].u=u;es[tot].v=v;es[tot].w=w;es[tot].nxt=head[u];
	head[u]=tot;
}
int id[MAXN+3],bfsn[MAXN+3],sz[MAXN+3],pa[MAXN+3],tme;
void bfs(){
	static queue<int> q;
	q.push(1);tme=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		id[u]=++tme;bfsn[tme]=u;
		for(int i=head[u];i;i=es[i].nxt){
			if(id[es[i].v])continue;
			pa[es[i].v]=u;
			q.push(es[i].v);
		}
	}
}
int n;
LL calc(){
	for(int i=tme;i>=1;i--){
		int x=bfsn[i];sz[x]++;
		sz[pa[x]]+=sz[x];
	}
	LL ans=0;
	for(int i=1;i<=tot;i+=2){
		int u=es[i].u,v=es[i].v;
		if(pa[u]==v)ans+=(LL)es[i].w*abs(n-sz[u]-sz[u]);
		else ans+=(LL)es[i].w*abs(n-sz[v]-sz[v]);
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	bfs();
	printf("%lld\n",calc());
	return 0;
}
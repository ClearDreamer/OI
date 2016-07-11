#include<queue>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=40000,MAXE=2*MAXN;
struct edge{
	int v,w,nxt;
}es[MAXE+3];
int n,m,K;
int etot=0,head[MAXN+3];
void addedge(int u,int v,int w){
	etot++;
	es[etot].v=v;es[etot].w=w;es[etot].nxt=head[u];
	head[u]=etot;
}
int sz[MAXN+3],dis[MAXN+3],mx[MAXN+3],sta[MAXN+3],top;
int vis[MAXN+3],root=0,sum=0;
int Ans=0;
void get_root(int u,int f){
	sz[u]=1;mx[u]=0;
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(vis[v]||v==f)continue;
		get_root(v,u);
		sz[u]+=sz[v];
		mx[u]=max(mx[u],sz[v]);
	}
	mx[u]=max(mx[u],sum-mx[u]);
	if(mx[u]<mx[root])root=u;
}
void get_deep(int u,int f){
	sta[++top]=dis[u];
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(vis[v]||v==f)continue;
		dis[v]=dis[u]+es[i].w;
		get_deep(v,u);
	}
}
int calc(int u,int len){
	dis[u]=len;top=0;
	get_deep(u,0);
	sort(sta+1,sta+top+1);
	int res=0,l=1,r=top;
	while(l<r)if(sta[l]+sta[r]<=K)res+=(r-l),l++;else r--;
	return res;
}
void solve(int u){
	Ans+=calc(u,0);
	vis[u]=1;
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(vis[v])continue;
		Ans-=calc(v,es[i].w);root=0;sum=sz[v];
		get_root(v,0);
		solve(root);
	}
}
int main(){
	char c;
	scanf("%d%d",&n,&m);
	while(m--){
		int a,b,w;scanf("%d %d %d %c",&a,&b,&w,&c);
		addedge(a,b,w);addedge(b,a,w);
	}
	scanf("%d",&K);
	mx[0]=n;
	root=0;sum=n;get_root(1,0);
	solve(root);
	printf("%d\n",Ans);
	return 0;
}
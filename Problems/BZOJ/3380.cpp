#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100,MAXM=1000;
struct edge{
	int u,v,w,nxt;
	edge(int u,int v,int w,int nxt):u(u),v(v),w(w),nxt(nxt){}
	edge(){}
}es[2*MAXM+3];
int mx[MAXN+3],head[MAXN+3],etot=0;
void addedge(int u,int v,int w){
	etot++;
	es[etot]=edge(u,v,w,head[u]);
	head[u]=etot;
}
int vis[MAXN+3];
queue<int> q;
void bfs(int s){
	q.push(s);vis[s]=1;mx[s]=0x3f3f3f3f;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=es[i].nxt){
			int v=es[i].v,x=min(mx[u],es[i].w);
			if(mx[v]<x){
				mx[v]=x;
				if(vis[v]==0){vis[v]=1;q.push(v);}
			}
		}
	}
}
int has[MAXN+3];
int n,m,K;
int s[MAXN+3];
int main(){
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=K;i++)scanf("%d",&has[i]);
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	bfs(1);
	for(int i=1;i<=K;i++){
		s[i]=mx[has[i]];
	}
	sort(s+1,s+K+1);
	int cur=0;
	for(int i=1;i<=K;i++){
//		cout<<s[i].first<<endl;
		if(cur>=s[i])continue;
		cur++;
	}
	printf("%d\n",cur);
	return 0;
}
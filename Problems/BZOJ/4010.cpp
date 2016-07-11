/*
反向输出反图字典序最大拓扑序
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
const int MAXN=100000;
struct edge{
	int u,v,nxt;
	edge(){}
	edge(int u,int v,int nxt):u(u),v(v),nxt(nxt){}
}es[MAXN+3];
int head[MAXN+3],etot=0;
void addedge(int u,int v){
	etot++;
	es[etot]=edge(u,v,head[u]);
	head[u]=etot;
}
int d[MAXN+3];
int D,n,m;
int ans[MAXN+3];
priority_queue<int> q;
void init(){
	etot=0;
	memset(d,0,sizeof(d));
	memset(head,0,sizeof(head));
	while(!q.empty())q.pop();
}
int main(){
	scanf("%d",&D);
	while(D--){
		init();
		scanf("%d%d",&n,&m);
		for(int i=1,u,v;i<=m;i++){
			scanf("%d%d",&u,&v);
			addedge(v,u);d[u]++;
		}
		for(int i=1;i<=n;i++)if(d[i]==0)q.push(i);
		int cnt=n;
		while(!q.empty()){
			int u=q.top();q.pop();
			ans[cnt--]=u;
			for(int i=head[u];i;i=es[i].nxt){
				d[es[i].v]--;
				if(d[es[i].v]==0)q.push(es[i].v);
			}
		}
		if(cnt!=0){puts("Impossible!");continue;}
		for(int i=1;i<=n;i++)printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
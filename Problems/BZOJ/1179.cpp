/*
Tarjan缩点+SPFA最长路 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
const int MAXN=500000;
struct Edge{int u,to,next;}e[MAXN+3],g[MAXN+3];
int head[MAXN+3],cnt,last[MAXN+3],sz;
int val[MAXN+3],d[MAXN+3],sum[MAXN+3];
int sccno[MAXN+3],scc_cnt,low[MAXN],pre[MAXN],dtime=0;
stack<int> s;
bool ispub[MAXN+3],inq[MAXN+3];
void ins(int u,int v){
	e[++cnt].to=v;e[cnt].u=u;e[cnt].next=head[u];head[u]=cnt;
}
void insert(int u,int v){
	g[++sz].to=v;g[sz].next=last[u];last[u]=sz;
}
void tarjan(int u){
	pre[u]=low[u]=++dtime;
	s.push(u);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(!pre[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!sccno[v])low[u]=min(low[u],pre[v]);
	}
	if(pre[u]==low[u]){
		scc_cnt++;
		while(true){
			int x=s.top();s.pop();
			sccno[x]=scc_cnt;
			if(x==u)break;
		}
	}
}
void spfa(int S){
	static queue<int> q;
	memset(d,-1,sizeof(d));
	d[S]=sum[S];q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=false;
		for(int i=last[u];i;i=g[i].next){
			int v=g[i].to;
			if(d[v]<d[u]+sum[v]){
				d[v]=d[u]+sum[v];
				if(!inq[v]){inq[v]=true;q.push(v);}
			}
		}
	}
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		ins(u,v);
	}
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	int S,P;scanf("%d%d",&S,&P);
	for(int i=1,u;i<=P;i++){
		scanf("%d",&u);ispub[u]=true;
	}
	for(int i=1;i<=n;i++)if(!pre[i])tarjan(i);
	for(int i=1;i<=n;i++)sum[sccno[i]]+=val[i];
	for(int i=1;i<=cnt;i++)
		if(sccno[e[i].to]!=sccno[e[i].u])insert(sccno[e[i].u],sccno[e[i].to]);
	spfa(sccno[S]);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(ispub[i])ans=max(ans,d[sccno[i]]);
	printf("%d\n",ans);
	return 0;
}

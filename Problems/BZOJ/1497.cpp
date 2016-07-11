/*
若a,b之间有一条收益为c的边，则新建一个点，点权为c，分别向a,b连边，a,b点权为他们的花费，这样转换成求最大权封闭子图，详见胡伯涛论文，s向正权点连边（容量为权值），负权点向t连边（容量为权值的绝对值），可以证明一个方案和一个割一一对应。
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=60000,INF=0x3f3f3f3f;
struct edge{
	int u,v,c,nxt;
	edge(int u,int v,int c,int nxt):nxt(nxt),u(u),v(v),c(c){}
	edge(){}
}es[10*MAXN+3];
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
bool bfs(){
	static queue<int> q;
	while(!q.empty())q.pop();
	memset(d,-1,sizeof(d));d[S]=0;q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=es[i].nxt){
			if(es[i].c==0 || d[es[i].v]!=-1)continue;
			d[es[i].v]=d[u]+1;
			q.push(es[i].v);
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
			flow+=f;a-=f;
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
int n,m,sum=0;
int main(){
	scanf("%d%d",&n,&m);
	S=n+m+1,T=S+1;
	for(int i=1,p;i<=n;i++){
		scanf("%d",&p);
		addedge(i,T,p);
	}
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		addedge(n+i,a,INF);
		addedge(n+i,b,INF);
		addedge(S,n+i,c);
		sum+=c;
	}
	int ans=maxflow();
	printf("%d\n",sum-ans);
	return 0;
}
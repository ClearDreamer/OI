/*
首先如果这是一棵树的话，那么我们只需要选定一个根，之后扫一遍这棵树，询问的话即是两点到根节点的距离之和减去二倍的两点lca到根节点距离。 
那么如果是一棵仙人掌的话，我们强行套用这个办法，重新构造一棵树。 
对于仙人掌中的一个环来说，我们把该环中深度最小的点当做这个环的根，然后环上其他点连向该环，非环上边正常连接。 
这个树有什么优越性呢？ 
不妨假定1为根，那么每个点到1的最短路即是他到根的距离。 
在新树中，我们可以记录两个点(a,b)找到他们lca前的那两个点(c,d)，如果那两个点在一个环中，那么显然这两个点的lca在一个环中，所以我们需要比较在环上逆时针走的距离以及顺时针走的距离，取最小值，再把答案加上dis[a]?dis[c]+dis[b]?dis[d]即可（画图可以知道这个距离就是刨除环上走的那段距离的距离）。 
如果那两个点不在一个环中，那么直接像树一样，输出答案即可。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>n
#include<queue>
#include<cstdlib>
using namespace std;
const int MAXN=10000,POW=18,INF=0x3f3f3f3f;
int n,top,m;
int dis[MAXN+3],dep[MAXN+3],low[MAXN+3],pre[MAXN+3],dtime=0,pa[POW][MAXN+3];
bool inq[MAXN+3];
struct S{
	int u,v,w;
	S(){}
	S(int u,int v,int w):u(u),v(v),w(w){}
}sta[10*MAXN+3];
struct edge{
	int u,v,w,nxt;
	edge(){}
	edge(int u,int v,int w,int nxt):u(u),v(v),w(w),nxt(nxt){}
}es[4*MAXN+3];
int head[MAXN+3],etot=0;
void addedge(int u,int v,int w){
	etot++;
	es[etot]=edge(u,v,w,head[u]);
	head[u]=etot;
}
queue<int> q;
void init(){
	etot=0;
	memset(head,0,sizeof(head));
}
void spfa(int s){
	q.push(s);inq[s]=1;
	memset(dis,INF,sizeof(dis));dis[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(int i=head[u];i;i=es[i].nxt){
			int v=es[i].v;
			if(dis[v]>dis[u]+es[i].w){
				dis[v]=dis[u]+es[i].w;
				if(inq[v]==0){
					inq[v]=1;q.push(v);
				}
			}
		}
	}
}
int rcnt=0;
int sum[MAXN+3],len[MAXN+3],belong[MAXN+3];
void ring(int u,int v){
	rcnt++;
	while(sta[top].u!=u&&sta[top].v!=v){
		int x=sta[top].u,y=sta[top].v,val=sta[top].w;top--;
		sum[x]=sum[y]+val;
		len[rcnt]+=val;
		if(x!=u)belong[x]=rcnt,pa[0][x]=u;
		if(y!=u)belong[y]=rcnt,pa[0][y]=u;
	}
	sum[u]=sum[v]+sta[top].w;len[rcnt]+=sta[top].w;pa[0][v]=u;top--;
}
void tarjan(int u,int f){
	pre[u]=low[u]=++dtime;
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(v==f)continue;
		if(pre[v]==0){
			sta[++top]=S(u,v,es[i].w);
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=pre[u])ring(u,v);
		}
		else if(pre[v]<low[u]){
			low[u]=pre[v];
			sta[++top]=S(u,v,es[i].w);
		}
	}
}
void rebuild(int u,int f){
	dep[u]=dep[f]+1;
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(v==f)continue;
		rebuild(v,u);
	}
}
int lca(int x,int y,int &lca1,int &lca2){
	if(dep[x]<dep[y])swap(x,y);
	int res=dis[x]+dis[y];
	lca1=lca2=y;
	for(int i=POW-1;i>=0;i--)
		if(dep[pa[i][x]]>=dep[y])x=pa[i][x];
	if(x==y)return res-2*dis[lca1];
	for(int i=POW-1;i>=0;i--)
		if(pa[i][x]!=pa[i][y])x=pa[i][x],y=pa[i][y];
	lca1=x,lca2=y;
	return res-2*dis[pa[0][x]];
}
int main(){
	init();int q;
	scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);addedge(y,x,z);
    }
    spfa(1);
    tarjan(1,0);
    for(int i=1;i<POW;i++)
    	for(int j=1;j<=n;j++)
    		pa[i][j]=pa[i-1][pa[i-1][j]];
    init();
    for(int i=2;i<=n;i++)addedge(pa[0][i],i,0);
    rebuild(1,0);
    for(int i=1,x,y,l1,l2;i<=q;i++){
    	scanf("%d%d",&x,&y);
    	int ans=lca(x,y,l1,l2);
    	if(belong[l1]!=0&&belong[l1]==belong[l2]){
    		ans=dis[x]+dis[y]-dis[l1]-dis[l2];
    		int len1=abs(sum[l1]-sum[l2]),len2=len[belong[l1]]-len1;
    		ans+=min(len1,len2);
    	}
    	printf("%d\n",ans);
    }
	return 0;
}
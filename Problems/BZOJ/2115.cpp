/*
题目大意：给定一个无向图，每条边上有边权，求一条1到n的路径，使路径上权值异或和最大
首先一条路径的异或和可以化为一条1到n的简单路径和一些简单环的异或和
我们首先DFS求出任意一条1到n的简单路径以及图中所有最简单的简单环(环上不存在两个点可以通过环外边直连)
然后在一些数中选出一个子集，使它们与一个给定的数的异或和最大，这就是高斯消元的问题了
利用高斯消元使每一位只存在于最多一个数上 然后贪心求解即可
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN=50000,MAXM=2*MAXN;
struct edge{int v,nxt;LL w;}es[2*MAXM+3];
int head[MAXN+3],etot=0,qcnt=0,n,m;
LL d[MAXN+3],q[MAXM*10+3],a[70];
void addedge(int u,int v,LL w){
	etot++;
	es[etot].v=v;es[etot].w=w;es[etot].nxt=head[u];head[u]=etot;
}
bool vis[MAXN+3];
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=es[i].nxt){
		if(!vis[es[i].v]){
			d[es[i].v]=d[u]^es[i].w;dfs(es[i].v);
		}
		else q[++qcnt]=d[es[i].v]^d[u]^es[i].w;
	}
}
void gauss(){
	for(int i=1;i<=qcnt;i++){
		for(int j=60;j>=0;j--){
			if(q[i]>>j&1){
				if(!a[j]){a[j]=q[i];break;}
				else q[i]^=a[j];
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;LL w;scanf("%d%d%lld",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dfs(1);
//	for(int i=1;i<=n;i++)cout<<d[i]<<endl;
	gauss();
	LL ans=d[n];
	for(int j=60;j>=0;j--){
		if((ans>>j&1)==0)ans^=a[j];
	}
	printf("%lld\n",ans);
	return 0;
}
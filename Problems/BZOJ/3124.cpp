/*
http://blog.csdn.net/cjk_cjk/article/details/43412237
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN=200000;
struct edge{
	int u,v,w,nxt;
	edge(int u,int v,int w,int nxt):u(u),v(v),w(w),nxt(nxt){};
	edge(){}
}es[2*MAXN+3];
LL d[MAXN+3];
int head[MAXN+3],etot=0,pa[MAXN+3];
void addedge(int u,int v,int w){
	etot++;
	es[etot]=edge(u,v,w,head[u]);
	head[u]=etot;
}
LL mxd=0;
int low=0,high;
void dfs(int u,int fa,int &P){
	pa[u]=fa;
	if(d[u]>mxd)mxd=d[u],P=u;
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(v==fa)continue;
		d[v]=d[u]+es[i].w;
		dfs(v,u,P);
	}
}
bool del[MAXN+3];int n;
void find(int u,int fa){
	if(d[u]>mxd)mxd=d[u];
	for(int i=head[u];i;i=es[i].nxt){
		int v=es[i].v;
		if(v==fa||del[v]==1)continue;
		d[v]=d[u]+es[i].w;
		find(v,u);
	}
}
LL check(int u){
	mxd=d[u]=0;find(u,0);
	return mxd;
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dfs(1,0,low);
	mxd=d[low]=0;
	dfs(low,0,high);
	printf("%lld\n",mxd);
	for(int i=high;i;i=pa[i])del[i]=1;
	int l=low,r=high;
	for(int i=pa[high];i!=low;i=pa[i]){
		LL x=d[i],y=d[high]-d[i],p=check(i);
		if(p==x&&l==low)l=i;
		if(p==y)r=i;
	}
	int ans=0;
	for(int i=r;i!=l;i=pa[i])ans++;
	printf("%d\n",ans);
	return 0;
}
/*
直观的思想是当领导力确定时，尽量选择薪水少的---->枚举领导力
树上每个节点维护一个大根堆，先将所有儿子并起来，若超过预算，再弹出根直到满足预算。
左偏树的合并操作是logn的，遍历一遍树，时间复杂度O(nlogn)
每次选的一定是一个子树内的 
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
const int MAXN=100000;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int N,M;
int b[MAXN+3],c[MAXN+3],l[MAXN+3],sz[MAXN+3],root=0;
LL sum[MAXN+3];
vector<int> g[MAXN+3];
int ls[MAXN+3],rs[MAXN+3],dep[MAXN+3],val[MAXN+3],rt[MAXN+3];
int merge(int l,int r){
	if(!l || !r)return l+r;
	if(val[l]<val[r])swap(l,r);
	rs[l]=merge(rs[l],r);
	if(dep[rs[l]]>dep[ls[l]])swap(rs[l],ls[l]);
	dep[l]=dep[rs[l]]+1;
	return l;
}
LL ans=0;
void dfs(int u){
	sz[u]=1;sum[u]=c[u];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];dfs(v);
		sz[u]+=sz[v];sum[u]+=sum[v];
		rt[u]=merge(rt[u],rt[v]);
	}
	while(sum[u]>M){
		sum[u]-=val[rt[u]];
		rt[u]=merge(ls[rt[u]],rs[rt[u]]);
		sz[u]--;
	}
	ans=max(ans,(LL)sz[u]*l[u]);
}
int main(){
	N=read();M=read();
	for(int i=1;i<=N;i++){
		b[i]=read();c[i]=read();l[i]=read();val[i]=c[i];rt[i]=i;
		if(b[i])g[b[i]].push_back(i);else root=i;
	}
	dfs(root);
	printf("%lld\n",ans);
	return 0;
}
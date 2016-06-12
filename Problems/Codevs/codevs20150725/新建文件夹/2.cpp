/*

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=2000,INF=0x3f3f3f3f;
vector<int> g[MAXN+3];
int n,q,w[MAXN+3],opt[MAXN+3];
int ans[MAXN+3][MAXN+3];
inline void input(){
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
}
int curstart;
void dp(int u,int fa){
	int idx=lower_bound(opt,opt+n,w[u])-opt;//is not strict up seq 
	ans[curstart][u]=max(ans[curstart][u],idx+1);
	int tmp=opt[idx];
	opt[idx]=w[u];
	for(int i=0;i<g[u].size();i++){
		if(g[u][i]==fa)continue;
		dp(g[u][i],u);
	}
	opt[idx]=tmp;
}
int main(){
	input();
	for(int i=1;i<=n;i++){
		curstart=i;
		memset(opt,INF,sizeof(opt));
		dp(i,0);
	}
	scanf("%d",&q);
	for(int i=1,a,b;i<=q;i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",ans[a][b]);
	}
	return 0;
}


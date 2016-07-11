#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=10000;
queue<int> q;
int d[MAXN+3],n,m;
vector<int> g[MAXN+3];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v);g[v].push_back(u);
	}
	memset(d,-1,sizeof(d));
	q.push(1);d[1]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			if(d[v]!=-1)continue;
			d[v]=d[u]+1;
			q.push(v);
		}
	}
	printf("%d\n",*max_element(d+1,d+n+1));
	return 0;
}
	

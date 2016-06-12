#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=50000,POW=18;
struct edge{
	int u,v,c;
};
vector<edge> es;
vector<int> g[MAXN+3];
int d[MAXN+3],p[MAXN+3][POW+1];
void add(int u,int v,int c){
	es.push_back((edge){u,v,c});
	es.push_back((edge){v,u,c});
	g[u].push_back(es.size()-2);
	g[v].push_back(es.size()-1);
}
void dfs(int u,int fa){
	d[u]=d[fa]+1;
	p[u][0]=fa;
	for(int i=1;i<=POW;i++)p[u][i]=p[p[u][i-1]][i-1];
	for(int i=0;i<g[u].size();i++){
		edge &e=g[u][i];
		if(e.v!=fa){
			dfs(e.v,u);
		}
	}
}
int lca(int a,int b){
	if(d[a]<d[b])swap(a,b);
	if(d[a]!=d[b]){
		int h=d[a]-d[b];
		for(int i=0;i<=POW;i++){
			if(h&(1<<i))a=p[a][i];
		}
	}
	if(a!=b){
		for(int i=POW;i>=0;i--){
			if(p[a][i]!=p[b][i]){
				a=p[a][i];
				b=p[b][i];
			}
		}
		a=p[a][0];b=p[b][0];
	}
	return a;
}

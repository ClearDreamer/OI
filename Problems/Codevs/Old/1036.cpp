#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=30000,POW=18;
struct edge{
	int u,v;
};
vector<edge> es;
vector<int> g[MAXN+3];
int n,m,c,d[MAXN+3],p[MAXN+3][POW+1],cur=1,ans=0;
void add(int u,int v){
	es.push_back((edge){u,v});
	es.push_back((edge){v,u});
	g[u].push_back(es.size()-2);
	g[v].push_back(es.size()-1);
}
void dfs(int u,int fa){
	d[u]=d[fa]+1;
	p[u][0]=fa;
	for(int i=1;i<=POW;i++)p[u][i]=p[p[u][i-1]][i-1];
	for(int i=0;i<g[u].size();i++){
		edge &e=es[g[u][i]];
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
				a=p[a][i];b=p[b][i];
			}
		}
		a=p[a][0];
		b=p[b][0];
	}
	return a;
}
int main(){
	int a,b;
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n-1;i++){
		cin>>a>>b;
		add(a,b);
	}
	cin>>m;
	dfs(1,0);
	for(int i=1;i<=m;i++){
		cin>>c;
		ans+=d[cur]+d[c]-2*d[lca(cur,c)];
		cur=c;
	}
	cout<<ans;
	return 0;
}

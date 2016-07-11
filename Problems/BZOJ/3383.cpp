#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<cmath> 
using namespace std;
const int MAXN=50000;
typedef pair<int,int> P;
P ps[MAXN+3];
//bool can[MAXN+3];
vector<int> g[MAXN+3]; 
int n,d[MAXN+3],T;
//inline bool check(P &p){return p.second>=T-2;}
inline bool check(P &s,P &t){
	return abs(s.first-t.first)<=2&&abs(s.second-t.second)<=2;
}
queue<int> q;
int bfs(int S){
	memset(d,-1,sizeof(d));
	d[S]=0;q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i];
			if(d[v]!=-1)continue;
			d[v]=d[u]+1;
			if(ps[v].second==T)return d[v];
			q.push(v);
		}
	}
	return -1;
}
inline void build(){
	sort(ps+1,ps+n+1);
//	for(int i=0;i<=n;i++){can[i]=check(ps[i]);}
	for(int i=0;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(ps[j].first-ps[i].first>2)break;
			if(check(ps[i],ps[j])==false)continue;
			g[i].push_back(j);g[j].push_back(i);
		}
	}
}
int main(){
	scanf("%d%d",&n,&T);
	ps[0]=P(0,0);
	for(int i=1;i<=n;i++)scanf("%d%d",&ps[i].first,&ps[i].second);
	build();
	printf("%d\n",bfs(0)); 
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=405,MAXM=MAXN*4*MAXN*4;
typedef long long LL;
typedef pair<LL,int> P;
const LL INF=1LL<<60;
inline void read(int&a){
	char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';
}
priority_queue<P,vector<P>,greater<P> > q;
namespace graph{
	const int MAXN=4*405*405+3;
	int v[MAXM+3],w[MAXM+3],nxt[MAXM+3];
	int head[MAXN+3],etot,del[MAXN+3];
	inline void init(){
		etot=0;
	}
	inline void _addedge(int _u,int _v,int _w){
//		if(u==1&&v==2 || u==1&&v==3)cout<<"E"<<endl;
		etot++;v[etot]=_v;nxt[etot]=head[_u];w[etot]=_w;
		head[_u]=etot;
	}
	inline void addedge(int u,int v,int w){
		if(del[u] || del[v])return;
		_addedge(u,v,w);
		_addedge(v,u,w);
	}
	LL d[MAXN+3];
	void dijkstra(int S){
		while(!q.empty())q.pop();
		q.push(P(0,S));d[S]=0;
		while(!q.empty()){
			P t=q.top();q.pop();int u=t.second;
			if(t.first>d[u])continue;
			for(int i=head[u],t;i;i=nxt[i]){
				if(d[v[i]]>(t=d[u]+w[i])){
					q.push(P(d[v[i]]=t,v[i]));
				}
			}
		}
	}
}
int id[MAXN+3][MAXN+3],idtot=0,id2[MAXN+3][MAXN+3][4];
int a[MAXN+3][MAXN+3],b[MAXN+3][MAXN+3],c[MAXN+3][MAXN+3];
int n,m;
LL d[MAXN+3][MAXN+3];
int X[MAXN*MAXN+3],Y[MAXN*MAXN+3];
bool mark[MAXN+3][MAXN+3][4];
int pre[MAXN+3][MAXN+3];
inline void extend(int x,int y,LL val,int p){
	if(id[x][y]==0 || d[x][y]<=val)return;
	d[x][y]=val;pre[x][y]=p;
	q.push(P(val,id[x][y]));
}
bool vis[MAXN+3][MAXN+3];
inline void bfs(){
	while(!q.empty())q.pop();
	d[1][1]=0;q.push(P(0,id[1][1]));
	while(!q.empty()){
		P t=q.top();q.pop();
		int x=X[t.second],y=Y[t.second];
//		cout<<x<<" "<<y<<endl;
		LL v=d[x][y];
		if(v<t.first)continue;
		extend(x+1,y,v+b[x][y],0);
		extend(x-1,y,v+b[x-1][y],1);
		extend(x,y+1,v+c[x][y],2);
		extend(x,y-1,v+c[x][y-1],3);
	}
}
void dfs(int x,int y){
	if(x==1&&y==1 || vis[x][y])return;
	vis[x][y]=1;
	int tx=x,ty=y,p=pre[x][y];
	switch(p){
		case 0:--tx;break;
		case 1:++tx;break;
		case 2:--ty;break;
		case 3:++ty;break;
	}
	mark[x][y][p]=mark[tx][ty][p^1]=1;
	dfs(tx,ty);
}
inline void prep(){
	idtot=0;
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=m+1;j++){
			id[i][j]=++idtot;X[idtot]=i;Y[idtot]=j;
			d[i][j]=INF;
		}
	idtot=0;
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=m+1;j++)
			for(int k=0;k<4;k++){
				id2[i][j][k]=++idtot;
				graph::d[idtot]=INF;
			}
	bfs();
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]==0)continue;
//			cout<<i<<" "<<j<<":"<<d[i][j]<<endl;
			dfs(i,j);
		}
}
inline void build(){
	graph::init();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]==0)continue;
			graph::del[id2[i][j][3]]=1;
			graph::del[id2[i][j+1][2]]=1;
			graph::del[id2[i+1][j][1]]=1;
			graph::del[id2[i+1][j+1][0]]=1;
		}
	graph::del[id2[1][1][0]]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m+1;j++){
			graph::addedge(id2[i][j][2],id2[i+1][j][0],b[i][j]);
			graph::addedge(id2[i][j][3],id2[i+1][j][1],b[i][j]);
		}
	}
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=m;j++){
			graph::addedge(id2[i][j][1],id2[i][j+1][0],c[i][j]);
			graph::addedge(id2[i][j][3],id2[i][j+1][2],c[i][j]);
		}
	}
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=m+1;j++){
			if(!mark[i][j][0])graph::addedge(id2[i][j][0],id2[i][j][1],0);
			if(!mark[i][j][1])graph::addedge(id2[i][j][2],id2[i][j][3],0);
			if(!mark[i][j][2])graph::addedge(id2[i][j][0],id2[i][j][2],0);
			if(!mark[i][j][3])graph::addedge(id2[i][j][1],id2[i][j][3],0);
		}
	}
}
int main(){
//	freopen("sheep.in","r",stdin);
//	freopen("sheep.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)read(a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m+1;j++)read(b[i][j]);
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=m;j++)read(c[i][j]);
	prep();
	build();
	graph::dijkstra(id2[1][1][1]);
//	cout<<id2[1][1][1]<<" "<<id2[1][1][2]<<endl;
	printf("%lld\n",graph::d[id2[1][1][2]]);
//	for(int i=1;i<=idtot;i++)cout<<graph::d[i]<<" ";
	return 0;
}
/*
http://blog.csdn.net/iamzky/article/details/42029921
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
typedef pair<int,int> P;
struct node{
	int a,b,c;
	node(int a=0,int b=0,int c=0):a(a),b(b),c(c){}
}pre[10][10][1<<10];
const int INF=0x3f3f3f3f;
int a[10][10],d[10][10][1<<10];
bool vis[10][10];
int N,M,K;
bool update(int i,int j,int sta,int val){
	if(d[i][j][sta]>val){
		d[i][j][sta]=val;
		return true;
	}
	return false;
}
queue<P> q;
void spfa(int sta){
	const static int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
	while(!q.empty()){
		P u=q.front();q.pop();
		vis[u.first][u.second]=0;
		int v=d[u.first][u.second][sta];
		for(int i=0;i<4;i++){
			int tx=u.first+dx[i],ty=u.second+dy[i];
			if(tx<0||ty<0||tx>=N||ty>=M)continue;
			if(update(tx,ty,sta,v+a[tx][ty])){
				pre[tx][ty][sta]=node(u.first,u.second,sta);
				if(!vis[tx][ty]){
					vis[tx][ty]=1;
					q.push(make_pair(tx,ty));
				}
			}
		}
	}
}
void dfs(int i,int j,int sta){
	if(pre[i][j][sta].c==0)return;
	vis[i][j]=1;
	node t=pre[i][j][sta];
	dfs(t.a,t.b,t.c);
	if(t.a==i&&t.b==j)dfs(i,j,sta^t.c);
}
int X,Y;
int main(){
	scanf("%d%d",&N,&M);
	memset(d,INF,sizeof(d));
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			scanf("%d",&a[i][j]);
			if(!a[i][j]){d[i][j][1<<(K++)]=0;X=i,Y=j;}
		}
	}
	for(int sta=1;sta<(1<<K);sta++){
		for(int i=0;i<N;i++)for(int j=0;j<M;j++){
			for(int s=(sta-1)&sta;s;s=(s-1)&sta){
				if(update(i,j,sta,d[i][j][s]+d[i][j][sta^s]-a[i][j]))
					pre[i][j][sta]=node(i,j,s);
			}
			if(d[i][j][sta]!=INF){q.push(make_pair(i,j));vis[i][j]=1;}
		}
		spfa(sta);
	}
	printf("%d\n",d[X][Y][(1<<K)-1]);
	dfs(X,Y,(1<<K)-1);
	for(int i=0;i<N;i++)for(int j=0;j<M;j++){
		if(!a[i][j])putchar('x');
		else if(vis[i][j])putchar('o');
		else putchar('_');
		if(j==M-1)puts("");
	}
	return 0;
}
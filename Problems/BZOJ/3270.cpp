/*
变量(x,y)表示两人分别在x，y时的期望 
列方程解即可 
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=20;
double p[MAXN+3];
int N,M,A,B,d[MAXN+3];
vector<int> g[MAXN+3];
double a[MAXN*MAXN+10][MAXN*MAXN+10];
int tot;
#define id(x,y) ((x-1)*N+y)
void gauss(){
	int cur=1;
	for(int i=1,j;i<=tot;i++){
		for(j=cur;a[j][cur]==0 && j<=tot;j++);
		for(int k=1;k<=tot+1;k++)swap(a[cur][k],a[j][k]);
		for(j=1;j<=tot;j++){
			if(j==cur)continue;
			double t=a[j][cur]/a[cur][cur];
			for(int k=1;k<=tot+1;k++)a[j][k]-=t*a[cur][k];
		}
		cur++;
	}
}
void build(int x,int y){
	int S=id(x,y);a[S][S]--;
	for(int i=0;i<g[x].size();i++){
		for(int j=0;j<g[y].size();j++){
			int tx=g[x][i],ty=g[y][j],t=id(tx,ty);
			if(tx!=ty){
				if(x==tx&&y==ty)a[S][t]+=p[tx]*p[ty];
				else if(x==tx)a[S][t]+=p[tx]*(1-p[ty])/d[ty];
				else if(y==ty)a[S][t]+=p[ty]*(1-p[tx])/d[tx];
				else a[S][t]+=(1-p[tx])/d[tx]*(1-p[ty])/d[ty];
			}
		}
	}
}
int main(){
	scanf("%d%d%d%d",&N,&M,&A,&B);
	tot=N*N;a[id(A,B)][tot+1]=-1;//in build() the a[id(A,B)][id(A,B)]=-1
	for(int i=1,u,v;i<=M;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
		d[u]++;d[v]++;
	}
	for(int i=1;i<=N;i++){scanf("%lf",&p[i]); g[i].push_back(i);}
	for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)build(i,j);
	gauss();
	for(int i=1;i<=N;i++){
		int t=id(i,i);
		printf("%.6lf ",a[t][tot+1]/a[t][t]);
	}
	return 0;
}
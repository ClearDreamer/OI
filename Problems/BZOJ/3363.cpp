#include<queue>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXV=50000,MAXE=100000;
struct edge{
	int v,w,nxt;
}es[MAXE+3];
int n,m;
int etot=0,head[MAXV+3],d[MAXV+3];
void addedge(int u,int v,int w){
	etot++;
	es[etot].v=v;es[etot].w=w;es[etot].nxt=head[u];
	head[u]=etot;
}
int bfs(int s,int flag){
	int i,v,t;
	int tmp=0,tmpi=s;
	queue<int> q;
	memset(d,-1,sizeof(d));
	d[s]=0;q.push(s);
	while(!q.empty()){
		v=q.front();q.pop();
		for(int i=head[v];i;i=es[i].nxt){
			t=es[i].v;
			if(d[t]==-1){
				d[t]=d[v]+es[i].w;
				if(d[t]>tmp)tmp=d[t],tmpi=t;
				q.push(t);
			}
		}
	}
	return flag?tmpi:tmp;
}
int main(){
	char c;
	scanf("%d%d",&n,&m);
	while(m--){
		int a,b,w;scanf("%d %d %d %c",&a,&b,&w,&c);
		addedge(a,b,w);addedge(b,a,w);
	}
	printf("%d\n",bfs(bfs(1,1),0));
	return 0;
}
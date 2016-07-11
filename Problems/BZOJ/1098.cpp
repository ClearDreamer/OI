/*
补图 的联通块个数
链表维护当前剩余点 
*/
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm> 
using namespace std;
const int MAXN=100000+5;
int pre[MAXN+3],nxt[MAXN+3],vis[MAXN+3],cnt[MAXN+3],n,m,tot=0;
vector<int> g[MAXN+3];
inline void erase(int x){
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
}
inline void mark(int x,int v){
	for(int i=0;i<g[x].size();i++)vis[g[x][i]]=v;
}
#define travel for(int i=nxt[0];i<=n;i=nxt[i])
void bfs(int S,int id){
	static queue<int> q;
	q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();
		mark(u,1);
		travel{
			if(vis[i])continue;
			erase(i);cnt[id]++;q.push(i);
		}
		mark(u,0);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)nxt[i]=i+1;
	for(int i=1;i<=n+1;i++)pre[i]=i-1;
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v);g[v].push_back(u);
	}
	for(int i=nxt[0];i<=n;i=nxt[0]){
		erase(i);cnt[++tot]=1;bfs(i,tot);
	}
	sort(cnt+1,cnt+tot+1);
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)printf("%d ",cnt[i]);
	return 0;
}
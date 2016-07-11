/*
dp[i]=min{sum{dp[child[i]]}+S[i],K[i]}
有环，SPFA，记录每个点的前驱与后继 
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
const int MAXN=200000;
int N;
LL S[MAXN+3],K[MAXN+3];
bool inq[MAXN+3];
int es[40*MAXN+3],en[40*MAXN+3],nxt[MAXN+3],lst[MAXN+3],etot=0;
inline void addedge(int *head,int u,int v){
	etot++;
	es[etot]=v;
	en[etot]=head[u];
	head[u]=etot;
}
void work() {
	static queue<int> q;
	while(!q.empty())q.pop();
	for(int i=1;i<=N;i++)q.push(i),inq[i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		LL sum=0;
		for(int i=nxt[u];i;i=en[i])
			if((sum+=K[es[i]])>=K[u]) break;
		if(sum+S[u]<K[u]){
			K[u]=sum+S[u];
			for(int i=lst[u];i;i=en[i])
				if(!inq[es[i]]){
					q.push(es[i]);
					inq[es[i]]=1;
				}
		}
	}
}
int main() {
	scanf("%d", &N);
	for(int i=1,r,t;i<=N;i++) {
		scanf("%lld%lld%d", &S[i], &K[i], &r);
		while(r--){
			scanf("%d",&t);
			addedge(nxt,i,t);
			addedge(lst,t,i);
		}
	}
	work();
	printf("%lld\n",K[1]);
	return 0;
}
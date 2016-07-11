/*
拆点费用流 
如果i能到j，j能到k，那么显然无需连i->k这条边 这是一个剪枝
加了这个剪枝之后可能会WA 因此还要考虑一个点经过多次的情况
即每个点从入点向出点再连一条流量为1，费用为0的边
*/
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2000;
const int INF=0x7fffffff;
inline int read(){
	int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
typedef pair<int,int> P;
P ps[MAXN+3];
int n,cnt=1,ans,T,S;
int head[2*MAXN+3],q[2*MAXN+3],dis[2*MAXN+3],from[2*MAXN+3];
bool inq[2*MAXN+3],used[MAXN+3];
struct data{int u,v,nxt,w,c;}es[2000005];
void _addedge(int u,int v,int w,int c){
    es[++cnt].v=v;es[cnt].u=u;
    es[cnt].nxt=head[u];head[u]=cnt;
    es[cnt].w=w;es[cnt].c=c;
}
void addedge(int u,int v,int w,int c){_addedge(u,v,w,c);_addedge(v,u,-w,0);}
bool spfa(int s){
    for(int i=0;i<=T;i++)dis[i]=-INF;
    int t=0,w=1;dis[s]=0;q[0]=s;inq[s]=1;
    while(t!=w){
        int now=q[t];t++;inq[now]=0;if(t==4001)t=0;
        for(int i=head[now];i;i=es[i].nxt)
            if(es[i].c&&es[i].w+dis[now]>dis[es[i].v]){
                dis[es[i].v]=es[i].w+dis[now];from[es[i].v]=i;
                if(!inq[es[i].v]){
                    inq[es[i].v]=1;q[w++]=es[i].v;
                    if(w==4001)w=0;
                }
            }
    }
    return dis[T]!=-INF;
}
inline void augment(){
    int x=INF;
    for(int i=from[T];i;i=from[es[i].u])x=min(es[i].c,x);
    for(int i=from[T];i;i=from[es[i].u]){ans+=x*es[i].w;es[i].c-=x;es[i^1].c+=x;}
}
int y[MAXN+3];
int main(){
	n=read();S=2*n+1,T=S+1;
	for(int i=1;i<=n;i++)ps[i].first=read(),ps[i].second=read();
	sort(ps+1,ps+n+1);
	for(int i=1;i<=n;i++){
	    addedge(S,i,0,1);
	    addedge(i,i+n,1,1);
	    addedge(i,i+n,0,1);//attention 
	    addedge(i+n,T,0,1);
	}
	addedge(0,S,0,2);
	for(int i=1;i<=n;i++){//减小建边数量 
		y[i]=ps[i].second;int tmp=-1;
		for(int j=i-1;j;j--){
			if(y[j]<=y[i]&&y[j]>tmp)
				tmp=y[j],addedge(n+j,i,0,2);//注意流量为2 
		}
	}
	while(spfa(0))augment();
	printf("%d",ans);
	return 0;
}
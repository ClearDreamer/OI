#include <cstdio>
const int N=10010;
const int M=50010;
const int INF=1<<28;
int  n,m,k,S,T,cnt=1,he,ta,mcf,mcost;
int  head[N],Q[N],d[N],cur[N],mina[N],last[N],num[N],minf[N];
bool inq[N];
struct Edge{
    int v,f,a,next;

    Edge() {}
    Edge(int v,int f,int a,int next):v(v),f(f),a(a),next(next) {}
}E[M];
int Min(int x,int y){
    return x<y?x:y;
}
void addedge(int u,int v,int c,int a){
    E[++cnt]=Edge(v,c,a,head[u]);
    E[++cnt]=Edge(u,0,-a,head[v]);
    head[u]=cnt-1;head[v]=cnt;
}
void read(){
    scanf("%d%d%d",&n,&m,&k);
    S=1;T=n;
    for(int i=1;i<=m;i++){
        int u,v,c,a;
        scanf("%d%d%d%d",&u,&v,&c,&a);
        addedge(u,v,c,a);
    }
}
int BFS(){
    he=0;ta=1;Q[0]=S;
    for(int i=1;i<=T;i++){
        d[i]=0;cur[i]=head[i];
    }
    while(he!=ta){
        int x=Q[he++];
        if(he==1001) he=0;
        for(int i=head[x];i;i=E[i].next){
            Edge e=E[i];
            if(e.v==S||d[e.v]||(!e.f)) continue;
            d[e.v]=d[x]+1;
            Q[ta++]=e.v;
            if(ta==1001) ta=0;
        }
    }
    return d[T];
}
int DFS(int x,int a){
    if(x==T||(!a)) return a;
    int flow,tag=0;
    for(int &i=cur[x];i;i=E[i].next){
        Edge e=E[i];
        if(d[x]+1!=d[e.v]||(!e.f)) continue;
        flow=DFS(e.v,Min(a-tag,e.f));
        tag+=flow;
        E[i].f-=flow;
        E[i^1].f+=flow;
        if(!(a-tag)) break;
    }
    return tag;
}
void Dinic(){
    int mxf=0;
    while(BFS()) mxf+=DFS(S,INF);
    printf("%d ",mxf);
}
bool SPFA(){
    he=ta=0;Q[0]=S;minf[S]=INF;
    for(int i=2;i<=T;i++) mina[i]=INF;
    while(he!=ta+1){
        int x=Q[he++];
        inq[x]=0;
        if(he==1001) he=0;
        for(int i=head[x];i;i=E[i].next){
            Edge e=E[i];
            if(e.v==S||(!e.f)||mina[x]+e.a>=mina[e.v]) continue;
            num[e.v]=i;
            last[e.v]=x;
            mina[e.v]=mina[x]+e.a;
            minf[e.v]=Min(minf[x],e.f);
            if(!inq[e.v]){
                inq[e.v]=1;
                Q[++ta]=e.v;
                if(ta==1001) ta=0;
            }
        }
    }
    if(mcf+minf[T]>=k){
        mcost+=mina[T]*(k-mcf);
        return 0;
    }
    for(int i=T;i!=S;i=last[i]) E[num[i]].f-=minf[T];
    mcf+=minf[T];mcost+=mina[T]*minf[T];
    return 1;
}
int main(){
    read();
    Dinic();
    for(int i=1;i<=T;i++){
        for(int j=head[i];j;j=E[j].next){
            if(E[j].a>0){
                if(E[j].f) addedge(i,E[j].v,E[j].f,0);
                E[j].f=INF;
            }
            else E[j].a=0;//去掉有负环 
        }
    }
    while(SPFA());
    printf("%d",mcost);
    return 0;
}
/*#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
struct edge{
	int u,v,w,c,nxt;
	edge(){}
	edge(int u,int v,int w,int c,int nxt):u(u),v(v),w(w),c(c),nxt(nxt){}
}es[MAXM*2+3];
int head[MAXN+3],etot;
inline void init(){
	etot=1;
}
void addedge(int u,int v,int w,int c){
	etot++;
	es[etot]=edge(u,v,w,c,head[u]);
	head[u]=etot;
}
#define travel(u) for(int i=head[u];i;i=es[i].nxt)
namespace Dinic{
	int d[MAXN+10],cur[MAXN+10];
	int S,T,N;
	bool bfs(){
		static queue<int> q;
		memset(d,-1,sizeof(int)*(N+3));
		while(!q.empty())q.pop();
		q.push(S);d[S]=0;
		while(!q.empty()){
			int u=q.front();q.pop();
			travel(u){
				int v=es[i].v;
				if(es[i].c==0 || d[v]!=-1)continue;
				d[v]=d[u]+1;
				q.push(v);
			}
		}
		return d[T]!=-1;
	}
	int dfs(int u,int a){
		if(u==T||a==0)return a;
		int flow=0,f=0;
		for(int &i=cur[u];i;i=es[i].nxt){
			int v=es[i].v;
			if(d[v]==d[u]+1 && (f=dfs(v,min(a,es[i].c)))>0){
				es[i].c-=f;
				es[i^1].c+=f;
				flow+=f;
				a-=f;
				if(a==0)break;
			}
		}
		if(flow==0)d[u]=-1;
		return flow;
	}
	int maxflow(){
		int ans=0;
		while(bfs()){
			for(int i=1;i<=N;i++)cur[i]=head[i];
			ans+=dfs(S,INF);
		}
		return ans;
	}
}
namespace WFlow{
	int d[MAXN+10],from[MAXN+10];
	bool inq[MAXN+10];
	int S,T;
	bool spfa(){
		static queue<int> q;
		memset(d,INF,sizeof(int)*(N+3));
		memset(inq,0,sizeof(int)*(N+3));
		while(!q.empty())q.pop();
		q.push(S);d[S]=0;inq[S]=1;from[S]=0;
		while(!q.empty()){
			int u=q.front();q.pop();inq[u]=0;
			travel(u){
				int v=es[i].v;
				if(es[i].c==0)continue;
				if(d[v]>d[u]+es[i].w){
					d[v]=d[u]+es[i].w;
					from[v]=i;
					if(inq[v]==0){
						inq[v]=1;
						q.push(v);
					}
				}
			}
		}
		return d[T]!=INF;
	}
	int Cost=0;
	int augment(){
		int minc=INF;
		for(int t=from[T];t!=0;t=from[es[t].u]){
			minc=min(minc,es[t].c);
		}
		for(int t=from[T];t!=0;t=from[es[t].u]){
			Cost+=minc*es[t].w;
			es[t].c-=minc;
			es[t^1].c+=minc;
		}
		return minc;
	}
	int mincost(){
		Cost=0;
		while(spfa()){
			augment();
		}
		return Cost;
	}
}
int main(){
	N=read();M=read();K=read();
	for(int i=1,u,v,c,w;i<=M;i++){
		u=read();v=read();c=read();w=read();
		addedge(u,v,w,c);
		addedge(v,u,-w,0);
	}
	Dinic::N=N;
	Dinic::S=1;
	Dinic::T=N;
	printf("%d ",Dinic::maxflow());
	int tt=etot;
	for(int i=2;i<=etot;i+=2){
		if(es[u].c>0){
			addedge(u,v,
	return 0;
}*/
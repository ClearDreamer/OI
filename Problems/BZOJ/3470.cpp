#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=10000,MAXM=100000;
struct edge{
    int u,v,w,nxt;
    edge(){}
    edge(int u,int v,int w,int nxt):u(u),v(v),w(w),nxt(nxt){}
}es[MAXM+3];
int head[MAXN+3],etot=0;
void addedge(int u,int v,int w){
    es[++etot]=edge(u,v,w,head[u]);head[u]=etot;
}
int tp[MAXN+3],top=0;
int n,m,sum[MAXN+3],d[MAXN+3];
double d1[MAXN+3],d2[MAXN+3];
queue<int> q;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);u++,v++;
        addedge(u,v,w);
        sum[u]+=w;d[v]++;
    }
    for(int i=1;i<=n;i++)if(d[i]==0)q.push(i); 
    while(!q.empty()){
        int u=q.front();q.pop();tp[++top]=u;
        for(int i=head[u];i;i=es[i].nxt){
            int v=es[i].v;
            if((--d[v])==0)q.push(v);
        }
    }
    d1[1]=1;
    for(int i=1;i<=top;i++){
        for(int j=head[i];j;j=es[j].nxt){
            int v=es[j].v;
            d1[v]+=d1[i]*(double)es[j].w/(double)sum[i];
        }
    }
//  cout<<r<<endl;
    for(int i=top;i>=1;i--){
        for(int j=head[i];j;j=es[j].nxt){
            int v=es[j].v;
            d2[i]+=(d2[v]+1)*(double)es[j].w/(double)sum[i];
        }
    }
//  cout<<d2[1]<<endl;
    double ans=0;
    for(int i=1;i<=etot;i++){
        int u=es[i].u,v=es[i].v,c=es[i].w;
        double t=d2[1]-d1[u]*d2[u];
        int _w=sum[u]-c;
        if(_w>0){
            double p=(d2[u]*sum[u]-(d2[v]+1)*(double)c)/(double)_w;
            t=t+p*d1[u];
        }
        ans=max(ans,t);
    }
    printf("%.6lf\n",ans);
    return 0;
}
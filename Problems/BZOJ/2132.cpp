/*
黑白染色，对于每个黑点A，S->A:W商业，A->T:W工业，
对于每个白点B，S->B:W工业，B->T:W商业，对于每对有关系的两点A，B，A<–>B:c1+c2。
最小割 
*/
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#define maxn 10005
#define maxm 550000
#define inf 1061109567
using namespace std;
char ch;
bool ok;
void read(int &x){
    for (ok=0,ch=getchar();!isdigit(ch);ch=getchar()) if (ch=='-') ok=1;
    for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
    if (ok) x=-x;
}
int n,m,a[105][105],b[105][105],c[105][105],col[105][105],ans;
struct flow{
    int s,t,tot,now[maxn],son[maxm],pre[maxm],val[maxm];
    int dis[maxn],head,tail,list[maxn];
    bool bo[maxn];
    void init(){s=0,t=n*m+1,tot=1,memset(now,0,sizeof(now));}
    void put(int a,int b,int c){pre[++tot]=now[a],now[a]=tot,son[tot]=b,val[tot]=c;}
    void add(int a,int b,int c){put(a,b,c),put(b,a,0);}
    bool bfs(){
        memset(bo,0,sizeof(bo));
        head=0,tail=1,list[1]=s,dis[s]=0,bo[s]=1;
        while (head<tail){
            int u=list[++head];
            for (int p=now[u],v=son[p];p;p=pre[p],v=son[p])
                if (val[p]&&!bo[v]) bo[v]=1,dis[v]=dis[u]+1,list[++tail]=v;
        }
        return bo[t];
    }
    int dfs(int u,int rest){
        if (u==t) return rest;
        int ans=0;
        for (int p=now[u],v=son[p];p&&rest;p=pre[p],v=son[p])
            if (val[p]&&dis[v]==dis[u]+1){
                int d=dfs(v,min(rest,val[p]));
                val[p]-=d,val[p^1]+=d,ans+=d,rest-=d;
            }
        if (!ans) dis[u]=-1;
        return ans;
    }
    int dinic(){
        int ans=0;
        while (bfs()) ans+=dfs(s,inf);
        return ans;
    }
}f;
inline int calc(int a,int b){return (a-1)*m+b;}
#define FOR for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
void build(){
	FOR{
		if(col[i][j])swap(a[i][j],b[i][j]);
		int u=calc(i,j);
		f.add(f.s,u,a[i][j]);ans+=a[i][j];
		f.add(u,f.t,b[i][j]);ans+=b[i][j];
		if(col[i][j]){
			for(int k=0;k<4;k++){
				int tx=i+dx[k],ty=j+dy[k];
				if(tx>n||tx<1||ty>m||ty<1)continue;
				int v=calc(tx,ty),val=c[i][j]+c[tx][ty];
				f.add(u,v,val);f.add(v,u,val);ans+=val;
			}
		}
	}
}
int main(){
    read(n),read(m),f.init();
    FOR read(a[i][j]);
    FOR read(b[i][j]);
    FOR read(c[i][j]);
    FOR if((i+j) & 1)col[i][j]=1;
    build();
    printf("%d\n",ans-(f.dinic()));
    return 0;
}
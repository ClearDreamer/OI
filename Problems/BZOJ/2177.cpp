#include <iostream>
#include <cstdio>
#include <algorithm>
#define lowbit(x) (x&(-x))
using namespace std;
const int N = 50005;
struct Point{
    int x,y,id;
    bool operator<(const Point p)const{
        return x!=p.x?x<p.x:y<p.y;
    }
}p[N];
struct BIT{
    int min_val,pos;
    void init(){
        min_val=(1<<30);
        pos=-1;
    }
}bit[N];
struct Edge{
    int u,v,d;
    bool operator<(const Edge e)const{
        return d<e.d;
    }
}e[N<<2];
int n,tot,pa[N];
int find(int x){
    return pa[x]=(x==pa[x]?x:find(pa[x]));
}
int dist(int i,int j){
    return abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y);
}
void addedge(int u,int v,int d){
    e[tot].u=u;e[tot].v=v;e[tot++].d=d;
}
void update(int x,int val,int pos){
    for(int i=x;i>=1;i-=lowbit(i))
        if(val<bit[i].min_val)
            bit[i].min_val=val,bit[i].pos=pos;
}
int ask(int x,int m){
    int min_val=(1<<30),pos=-1;
    for(int i=x;i<=m;i+=lowbit(i))
        if(bit[i].min_val<min_val)
            min_val=bit[i].min_val,pos=bit[i].pos;
    return pos;
}
void build(Point *p){
	static int a[N],b[N];
    for(int dir=0;dir<4;dir++){//4种坐标变换
        if(dir==1||dir==3)
            for(int i=0;i<n;i++)
                swap(p[i].x,p[i].y);
        else if(dir==2)
            for(int i=0;i<n;i++)p[i].x=-p[i].x;
        sort(p,p+n);
        for(int i=0;i<n;i++)
            a[i]=b[i]=p[i].y-p[i].x;
        sort(b,b+n);
        int m=unique(b,b+n)-b;
        for(int i=1;i<=m;i++)bit[i].init();
        for(int i=n-1;i>=0;i--){
            int pos=lower_bound(b,b+m,a[i])-b+1;
            int ans=ask(pos,m);
            if(ans!=-1)addedge(p[i].id,p[ans].id,dist(i,ans));
            update(pos,p[i].x+p[i].y,i);
        }
    }
}
int mst(){
	for(int i=1;i<=n;i++)pa[i]=i;
	sort(e,e+tot);int ans=0;
	for(int i=0;i<tot;i++){
		int u=find(e[i].u),v=find(e[i].v);
		if(u==v)continue;
		pa[u]=v;ans+=e[i].d;
	}
	return ans;
}
int main(){
    scanf("%d",&n);tot=0;
    for(int i=0;i<n;i++){
        scanf("%d%d",&p[i].x,&p[i].y);
        p[i].id=i;
    }
    build(p);
    printf("%d\n",mst());
    return 0;
}
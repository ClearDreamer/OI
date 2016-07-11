#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<set>
#include<cstring>
#include<cmath>
using namespace std;
#define sqr(x) ((x)*(x))
const int MAXN=100000;
int N,X,Y,M,Q;
double Len=0;
bool vis[MAXN+3];
struct point{
	int x,y;
	bool operator <(const point &p)const{
		return x<p.x||x==p.x&&y<p.y;
	}
	point(){}
	point(int x,int y):x(x),y(y){}
	point operator -(const point &b)const{
		return point(x-b.x,y-b.y);
	}
	int operator *(const point &b)const{
		return x*b.y-y*b.x;
	}
}ps[MAXN+3];
double dis(point a,point b){
	point t=a-b;
	return sqrt(sqr(t.x)+sqr(t.y));
}
set<point> S;
typedef set<point>::iterator it;
void insert(point p){
	it l=S.lower_bound(p),r=l,t;
	l--;
	if((*r-*l)*(p-*l)<0)return;
	Len-=dis(*l,*r);
	S.insert(p);
	while(1){
		t=r;r++;
		if(r==S.end())break;
		if((*r-p)*(*t-p)>0)break;
		Len-=dis(*t,*r);
		S.erase(t);
	}
	while(l!=S.begin()){
		t=l;l--;
		if((*t-p)*(*l-p)>0)break;
		Len-=dis(*t,*l);
		S.erase(t);
	}
	l=r=S.find(p);
	l--;r++;
	Len+=dis(*l,p)+dis(p,*r);
}
point L,R,C;
int del[2*MAXN+3],ask[2*MAXN+3],top1,top2;
double ans[2*MAXN+3];
int main(){
	scanf("%d%d%d",&N,&X,&Y);
	scanf("%d",&M);
	for(int i=1;i<=M;i++)scanf("%d%d",&ps[i].x,&ps[i].y);
	scanf("%d",&Q);
	for(int i=1,op,x;i<=Q;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);vis[x]=1;
			del[++top1]=x;
		}
		else{
			ask[++top2]=top1;
		}
	}
	S.insert(L=point(0,0));
	S.insert(R=point(N,0));
	S.insert(C=point(X,Y));
	Len+=dis(L,C)+dis(R,C);
	for(int i=1;i<=M;i++)if(vis[i]==0)insert(ps[i]);
	for(int i=top2;i>=1;i--){
		while(top1>ask[i]){insert(ps[del[top1]]);top1--;}
		ans[i]=Len;
	}
	for(int i=1;i<=top2;i++)printf("%.2lf\n",ans[i]);
	return 0;
}
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const double eps=1e-8,INF=1e10;
const int MAXN=300;
struct point{
	double x,y;
}ps[MAXN+3];
struct line{
	double k,b;
	double calc(double x){
		return k*x+b;
	}
}ls[MAXN+3],st[MAXN+3];
int top=0,n;
line make_line(point &a,point &b){
	line res;res.k=(a.y-b.y)/(a.x-b.x);
	res.b=a.y-res.k*a.x;
	return res;
}
bool cmp(const line &a,const line &b){
	if(fabs(a.k-b.k)<eps)return a.b<b.b;
	else return a.k<b.k;
}
double crossx(const line &a,const line &b){//get cross of two line
	return (b.b-a.b)/(a.k-b.k);
}
void addline(line &l){//add line and adjust the bag
	while(top){
		if(fabs(l.k-st[top].k)<eps)top--;
		else if(top>1 && crossx(l,st[top-1])<=crossx(st[top],st[top-1]))top--;
		else break;
	}
	st[++top]=l;
}
double getup(double x){
	double res=0;
	for(int i=1;i<=top;i++)
		res=max(res,st[i].calc(x));
	return res;
}
double getdown(double x){
	int pos=0;
	for(pos=1;pos<n&&ps[pos+1].x<x;pos++);
	if(pos==n)return -INF;
	line l=make_line(ps[pos],ps[pos+1]);
	return l.calc(x);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf",&ps[i].x);
	for(int i=1;i<=n;i++)scanf("%lf",&ps[i].y);
	for(int i=1;i<n;i++)ls[i]=make_line(ps[i],ps[i+1]);
	sort(ls+1,ls+n,cmp);
	for(int i=1;i<n;i++)addline(ls[i]);
	double ans=INF;
	for(int i=1;i<=n;i++)ans=min(ans,getup(ps[i].x)-ps[i].y);//attention
	for(int i=1;i<top;i++){
		point p;p.x=crossx(st[i],st[i+1]);p.y=st[i].calc(p.x);
		ans=min(ans,p.y-getdown(p.x));//attention
	}
	printf("%.3lf\n",ans);
	return 0;
}
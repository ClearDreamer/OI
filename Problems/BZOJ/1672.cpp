/*
按照l端点排序牛
f[i]表示到i时刻的最小代价，那么对于一只l-r费用c的牛
可以用f[l-1]+c更新l-r
用线段树维护，单点查询，区间更新
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef long long LL;
const LL INF=1LL<<60;
const int MAXN=100000;
struct segment{
	int l,r,c;
	bool operator <(const segment &t)const{
		return l<t.l;
	}
}s[10000+3];
LL tag[4*MAXN+3],mn[4*MAXN+3];
#define LC(x) ((x)<<1)
#define RC(x) ((x)<<1|1)
inline void update(int x){
	mn[x]=min(mn[LC(x)],mn[RC(x)]);
}
inline void add_tag(int x,LL t){
	tag[x]=min(tag[x],t);
	mn[x]=min(mn[x],t);
}
inline void down(int x){
	if(tag[x]==INF)return;
	add_tag(LC(x),tag[x]);
	add_tag(RC(x),tag[x]);
	tag[x]=INF;
}
void build(int x,int l,int r){
	tag[x]=INF;
	if(l==r){mn[x]=INF;return;}
	int mid=(l+r)>>1;
	build(LC(x),l,mid);
	build(RC(x),mid+1,r);
}
int L,R;LL val;
void modify(int x,int l,int r){
	if(L<=l&&R>=r){
		add_tag(x,val);return;
	}
	down(x);
	int mid=(l+r)>>1;
	if(L<=mid)modify(LC(x),l,mid);
	if(R>mid)modify(RC(x),mid+1,r);
	update(x);
}
int P;
LL query(int x,int l,int r){
	if(P<l)return 0;
	if(l==r)return mn[x];
	down(x);
	int mid=(l+r)>>1;
	if(P<=mid)return query(LC(x),l,mid);
	else return query(RC(x),mid+1,r);
}
int n,bg,ed;
int main(){
	scanf("%d%d%d",&n,&bg,&ed);
	build(1,bg,ed);
	for(int i=1;i<=n;i++)scanf("%d%d%d",&s[i].l,&s[i].r,&s[i].c);
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++){
		P=s[i].l-1;
		LL t=query(1,bg,ed);
		if(t==INF){puts("-1");return 0;}
		L=s[i].l,R=s[i].r,val=t+s[i].c;
		modify(1,bg,ed);
	}
	P=ed;
	LL ans=query(1,bg,ed);
	printf("%lld\n",ans<INF?ans:(LL)-1);
	return 0;
}
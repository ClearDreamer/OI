/*
要找的是严格递增的斜率的最长长度,因此我们使用线段树来维护一个长度一个区间最大斜率,然后对每个节点的这个长度,我们可以用左右子树来更新.
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100000;
#define LC(x) ((x)<<1)
#define RC(x) ((x)<<1|1)
struct node{
	int l,r,ans;
	double k;
}ns[4*MAXN+3];
int n,m;
void build(int x=1,int l=1,int r=n){
	ns[x].l=l,ns[x].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(LC(x),l,mid);
	build(RC(x),mid+1,r);
}
int update(int x,double k){
	int l=ns[x].l,r=ns[x].r;
	if(l==r)return ns[x].k>k;
	if(ns[LC(x)].k<=k)return update(RC(x),k);
	return ns[x].ans-ns[LC(x)].ans+update(LC(x),k);
}
void update(int x){
	ns[x].k=max(ns[LC(x)].k,ns[RC(x)].k);
	ns[x].ans=ns[LC(x)].ans+update(RC(x),ns[LC(x)].k);
}
void modify(int x,double k,int pos){
	if(ns[x].l==ns[x].r){ns[x].ans=1;ns[x].k=k;return;}
	int mid=(ns[x].l+ns[x].r)>>1;
	if(pos<=mid)modify(LC(x),k,pos);
	else modify(RC(x),k,pos);
	update(x);
}
int main(){
	scanf("%d%d",&n,&m);
	build();
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		modify(1,(double)y/x,x);
		printf("%d\n",ns[1].ans);
	}
	return 0;
}
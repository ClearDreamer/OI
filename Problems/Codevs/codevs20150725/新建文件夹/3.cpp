/*

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=100000,INF=0x3f3f3f3f;
struct Segment_Tree{
	#define LC(x) ((x)<<1)
	#define RC(x) ((x)<<1|1)
	struct node{
		int l,r,sum,tag;
	}dat[MAXN*4+3];
	
	void update(int x){
		dat[x].sum=dat[LC(x)].sum+dat[RC(x)].sum;
		if(dat[LC(x)].tag>=3&&dat[RC(x)].tag>=3)dat[x].tag=3;
	}
	
	void pushdown(int x){
		if(!dat[x].tag)return;
		node &l=dat[LC(x)],&r=dat[RC(x)];
		l.tag+=dat[x].tag;
		r.tag+=dat[x].tag;
		dat[x].tag=0;
	}
	
	void build(int *a,int l,int r,int x=1){
		node &X=dat[x];
		X.l=l,X.r=r;
		if(l==r){X.sum=a[l];X.tag=0;return;}
		int mid=(l+r)>>1;
		build(a,l,mid,LC(x));
		build(a,mid+1,r,RC(x));
		update(x);
	}
	
	void changeln(int l,int r,int x=1){
		node &X=dat[x];
		if(X.tag>=3){
			X.sum=X.r-X.l+1;
			return; 
		} 
		if(l<=X.l&&r>=X.r){
			X.tag++;
			if(X.l==X.r)X.sum=floor(log(X.sum*1.0));
			else{
				changeln(l,r,LC(x));
				changeln(l,r,RC(x));
				update(x);
			}
		}
		else{
			int mid=(X.l+X.r)>>1;
			if(l<=mid)changeln(l,r,LC(x));
			if(r>mid)changeln(l,r,RC(x));
			update(x);
		}
	}
	
	void changevalue(int pos,int newvalue,int x=1){
		node &X=dat[x];
		if(X.l==X.r&&X.l==pos)X.sum=newvalue;
		else{
			pushdown(x);
			int mid=(X.l+X.r)>>1;
			if(pos<=mid)changevalue(pos,newvalue,LC(x));
			else if(pos>mid)changevalue(pos,newvalue,RC(x));
			update(x);
		}
	}
	
	int query(int l,int r,int x=1){
		node &X=dat[x];
		if(l<=X.l&&r>=X.r)return X.sum;
		int mid=(X.l+X.r)>>1,ans=0;
		if(l<=mid)ans+=query(l,r,LC(x));
		if(r>mid)ans+=query(l,r,RC(x));
		return ans;
	}
}T;
int n,m,a[MAXN+3];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	T.build(a,1,n);
	for(int i=1,op,x,y;i<=m;i++){
		scanf("%d%d%d",&op,&x,&y);
		switch(op){
			case 1:
				T.changevalue(x,y);
				break;
			case 2:
				T.changeln(x,y);
				break;
			case 3:
				printf("%d\n",T.query(x,y));
				break;
		}
	}
	return 0;
}


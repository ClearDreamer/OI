#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
struct sgement_tree {
	ll sum, mul, add;
} seg[400025];
ll mod;
int n, M, L, R, X, oper, Mul, Add;
inline ll read() {
	ll x = 0;char ch = getchar();while (ch < '0' || ch > '9')ch = getchar();
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0';ch = getchar();}
	return x;
}
inline void refresh(int p, int D) {
	int l = p << 1, r = p << 1 | 1;
	seg[l].sum = (seg[l].sum * seg[p].mul + (D - (D >> 1)) * seg[p].add) % mod;
	seg[l].mul = seg[l].mul * seg[p].mul % mod;
	seg[l].add = (seg[l].add * seg[p].mul + seg[p].add) % mod;
	seg[r].sum = (seg[r].sum * seg[p].mul + (D >> 1) * seg[p].add) % mod;
	seg[r].mul = seg[r].mul * seg[p].mul % mod;
	seg[r].add = (seg[r].add * seg[p].mul + seg[p].add) % mod;
	seg[p].mul = 1, seg[p].add = 0;
}
inline void fresh(int p) {
	seg[p].sum = (seg[p << 1].sum + seg[p << 1 | 1].sum) % mod;
}
void build_seg(int p, int l, int r) {
	seg[p].mul = 1, seg[p].add = 0;
	if (l == r) {seg[p].sum = read();return;}
	int mid = (l + r) >> 1;
	build_seg(p << 1, l, mid);
	build_seg(p << 1 | 1, mid + 1, r);
	fresh(p);
}
void update(int p, int l, int r) {
	if (R < l || r < L) return;
	if (L <= l && r <= R) {
		seg[p].sum = (seg[p].sum * Mul + (r - l + 1) * Add) % mod;
		seg[p].mul = seg[p].mul * Mul % mod;
		seg[p].add = (seg[p].add * Mul + Add) % mod;
		return;
	}
	int mid = (l + r) >> 1;
	refresh(p, r - l + 1);
	update(p << 1, l, mid);
	update(p << 1 | 1, mid + 1, r);
	fresh(p);
}
ll query(int p, int l, int r) {
	if (R < l || r < L) return 0;
	if (L <= l && r <= R) return seg[p].sum;
	int mid = (l + r) >> 1;
	refresh(p, r - l + 1);
	ll res = (query(p << 1, l, mid) + query(p << 1 | 1, mid + 1, r)) % mod;
	fresh(p);
	return res;
}
int main() {
	n = read(), mod = read();
	build_seg(1, 1, n);
	M = read();
	while (M--) {
		oper = read();
		if (oper == 1) {
			L = read(), R = read();
			Mul = read(), Add = 0;
			update(1, 1, n);
		} else if (oper == 2) {
			L = read(), R = read();
			Mul = 1, Add = read();
			update(1, 1, n);
		} else {
			L = read(), R = read();
			printf("%lld\n", query(1, 1, n));
		}
	}
	return 0;
}
/*
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN=100000;
LL P,N;
int a[MAXN+3];
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
struct node{
	int l,r,mid;
	LL sum,tag_add,tag_mul;
	node(){init();}
	inline void init(){
		l=r=sum=tag_add=0;tag_mul=0;
	}
	inline void add_plus(LL v){
		tag_add+=v;if(tag_add>=P)tag_add%=P;
		(sum+=(LL)(r-l+1)*v%P)%=P;
	}
	inline void add_mul(LL v){
		if(tag_mul==0){
			tag_mul=v;
		}
		else{
			tag_mul*=v;if(tag_mul>=P)tag_mul%=P;
		}
		tag_add*=v;if(tag_add>=P)tag_add%=P;
		(sum*=v)%=P;
	}
}ns[4*MAXN+3];
#define LC(x) ((x)<<1)
#define RC(x) ((x)<<1|1)
inline void update(int x){
	ns[x].sum=(ns[LC(x)].sum+ns[RC(x)].sum)%P;
}
inline void down(int x){
	LL &add=ns[x].tag_add,&mul=ns[x].tag_mul;
	if(mul){
		ns[LC(x)].add_mul(mul);
		ns[RC(x)].add_mul(mul);
		mul=0;
	}
	if(add){
		ns[LC(x)].add_plus(add);
		ns[RC(x)].add_plus(add);
		add=0;
	}
}
void build(int x,int l,int r){
	ns[x].l=l;ns[x].r=r;ns[x].mid=(l+r)>>1;
	if(l==r){
		ns[x].sum=a[l];return;
	}
	build(LC(x),l,ns[x].mid);
	build(RC(x),ns[x].mid+1,r);
	update(x);
}
void modify_plus(int x,int l,int r,int val){
	if(l<=ns[x].l&&r>=ns[x].r){
		ns[x].add_plus(val);return;
	}
	down(x);
	if(l<=ns[x].mid)modify_plus(LC(x),l,r,val);
	if(r>ns[x].mid)modify_plus(RC(x),l,r,val);
	update(x);
}
void modify_mul(int x,int l,int r,int val){
	if(l<=ns[x].l&&r>=ns[x].r){
		ns[x].add_mul(val);return;
	}
	down(x);
	if(l<=ns[x].mid)modify_mul(LC(x),l,r,val);
	if(r>ns[x].mid)modify_mul(RC(x),l,r,val);
	update(x);
}
LL query(int x,int l,int r){
	if(l<=ns[x].l&&r>=ns[x].r){
		return ns[x].sum%P;
	}
	down(x);LL ans=0;
	if(l<=ns[x].mid){ans+=query(LC(x),l,r);if(ans>=P)ans%=P;}
	if(r>ns[x].mid){ans+=query(RC(x),l,r);if(ans>=P)ans%=P;}
	return ans;
}
int main(){
	N=read();P=read();
	for(int i=1;i<=N;i++)a[i]=read();
	build(1,1,N);
	int m=read();
	for(int i=1,op,t,g,c;i<=m;i++){
		op=read();
		if(op==3){
			t=read();g=read();
			printf("%lld\n",query(1,t,g));
		}
		else{
			t=read();g=read();c=read()%P;
			if(op==1){if(c!=1)modify_mul(1,t,g,c);}
			else if(op==2)modify_plus(1,t,g,c);
		}
	}
	return 0;
}*/
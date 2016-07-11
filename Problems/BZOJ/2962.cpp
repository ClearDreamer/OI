/*
http://blog.csdn.net/popoqqq/article/details/43987881
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define LC(x) ((x)<<1)
#define RC(x) ((x)<<1|1)
typedef long long LL;
const int MAXN=50000;
const LL MOD=19940417;
int C[MAXN+3][21];
int a[MAXN+3],n;
void pre(){
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i&&j<=20;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	}
}
struct data{
	int f[21],size;
	void init(){
		memset(f,0,sizeof(f));size=0;
	}
	void init(int x){
		init();x=(x%MOD+MOD)%MOD;
		f[0]=1;f[1]=x;size=1;
	}
	int& operator [] (int ind){
		return f[ind];
	}
	void operator +=(const int &x){
		for(int i=20,temp=x;i>=0;i--,temp=x){
			for(int j=1;j<=i;j++,temp=((LL)temp*x%MOD)){
				(f[i]+=(LL)f[i-j]*temp%MOD*C[size-i+j][j]%MOD)%=MOD;
			}
		}
	}
	friend data operator +(data a,data b){
		data res;res.init();
		for(int i=0;i<=20;i++)
			for(int j=0;j<=i;j++){
				(res[i]+=(LL)a[i-j]*b[j]%MOD)%=MOD;
			}
		res.size=a.size+b.size;
		return res;
	}
	void negate(){
		for(int i=1;i<=20;i+=2)f[i]=(MOD-f[i]);
	}
};
struct segnode{
	segnode *ls,*rs;
	data val;
	int tadd;bool tneg;
	segnode(){
		ls=rs=NULL;
		tadd=tneg=0;
	}
	void build(int l,int r,int *a){
		if(l==r){val.init(a[l]);return;}
		int mid=(l+r)>>1;
		(ls=new segnode)->build(l,mid,a);
		(rs=new segnode)->build(mid+1,r,a);
		val=ls->val+rs->val;
	}
	void add(int x){
		x=(x%MOD+MOD)%MOD;
		(tadd+=x)%=MOD;
		val+=x;
	}
	void negate(){
		tadd=(MOD-tadd);
		tneg^=1;
		val.negate();
	}
	void down(){
		if(tneg){
			ls->negate();rs->negate();
			tneg=false;
		}
		if(tadd){
			ls->add(tadd);rs->add(tadd);
			tadd=0;
		}
	}
	void modify_add(int l,int r,int L,int R,int x){
		if(L<=l&&r<=R){add(x);return;}
		int mid=(l+r)>>1;down();
		if(L<=mid)ls->modify_add(l,mid,L,R,x);
		if(R>mid)rs->modify_add(mid+1,r,L,R,x);
		val=ls->val+rs->val;
	}
	void modify_neg(int l,int r,int L,int R){
		if(L<=l&&r<=R){negate();return;}
		int mid=(l+r)>>1;down();
		if(L<=mid)ls->modify_neg(l,mid,L,R);
		if(R>mid)rs->modify_neg(mid+1,r,L,R);
		val=ls->val+rs->val;
	}
	data query(int l,int r,int L,int R){
		if(L<=l&&r<=R){return val;}
		int mid=(l+r)>>1;down();
		if(R<=mid)return ls->query(l,mid,L,R);
		else if(L>mid)return rs->query(mid+1,r,L,R);
		else return ls->query(l,mid,L,R) + rs->query(mid+1,r,L,R);
	}
}rt;
int q;
char str[5];
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	pre();rt.build(1,n,a);
	for(int x,y,z,i=1;i<=q;i++){
		scanf("%s%d%d",str,&x,&y);
		switch(str[0]){
			case 'I':
				scanf("%d",&z);
				rt.modify_add(1,n,x,y,z);
				break;
			case 'R':
				rt.modify_neg(1,n,x,y);
				break;
			case 'Q':
				scanf("%d",&z);
				printf("%d\n",rt.query(1,n,x,y)[z]);
				break;
		}
	}
	return 0;
}
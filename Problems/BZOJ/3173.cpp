#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN=100000;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int N;
#define lowbit(x) ((x)&-(x))
namespace cnt{
	int c[MAXN+3];
	inline void add(int x,int ad){
		for(;x<=N;x+=lowbit(x))c[x]+=ad;
	}
	inline int query(int x){
		int ans=0;
		for(;x;x-=lowbit(x))ans+=c[x];
		return ans;
	}
}
namespace mx{
	int c[MAXN+3];
	inline void add(int x,int ad){
		for(;x<=N;x+=lowbit(x))c[x]=max(c[x],ad);
	}
	inline int query(int x){
		int ans=0;
		for(;x;x-=lowbit(x))ans=max(ans,c[x]);
		return ans;
	}
}
int a[MAXN+3];
int dp[MAXN+3],pos[MAXN+3];
int main(){
	N=read();
	for(int i=1;i<=N;i++)a[i]=read()+1;
	for(int i=N;i>=1;i--){
		int l=1,r=N;
		while(l<=r){
			int mid=(l+r)>>1;
			if(mid-cnt::query(mid)>=a[i])r=mid-1,pos[i]=mid;//二分插入位置，mid-query(mid)得到此时位置小于等于mid的数的个数 
			else l=mid+1;
		}
		cnt::add(pos[i],1);
	}
	for(int i=1;i<=N;i++){
		dp[i]=mx::query(pos[i])+1;
		mx::add(pos[i],dp[i]);
		dp[i]=max(dp[i],dp[i-1]);
		printf("%d\n",dp[i]);
	}
	return 0;
}
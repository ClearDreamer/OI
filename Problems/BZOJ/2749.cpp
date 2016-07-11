/*
首先由题目给的公式，对于素数x > 2，phi(x)会变出好多2...而phi(2) = 1
可以发现，就是求出每一个质数经过分解会变出多少个2来，2的个数就是ans。
于是我们令f[i]表示i分解出了几个2：这一过程类似素数筛法
i为质数，f[i] = f[i - 1]；否则，f[i * prime[j] = f[i] + f[prime[j]]  （<--这就是传说中的纯O(n)线性筛）
另：如果一开始n为奇数，则ans需+ 1，因为变出2需要第一步。
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN=100000;
int cnt[MAXN+3];
bool vis[MAXN+3];
int ps[MAXN+3],pcnt=0;
int main(){
	int T;scanf("%d",&T);
	cnt[1]=1;
	for(int i=2;i<=MAXN;i++){
		if(vis[i]==0)ps[++pcnt]=i,cnt[i]=cnt[i-1];
		for(int j=1;j<=pcnt;j++){
			int k=i*ps[j];if(k>MAXN)break;
			cnt[k]=cnt[i]+cnt[ps[j]];vis[k]=1;
			if(i%ps[j]==0)break;
		}
	}
	while(T--){
		LL ans=0;bool odd=1;int m;scanf("%d",&m);
		for(int i=1,p,q;i<=m;i++){
			scanf("%d%d",&p,&q);
			ans+=(LL)cnt[p]*q;odd=odd&(p&1);
		}
		printf("%lld\n",ans+odd);
	}
	return 0;
}
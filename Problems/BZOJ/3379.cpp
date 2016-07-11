#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
const int MAXN=1000,INF=0x3f3f3f3f;
struct data{
	int x,t;
	bool operator <(const data &d)const{
		return x<d.x || x==d.x&&t<d.t;
	}
}ds[MAXN+3];
int dp[MAXN+3][MAXN+3][2],n,B,H;
inline int solve(){
	dp[1][n][0]=max(ds[1].x,ds[1].t);
	dp[1][n][1]=max(ds[n].x,ds[n].t);
	for(int len=n-2;len>=0;len--){
		for(int l=1;l+len<=n;l++){
			int r=l+len;
			int &zero=dp[l][r][0],&one=dp[l][r][1];
			zero=one=INF;
			if(l-1>0)
				zero=min(zero,dp[l-1][r][0]+ds[l].x-ds[l-1].x),
				one=min(one,dp[l-1][r][0]+ds[r].x-ds[l-1].x);
			if(r+1<=n)
				zero=min(zero,dp[l][r+1][1]+ds[r+1].x-ds[l].x),
				one=min(one,dp[l][r+1][1]+ds[r+1].x-ds[r].x);
			zero=max(zero,ds[l].t);one=max(one,ds[r].t);
		}
	}
	int ans=INF;
	for(int i=1;i<=n;i++)
		ans=min(ans,min(dp[i][i][0],dp[i][i][1])+abs(B-ds[i].x));
	return ans;
}
int main(){
	scanf("%d%d%d",&n,&H,&B);
	for(int i=1;i<=n;i++)scanf("%d%d",&ds[i].x,&ds[i].t);
	sort(ds+1,ds+n+1);
	printf("%d\n",solve());
	return 0;
}
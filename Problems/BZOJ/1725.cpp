#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN=13,MOD=100000000;
int st[MAXN+3];
int dp[MAXN+3][(1<<MAXN)+3];
int n,m,bit[20];
inline bool check(int s,int i){
	if((s|st[i])>st[i])return false;
	for(int i=0;i<m-1;i++)
		if((s>>i&1) && (s>>(i+1)&1))return false;
	return true;
}
int main(){
	scanf("%d%d",&n,&m);
	bit[0]=1;for(int i=1;i<20;i++)bit[i]=bit[i-1]<<1;
	for(int i=1,x;i<=n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&x);
			if(x)st[i]+=bit[j];
		}
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int st=0;st<(1<<m);st++){
			int pre=((1<<m)-1)^st;
			if(check(st,i)==0){dp[i][st]=0;continue;}
			dp[i][st]+=dp[i-1][0];
			for(int k=pre;k;k=pre&(k-1))
				(dp[i][st]+=dp[i-1][k])%=MOD;
		}
	}
	int ans=0;
	for(int i=0;i<(1<<m);i++)(ans+=dp[n][i])%=MOD;
	printf("%d\n",ans); 
	return 0;
}
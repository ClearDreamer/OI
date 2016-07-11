#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=5000;
int sum[MAXN+3][MAXN+3],n,r;
int main(){
	scanf("%d%d",&n,&r);
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);
		scanf("%d",&sum[x+1][y+1]);
	}
	for(int i=1;i<=MAXN+1;i++)
		for(int j=1;j<=MAXN;j++)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	int ans=0;
	for(int i=r;i<=MAXN+1;i++)
		for(int j=r;j<=MAXN+1;j++)
			ans=max(ans,sum[i][j]+sum[i-r][j-r]-sum[i-r][j]-sum[i][j-r]);
	printf("%d\n",ans);
	return 0;
}
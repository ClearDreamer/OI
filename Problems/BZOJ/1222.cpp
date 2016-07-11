/*
f[i][ta]表示在加工完第i个产品后再a上工作ta时间时在tb上所用的最少时间。
f[i][ta]=min{f[i-1][ta]+t2,f[i-1][ta-t1],f[i-1][ta-t3]+t3}
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int INF=0x3f3f3f3f,MAXN=6000;
int f[MAXN*5+3],n,t1,t2,t3;
int main(){
	scanf("%d",&n);
	memset(f,INF,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&t1,&t2,&t3);
		for(int j=n*5;j>=0;j--){
			if(t2)f[j]+=t2;else f[j]=INF;
			if(t1&&j>=t1)f[j]=min(f[j],f[j-t1]);
			if(t3&&j>=t3)f[j]=min(f[j],f[j-t3]+t3);
		}
	}
	int ans=INF;
	for(int i=0;i<=n*5;i++)
		ans=min(ans,max(i,f[i]));
	printf("%d\n",ans);
	return 0;
}
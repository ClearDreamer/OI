/*
DP
设f[i][j]表示第i个电线杆高度为j时的最小花费,
DP方程为f[i][j]=min( (j-a[i])^2+f[i-1][k]+|j-k|*c )
直接根据这条方程做的话复杂度是100000*100*100,明显会超时.
可以将方程进行化简：
f[i][j]=min( (j-a[i])^2+f[i-1][k]+|j-k|*c ) (j>=a[i])
       =(j-a[i])^2+j*c+min(f[i-1][k]-k*c) (j>=k)
     	(j-a[i])^2-j*c+min(f[i-1][k]+k*c) (j<k)
设high[j]=min(f[i-1][k]-k*c) (j>=k)
low[j]=min(f[i-1][k]+k*c) (j<k)
方程就变为f[i][j]=(j-a[i])^2+min(high[j]+j*c,low[j]-j*c);
可以通过预处理计算先出high[j],low[j].
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
#define sqr(x) ((x)*(x))
const int MAXH=100,MAXN=100000,INF=0x3f3f3f3f; 
int n,c;
int h[MAXH+3],l[MAXH+3],a[MAXN+3];
int f[2][MAXH+3];
int main(){
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	memset(f,INF,sizeof(f));
	for(int i=a[1];i<=MAXH;i++)f[1][i]=sqr(i-a[1]);
	for(int T=2;T<=n;T++){
		int cur=T&1,pre=cur^1;
		for(int i=0;i<=MAXH;i++)h[i]=l[i]=f[cur][i]=INF;
		l[0]=f[pre][0];
		for(int i=1;i<=MAXH;i++)
			l[i]=min(l[i-1],f[pre][i]-i*c);
		h[MAXH]=f[pre][MAXH]+MAXH*c;
		for(int i=MAXH-1;i>=0;i--)
			h[i]=min(h[i+1],f[pre][i]+i*c);
		for(int i=a[T];i<=MAXH;i++)
			f[cur][i]=min(h[i]-i*c,l[i]+i*c)+sqr(i-a[T]);
	}
	printf("%d\n",*min_element(f[n&1]+a[n],f[n&1]+MAXH+1));
	return 0;
}
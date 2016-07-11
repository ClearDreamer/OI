/*
d[i]=min{d[j]+cost(j+1,i)}+c[i]
d[i]=min{d[j]+cost(j+1,i)}+c[i]
其中d[i]d[i]是前i个且在i建仓库的最小费用，cost(j+1,i)cost(j+1,i)是将j+1～i的东西全都运到i的费用

而我们先考虑cost怎么求，orz，好神的前缀和，首先维护sum[i]表示1～i的物品，则j～i的东西从j全都运到i需要
(sum[i]-sum[j])×x[i]
(sum[i]-sum[j])×x[i]
，然后再设前缀和b[i]表示1～i的物品每一个i从1运到i的费用，则
cost[j+1,i]=(sum[i]-sum[j])×x[i]-(b[i]-b[j])
cost[j+1,i]=(sum[i]-sum[j])×x[i]-(b[i]-b[j])
其中
sum[i]=sum[i-1]+p[i],b[i]=b[i-1]+p[i]×x[i]
sum[i]=sum[i-1]+p[i],b[i]=b[i-1]+p[i]×x[i]
然后方程变成
d[i]=min{d[j]+(sum[i]-sum[j])×x[i]-(b[i]-b[j])}+c[i]
d[i]=min{d[j]+(sum[i]-sum[j])×x[i]-(b[i]-b[j])}+c[i]
化简一下可得
d[i]=min{d[j]+b[j]-x[i]×sum[j])}+c[i]+sum[i]×x[i]-b[i]

假设决策j<k且k比j优，即：
d[k]+b[k]-x[i]×sum[k]<d[j]+b[j]-x[i]×sum[j]
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN=1000000;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int n;
LL x[MAXN+3],p[MAXN+3],c[MAXN+3];
LL s[MAXN+3],b[MAXN+3];
LL dp[MAXN+3];
int q[MAXN+3],front=0,tail=1;
#define F(x) (dp[x]+b[x])
#define Y(r,l) (F(r)-F(l))
#define X(r,l) (s[r]-s[l])
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		x[i]=read();p[i]=read();c[i]=read();
		s[i]=s[i-1]+p[i];b[i]=b[i-1]+p[i]*x[i];
	}
	for(int i=1;i<=n;i++){
		while(front<tail-1 && Y(q[front+1],q[front])<x[i]*X(q[front+1],q[front]))front++;
		int j=q[front];
		dp[i]=dp[j]+(s[i]-s[j])*x[i]-(b[i]-b[j])+c[i];
		while(front<tail-1 && Y(q[tail-1],q[tail-2])*X(i,q[tail-1]) > Y(i,q[tail-1])*X(q[tail-1],q[tail-2]))tail--;//单调增的斜率 
		q[tail++]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
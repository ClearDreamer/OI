/*
写出如下矩阵
1 3  9  27…
2 6 18 54…
4 12 36 108…
发现最多有11列。
我们在其中选取一些数，相邻的不能选择
然后就可以状压求方案数了，但是5没有出现，同样5的倍数也没有出现，7也如此。
应该记录哪些数字出现过，没出现过就作为矩阵的第一个元素，最后把若干个矩阵的方案相乘
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MOD=1000000001;
int a[19][12],b[19],n,bit[12],cnt[19][1<<12];
bool vis[100000+5];
bool check(int i,int j){
	if((i&j)||(j&(j>>1)))return false;
	return true;
}
int calc(int S){
	memset(b,0,sizeof(b));
	a[1][1]=S;
	for(int i=2;i<=18;i++)a[i][1]=min(n+1,a[i-1][1]<<1);
	for(int i=1;i<=18;i++)
		for(int j=2;j<=11;j++)
			a[i][j]=min(n+1,a[i][j-1]*3);
	for(int i=1;i<=18;i++)
		for(int j=1;j<=11;j++){
			if(a[i][j]>n)continue;
			b[i]+=bit[j-1];vis[a[i][j]]=1;
		}
	for(int i=0;i<=18;i++)
		for(int j=0;j<=b[i];j++)
			cnt[i][j]=0;
	cnt[0][0]=1;
	for(int i=0;i<18;i++){
		for(int j=0;j<=b[i];j++){
			if(cnt[i][j]==0)continue;
			for(int k=0;k<=b[i+1];k++)
				if(check(j,k))(cnt[i+1][k]+=cnt[i][j])%=MOD;
		}
	}
	return cnt[18][0];
}
LL ans=1;
int main(){
	bit[0]=1;for(int i=1;i<12;i++)bit[i]=bit[i-1]<<1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		if(!vis[i])ans=ans*calc(i)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
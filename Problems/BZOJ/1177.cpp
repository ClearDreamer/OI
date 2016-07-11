/*
利用前缀和优化可以将问题转换为，在(n-k)*(m-k)的范围内选三个两两距离不小于k的点，使得它们的和最大。
把矩阵分成三块：枚举两条线切法 （共 6种） 【麻烦题】 
*/
#include<cstdio>
using namespace std;
#define up(x,l,r) for(int x=l;x<=r;x++)
#define down(x,l,r) for(int x=r;x>=l;x--)
const int MAXN=1500;
typedef int arr[MAXN+3][MAXN+3];
int max(int x,int y){
	return x<y?y:x;
}
arr a,b,c,d,s;
int n,m,K,ans=0;
int main(){
	scanf("%d%d%d",&n,&m,&K);
	up(i,1,n)up(j,1,m){
		int x;scanf("%d",&x);
		s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+x;
	}
	down(i,K,n)down(j,K,m)
		s[i][j]-=s[i-K][j]+s[i][j-K]-s[i-K][j-K];
	
	up(i,K,n)up(j,K,m)//right and down
		a[i][j]=max(s[i][j],max(a[i-1][j],a[i][j-1]));
	up(i,K,n)down(j,K,m)//left and down
		b[i][j]=max(s[i][j],max(b[i-1][j],b[i][j+1]));
	down(i,K,n)up(j,K,m)//right ans up
		c[i][j]=max(s[i][j],max(c[i+1][j],c[i][j-1]));
	down(i,K,n)down(j,K,m)//left and up
		d[i][j]=max(s[i][j],max(d[i+1][j],d[i][j+1]));
	
	up(i,K,n-K)up(j,K,m-K)ans=max(ans,a[i][j]+b[i][j+K]+c[i+K][m]);
    up(i,K,n-K)up(j,K+K,m)ans=max(ans,b[i][j]+d[i+K][j]+a[n][j-K]);
    up(i,K+K,n)up(j,K,m-K)ans=max(ans,c[i][j]+d[i][j+K]+a[i-K][m]);
    up(i,K,n-K)up(j,K,m-K)ans=max(ans,a[i][j]+c[i+K][j]+b[n][j+K]);
    up(i,K,n)up(j,K+K,m-K)ans=max(ans,s[i][j]+a[n][j-K]+b[n][j+K]);
    up(i,K+K,n-K)up(j,K,m)ans=max(ans,s[i][j]+a[i-K][m]+c[i+K][m]);
    printf("%d\n",ans);
	return 0;
}
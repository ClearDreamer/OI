/*
(F[n] ) (  10^k  1    1 )(F[n-1])
(  n  )=(   0    1    1 )(  n-1 )
(  1  ) (   0    0    1 )(    1 )
然后分段矩阵乘法
0-9,10-99…10^k-n
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
typedef LL arr[4][4];
LL n,mod;
void mul(arr a,arr b,arr res){
	static arr tmp;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			LL &v=tmp[i][j];v=0;
			for(int k=1;k<=3;k++)(v+=a[i][k]*b[k][j])%=mod;
		}
	}
	for(int i=1;i<=3;i++)for(int j=1;j<=3;j++)res[i][j]=tmp[i][j];
}
arr a,b;
void calc(LL K,LL lst){
	memset(b,0,sizeof(b));
	b[1][1]=K%mod;
	b[2][1]=b[2][2]=b[3][1]=b[3][2]=b[3][3]=1;
	LL up=lst-(K/10-1);
	while(up){
		if(up&1)mul(a,b,a);
		mul(b,b,b);
		up>>=1;
	}
}
int main(){
	scanf("%lld%lld",&n,&mod);
	for(int i=1;i<=3;i++)a[i][i]=1;
	LL K=10;
	while(n>=K){
		calc(K,K-1);
		K*=10;
	}
	calc(K,n);
	printf("%lld\n",a[3][1]);
	return 0;
}
/*
12345678910
1000000000
*/
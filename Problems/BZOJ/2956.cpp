/*
http://hzwer.com/6113.html
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const LL INV=3323403,MOD=19940417;
LL n,m,ans;
LL sum(LL a,LL b){//sigma{i|i=a..b}
	return (b-a+1)*(a+b)/2%MOD;
}
LL sum2(LL x){//sigma{i^2|i=1..x}
    return x*(x+1)%MOD*(2*x+1)%MOD*INV%MOD;
}
LL calc(LL n){
	LL res=n*n%MOD;
	for(LL i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		res=(res-sum(i,j)*(n/i)%MOD+MOD)%MOD;
	}
	return (res+MOD)%MOD;
}
int main(){
	scanf("%lld%lld",&n,&m);
    ans=calc(n)*calc(m)%MOD;
	if(n>m)swap(n,m);
	LL s1,s2,s3;
	for(int i=1,j;i<=n;i=j+1){
		j=min(n/(n/i),m/(m/i));
		s1=n*m%MOD*(j-i+1)%MOD;
		s2=(n/i)*(m/i)%MOD*(sum2(j)-sum2(i-1)+MOD)%MOD;
		s3=(n/i*m+m/i*n)%MOD*sum(i,j)%MOD;
		ans=(ans-(s1+s2-s3)%MOD+MOD)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
/*
除了最大值（=2^64）以外都可以用uLL做。
注意内存限制1M 
*/
#include<cstdio>
typedef unsigned long long ULL;
const ULL lim=(ULL)9223372036*(ULL)1000000000+(ULL)854775808;  
ULL calc(int p){
	ULL ans=1;
	for(int i=1;i<=p;i++)ans*=(ULL)2;
	return ans;
}
int a[8],sum;
ULL I=0;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		sum=0;for(int i=0;i<8;i++){scanf("%d",&a[i]);sum+=a[i];}scanf("%llu",&I);
		if(sum==60*8 && I==lim)puts("18446744073709551616");
		else{
			ULL ans=I;
			for(int i=0;i<8;i++)ans+=calc(a[i]);
			printf("%llu\n",ans);
		}
	}
	return 0;
}
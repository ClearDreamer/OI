#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MOD=10007;
int fac[MOD+3],inv[MOD+3];
int qpow(int a,int n){
	int ans=1;
	while(n){
		if(n&1)ans=ans*a%MOD;
		a=a*a%MOD;
		n>>=1;
	}
	return ans;
}
inline void pre(){
	fac[0]=inv[0]=1;
	for(int i=1;i<MOD;i++)fac[i]=fac[i-1]*i%MOD;
	inv[MOD-1]=qpow(fac[MOD-1],MOD-2);
	for(int i=MOD-2;i>=1;i--)inv[i]=inv[i+1]*(i+1)%MOD;
}
int C(int n,int m){
	if(m>n)return 0;
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
int lucas(int n,int m){
	if(n<MOD&&m<MOD)return C(n,m);
	return C(n%MOD,m%MOD)*lucas(n/MOD,m/MOD)%MOD;
}
int main(){
	pre();
	int T,n,m;scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		printf("%d\n",lucas(n,m));
	}
	return 0;
}
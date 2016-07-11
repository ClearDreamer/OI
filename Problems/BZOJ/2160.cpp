#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long LL;
const LL MOD=19930726,MAXN=1000000;
LL N,K;
char str[MAXN+3];
LL p[MAXN+3],mx,id;
LL sum[MAXN+3],len,cnt=0;
LL ans=1;
LL qpow(LL a,LL n){
	LL ans=1;
	while(n){
		if(n&1)ans=ans*a%MOD;
		a=a*a%MOD;
		n>>=1;
	}
	return ans;
}
int main(){
	scanf("%lld%lld",&N,&K);
	scanf("%s",str+1);len=N;
	str[0]='#';str[len+1]='@';
	for(int i=1;i<=len;i++){
		if(mx>i)p[i]=min(p[2*id-i],mx-i);else p[i]=1;
		while(str[i+p[i]]==str[i-p[i]])p[i]++;
		if(i+p[i]>mx)mx=i+p[i],id=i;
		sum[0]++;sum[p[i]+1]--;
	}
	for(int i=1;i<=len;i++)sum[i]+=sum[i-1];
	for(int i=len;i>=1 && cnt<K;i--){
		if(cnt+sum[i]<K)(ans*=qpow(2*i-1,sum[i]))%=MOD,cnt+=sum[i];
		else (ans*=qpow(2*i-1,K-cnt))%=MOD,cnt=K;
	}
	if(cnt<K)puts("-1");
	else printf("%lld\n",ans);
	return 0;
}
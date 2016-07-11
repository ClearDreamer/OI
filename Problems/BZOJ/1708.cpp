#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN=30;
int v,n,a[MAXN+3];
LL f[10003];
int main(){
	scanf("%d%d",&n,&v);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=a[i];j<=v;j++)
			f[j]=f[j]+f[j-a[i]];
	printf("%lld\n",f[v]);
	return 0;
}
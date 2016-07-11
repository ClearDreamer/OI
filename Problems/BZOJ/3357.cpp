/*
f[i][j] 最后一个数是a[i]，上一个数为j的最长等差序列 
f[i][a[j]]=max{2,f[a[j]][2*a[j]-a[i]]} 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<map> 
using namespace std;
const int MAXN=2000;
int a[MAXN+3],n,ans=0;
map<int,int> f[MAXN+3];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	if(n==1){puts("1");return 0;}
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			ans=max(ans,f[i][a[j]]=max(f[i][a[j]],max(2,f[j][2*a[j]-a[i]]+1)));
	printf("%d\n",ans);
	return 0;
}
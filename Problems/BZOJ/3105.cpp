/*
第一次拿完后，要使剩下的火柴中不存在异或和为0的子集，且让子集和最大
求解极大线性无关组。
证明是个拟阵
因此只要从大到小排序，依次贪心的添加到当前集合就可以了，需要动态维护线性基
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int MAXN=100;
typedef long long LL;
int n,a[MAXN+3],b[33];
LL tot=0,ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1,greater<int>());
	for(int i=1;i<=n;i++)tot+=a[i];
	for(int i=1;i<=n;i++){
		int tmp=a[i];
		for(int j=30;j>=0;j--){
			if(a[i]>>j&1){
				if(b[j])a[i]^=a[b[j]];
				else {b[j]=i;break;}
			}
		}
		if(a[i])ans+=tmp;
	}
	printf("%lld\n",tot-ans);
	return 0;
}
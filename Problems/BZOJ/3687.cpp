/*
f[i]表示算术和为i的集合有多少个（奇数或偶数个） 
f[0]=1;
f[i]=(f[i]+f[i-a[x]])%2
用bitset优化
f=f^(f<<a[x]) 
*/
#include<bitset>
#include<cstdio>
using namespace std;
const int MAXN=2000000;
bitset<MAXN+3> f;
int ans=0,sum=0;
int main(){
	int n,a;scanf("%d",&n);f[0]=1;
	while(n--){
		scanf("%d",&a);sum+=a;
		f^=f<<a;
	}
	for(int i=1;i<=sum;i++)
		if(f[i])ans^=i;
	printf("%d\n",ans);
	return 0;
}
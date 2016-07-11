/*
f[i][j]：i个月，做了j道题的最大剩余
f[i][j]=max{m-sb[j]-sb[k] | sa[j]-sa[k]<=f[i-1][k]}
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN=305;
int n,m,a[MAXN+3],b[MAXN+3],sa[MAXN+3],sb[MAXN+3];
int f[2][MAXN+3];
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++){scanf("%d%d",&a[i],&b[i]);sa[i]=sa[i-1]+a[i];sb[i]=sb[i-1]+b[i];}
	memset(f[1],-1,sizeof(f[1]));
	f[1][0]=m;int pre=1,now=0,ans=1;
	while(1){
		ans++;int i;
		memset(f[now],-1,sizeof(f[now]));
		for(i=0;i<=n;i++){
			bool flg=0;
			for(int j=i;j>=0&&sb[i]-sb[j]<=m;j--){
				if(sa[i]-sa[j]<=f[pre][j]){
					flg=1;
					f[now][i]=m-(sb[i]-sb[j]);
					break;
				}
			}
			if(flg==false)break;
		}
		if(i>n)break;
		swap(now,pre);
	}
	printf("%d\n",ans+1);
	return 0;
}
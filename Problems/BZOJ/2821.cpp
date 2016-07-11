#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=100000,MAXB=320;
int block,bcnt,id[MAXN+3],sum[MAXB+3][MAXN+3],a[MAXN+3],l[MAXB+3],r[MAXB+3],tsum[MAXN+3];
int f[MAXB+3][MAXB+3];
int n,c,m,ans=0;
void work(int x,int y){
	int L=id[x],R=id[y];
	if(L==R){
		for(int i=x;i<=y;i++)tsum[a[i]]=0;
		for (int i=x;i<=y;i++)
			if (++tsum[a[i]]!=1)
				ans+=(tsum[a[i]]&1)?-1:1;
	}
	else{
		ans=f[L+1][R-1];
		for (int i=x;i<=r[L];i++) tsum[a[i]]=sum[R-1][a[i]]-sum[L][a[i]];
		for (int i=l[R];i<=y;i++) tsum[a[i]]=sum[R-1][a[i]]-sum[L][a[i]];
		//for (int i=1;i<=c;i++) printf("tsum%d\n",tsum[i]);
		for (int i=x;i<=r[L];i++)
			if (++tsum[a[i]]!=1)
				ans+=(tsum[a[i]]&1)?-1:1;
		for (int i=l[R];i<=y;i++)
			if (++tsum[a[i]]!=1)
				ans+=(tsum[a[i]]&1)?-1:1;
	}
}
int main(){
	scanf("%d%d%d",&n,&c,&m);
	block=sqrt(n),bcnt=n/block+(n%block!=0);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)id[i]=(i-1)/block+1;
	for(int i=1;i<=n;i++){r[id[i]]=i;if(l[id[i]]==0)l[id[i]]=i;}
	for(int i=1;i<=bcnt;i++){
		for(int j=1;j<=c;j++)sum[i][j]=sum[i-1][j];
		for(int j=l[i];j<=r[i];j++)sum[i][a[j]]++;
	}
	for(int i=1;i<=bcnt;i++){
		for(int j=1;j<=c;j++)tsum[j]=0;int tmp=0;
		for(int j=i;j<=bcnt;j++){
			for(int k=l[j];k<=r[j];k++)
				if(++tsum[a[k]]!=1)tmp+=(tsum[a[k]]&1)?-1:1;
			f[i][j]=tmp;
		}
	}
	for (int i=1;i<=m;i++) {
		int x,y;scanf("%d%d",&x,&y);
		x=(x+ans)%n+1,y=(y+ans)%n+1,ans=0;
		if (x>y) swap(x,y);
		work(x,y);
		printf("%d\n",ans);
	}
	return 0;
}
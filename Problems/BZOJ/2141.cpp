/*
题目大意：给定一个序列，m次交换两个数，求初始逆序对数及每次交换后的逆序对数
首先离散化，分块，对于每块建立一个树状数组，保存这个块中的所有元素
然后对于每个询问(x,y) (x<y) 两侧的数是没有影响的，区间(x,y)的数a[i]讨论如下：
a[i]<a[x] --ans
a[i]>a[x] ++ans
a[i]<a[y] ++ans
a[i]>a[y] --ans
然后对于块中的树状数组处理，块外的暴力
注意此题元素有重复 亲测可信
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=20000+100;
int n,m,ans,tot,block,a[MAXN+3];
pair<int,int> b[MAXN+3];
int pre[MAXN+3],cnt[200][MAXN+3];
void up(int *c,int x){
	for(;x<=n;x+=x&-x)++c[x];
}
void down(int *c,int x){
	for(;x<=n;x+=x&-x)--c[x];
}
int query(int *c,int x){
	int ans=0;for(;x;x-=x&-x)ans+=c[x];return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&b[i].first),b[i].second=i;
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		if(b[i].first!=b[i-1].first)++tot;
		a[b[i].second]=tot;
	}
	for(int i=n;i;i--)ans+=query(pre,a[i]-1),up(pre,a[i]);
	block=static_cast<int>(sqrt(n)+1e-7);
	for(int i=1;i<=n;i++)up(cnt[(i-1)/block],a[i]);
	printf("%d\n",ans);
	scanf("%d",&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);if(x>y)swap(x,y);
		int b1=(x-1)/block+1,b2=(y-1)/block-1;
		if(b1<=b2){
			for(int j=b1;j<=b2;j++){
				ans-=query(cnt[j],a[x]-1);
				ans+=query(cnt[j],n)-query(cnt[j],a[x]);
				ans+=query(cnt[j],a[y]-1);
				ans-=query(cnt[j],n)-query(cnt[j],a[y]);
			}
			for(int j=x+1;j<=b1*block;j++){
				if(a[j]<a[x])ans--;
				if(a[j]>a[x])ans++;
				if(a[j]<a[y])ans++;
				if(a[j]>a[y])ans--;
			}
			for(int j=(b2+1)*block+1;j<y;j++){
				if(a[j]<a[x])ans--;
				if(a[j]>a[x])ans++;
				if(a[j]<a[y])ans++;
				if(a[j]>a[y])ans--;
			}
		}
		else{
			for(int j=x+1;j<y;j++){
				if(a[j]<a[x])ans--;
				if(a[j]>a[x])ans++;
				if(a[j]<a[y])ans++;
				if(a[j]>a[y])ans--;
			}
		}
		if(a[x]<a[y])ans++;
		else if(a[x]>a[y])ans--;
		printf("%d\n",ans);
		down(cnt[(x-1)/block],a[x]);
		down(cnt[(y-1)/block],a[y]);
		swap(a[x],a[y]);
		up(cnt[(x-1)/block],a[x]);
		up(cnt[(y-1)/block],a[y]);
	}
	return 0;
}
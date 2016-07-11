/*
枚举对称轴x，考虑用len(x+1,y)*4更新答案，则必须满足y-p[y]<=x，y<=x+p[x]/2。
那么我们按照y-p[y]排序后，依次插入set，每次询问比x+p[x]/2小的最大值就可以了。
注意：本题只讨论长度为偶数的回文子串，所以不需要加上#号。
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<set>
using namespace std;
const int MAXN=500000;
struct data{
	int x,y;
	bool operator <(const data &d)const{
		return x<d.x;
	}
}ds[MAXN+3];
set<int> S;
int mx,id,p[MAXN+3],n;
char str[MAXN+3];
int main(){
	scanf("%d",&n);
	scanf("%s",str+1);str[0]='#';
	for(int i=1;i<=n;i++){
		if(mx>i)p[i]=min(mx-i,p[2*id-i]);else p[i]=0;
		while(str[i+p[i]+1]==str[i-p[i]])p[i]++;
		if(i+p[i]>mx)mx=i+p[i],id=i;
	}
	for(int i=1;i<=n;i++)ds[i].x=i-p[i],ds[i].y=i;
	sort(ds+1,ds+n+1);
	int ans=0;
	for(int i=1,top=1;i<=n;i++){
		while(top<=n && ds[top].x<=i)S.insert(ds[top++].y);
		ans=max(ans,4*(*--S.lower_bound(i+p[i]/2+1)-i));
	}
	printf("%d\n",ans);
	return 0;
}
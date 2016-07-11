/*
最小区间覆盖问题
将所有区间按左端点坐标从小到大排序，顺序处理每个区间。每次选择覆盖点的区间中右端点坐标最大的一个，并将更新为该区间的右端点坐标，直到选择的区间已包含。
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int MAXN=25000;
typedef pair<int,int> P;
P s[MAXN+3];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&s[i].first,&s[i].second);
	sort(s+1,s+n+1);
	int p=1,cur=1,ans=0;
	while(p<=m){
		if(cur>n){ans=-1;break;}
		int mxr=0;
		while(cur<=n&&s[cur].first<=p)mxr=max(mxr,s[cur].second),cur++;
		if(mxr<p){ans=-1;break;}
		p=mxr+1;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
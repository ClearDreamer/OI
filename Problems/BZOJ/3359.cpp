#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAXN=100;
struct data{
	int x,y;
	bool operator <(const data &d)const{
		if(x==d.x&&y==d.y)return false;
		if(x>d.x || y>d.y)return false;
		return true;
	}
}ds[MAXN+3];
bool cmp(data a,data d){
	return a.x<d.x || a.x==d.x&&a.y<d.y;
}
int f[MAXN+3],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&ds[i].x,&ds[i].y);
		if(ds[i].x>ds[i].y)swap(ds[i].x,ds[i].y);
	}
	sort(ds+1,ds+n+1,cmp);
	for(int i=1;i<=n;i++){
		f[i]=1;
		for(int j=1;j<i;j++)
			if(ds[j]<ds[i])f[i]=max(f[i],f[j]+1);
	}
	printf("%d\n",*max_element(f+1,f+n+1));
	return 0;
}
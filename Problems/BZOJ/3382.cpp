#include<cstdio>
#include<algorithm>
using namespace std;
int n,mxp,mxd,mnp,mnd;
inline void Max(int &x,int y){if(y>x)x=y;}
inline void Min(int &x,int y){if(y<x)x=y;}
int main(){
	mxp=mxd=-(1<<30);mnp=mnd=1<<30;
	scanf("%d",&n);
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);
		Max(mxp,x+y);Max(mxd,x-y);
		Min(mnp,x+y);Min(mnd,x-y);
	}
	printf("%d\n",max(mxp-mnp,mxd-mnd));
	return 0;
}
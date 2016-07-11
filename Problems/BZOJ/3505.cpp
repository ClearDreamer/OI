/*
首先答案就是所有取出三个点的方案数减去会三点共线的方案数
显然n*m的网格上有(n+1)*(m+1)个整点，然后令t=(n+1)*(m+1)，那么取三个点的方案数就是t*(t-1)*(t-2)/6（就是排列组合啦T T）
然后要考虑怎么算三点共线的方案数
然后有一个结论是在(a,b) (x,y)两点构成的线段上有gcd(a-x,b-y)-1个整点(a>x,b>y)
我们固定(a,b) (x,y)为共线的三点中左边两个，那么第三个点的方案数就是gcd(a-x,b-y)-1
这样枚举abxy的复杂度是O(n^2*m^2)
优化是把这线段平移到原点处，那么会发现其实只要枚举(0,0) (x-a+1,y-b+1)，其他的线段平移就可以了（这里强烈建议自己动手画一画！）
画完很容易发现这样(0,0) (x-a+1,y-b+1)的线段可以平移出(n-i+1)*(m-j+1)种不同方案，在 (x-a+1,y-b+1)的时候如果不在坐标轴上还要算两次
*/
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN=1000;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
LL C(LL x){
	return x*(x-1)*(x-2)/6;
}
LL calc(int n,int m){
	LL ans=C(n*m);
	ans-=n*C(m);
	ans-=m*C(n);
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			int d=gcd(i,j)+1;
			if(d>2)ans-=(d-2)*2*(n-i)*(m-j);
		}
	}
	return ans;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	printf("%lld\n",calc(n+1,m+1));
	return 0;
}
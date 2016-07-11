#include<cstdio>
#include<cmath>
using namespace std;
typedef long long LL;
const double r=0.57721566490153;
const double eps=1e-10;
LL n,m;
double ans=0;
int main(){
	scanf("%lld%lld",&n,&m);
	if(n<=10000)
		for(int i=1;i<=n;i++)ans+=0.5/i;
	else ans=(log(n+1)+r)/2.0;
	printf("%d\n",(int)(ans*m-eps));//attention to eps
	return 0;
}
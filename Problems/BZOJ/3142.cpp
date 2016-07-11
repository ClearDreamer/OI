/*
http://blog.csdn.net/xieguofu2014/article/details/50285219
*/
#include<iostream> 
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
typedef long long LL;
LL ans,n,m,k,p;
LL power(LL x,LL y,LL z){
    if (y==1) return x;
    else {
        LL e=power(x,y>>1,z);
        e=(e*e)%p;
        if (y&1) e=(e*x)%p;
        return e;
    }
}
int main(){
    scanf("%lld%d%d%d",&n,&k,&m,&p);
    ans=(power(m % p,k-1,p)*(n%p))%p;
    ans-=((power(m % p,k-2,p)*(k-1)% p)*(((m+1)*m/2)% p))%p;
    ans=(ans+p)%p;
    printf("%d",ans);
}
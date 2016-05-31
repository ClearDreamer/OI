/*
Zju2116 Christopher
分析：卢卡斯定理：
	求C(n,m)模素数p的值。
	将n和m都化成p进制。
	设n化成p进制为{a[i]}，m化成p进制为{b[i]}
	有：C(n,m)=pi(C(a[i],b[i])) (mod p)
	那么C(n,m)为p的倍数，等效于存在b[i]>a[i]，
	即求有多少数<N，且p进制某一位大于n的p进制的对应位。
	那么先求出a[i]，然后dp即可。
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
struct bign{
    int n,g[505];
    void set(int k){n=1; g[1]=k;}
    bign operator*(const int &b){
        bign c;int y=0; c.n=n;
        if (!b){c.set(0);return c;}
        for(int i=1;i<=n;i++){y+=g[i]*b;c.g[i]=y%10;y/=10;}
        while(y){c.g[++c.n]=y%10;y/=10;}
        return c;
    }
    bign operator+(const bign &b){
        bign c; int y=0,p;
        if (n>b.n){
            c=*this;p=b.n;
            for(int i=1;i<=b.n;i++){y+=b.g[i]+c.g[i];c.g[i]=y%10;y/=10;}
            while(y&&p<n){y+=c.g[++p];c.g[p]=y%10;y/=10;}
        }
		else{
            c=b;p=n;
            for(int i=1;i<=n;i++){y+=g[i]+c.g[i];c.g[i]=y%10;y/=10;}
            while(y&&p<b.n){y+=c.g[++p];c.g[p]=y%10;y/=10;}
        }
        if(y)c.g[++c.n]=y;
        return c;
    }
    int operator/(const int &b){
        int y=0;
        for (int i=n;i;i--){
            y=y*10+g[i];
            if(y<b)g[i]=0;
            else{g[i]=y/b;y%=b;}
        }
        while(n>1&&!g[n])n--;
        return y;
    }
    void input(){
        static char s[105]; scanf("%s",s+1);n=strlen(s+1);
        for(int i=1;i<=n;i++)g[n+1-i]=s[i]-48;
    }
}x,mi,ans,f[505];
int p,a[505],t;
int main(){
    x.input();
    scanf("%d",&p);
    while(x.n!=1||x.g[1])a[++t]=x/p;
    f[0].set(0); mi.set(1); ans.set(0);
    for(int i=1;i<t;i++){
        f[i]=mi*(p-1-a[i]);
        f[i]=f[i]+f[i-1]*(a[i]+1);
        mi=mi*p;
    }
    for(int i=t;i>1;i--)ans=ans+f[i-1]*a[i];
    for(int i=ans.n;i;i--)printf("%d",ans.g[i]);
    puts("");
    return 0;
}
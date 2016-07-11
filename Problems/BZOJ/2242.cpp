#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<map>
#include<algorithm>
typedef long long LL;
using namespace std;
int T,K;
int read(){
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
void exgcd(int a,int b,int &x,int &y){
	if(b==0){x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	int t=x;x=y;y=t-a/b*y;
}
int solve1(LL y,int z,int p){
	y%=p;
	LL ans=1;
	for(int i=z;i;i>>=1,y=y*y%p)
		if(i&1)ans=ans*y%p;
	return ans;
}
int solve2(int y,int z,int p){
	p=-p;
	int t=gcd(y,p);
	if(z%t)return -1;
	y/=t;z/=t;p/=t;
	int a,b;exgcd(y,p,a,b);
	a=(LL)a*z%p;
	while(a<0)a+=p;
	return a;
}
map<int,int> mp;
int solve3(int y,int z,int p){
	y%=p;
	if(!y&&!z)return 1;
	if(!y)return -1;
	mp.clear();
	LL m=ceil(sqrt(p)),t=1;mp[1]=m+1;
	for(LL i=1;i<m;i++){
		t=t*y%p;
		if(!mp[t])mp[t]=i;
	}
	LL tmp=solve1(y,p-m-1,p),ine=1;
	for(LL k=0;k<m;k++){
		int i=mp[z*ine%p];
		if(i){
			if(i==m+1)i=0;
			return k*m+i;
		}
		ine=ine*tmp%p;
	}
	return -1;
}
int main(){
	T=read();K=read();
	while(T--){
		int y=read(),z=read(),p=read();
		int res=-1;
		if(K==1)res=solve1(y,z,p);
		else if(K==2)res=solve2(y,z,p);
		else res=solve3(y,z,p);
		if(res==-1)puts("Orz, I cannot find x!");
		else printf("%d\n",res);
	}
	return 0;
}
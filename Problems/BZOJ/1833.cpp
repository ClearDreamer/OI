#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long LL;
struct data {
	LL a[10];
	data(){init();}
	LL& operator [](int id){
		return a[id];
	}
	data operator +(const data &b)const{
		data res;
		for(int i=0;i<=9;i++)res[i]=a[i]+b.a[i];
		return res;
	}
	data operator -(const data &b)const{
		data res;
		for(int i=0;i<=9;i++)res[i]=a[i]-b.a[i];
		return res;
	}
	inline void init(){
		memset(a,0,sizeof(a));
	}
};
LL A,B,t[25];
data f[25][10];
data calc(LL x){
	data ans;
	if(!x){ans.a[0]=1;return ans;}
	int len=15;
	while(t[len]>x)len--;
	for(int i=1;i<len;i++)
		for(int j=1;j<=9;j++)ans=ans+f[i][j];
	ans.a[0]++;
	int cur=x/t[len];
	for(int i=1;i<cur;i++)ans=ans+f[len][i];//attention i=1..cur-1
	x%=t[len];ans.a[cur]+=x+1;
	for(int i=len-1;i;i--) {
		cur=x/t[i];
		for(int j=0;j<cur;j++)ans=ans+f[i][j];//attention j=0..cur-1
		x%=t[i];ans.a[cur]+=x+1;
	}
	return ans;
}
int main() {
	t[1]=1;for(int i=2;i<=15;i++)t[i]=t[i-1]*10;
	for(int i=0;i<=9;i++)f[1][i].a[i]=1;
	for(int i=2;i<=12;i++)
		for(int x=0;x<=9;x++){
			f[i][x].a[x]+=t[i];
			for(int y=0;y<=9;y++)
				f[i][x]=f[i][x]+f[i-1][y];
		}
	scanf("%lld%lld",&A,&B);
	data res=calc(B)-calc(A-1);
	printf("%lld",res[0]);
	for(int i=1;i<=9;i++)printf(" %lld",res[i]);
	return 0;
}
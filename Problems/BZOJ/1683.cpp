#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=50000,INF=0x3f3f3f3f;
int sta[MAXN+3],top=0,ans,n,tmp; 
int main(){
	scanf("%d%d",&n,&tmp);
	ans=n;
	for(int i=1,h;i<=n;i++){
		scanf("%d%d",&tmp,&h);
		while(top && sta[top]>h)top--;
		if(sta[top]==h)ans--;
		sta[++top]=h;
	}
	printf("%d\n",ans);
	return 0;
}

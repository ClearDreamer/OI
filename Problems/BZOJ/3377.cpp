/*
将原序列分成连续的几块，使得每一块内包含了所有的数字 ，ans=块数+1 
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int n,a,k,ans=0;
int vis[10003],cur=0,cnt=0;
int main(){
	scanf("%d%d",&n,&k);cur++;
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		if(vis[a]==cur)continue;
		vis[a]=cur;cnt++;
		if(cnt==k)cur++,ans++,cnt=0;
	}
	printf("%d\n",ans+1);
	return 0; 
}
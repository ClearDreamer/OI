#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib> 
using namespace std;
int flg[12],D,ans=0,a[12];
int calc(){
	int a1=0,a2=a[1],a3=1;
	for(int i=2;i<=D;i++){
		switch(flg[i-1]){
			case 1:
			case 2:
				if(a3==1)a1=a1+a2;else a1=a1-a2;
				a2=a[i];a3=flg[i-1];
				break;
			case 3:
				a2=a2*a[i];
				break;
		}
	}
	if(a3==1)a1=a1+a2;else a1=a1-a2;
	return a1;
}
void dfs(int dep){
	if(dep>=D){
		ans+=(calc()==24);return;
	}
	for(int i=1;i<=3;i++){flg[dep]=i;dfs(dep+1);}
}
int main(){
	scanf("%d",&D);
	for(int i=1;i<=D;i++)scanf("%d",&a[i]);
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
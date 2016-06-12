#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
char a[11][20];
int n;
void dfs(int l,int r){
	if(l==r){
		printf("%s",a[l]);
		if(r==n)printf("\n");
	}
	else if(l==r-1){
		printf("(%s*%s)",a[l],a[r]);
	}
	else for(int i=l;i<r;i++){
		printf("(");
		dfs(l,i);
		dfs(i+1,r);
		printf(")");
	}
}
int main(){
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++)scanf("%s\n",a[i]);
	dfs(1,n);
	return 0;
}

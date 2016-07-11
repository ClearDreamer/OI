#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=25000;
int mn[16][MAXN+3],n,q,bin[MAXN+3];
int query(int l,int r){
	int k=bin[r-l+1];
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
int main(){
	scanf("%d%d",&n,&q);
	bin[0]=1;
	for(int i=1;i<=n;i++){
		scanf("%d",&mn[0][i]);
		if((1<<bin[i-1]+1)<=i)bin[i]=bin[i-1]+1;
		else bin[i]=bin[i-1];
	}
	for(int i=1;i<16;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
	for(int i=1,u,v;i<=q;i++){
		scanf("%d%d",&u,&v);
		printf("%d\n",query(u,v));
	}
	return 0;
}
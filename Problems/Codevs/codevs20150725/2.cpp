#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000000,INF=0x3f3f3f3f,MAXL=1000000010;
int n,m,a[MAXN+3],b[MAXN+3],c[MAXN+3],d[MAXN+3],ans=0;
int fail[MAXN+3],*str,L;
void load(int* s,int len){
	fail[0]=fail[1]=0;L=len;
	for(int i=1;i<len;i++){
		int j=fail[i];
		while(j&&s[i]!=s[j])j=fail[j];
		fail[i+1]=s[i]==s[j]?j+1:0;
	}
	str=s;
}
int kmp(int *t,int len){
	int j=0,ans=0;
	for(int i=0;i<len;i++){
		while(j&&t[i]!=str[j])j=fail[j];
		j+=t[i]==str[j];
		if(j==L)ans++,j=fail[j];
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for(int j=0;j<m;j++)
		scanf("%d",&b[j]);
	for(int i=0;i<n-1;i++)
		c[i]=a[i+1]-a[i];
	for(int i=0;i<m-1;i++)
		d[i]=b[i+1]-b[i];
	load(c,n-1);
	ans+=kmp(d,m-1);
	for(int i=0;i<n-1;i++)
		c[i]=-c[i];
	for(int i=0;i<m-1;i++)
		d[i]=b[m-i-2]-b[m-i-1];
	//for(int i=0;i<n-1;i++)printf("%d ",c[i]);puts("");for(int i=0;i<m-1;i++)printf("%d ",d[i]);puts("");
	load(c,n-1);
	ans+=kmp(d,m-1);
	printf("%d\n",ans);
	return 0;
}


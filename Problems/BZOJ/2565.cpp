/*
反串加入PAM，处理每个后缀的最长回文长度，
再把原串加入，统计答案 
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN=100000+1000;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
char str[MAXN+3];
int n;
int len[MAXN+3],fail[MAXN+3],ch[MAXN+3][26],S[MAXN+3],lst,tot,L;
int newnode(int l){
	memset(ch[tot],0,sizeof(ch[tot]));
	len[tot]=l;return tot++;
}
inline void init(){
	tot=0;newnode(0);newnode(-1);
	fail[0]=1;L=0;S[0]=-1;lst=0;
}
int getfail(int x){
	while(S[L-len[x]-1]!=S[L])x=fail[x];
	return x;
}
int add(int v){
	S[++L]=v;
	int cur=getfail(lst);
	if(!ch[cur][v]){
		int p=newnode(len[cur]+2);
		fail[p]=ch[getfail(fail[cur])][v];
		ch[cur][v]=p;
	}
	lst=ch[cur][v];
	return lst;
}
int suflen[MAXN+3],ans=0;
int main(){
	scanf("%s",str+1);n=strlen(str+1);
	init();
	for(int i=n;i>=1;i--){
		suflen[i]=len[add(str[i]-'a')];
	}
	init();
	for(int i=1;i<n;i++){
		ans=max(ans,suflen[i+1]+len[add(str[i]-'a')]);
	}
	printf("%d\n",ans);
	return 0;
}
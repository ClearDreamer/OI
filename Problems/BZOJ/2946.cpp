/*
第一个串建自动机，每个串放进去匹配，得出每个状态的最大匹配长度
每个状态取所有串最小值，得出最大公共子串长
对所有状态子串长取最大值就是答案
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN=2000;
struct SAM{
	int ch[2*MAXN+3][26],last,pa[2*MAXN+3],len[2*MAXN+3],tot;
	void init(){
		tot=0;
		last=newnode(0);pa[last]=0;
	}
	int newnode(int l){
		tot++;
		len[tot]=l;
		return tot;
	}
	void append(int x){
		int np=newnode(len[last]+1),p=last;
		while(p&&ch[p][x]==0)ch[p][x]=np,p=pa[p];
		if(p==0)pa[np]=1;
		else{
			int q=ch[p][x];
			if(len[p]+1==len[q])pa[np]=q;
			else{
				int nq=newnode(len[p]+1);
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				pa[nq]=pa[q];
				pa[np]=pa[q]=nq;
				while(p&&ch[p][x]==q)ch[p][x]=nq,p=pa[p];
			}
		}
		last=np;
	}
	int ans[2*MAXN+3],mx[2*MAXN+3],q[2*MAXN+3];
	void pre(){
		static int v[2*MAXN+3];
		memset(v,0,sizeof(v));
		for(int i=1;i<=tot;i++){ans[i]=len[i];v[len[i]]++;}
		for(int i=1;i<=tot;i++)v[i]+=v[i-1];
		for(int i=tot;i>=1;i--)q[v[len[i]]--]=i;
	}
	void solve(char *str){
		int l=strlen(str+1);
		memset(mx,0,sizeof(mx));
		int p=1,tmp=0;
		for(int i=1;i<=l;i++){
			int c=str[i]-'a';
			while(ch[p][c]==0&&p)p=pa[p];
			if(p==0)p=1,tmp=0;
			else tmp=min(tmp,len[p])+1,p=ch[p][c];
			mx[p]=max(mx[p],tmp);//识别了p，连同他的parent都识别了 
		}
		for(int i=tot;i>=1;i--)mx[pa[q[i]]]=max(mx[pa[q[i]]],mx[q[i]]);
		for(int i=1;i<=tot;i++)ans[i]=min(ans[i],mx[i]);
	}
	int Ans(){
		return *max_element(ans+1,ans+tot+1);
	}
}sam;
int n;
char str[MAXN+3];
int main(){
	scanf("%d",&n);
	scanf("%s",str+1);int l=strlen(str+1);
	sam.init();
	for(int i=1;i<=l;i++)
		sam.append(str[i]-'a');
	sam.pre();
	for(int i=2;i<=n;i++){
		scanf("%s",str+1);
		sam.solve(str);
	}
	printf("%d\n",sam.Ans());
	return 0;
}
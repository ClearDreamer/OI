#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN=100010;
namespace SAM{
	int ch[2*MAXN+3][26],last,tot,cnt[2*MAXN+3],pa[2*MAXN+3],len[2*MAXN+3];
	LL sum[2*MAXN+3];
	int vis[2*MAXN+3];
	void clear(){
		for(int i=1;i<=tot;i++)vis[i]=0;
	}
	int newnode(int l){
		tot++;
		memset(ch,0,sizeof(ch[tot]));
		len[tot]=l;
		sum[tot]=cnt[tot]=pa[tot]=0;
		return tot;
	}
	void init(){
		tot=0; 
		last=newnode(0);
		clear();
	}
	void insert(int x){
		int np=newnode(len[last]+1),p=last;
		while(p&&ch[p][x]==0)ch[p][x]=np,p=pa[p];
		if(p==0)pa[np]=1;
		else{
			int q=ch[p][x];
			if(len[q]==len[p]+1)pa[np]=q;
			else{
				int nq=newnode(len[p]+1);
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				pa[nq]=pa[q];pa[q]=pa[np]=nq;
				while(p&&ch[p][x]==q)ch[p][x]=nq,p=pa[p];
			}
		}
		last=np;
	}
	int count(int x){
		return len[x]-len[pa[x]];
	}
	void dp(int x){
		if(x==1||vis[x])return;
		vis[x]=1;dp(pa[x]);sum[x]+=sum[pa[x]];
	}
}
int n,K,len[MAXN+3];
string S[MAXN+3];
char str[MAXN+3];
int main(){
	scanf("%d%d",&n,&K);
	SAM::init();
	for(int i=1;i<=n;i++){
		scanf("%s",str);
		S[i]=(string)(str);len[i]=S[i].length();
		SAM::last=1;
		for(int j=0;j<len[i];j++){
			SAM::insert(str[j]-'a');
		}
	}
	for(int i=1;i<=n;i++){
		int cur=1;
		for(int j=0;j<len[i];j++){
			cur=SAM::ch[cur][S[i][j]-'a'];
			for(int k=cur;k&&SAM::vis[k]!=i;k=SAM::pa[k]){
				SAM::cnt[k]++;
				SAM::vis[k]=i;
			}
		}
	}
	for(int i=1;i<=SAM::tot;i++)SAM::sum[i]=(LL)(SAM::cnt[i]>=K)*(SAM::count(i));
	SAM::clear();
	for(int i=1;i<=SAM::tot;i++)SAM::dp(i);
	LL ans=0;
	for(int i=1;i<=n;i++){
		int cur=1;ans=0;
		for(int j=0;j<len[i];j++){
			cur=SAM::ch[cur][S[i][j]-'a'];
			ans+=SAM::sum[cur];
		}
		printf("%lld ",ans);
	}
	return 0;
}
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=10000;
typedef long long LL;
struct Trie{
	struct node{
		node *ch[26];
		void clear(){memset(ch,0,sizeof(ch));}
	}a[MAXN*40],*root;
	int tot;
	node *newnode(){++tot,a[tot].clear();return &a[tot];}
	void add(char s[],int sum[]){
		int len = strlen(s);
		node *p = root;
		for(int i=0;i<len;i++){
			if (!p->ch[s[i]-'a']){p->ch[s[i]-'a']=newnode();if(sum!=NULL)sum[s[i]-'a']++;}
			p=p->ch[s[i]-'a'];
		}
	}
	void clear(){tot=0,root=newnode();}
	LL solve(int sum[], bool b[]){
		LL ans=0;
		for(int i=2;i<=tot;i++){
			for(int j=0;j<26;j++)
				if(!a[i].ch[j])ans+=sum[j];
				else ans+=b[j];
		}
		return ans;
	}
}trie;
char s[MAXN+3][41];
int n,sum[41];
bool b[41],d[41];
long long ans;
int main(){
	scanf("%d", &n);
	trie.clear();
	memset(b,0,sizeof(b));
	memset(sum,0,sizeof(sum)); 
	ans=0;memset(d,0,sizeof(d));
	for (int i = 0; i < n; i ++){
		scanf("%s", s[i]); int len = strlen(s[i]);
		reverse(s[i],s[i]+len);
		b[s[i][0]-'a']=1;
		if(len==1&&!d[s[i][0]-'a'])//长度为1的时候，无法在统计后继的时候统计到这个字符串 eg：3 a b c  right ans=12 
			d[s[i][0]-'a']=1,ans++;
		trie.add(s[i],sum);
		reverse(s[i],s[i]+len);
	}
	trie.clear();
	for(int i=0;i<n;i++){
		
		trie.add(s[i],NULL);
	}
	ans+=trie.solve(sum, b);
	printf("%lld\n",ans);
	return 0;
}
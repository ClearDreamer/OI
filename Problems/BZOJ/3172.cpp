#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=1000010;
using namespace std;
int n,w[210];char s[MAXN];
struct AC_DFA{
	int tot,ch[MAXN][26],fail[MAXN],q[MAXN],head,tail,sum[MAXN];
	void insert(int &x){
		int p=0;
		int len=strlen(s);
		for (int i=0;i<len;i++){
			if (!ch[p][s[i]-'a']) ch[p][s[i]-'a']=++tot;
			++sum[p=ch[p][s[i]-'a']];//所有前缀都要+1，但查询时只用查终止节点 
		}
		x=p;
	}
	inline void build(){
		head=0,q[tail=1],fail[0]=-1;
		while (head!=tail){
			int x=q[++head];
			for (int i=0;i<26;i++){
				if (ch[x][i]) q[++tail]=ch[x][i],fail[ch[x][i]]=x==0?0:ch[fail[x]][i];
				else ch[x][i]=x==0?0:ch[fail[x]][i];
			}
		}
	}
	inline void calc(){
		for (int i=tail;i;i--) sum[fail[q[i]]]+=sum[q[i]];//逆bfs序，直接tot->1是不对的 
	}
}T;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%s",s),T.insert(w[i]);
	T.build();T.calc();
	for (int i=1;i<=n;i++) printf("%d\n",T.sum[w[i]]);
	return 0;
}
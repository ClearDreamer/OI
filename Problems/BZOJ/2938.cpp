/*
可以在AC自动机上不停的走但始终无法匹配，
找一个无法匹配的环即可 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=30000;
struct ACM{
	int ch[MAXN+3][2],fail[MAXN+3],tot;
	bool val[MAXN+3],vis[MAXN+3],ins[MAXN+3];
	void init(){tot=-1;newnode();}
	int newnode(){
		tot++;
		memset(ch[tot],0,sizeof(ch[tot]));
		val[tot]=vis[tot]=0;
		return tot;
	}
	void insert(char *str){
		int len=strlen(str+1),cur=0;
//		cout<<ch[0][0]<<endl;
		for(int i=1;i<=len;i++){
			if(ch[cur][str[i]-'0']==0)ch[cur][str[i]-'0']=newnode();
			cur=ch[cur][str[i]-'0'];
		}
		val[cur]=1;
	}
	void build(){
		static queue<int> q;
		while(!q.empty())q.pop();
		for(int i=0;i<2;i++)if(ch[0][i]){
			fail[ch[0][i]]=0;
			q.push(ch[0][i]);
		}
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=0;i<2;i++){
				int &v=ch[u][i];
				if(v==0){
					v=ch[fail[u]][i];continue;
				}
				int p=fail[u];
				while(p && ch[p][i]==0)p=fail[p];
				fail[v]=ch[p][i];
				val[v]|=val[fail[v]];
				q.push(v);
			}
		}
	}
	bool dfs(int u){
		ins[u]=1;
		for(int i=0;i<2;i++){
			int v=ch[u][i];
			if(ins[v])return true;
			if(vis[v] || val[v])continue;
			vis[v]=1;
			if(dfs(v))return true;
		}
		ins[u]=0;
		return false;
	}
}acm;
int n;
char str[MAXN+3];
int main(){
	scanf("%d",&n);acm.init();
	for(int i=1;i<=n;i++){
		scanf("%s",str+1);
		acm.insert(str);
	}
	acm.build();
	puts(acm.dfs(0)?"TAK":"NIE");
	return 0;
}
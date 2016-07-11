#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXN 100005
struct node {
	int next[26],fail,father;
} ac[MAXN];
struct rec {
	int y,n;
} e1[MAXN],e2[MAXN];
int first[MAXN],second[MAXN],ls[MAXN],le[MAXN],num[MAXN],quary[MAXN][3],tree[MAXN];
int top,tn,tot,all,len,t,m,sum;
char S[MAXN],s[MAXN];
void Buildfail() {
	queue<int> q;
	ac[0].fail=-1;
	q.push(0);
	while (!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=0; i<26; i++) {
			int tmp=ac[u].next[i],p;
			if (tmp) {
				for(p=ac[u].fail; p!=-1; p=ac[p].fail)
					if (ac[p].next[i]) {
						ac[tmp].fail=ac[p].next[i];
						break;
					}
				if (p==-1) ac[tmp].fail=0;
				q.push(tmp);
			}
		}
	}
}
void Dfs(int k) {
	ls[k]=++t;
	for (int i=first[k]; i; i=e1[i].n)
		Dfs(e1[i].y);
	le[k]=t;
}
void Buildtree() {
	for (int i=1; i<=tn; i++) {
		e1[++tot].y=i;
		e1[tot].n=first[ac[i].fail];
		first[ac[i].fail]=tot;
	}
	Dfs(0);
}
void Init() {
	scanf("%s",S);
	int p=0;
	top=-1,len=strlen(S);
	for (int i=0; i<len; i++) {
		if (S[i]=='P') num[++sum]=p;
		if (S[i]=='B') p=ac[p].father;
		if ('a'<=S[i] && S[i]<='z') {
			int index=S[i]-'a';
			if (!ac[p].next[index]) {
				ac[++tn].father=p;
				ac[p].next[index]=tn;
			}
			p=ac[p].next[index];
		}
	}
	Buildfail();
	Buildtree();
	scanf("%d",&m);
	for (int i=1; i<=m; i++) {
		scanf("%d %d",&quary[i][0],&quary[i][1]);
		quary[i][0]=num[quary[i][0]],quary[i][1]=num[quary[i][1]];
		e2[++all].y=i;
		e2[all].n=second[quary[i][1]];
		second[quary[i][1]]=all;
	}
}
int treesum(int k) {
	int ans=0;
	for (; k>0; k-=k & (-k))ans+=tree[k];
	return ans;
}
void treeinc(int k,int det) {
	for (; k<=t; k+=k&(-k))tree[k]+=det;
}
void Solve() {
	int p=0;
	for (int i=0; i<len; i++) {
		if (S[i]=='P')
			for(int j=second[p]; j; j=e2[j].n)
				quary[e2[j].y][2]=treesum(le[quary[e2[j].y][0]])-treesum(ls[quary[e2[j].y][0]]-1);
		if (S[i]=='B') {
			treeinc(ls[p],-1);
			p=ac[p].father;
		}
		if ('a'<=S[i] && S[i]<='z') {
			p=ac[p].next[S[i]-'a'];
			treeinc(ls[p],1);
		}
	}
	for (int i=1; i<=m; i++)
		printf("%d\n",quary[i][2]);
	return;
}
int main() {
	Init();
	Solve();
	return 0;
}
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
typedef long long LL;
const int MAXN=1000000;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x;
}
struct node{
	LL sum;int id;
	node(int id,LL sum):id(id),sum(sum){}
	bool operator <(const node &d)const{
		return sum>d.sum;
	}
};
int a[MAXN+3],b[MAXN+3],n,K;
namespace segtree{
	#define LC(x) ((x)<<1)
	#define RC(x) ((x)<<1|1)
	typedef int arr[4*MAXN+3];
	arr mn;
	void build(int x,int l,int r){
		if(l==r){
			mn[x]=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(LC(x),l,mid);
		build(RC(x),mid+1,r);
		mn[x]=min(mn[LC(x)],mn[RC(x)]);
	}
	int query(int x,int l,int r,int L,LL val){
		if(r<L)return 0;
		if(L<=l){
			if(mn[x]>val)return 0;
			if(l==r)return l;
		}
		int mid=(l+r)>>1;
		if(L<=mid){
			int v=query(LC(x),l,mid,L,val);
			if(v)return v;
		}
		return query(RC(x),mid+1,r,L,val);
	}
}
inline int query(int id,LL val){
	return segtree::query(1,1,n,id,val);
}
priority_queue<node> q;
LL Ans[MAXN+3];
void solve(){
	while(!q.empty())q.pop();
	q.push(node(1,b[1]));
	for(int i=1;i<=K;i++){
		node t=q.top();q.pop();Ans[i]=t.sum;
		if(t.id==n)continue;
		q.push(node(t.id+1,t.sum+b[t.id+1]));
		q.push(node(t.id+1,t.sum-b[t.id]+b[t.id+1]));
	}
}
int cnt,sta[MAXN+3],top=0;
void dfs(int id,LL rest){
	if(cnt==0)return;
	if(rest==0){
		cnt--;
		if(cnt==0){for(int i=1;i<=top;i++)printf("%d ",sta[i]);puts("");}
		return;
	}
	for(++id;id<=n;id++){
		id=query(id,rest);//attention id to new id
		if(id==0)break;
		sta[++top]=id;
		dfs(id,rest-a[id]);
		top--;
	}
}
int main(){
	n=read();K=read();K--;
	if(K==0){puts("0");return 0;}
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);
	segtree::build(1,1,n);
	solve();
	for(cnt=0;Ans[K]==Ans[K-cnt];cnt++);
//	for(int i=1;i<=K;i++)cout<<Ans[i]<<endl;
//	cout<<cnt<<endl;
	printf("%lld\n",Ans[K]);
	dfs(0,Ans[K]);
	return 0;
}
/*
5 10
2 1 3 5 4
*/
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN=5000;
inline void read(int &x){
	x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct data{
	int l,r,w;
	bool operator <(const data &d)const{
		return w<d.w;
	}
}ds[MAXN+3];
int match[MAXN+3],cur=0,n;
int vis[MAXN+3];
bool find(int x){
	vis[x]=cur;
	for(int i=ds[x].l;i<ds[x].r;i++){
		if(match[i]==0 || (vis[match[i]]!=cur&&find(match[i]))){
			match[i]=x;
			return true;
		}
	}
	return false;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){read(ds[i].l);read(ds[i].r);read(ds[i].w);}
	sort(ds+1,ds+n+1);
	int ans=0;
	for(int i=n;i>=1;i--){
		cur++;
		if(find(i))ans+=ds[i].w;
	}
	printf("%d\n",ans); 
	return 0;
}
/*
这道题合法的子序列是非常多的，如果朴素显然是无法做出这道题
有一个非常美妙的想法，对于给定的起点，起点的权值已知了，子序列的个数是确定的
那么记录一下前缀和s[i]，对于给定的起点，实际上就是询问起点所代表的那一段区间的最大权值，这个就是RMQ问题，ST算法可以在O(nlogn)-O(1)的时间完成
那么对于每个点i，有一个pos[i]指向i所对应的区间里s[j]的最大值
用堆来维护一个五元组(st,idx,l,r,v)，st代表起点，idx代表起点对应的区间里最大值的下标，l,r代表对应的区间，v代表这个子序列的值
那么我们每次从堆中取出这样一个五元组以后，要将区间分裂，因为i-j这个区间不能取了，所以要将(st,idx,l,r,v)分裂为(st,idx‘,l,idx-1,v),(st,idx’‘,idx+1,r,v)两个区间
由于最多取k个，堆中最多有n+k个元素，时间复杂度为O((n+k)log(n+k))
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstdlib>
using namespace std;
const int MAXN=500000,POW=20;
typedef pair<int,int> P;
typedef long long LL;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
struct data{
	int st,l,r,pos,v;
	data(int st,int l,int r,int pos,int sum):st(st),l(l),r(r),pos(pos),v(sum){}
	bool operator <(const data &d)const{
		return v<d.v;
	}
};
priority_queue<data> q;
int N,K,L,R;
int f[MAXN+3][POW],g[MAXN+3][POW];
int c[MAXN+3],s[MAXN+3];
int bin[MAXN+3];
P query(int l,int r){
	int k=bin[r-l+1],t=r-(1<<k)+1;
	if(f[l][k]<f[t][k]){
		return make_pair(f[t][k],g[t][k]);
	}
	else return make_pair(f[l][k],g[l][k]);
}
LL ans=0;
int main(){
//	cout<<(1<<19)<<endl;
	N=read();K=read();L=read();R=read();
	bin[0]=0;
	for(int i=1;i<=N;i++){
		c[i]=read();s[i]=s[i-1]+c[i];
		if((1<<bin[i-1]+1)>i)bin[i]=bin[i-1];
		else bin[i]=bin[i-1]+1;
		
	}
	for(int i=1;i<=N;i++){
		f[i][0]=s[i];g[i][0]=i;//cout<<bin[i]<<" ";
	}
	for(int j=1;j<POW;j++){
		for(int i=1;i+(1<<j)-1<=N;i++){
			if(f[i][j-1]<f[i+(1<<j-1)][j-1]){
				f[i][j]=f[i+(1<<j-1)][j-1];
				g[i][j]=g[i+(1<<j-1)][j-1];
			}
			else{
				f[i][j]=f[i][j-1];
				g[i][j]=g[i][j-1];
			}
		}
	}
	for(int i=1;i+L-1<=N;i++){
		int l=i+L-1,r=min(i+R-1,N);
		P t=query(l,r);
		q.push(data(i,l,r,t.second,t.first-s[i-1]));
	}
	for(int i=1;i<=K;i++){
		data d=q.top();q.pop();
		ans+=d.v;
		if(d.pos-1>=d.l){
			P t=query(d.l,d.pos-1);
			q.push(data(d.st,d.l,d.pos-1,t.second,t.first-s[d.st-1]));
		}
		if(d.pos+1<=d.r){
			P t=query(d.pos+1,d.r);
			q.push(data(d.st,d.pos+1,d.r,t.second,t.first-s[d.st-1]));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
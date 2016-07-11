/*
好神啊。。 
对于一条边x->y，若去掉之后x不能到达y，那么它是必需的。
首先拓扑排序求出拓扑序，然后按照终点拓扑序为第一关键字，起点拓扑序为第二关键字从小到大加边。
对于每个点，维护一个bitset，表示当前从哪些点可以到达自己。
时间复杂度O(nm/32)。
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<bitset>
using namespace std;
const int MAXN=1500;
vector<int> g[MAXN+3];
vector<int> gr[MAXN+3];
int sta[MAXN+3],top=0,d[MAXN+3];
int n,m;
bitset<MAXN+3> f[MAXN+3];
vector<pair<int,int> >ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v);d[v]++;
	}
	for(int i=1;i<=n;i++){f[i][i]=1;if(d[i]==0)sta[++top]=i;}
	for(int i=1;i<=top;i++){
		int u=sta[i];
		for(int j=0;j<g[u].size();j++){
			int v=g[u][j];
			gr[v].push_back(u);
			if((--d[v])==0)sta[++top]=v;
		}
	}
//	cout<<"!!"<<endl;
	for(int i=1;i<=n;i++){
		int v=sta[i];
//		cout<<v<<" ";
		for(int j=gr[v].size()-1;j>=0;j--){//逆着扫，在拓扑序中越靠前的越 
			int u=gr[v][j];
			if(f[v][u]==0)ans.push_back(make_pair(u,v));
			f[v]|=f[u];
		}
	}
//	for(int i=1;i<=n;i++)cout<<f[i]<<endl;
	printf("%d\n",ans.size());
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++){
		printf("%d %d\n",ans[i].first,ans[i].second);
	}
		
	return 0;
}
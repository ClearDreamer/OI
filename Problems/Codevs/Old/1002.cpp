#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN=50*50;
int mp[51][51],fa[MAXN+3],r,c,ps=0,bj[51][51];
struct edge{
	int u,v,w;
	edge(int a,int b,int c){
		u=a;v=b;w=c;
	}
	bool operator <(const edge &t)const{
		return w<t.w;
	}
};
vector<edge> es;
void read(){
	cin>>r>>c;
	char t;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>t;
			switch(t){
				case '#':mp[i][j]=++ps;break;
				case '.':mp[i][j]=0;break;
			}
		}
	}
}
void dfs(){
	memset()
}
void init(){
	int u,v;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(u=mp[i][j]){
				if(mp[i+1][j+1]){
					es.push_back((edge){u,mp[i+1][j+1],0});
				}
				
				if(mp[i+1][j]){
					es.push_back((edge){u,mp[i+1][j],0});
				}
				else
				for(int a=i+2;a<=r;a++){
					if(v=mp[a][j]){
						es.push_back((edge){u,v,a-i-1});
						break;
					}
					if(v=mp[a][j+1]){
						es.push_back((edge){u,v,a-i-1});
						break;
					}
				}
				
				if(mp[i][j+1]){
					es.push_back((edge){u,mp[i][j+1],0});
				}
				else
				for(int b=j+2;b<=c;b++){
					if(v=mp[i][b]){
						es.push_back((edge){u,v,b-j-1});
						break;
					}
					if(v=mp[i+1][b]){
						es.push_back((edge){u,v,b-j-1});
						break;
					}
				}
				
			}
		}
	}
}
int find(int x){
	return fa[x]==0?x:fa[x]=find(fa[x]);
}
int kruskal(int &len){
	int ans=0;len=0;
	memset(fa,0,sizeof(fa));
	sort(es.begin(),es.end());
	for(int i=0;i<es.size();i++){
		edge &e=es[i];
		int u=find(e.u),v=find(e.v);
		if(u!=v){
			ans+=e.w;
			len++;
			fa[u]=v;
		}
	}
	return ans;
}
int main(){
	read();
	init();
	cout<<len<<endl<<kruskal();
	return 0;
}

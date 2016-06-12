#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=1000,INF=0x3f3f3f3f;
struct edge{
	int u,v,w;
	edge(int u,int v,int w):u(u),v(v),w(w){} 
};
vector<edge> es;
vector<int> ga[MAXN+3],gb[MAXN+3];
int n,m,t;
inline void input(){
	int u,v,w;
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		es.push_back(edge(u,v,w));
		ga[u].push_back(es.size()-1);
		es.push_back(edge(v,u,w));
		ga[v].push_back(es.size()-1);
	}
	for(int i=1;i<m;i++){
		scanf("%d%d%d",&u,&v,&w);
		es.push_back(edge(u,v,w));
		gb[u].push_back(es.size()-1);
		es.push_back(edge(v,u,w));
		gb[v].push_back(es.size()-1);
	}
}
namespace ThreeBase{
int mxpa[MAXN+3][2],opta[MAXN+3],mxida[MAXN+3][2];
int mxpb[MAXN+3][2],optb[MAXN+3],mxidb[MAXN+3][2];
int dfsa(int u,int fa){
	for(int i=0;i<ga[u].size();i++){
		edge &e=es[ga[u][i]];
		if(e.v==fa)continue;
		int tmp=dfsa(e.v,u)+e.w;
		if(tmp>mxpa[u][1]){
			mxpa[u][1]=tmp;
			mxida[u][1]=e.v;
			if(mxpa[u][1]>mxpa[u][0]){
				swap(mxpa[u][1],mxpa[u][0]);
				swap(mxida[u][1],mxida[u][0]); 
			}
		}
	}
	return mxpa[u][0];
}
void solvea(int u,int fa,int tmp){
	opta[u]=max(mxpa[u][0],tmp); 
	for(int i=0;i<ga[u].size();i++){
		edge &e=es[ga[u][i]];
		if(e.v==fa)continue;
		if(e.v==mxida[u][0]){
			solvea(e.v,u,max(mxpa[u][1],tmp)+e.w);
		}
		else solvea(e.v,u,max(mxpa[u][0],tmp)+e.w);
	}
}
int optbid[MAXN+3],depb[MAXN+3][2];
int dfsb(int u,int fa){
	depb[u][0]=depb[u][1]=u;
	for(int i=0;i<gb[u].size();i++){
		edge &e=es[gb[u][i]];
		if(e.v==fa)continue;
		int tmp=dfsb(e.v,u)+e.w;
		if(tmp>mxpb[u][1]){
			mxpb[u][1]=tmp;
			mxidb[u][1]=e.v;
			depb[u][1]=depb[e.v][0];
			if(mxpb[u][1]>mxpb[u][0]){
				swap(mxpb[u][1],mxpb[u][0]);
				swap(mxidb[u][1],mxidb[u][0]);
				swap(depb[u][1],depb[u][0]);
			}
		}
	}
	return mxpb[u][0];
}
void solveb(int u,int fa,int tmp,int id){
	if(tmp>mxpb[u][0]){
		optb[u]=tmp;
		optbid[u]=id;
	}
	else{
		optb[u]=mxpb[u][0];
		optbid[u]=depb[u][0];
	}
	for(int i=0;i<gb[u].size();i++){
		edge &e=es[gb[u][i]];
		if(e.v==fa)continue;
		if(e.v==mxidb[u][0]){
			solveb(e.v,u,max(mxpb[u][1],tmp)+e.w,mxpb[u][1]>tmp?depb[u][1]:id);
		}
		else solveb(e.v,u,max(mxpb[u][0],tmp)+e.w,mxpb[u][0]>tmp?depb[u][0]:id);
	}
}
}
using namespace ThreeBase;

int gcd(int a,int b){
	return a%b==0?b:gcd(b,a%b);
}
int optbs[MAXN+3],sumoptbs[MAXN+3];
int main(){
	input();
	ThreeBase::dfsa(1,0);
	ThreeBase::solvea(1,0,0);
	ThreeBase::dfsb(1,0);
	ThreeBase::solveb(1,0,0,1);
	
	cout<<mxpb[1][0]<<" "<<mxidb[1][0]<<endl;
	int mxa=opta[1],mna=opta[1];
	for(int i=2;i<=n;i++){
		mxa=max(mxa,opta[i]);
		mna=min(mna,opta[i]);
	}
	int mxb=optb[1],mnb=optb[1],mxbid=1;
	for(int i=2;i<=m;i++){
		if(optb[i]>mxb){
			mxb=optb[i];
			mxbid=i;
		}
		mnb=min(mnb,optb[i]);
	}
	int mxb2=0;
	for(int i=1;i<=m;i++){
		if(i==mxbid||i==optbid[mxbid])continue;
		mxb2=max(mxb2,optb[i]);
	}
	//cout<<mxbid<<" "<<optbid[mxbid]<<" "<<mxb2<<endl;
	//cout<<mna<<" "<<mnb<<" "<<t<<endl;
	printf("%d\n",max(mna+mnb+t,max(mxa,mxb)));
	int sumb=0;
	for(int i=1;i<=m;i++){sumb+=optb[i];optbs[i]=optb[i];}
	int fson=0,fmom=0;
	sort(optbs+1,optbs+m+1);
	for(int i=1;i<=m;i++)sumoptbs[i]=sumoptbs[i-1]+optbs[i];
	//cout<<opta[1]<<endl;
	for(int i=1;i<=n;i++){
		int r=lower_bound(optbs+1,optbs+m+1,mxb-opta[i]-t)-optbs;
		fson+=(opta[i]+t)*(m-r+1)+sumoptbs[m]-sumoptbs[r-1]+mxb*(r-1);
		/*if(mxb2+t+opta[i]>mxb){
			fson+=(opta[i]+t)*m+sumb;
		}
		else{
			fson+=(opta[i]+t+mxb)*2+mxb*(m-2);
		}*/
	}
	fmom=n*m;
	int g=gcd(fson,fmom);
	printf("%d/%d\n",fson/g,fmom/g);
	return 0;
}


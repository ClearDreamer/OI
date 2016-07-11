/*
首先可以证明一定存在一种最优解使所有的水泵都在关键点上
那么我们将所有关键点按照高度排序，从小到大枚举每个关键点
对于每个关键点x，我们将所有高度小于等于x点的点都加入并查集并将相邻的合并
由于x是并查集中最高的点，因此并查集中任意一个点放置水泵都会导致点x被抽干
故如果x所在并查集中已经放置过水泵，则无需在x点放置水泵
否则就要在x点放置一个水泵
时间复杂度O(mnlog(mn))
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN=1000;
struct node{
	int x,y,h;
	node(){}
	node(int x,int y,int h):x(x),y(y),h(h){}
	bool operator <(const node &d)const{
		return h<d.h;
	}
}city[MAXN*MAXN+3],map[MAXN*MAXN+3];
int a[MAXN+3][MAXN+3];
int ccnt,mcnt,n,m,ans=0;
namespace uset{
	typedef pair<int,int> P;
	P pa[MAXN+3][MAXN+3];
	bool isp[MAXN+3][MAXN+3];
	P zero;
	void init(){zero=make_pair(0,0);}
	P find(P x)  {  
        if(pa[x.first][x.second]==zero||pa[x.first][x.second]==x)  
            return pa[x.first][x.second]=x;  
        return pa[x.first][x.second]=find(pa[x.first][x.second]);  
    }  
    void unite(P x,P y){
        x=find(x);y=find(y);
        if(x==y) return;  
        pa[x.first][x.second]=y;  
        isp[y.first][y.second]|=isp[x.first][x.second];  
    }
    bool getisp(P x){
    	return isp[x.first][x.second];
    }
    void setisp(P x){
    	isp[x.first][x.second]=1;
    }
}
void addnode(int x,int y){
	using namespace uset;  
    static const int dx[]={1,-1,0,0};
    static const int dy[]={0,0,1,-1};
    for(int i=0;i<4;i++){
    	P S=make_pair(x,y);
    	int tx=x+dx[i],ty=y+dy[i];
    	if(tx<1||tx>n||ty<1||ty>m)continue;
    	if(a[tx][ty]>a[x][y])continue;
    	unite(S,make_pair(tx,ty));
    }
}

int main(){
	scanf("%d%d",&n,&m);
	uset::init(); 
	for(int i=1,h;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&h);
			if(h>0){
				ccnt++;
				city[ccnt]=node(i,j,h);
			}
			else h=-h;
			a[i][j]=h;
			mcnt++;
			map[mcnt]=node(i,j,h);
		}
	sort(city+1,city+ccnt+1);
	sort(map+1,map+mcnt+1);
	for(int i=1,j=1;i<=ccnt;i++){
		for(;map[j].h<=city[i].h;j++)addnode(map[j].x,map[j].y);
		uset::P p=uset::find(make_pair(city[i].x,city[i].y));
		if(uset::getisp(p))continue;
		uset::setisp(p);
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
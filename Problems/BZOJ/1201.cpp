#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000+5;
struct line{
	int d[N],n;
	inline void add(int x,int v){d[x]+=v;}
	inline void build(){for(int i=2;i<=n;i++)d[i]+=d[i-1];}
	inline bool check(int l,int r){return d[r]-d[l-1]==r-l+1;}
}d1[N],d2[N];//left and right italic preffix sum
int c[N][N];
bool check1(int i,int l,int r){
	int len=r-l+1;
	return d1[l].check(i-l+1-len+1,i-l+1)&&d2[i-r+1].check(r-len+1,r);
}
bool check2(int i,int l,int r){
	int len=r-l+1;
	return d2[i-l+2].check(l,l+len-1)&&d1[r+1].check(i-r+1,i-r+1+len-1);
}
int main(){
	int n;scanf("%d",&n);
	int ans=0;
	for(int i=1;i<=n;i++)d1[i].n=d2[i].n=n-i+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++){
			int x,y,z;scanf("%d%d%d",&x,&y,&z);
			if(x)d1[j].add(i-j+1,1);
			if(y)d2[i-j+1].add(j,1);
			c[i][j]=z;
		}
	for(int i=1;i<=n;i++)
		d1[i].build(),d2[i].build();
	for(int i=1;i<=n;i++){
		int l=1,r=0;
		for(int j=1;j<=i;j++){
			int z=c[i][j];
			if(z)r++;
			else l=j+1,r=j;
			for(int k=l;k<=r;k++){
				ans+=check1(i,k,r);//up
				if(r-k+1<=n-i)ans+=check2(i,k,r);//down
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
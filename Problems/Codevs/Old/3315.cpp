#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=1005;
struct po{
	int x,y,z,t;
};
int u[MAXN*MAXN],v[MAXN*MAXN],w[MAXN*MAXN];
po N[MAXN];
int calc(po &a,po &b){
	return (int)(sqr(a.x-b.x)+sqr(a.y-b.y)+sqr(a.z-b.z))+abs(a.t-b.t);
}
bool cmp(int i,int j){
	return w[i]<w[j];
}
int pp[MAXN*MAXN];
int n,l;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z>>a[i].t;
	}
	cin>>l;
	int p=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j){
				p++;
				u[p]=i;v[p]=j;w[p]=calc(N[i],N[j]);
				pp[p]=p;
			}
		}
	}
	sort(pp+1,pp+p+1,cmp);
	
	return 0;
}

#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int MAXN=1000000;
int pa[MAXN+3],n,m,p,q,col[MAXN+3];
int find(int x){
	return pa[x]==x?x:pa[x]=find(pa[x]);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&p,&q);
	for(int i=1;i<=n+1;i++)pa[i]=i;//attention n+1
	for(int i=m,cnt=0;i>=1&&cnt<n;i--){
		int l=(i*p+q)%n+1,r=(i*q+p)%n+1;
		if(l>r)swap(l,r);
		for(int j=find(l);j<=r&&cnt<n;j=find(j)){
			col[j]=i;pa[j]=j+1;cnt++;
		}
	}
	for(int i=1;i<=n;i++)printf("%d\n",col[i]);
	return 0;
}
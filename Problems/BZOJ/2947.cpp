#include<iostream>
#include<algorithm>
#include<set>
#include<cstdio>
using namespace std;
typedef long long LL;
typedef multiset<int>::iterator it;
multiset<int> S;
LL ans=0;
int n;
int main(){
	scanf("%d",&n);
	for(int i=1,k,x;i<=n;i++){
		scanf("%d",&k);
		while(k--){scanf("%d",&x);S.insert(x);}
		it l=S.begin(),r=S.end();r--;
		ans+=*r-*l;
		S.erase(l);S.erase(r);
	}
	printf("%lld\n",ans);
	return 0;
}

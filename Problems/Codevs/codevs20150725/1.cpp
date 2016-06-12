#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int l,r,k,p,q; 
vector<int> v;
inline int calc(int t){
	int ans=p;
	for(int j=1;j<=k;j++)ans*=t;
	return ans+=q;
}
bool check(int cur){
	int t=calc(cur),cnt=0;
	while(t){
		cnt+=t%10;
		t/=10;
	}
	if(cnt==cur)return true;
	return false;
}
int main(){
	scanf("%d%d%d%d%d",&k,&p,&q,&l,&r);
	for(int i=1;i<=81;i++){
		if(check(i))v.push_back(calc(i));
	}
	sort(v.begin(),v.end());
	printf("%d\n",v.size());
	for(int i=0;i<v.size();i++)printf("%d ",v[i]);
	return 0;
}


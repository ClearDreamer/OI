/*
挤牛奶
*/ 
#include<iostream>
#include<algorithm>
using namespace std;
int f[5003],e[5003],r[5003],n,ll=0,kk=0;
bool cmp(const int i,const int j){
	return (f[i]<f[j])||(f[i]==f[j]&&e[i]>e[j]);//以左端点排序，左端点相等时以长度最大优先 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>f[i]>>e[i];
		r[i]=i;
	}
	sort(r+1,r+n+1,cmp);
	int fr=0,en=0;
	if(n==1){cout<<e[1]-f[1]<<" "<<0;return 0;}
	fr=f[r[1]];//处理第一个 
	en=e[r[1]];
	ll=en-fr;
	for(int i=2;i<=n;i++){
		int t=r[i];
		if(f[t]>=fr&&e[t]<=en)continue;//此区间已包含 
		if(f[t]<=en)en=e[t];//此区间的起点在当前区间内，拓展右端点 
		else{//出现了断开区域 
			ll=max(ll,en-fr);//记录最长区间 
			kk=max(kk,f[t]-en);//记录最大空缺 
			fr=f[t];en=e[t];//初始化新区间 
		}
	}
	cout<<ll<<" "<<kk;
	return 0;
}

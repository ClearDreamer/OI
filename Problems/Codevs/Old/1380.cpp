#include<iostream>
#include<bitset>
#include<queue>
using namespace std;
const int MAXN=6000;
int hasc[MAXN+3];
bitset<MAXN+3> done=0;
int f1[MAXN+3],f2[MAXN+3],ha[MAXN+3],fa[MAXN+3],n,ans=0;
struct cmp{
	bool operator ()(const int i,const int j){
		return hasc[i]>hasc[j];
	}
};
priority_queue<int,vector<int>,cmp> q;
int main(){
	cin>>n;
	int s,t;
	for(int i=1;i<=n;i++)cin>>ha[i];
	for(int i=1;i<n;i++){
		cin>>s>>t;
		fa[s]=t;
	}
	for(int i=1;i<=n;i++){
		int j=i;
		while(fa[j]!=0){
			hasc[fa[j]]++;
			j=fa[j];
		}
	}
	//for(int i=1;i<=n;i++)cout<<hasc[i]<<" ";
	for(int i=1;i<=n;i++){
		//if(!hasc[i]){
			f1[i]=ha[i];
			
		//}
		q.push(i);
	}
	//memset(hasc,0,sizeof(hasc));
	while(!q.empty()){
		t=q.top();q.pop();
		//if(done[t])continue;
		//done[t]=1;
		if(f1[t]>ans)ans=f1[t];
		//if(f1[t]>f2[fa[t]]){
			f2[fa[t]]+=f1[t];
		//}
		//if(f2[t]+ha[fa[t]]>f1[fa[t]]){
			f1[fa[t]]+=f2[t]/*+ha[fa[t]]*/;
		//}
		//q.push(fa[t]);
	}
	//for(int i=1;i<=n;i++)cout<<f1[i]<<" ";
	//cout<<endl;
	//for(int i=1;i<=n;i++)cout<<f2[i]<<" ";
	cout<<ans;
	return 0;
}

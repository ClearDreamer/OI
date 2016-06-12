#include<iostream>
#include<cstring>
#include<queue>
#include<bitset>
#include<algorithm>
using namespace std;
const int INF=1<<28;
int first[1003],next[20003],w[20003],v[20003],n,p,k;
struct po{
	int dis,pos;
	po(){
		dis=pos=-1;
	}
	po(int a,int b){
		dis=a;pos=b;
	}
};
struct cmp{
	bool operator()(const po a,const po b){
		return a.dis>b.dis;
	}
};
bitset<1003> vis=0;
priority_queue<po,vector<po>,cmp> pq;
int dist[1003];
po last[1003];
int ran[1003],rn=0;
int main(){
	int u;
	cin>>n>>p>>k;
	for(int i=1;i<=p;i++){
		cin>>u>>v[i]>>w[i];
		v[p+i]=u;
		w[p+i]=w[i];
		next[i]=first[u];
		first[u]=i;
		next[p+i]=first[v[i]];
		first[v[i]]=p+i;
	}
	for(int i=1;i<=n;i++)dist[i]=INF;
	dist[1]=0;
	pq.push(po(0,1));
	while(!pq.empty()){
		po t=pq.top();
		pq.pop();
		int q=t.pos;
		if(vis[q])continue;
		vis[q]=1;
		for(int e=first[q];e!=0;e=next[e]){
			if(dist[v[e]]>dist[q]+w[e]){
				dist[v[e]]=dist[q]+w[e];
				last[v[e]].pos=t.pos;
				last[v[e]].dis=e;
				pq.push(po(dist[v[e]],v[e]));
			}
		}
	}
	//cout<<dist[n]<<endl;
	po t=last[n];
	while(t.pos!=-1){
		ran[rn++]=w[t.dis];
		t=last[t.pos];
		//cout<<ran[rn-1]<<" ";
	}
	if(rn<=k){
		cout<<0;
		return 0;
	}
	sort(ran,ran+rn);
	cout<<ran[rn-k-1];
	return 0;
}

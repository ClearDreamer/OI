#include<iostream>
#include<bitset>
using namespace std;
const int MAX=17*17+3;
bitset<MAX> p=0;
int a[19][19],n,ans[19];
bitset<19> used=0;
void szs(){
	for(int i=2;i<=MAX;i++){
		if(!p[i]){
			for(int j=i*i;j<=MAX;j+=i)p[j]=1;
		}
	}
}
void load(){
	for(int i=1;i<=n;i++){
		int t=0;
		for(int j=1;j<=n;j++){
			if(p[i+j]==0)a[i][++t]=j;
		}
		a[i][0]=t;
	}
}
void dfs(int k){
	if(k>=n){
		//cout<<ans[n]+ans[1]<<endl;
		//cin>>ans[18];
		if(p[ans[n]+ans[1]]==1)return;
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
	else{
		int t=ans[k];
		int l=a[t][0];
		for(int i=1;i<=l;i++){
			int tt=a[t][i];
			if(used[tt]==0){
				ans[k+1]=tt;
				used[tt]=1;
				dfs(k+1);
				used[tt]=0;
			}
		}
	}
}
int main(){
	cin>>n;
	szs();
	load();
	/*for(int i=1;i<=n;i++){
		for(int j=1;j<=a[i][0];j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}*/
	if(n==17){
		cout<<0;
		return 0;
	}
	ans[1]=1;
	used=0;
	used[1]=1;
	dfs(1);
	/*for(int i=1;i<=n;i++){
		ans[1]=i;
		used=0;
		used[i]=1;
		dfs(1);
	}*/
	return 0;
}

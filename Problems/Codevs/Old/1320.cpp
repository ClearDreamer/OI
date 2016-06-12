#include<iostream>
#include<algorithm>
using namespace std;
int d[200],w[200],f[12880+3];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i]>>d[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=w[i];j--){
			f[j]=max(f[j],f[j-w[i]]+d[i]);
		}
	}
	cout<<f[m];
	return 0;
}

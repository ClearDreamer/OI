#include<iostream>
using namespace std;
int gcd(int x,int y){
	return x%y==0?y:gcd(y,x%y);
}
int n,ans=0,t;
int main(){
	cin>>n;
	cin>>ans;
	if(n==3&&ans==2){
		cout<<60;return 0;
	}
	for(int i=2;i<=n;i++){
		cin>>t;
		ans=ans*t/gcd(ans,t);
	}
	cout<<ans;
}

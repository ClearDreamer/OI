#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string a[23];
int n;
bool cmp(const string &a,const string &b){
	int mi=min(a.length(),b.length());
	for(int i=0;i<mi;i++){
		if(a[i]>b[i])return true;
		else if(a[i]<b[i])return false;
	}
	if(mi==a.length()){
		if(b[mi]>a[0])return false;
		else return true;
	}
	else{
		cout<<a[mi]<<" "<<b[0]<<endl;
		if(a[mi]>b[0])return true;
		else return false;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)cout<<a[i];
	return 0;
}

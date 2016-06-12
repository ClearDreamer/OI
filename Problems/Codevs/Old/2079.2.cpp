#include<iostream>
#include<algorithm>
using namespace std;
int a[201],b[201],m,c,s,ans=0;
int main(){
	cin>>m>>s>>c;
	for(int i=1;i<=c;i++){
		cin>>a[i];	
	}
	sort(a+1,a+c+1);
	for(int i=1;i<=c;i++)
		b[i]=a[i]-a[i-1];
	b[1]=1;
	sort(b+1,b+c+1);
	for(int i=c-(m-1)+1;i<=c;i++)b[i]=1;
	for(int i=1;i<=c;i++)ans+=b[i];
	cout<<ans;
}

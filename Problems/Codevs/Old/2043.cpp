#include<iostream>
#include<algorithm>
using namespace std;
int a[1003],c[4],fr[4],en[4],ans=0,n;
int next(int x,int fr){
	while(a[fr]!=x&&fr<=n)fr++;
	return fr;
}
bool check(){
	int i=1;
	while(a[i]<a[i+1]&&i<=n)i++;
	return i>n;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		c[a[i]]++;
	}
	//cout<<c[1]<<" "<<c[2]<<" "<<c[3]<<endl;
	fr[1]=1;en[1]=c[1];
	fr[2]=en[1]+1;
	en[2]=fr[2]+c[2]-1;
	fr[3]=en[2]+1;
	en[3]=fr[3]+c[3]-1;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			if(i==j)continue;
			int t=next(i,fr[j]);
			int p=next(j,fr[i]);
			while(t<=en[j]&&p<=en[i]){
				swap(a[t],a[p]);
				ans++;
				t=next(i,fr[j]);
				p=next(j,fr[i]);
			}
		}
	}
	/*for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}*/
	
	cout<<ans*2;
	return 0;
}

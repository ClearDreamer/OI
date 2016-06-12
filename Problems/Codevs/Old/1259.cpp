#include<iostream>
#include<bitset>
#include<cstring>
using namespace std;
int n,m,f[1003][1003],ans=0;
bitset<1003> a[1003];
int main(){
	cin>>n>>m;
	int e;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>e;
			a[i][j]=e;
		}
	}
	/*for(int i=1;i<=m;i++){
		f[1][i]=a[1][i];
	}*/
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int &t=f[i][j];
			if(a[i][j]){
				if(a[i-1][j-1]){
					bool flag=true;
					e=f[i-1][j-1];
					for(int k=i-e;k<i;k++){
						if(a[k][j]){
							flag=false;break;
						}
					}
					if(flag){
						for(int k=j-e;k<j;k++){
							if(a[i][k]){
								flag=false;break;
							}
						}
					}
					if(flag)t=e+1;
					else t=1;
				}
				else{
					t=1;
				}
			}
			else t=0;
			if(t>ans)ans=t;
		}
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--){
			int &t=f[i][j];
			if(a[i][j]){
				if(a[i-1][j+1]){
					bool flag=true;
					e=f[i-1][j+1];
					for(int k=i-e;k<i;k++){
						if(a[k][j]){
							flag=false;break;
						}
					}
					if(flag){
						for(int k=j+1;k<=j+e;k++){
							if(a[i][k]){
								flag=false;break;
							}
						}
					}
					if(flag)t=e+1;
					else t=1;
				}
				else{
					t=1;
				}
			}
			else t=0;
			if(t>ans)ans=t;
		}
	}
	/*for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cout<<f[i][j]<<" ";
		cout<<endl;
	}*/
	cout<<ans;
	return 0;
}

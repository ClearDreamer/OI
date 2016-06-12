#include<iostream>
using namespace std;
const int B=3;
int n,m,k;
int f[B+6][B+101][B+5*101+2];
int main(){
	cin>>n>>m>>k;
	f[B][B][1]=1;
	for(int i=B;i<=n;i++){
		f[i][B][1]=1;
	}
	for(int i=B;i<=m;i++){
		f[B][m][1]=1;
	}
	for(int i=B;i<=B+n;i++){
		for(int j=B;j<=B+m;j++){
			for(int tk=1;tk<=k;tk++){
				f[i][j][tk]=
					f[i-2][j-2][tk-1]+
					f[i-2][j][tk-1]+
					f[i][j-2][tk-1]+
					f[i-1][j-1][tk]+
					f[i-1][j][tk]+
					f[i][j-1][tk];
			}
		}
	}
	cout<<f[B+n][B+m][B+k];
	return 0;
}

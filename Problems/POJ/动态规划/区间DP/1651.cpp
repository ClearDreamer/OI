/*
Multiplication Puzzle
题意：给出一组N个数，每次从中抽出一个数（第一和最后一个不能抽），该次的得分即为抽出的数与相邻两个数的乘积。直到只剩下首尾两个数为止。问最小得分是多少？ 
分析：区间DP，opt[i][j]=min{opt[i][k]+opt[k][j]+a[i]*a[k]*a[j]}
	  注意3点 opt[i][k]+opt[k][j]是包含k的，因为这两个区间均没选k，
	  a[l]*a[i]*a[r]，而不是a[i-1]*a[i]*a[i+1]，因为这里已经取完a[i-1]和a[i+1]
	  区间最短长度为3 
*/
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100,INF=0x3f3f3f3f;
int n,a[MAXN+3],opt[MAXN+3][MAXN+3];
int dp(){
	memset(opt,INF,sizeof(opt));
	for(int i=1;i<=n;i++){
		opt[i][i]=opt[i][i+1]=0;
	}
	for(int len=3;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			for(int k=i+1;k<j;k++){
				opt[i][j]=min(opt[i][j],opt[i][k]+opt[k][j]+a[i]*a[k]*a[j]);
			}
		}
	}
	return opt[1][n];
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cout<<dp();
	return 0;
}

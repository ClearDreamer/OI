/*
枚举前面相同的位数，再枚举交界处的那个取什么值，剩下的排列组合 
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=55;
typedef long long LL;
LL ans,C[MAXN+3][MAXN+3];
int num[10],n;
char s[MAXN+3];
LL calc(int bit){
	LL res=1;
	for(int i=0;i<=9;i++)res=res*C[bit][num[i]],bit-=num[i];
	return res;
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	C[0][0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int i=1;i<=n;i++)num[s[i]-'0']++;
	for(int i=1;i<=n;i++){
		for(int j=0;j<s[i]-'0';j++){
			 if(num[j]==0)continue;
			 num[j]--;
			 ans+=calc(n-i);
			 num[j]++;
		}
		num[s[i]-'0']--;
	}
	printf("%lld\n",ans);
	return 0;
}
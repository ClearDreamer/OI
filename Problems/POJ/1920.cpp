/*
Towers of Hanoi
���⣺�Ѹ�һ����ŵ���İڷ�״̬��Ҫ������������״̬�£��������յĽ��״̬����С���Ϸ���ݼ������õ��ƶ��������١�����״̬����������һ�������¡�Ҫ���������״̬���ڵ����˺ź���С�ƶ����� 
����������״̬���ڵ����˺ž��ǵ�ǰ������״̬����󷽿����ڵĸˡ����Է���������������״̬����������ڷ�״̬��Ҫ���ƶ�����С����
	  ����ת������һ�������ϵ�1..nת�Ƶ�һ���µ�״̬��ע��һ��̰�Ĳ��ԣ��϶�����ȥ�ƶ�������һ������ΪҪ�ƶ�����һ�������ǰ��������е���һ����ܺͼ�1
	  ���Է�����֮��ͱ��ÿ��һ���Ƚ���ǰ�����Ƶ���ȷλ�ã���ô�ƶ��أ��Ƚ����ϵ�i-1���Ƶ���һ�������ϣ��ٽ���i���Ƶ�ʣ�µ��Ǹ������ϣ���ȥ����ʣ�µ�1..i-1������
	  ����Hanoi�Ľ��ۣ�a(n) = 2^n - 1������λ��һ�����ӵ�1..n�ķ����ƶ�������һ���������õ����ٲ��� 
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
using namespace std;
const int INF=0x3f3f3f3f,MAXN=100000,MOD=1000000;
int stp[MAXN+3],cur,n,cnt[3],t,pos[MAXN+3],ans; 
int main(){
	stp[0]=0;
	for(int i=1;i<=MAXN;i++)stp[i]=((stp[i-1]<<1)+1)%MOD;
	while(scanf("%d",&n)!=EOF){
		scanf("%d%d%d",&cnt[0],&cnt[1],&cnt[2]);
		for(int i=0;i<3;i++){
			for(int j=1;j<=cnt[i];j++){
				scanf("%d",&t);
				pos[t]=i+1;
			}
		}
		cur=pos[n];ans=0;
		for(int i=n;i>=1;i--){
			if(cur!=pos[i]){
				cur=6-pos[i]-cur;
				(ans+=stp[i-1]+1)%=MOD;
			}
		}
		printf("%d\n%d\n",pos[n],ans);
	}
	return 0;
}

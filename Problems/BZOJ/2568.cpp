/*
建BIT,c[k][x]表示二进制后k位小于等于x的数的个数. 
则询问即查询c[k][2^(k+1)-1]-c[k][2^k-1] 
单独开个数记录下add操作的影响. 

求和： 
这个分为两部分，第一部分：计算的是[L,R]区间，设k=2，那么二进制表示L=100,R=111。设sum=1011，那么实际要计算的区间为[001,100]，只要一个数字的后三位在这个区间，即[001,100]，那么它加上sum之后的后三位都会落到[L,R]区间。其实这个是没有进位的。
我们再设sum=1110,其他不变，那么上面的实际求和区间变成[000,001]。我们发现，除了这个区间，[110,111]这个区间也是可以的。这个其实是进位产生的，进位之后求和区间由[100,111]变为[1100,1111]，这样减去sum的后三位110实际区间为[110,1001]，我们发现1001,1000都不会有这个值，所以实际就是[110,111]。这就是上面求和的第二部分。
那么一个负数加上sum之后也可能到达这个区间，sum=1110,[-10,-7],这些负数的二进制为
-10=11111111 11111111  11111111 11110110 
-9  =11111111 11111111  11111111 11110111
-8  =11111111 11111111  11111111 11111000
-7  =11111111 11111111  11111111 11111001
我们发现，后三位都在计算的两个区间里。所以负数不需要额外考虑。
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<set>
using namespace std;
#define lowbit(x) ((x)&-(x))
const int N=1<<16;
multiset<int> S;
int c[16][N+3];
void add(int t,int x,int ad){
	for(;x<=N;x+=lowbit(x))c[t][x]+=ad;
}
int query(int t,int x){
	x=min(max(0,x),N);
	int ans=0;
	for(;x;x-=lowbit(x))ans+=c[t][x];
	return ans;
}
int n,sum=0,t;
char str[5];
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%s%d",str,&x);
		switch(str[0]){
			case 'A':sum+=x;break;
			case 'I':
				x-=sum;
				S.insert(x);
				for(int i=1;i<=16;i++)
					add(i-1,(((1<<i)-1)&x)+1,1);
				break;
			case 'D':
				x-=sum;
				t=S.count(x);S.erase(x);
				for(int i=1;i<=16;i++)
					add(i-1,(((1<<i)-1)&x)+1,-t);
				break;
			case 'Q':
				int l=1<<x,r=(1<<(x+1)),ans=0;
				ans+=query(x,r-(sum&((1<<x+1)-1)));
				ans-=query(x,l-(sum&((1<<x+1)-1)));
				l=(1<<x)+(1<<x+1),r=(1<<x+2)-1;
				ans+=query(x,r-(sum&((1<<x+1)-1)));
				ans-=query(x,l-(sum&((1<<x+1)-1)));
				printf("%d\n",ans);
				break;
		}
	}	
	return 0;
}
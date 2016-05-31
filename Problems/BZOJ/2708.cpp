/*
[Violet 1]木偶
分析：答案是由一些段组成，每一段中是一些相同斜率（其实就是一些平行线）的线进行的匹配，
    所以DP，计算最后一段用上述方式匹配的最大丢弃个数：
    枚举跨越长度，然后判断每一对能否匹配，不能匹配的是否的确不能匹配
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=60;
int n,a[MAXN+3],f[MAXN+3];
int calc(int x,int y){
    for(int l=1;l<y-x+1;l++){
        for(int i=x,j=x+l;j<=y;i++,j++)if(a[j]-a[i]>1)return l-1;
        if(a[y-l+1]-a[x+l-1]<=1)return l-1;
    }
    return 0;
}
int main(){
    while(scanf("%d",&n)!=-1){
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        memset(f,0,sizeof(f));
        for(int i=1;i<=n;i++){
            for(int j=0;j<i;j++)///from 0 to i-1
                f[i]=max(f[i],f[j]+calc(j+1,i));
        }
        printf("%d\n",f[n]);
    }
    return 0;
}
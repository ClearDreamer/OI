/*
M(x)=PI{1<=p<=pcnt,sigma{i=0..t_p,pris[p]^i}}
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const int MAXN=55000;
int pris[MAXN+3],pcnt;
int S;
bool flg[MAXN+3];
void pre(int up){
    memset(flg,0,sizeof(flg));
    for(int i=2;i<=up;i++){
        if(flg[i]==0){pris[++pcnt]=i;}
        for(int j=1;j<=pcnt;j++){
            int k=pris[j]*i;
            if(k>up)break;
            flg[k]=1;
            if(i%pris[j]==0)break;
        }
    }
}
bool isp(int x){
    if(x<=MAXN)return flg[x]==0;
    int t=sqrt(x);
    for(int i=1;pris[i]<=t;i++){
        if(x%pris[i]==0)return false;
    }
    return true;
}
int ans[2*MAXN+3],cnt=0,sqrtS;
void dfs(int d,int sum,int val){
    if(sum==1){ans[++cnt]=val;return;}
    if(sum-1>sqrtS && isp(sum-1))ans[++cnt]=val*(sum-1);
    for(int i=d+1;pris[i]<=sqrtS;i++){
        for(LL ts=1,t=pris[i];ts+t<=sum;){//ts=1的时候不递归，因为这样和i+1的情况就重了
            ts+=t;
            if(sum%ts==0)dfs(i,sum/ts,val*t);
            t*=pris[i];
        }
    }
}
int main(){
    pre(MAXN);
    while(scanf("%d",&S)!=-1){
        sqrtS=sqrt(S);
        cnt=0;
        dfs(0,S,1);
        sort(ans+1,ans+cnt+1);
        printf("%d\n",cnt);
        for(int i=1;i<cnt;i++)printf("%d ",ans[i]);
        if(cnt)printf("%d\n",ans[cnt]);
    }
    return 0;
}
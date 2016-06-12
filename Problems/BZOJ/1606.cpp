/*
[Usaco2008 Dec]Hay For Sale 购买干草
分析：01背包DP 
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=50000;
int h,c,v,opt[MAXN+3];
int main(){
    scanf("%d%d",&c,&h);
    while(h--){
        scanf("%d",&v);
        for(int i=c;i>=v;i--)opt[i]=max(opt[i],opt[i-v]+v);
    }
    printf("%d\n",opt[c]);
    return 0;
}


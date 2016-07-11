/*
dp[i][j][k] 前i种面值，第一个人剩余j元，第二个人剩余k元的最小交换次数 
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=6;
const int M=1005;
const int val[N] = {1, 5, 10, 20, 50, 100};
int x1,x2,x3;
int now,tot;
int i,j,k,a,b,suma,sumb,dis;
int sum[3],Cnt[N];
int d[2][M][M],cnt[3][N];
inline void update(int &x, int y){
    if (x==-1 || y<x)x=y;
}
inline int calc(){//get exchange times
    return (abs(a-cnt[0][i])+abs(b-cnt[1][i])+abs(Cnt[i]-a-b-cnt[2][i]))/ 2;
}
int main(){
    scanf("%d%d%d", &x1, &x2, &x3);
    for(i=0;i<3;i++){
        sum[i] = 0;
        for(j=N-1;j>=0;j--){
            scanf("%d",&cnt[i][j]);
            Cnt[j]+=cnt[i][j];
            sum[i]+=cnt[i][j]*val[j];
        }
        tot+=sum[i];
    }
    memset(d[0],-1,sizeof(d[0]));
    d[0][sum[0]][sum[1]]=0;
    for(i=0;i<N;++i){
        now=i&1;
        memset(d[now^1],-1,sizeof(d[now^1]));
        for(j=0;j<=tot;++j){
            for(k=0;j+k<=tot;++k){
            	if(d[now][j][k]==-1)continue;
                update(d[now^1][j][k],d[now][j][k]);
                for(a=0;a<=Cnt[i];++a){//A exchange a money to C
                    for(b=0;a+b<=Cnt[i];++b){//B exchange b money to C
                        suma=j+val[i]*(a-cnt[0][i]);
                        sumb=k+val[i]*(b-cnt[1][i]);
                        if(suma>=0&&sumb>=0&&suma+sumb<=tot)
                            update(d[now^1][suma][sumb],d[now][j][k]+calc());
                    }
                }
            }
        }
    }
    int ea=sum[0]+x3-x1,eb=sum[1]+x1-x2,ec=sum[2]+x2-x3;
    if (ea<0||eb<0||ec<0||ea+eb+ec!=tot||d[N&1][ea][eb]<0)puts("impossible");
    else printf("%d\n",d[N&1][ea][eb]);
    return 0;
}
/*
内向树dp~
就是先找环，任取环上有边相连两点，u和v，以u为根，断开u和v之间的边，做两次树形dp，dp[i][0]表示i不选，dp[i][1]表示i选
①强制u不选，v随意
②u随意，v不选
两种情况取最大值即可~
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
const int N=1000000+10,M=2*N;
using namespace std;
int head[N],next[M],to[M],bh[N];
int n,ban,rp,cnt,root;
long long val[N],ans,res,dp[N][2];
bool vis[N],v[N];
void add(int u,int v){
    to[cnt]=v;next[cnt]=head[u];head[u]=cnt++;
}
void circle(int u,int fa){//get circle and travel 
    for(int i=head[u];~i;i=next[i]){
        if(!bh[to[i]]){
            bh[to[i]]=true;circle(to[i],u);
        }
        else if(to[i]!=fa){
			rp=u,root=to[i],ban=i;
		}
    }
}
void dfscir(int u){
    dp[u][0]=0;dp[u][1]=val[u];
    for(int i=head[u];~i;i=next[i])
        if(i!=ban&&(i^1)!=ban&&!vis[to[i]]){
            vis[to[i]]=true;
            dfscir(to[i]);
            dp[u][1]+=dp[to[i]][0];
            dp[u][0]=max(dp[to[i]][0],dp[to[i]][1])+dp[u][0];
        }
}
void dfsban(int u){
    dp[u][0]=0;dp[u][1]=val[u];
    for(int i=head[u];~i;i=next[i])
        if(i!=ban&&(i^1)!=ban&&!v[to[i]]){
            v[to[i]]=true;
            dfsban(to[i]);
            dp[u][1]+=dp[to[i]][0];
            if(to[i]==rp)dp[u][0]+=dp[to[i]][0];//强制不选rp 
            else dp[u][0]+=max(dp[to[i]][0],dp[to[i]][1]);
        }
}
int main(){
    memset(head,-1,sizeof head);cnt=0;
    scanf("%d",&n);
    for(int i=1,a;i<=n;i++){
        scanf("%lld%d",&val[i],&a);
        add(i,a);add(a,i);
    }
    for(int i=1;i<=n;i++)
        if(!bh[i]){
            root=-1;bh[i]=true;
            circle(i,-1);
            vis[root]=true;dfscir(root);res=dp[root][0];
            v[root]=true; dfsban(root);res=max(res,max(dp[root][0],dp[root][1]));
            ans+=res;
        }
    printf("%lld\n",ans);
    return 0;
}
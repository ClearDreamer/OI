/*
加了一维时间维：
n：1 2 3 4 5
x：3 5 4 1 2
y：3 2 4 1 5
（此为样例）
其中n为时间（按输入顺序逆序考虑），x为这个值在原序列中的位置，y为添加的顺序（不足补齐）。
这样转化的话，这道题变成了一个标准的三维偏序的问题，用cdq搞一搞即可。注意要搞两次，一次为左上方，一次为右下方。就是把当前点的(x,y)坐标弄到平面上去，询问之前在这个点左上方和右下方的点的个数。
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
const int N=100000+10;
typedef long long LL;
int read(){
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,m,k;
LL f[N],i,j,cnt,w[N],u[N],x[N],z[N],ans[N];
struct P{int x,y,z;}a[N],b[N];
void add(int t){for(;t<=n;t+=t&-t)z[t]++;}
LL gs(int t,int f=0){for(;t;t-=t&-t)f+=z[t];return f;}
void clr(int t){for(;t<=n;t+=t&-t)z[t]=0;}
void sol(int l,int r){
    if(l==r)return;
    int mid=l+r>>1,i,j,p=l,q=mid+1;
    sol(l,mid),sol(mid+1,r);
    for(i=l;i<=r;i++)b[i]=a[(q==r+1||(p<=mid&&a[p].y<a[q].y))?p++:q++];
    for(i=l;i<=r;i++){
        a[i]=b[i];
        if(a[i].x<=mid)add(a[i].z);
        else f[a[i].x]+=gs(a[i].z);
    }
    for(i=l;i<=r;i++)if(a[i].x<=mid)clr(a[i].z);
}
int main(){
	n=read();m=k=read();
    for(i=1;i<=n;i++)w[read()]=i;
    for(i=1;i<=m;i++)u[x[i]=read()]=1;
    for(i=1;i<=n;i++)if(!u[i])x[++k]=i;
    for(k=0,i=n;i;i--)a[++k]=(P){n-i+1,n-x[i]+1,w[x[i]]};sol(1,n);
    for(k=0,i=n;i;i--)a[++k]=(P){n-i+1,x[i],n-w[x[i]]+1};sol(1,n);
    for(i=1;i<=n;i++)ans[i]=ans[i-1]+f[i];
    for(i=1,k=n;i<=m;i++)printf("%lld\n",ans[k--]);
    return 0;
}
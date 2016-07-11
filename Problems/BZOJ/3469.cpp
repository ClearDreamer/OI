#include<iostream>
#include<algorithm>
#include<cstdio>
#include<set>
#include<cstring>
using namespace std;
const int MAXN=100000;
int ch[MAXN+3][26],id[MAXN+3],w[MAXN+3],tot=0;
struct node{
    int id,w;
    node(){}
    node(int id,int w):id(id),w(w){}
    bool operator <(const node &d)const{
        return w>d.w || w==d.w&&id<d.id;
    }
};
typedef set<node> Set;
typedef Set::iterator SIT;
Set S[MAXN+3];
int newnode(){
    tot++;return tot;
}
void insert(char *s,int cost,int id){
    int cur=0,len=strlen(s+1);node d=node(id,cost);
    for(int i=1;i<=len;i++){
        if(ch[cur][s[i]-'a']==0)ch[cur][s[i]-'a']=newnode();
        cur=ch[cur][s[i]-'a'];S[cur].insert(d);
    }
}
int recog(char *s){
    int cur=0,len=strlen(s+1);
    for(int i=1;i<=len;i++){
        if(ch[cur][s[i]-'a']==0)return -1;
        cur=ch[cur][s[i]-'a'];
    }
    return cur;
}
char str[5*MAXN+3];
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int c,k;scanf("%d%d",&c,&k);
        while(k--){
            scanf("%s",str+1);
            insert(str,c,i);
        }
    }
    for(int i=1,t;i<=m;i++){
        scanf("%d",&t);
        scanf("%s",str+1);
        int x=recog(str);
        if(x==-1){puts("0");continue;}
        printf("%d",S[x].size());
        for(SIT it=S[x].begin();it!=S[x].end();it++){
            printf(" %d",it->id -1);
            if((--t)==0)break;
        }
        puts("");
    }
    return 0;
}
/*
AC自动机，暴力扫
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;
const int N = 1000+10;
const int HN = 6e5+10;
int n,m,na,ma;
char mat[N][N],str[N];
int ans[N][N];
int scan(){int i=0;scanf("%d",&i);return i;}
int l_hn,n_hn;
struct list{
	list(){next =NULL;d=0;}
	list *next;short d;
	void push(short);
}lh[HN];
queue<list*>pupa;
list *newlist(){
	if(l_hn < HN){lh[l_hn]=list();return &lh[l_hn++];}
	return new list();
}
void list::push(short a){
	list *l = newlist();d++;
	l->next = next;next = l;
	l->d = a;
}
struct Node{
	Node(){ch[0] = ch[1] = NULL;end.next=NULL;}
	list end;
	Node *fail,*ch[2],*last;
}house[HN];
Node *newNode(){
	if(n_hn < HN){house[n_hn]=Node();return &house[n_hn++];}
	return new Node();
}
queue<Node*>dui;
struct AC{
	Node *ROOT;
	AC(){ROOT=newNode();ROOT->fail=ROOT->last=ROOT;}
	void clear(){n_hn=0;l_hn=0;AC();}
	void insert(char str[],int bh){
		Node *r = ROOT;
		int len = strlen(str+1);
		for(int i=1;i<=len;i++){
			if(!('0'<=str[i] && str[i]<='1'))break;
			int c = str[i]-'0';
			if(!r->ch[c]){r->ch[c]=newNode();}
			r=r->ch[c];
		}r->end.push(bh);
	}
	void makefail(){
		for(int i=0;i<=1;i++)
		if(ROOT->ch[i]){
			ROOT->ch[i]->fail=ROOT->ch[i]->last = ROOT;
			dui.push(ROOT->ch[i]);
		}else ROOT->ch[i] = ROOT;
		while(!dui.empty()){
			Node *r = dui.front();dui.pop();
			for(int i=0;i<=1;i++)
			if(r->ch[i]){
				Node *l = r->fail;
				while(l->ch[i]==ROOT && l!=ROOT)l=l->fail;
				r->ch[i]->fail = l->ch[i];
				r->ch[i]->last = l->ch[i]->end.next?l->ch[i]:l->ch[i]->last;
				dui.push(r->ch[i]);
			}else r->ch[i] = r->fail->ch[i];
		}
	}
	void count(Node *r,int x,int y){
		while(r->end.next){
			for(list *i=r->end.next;i!=NULL;i=i->next){
				int k = i->d;
				if(x-k +1>=1)ans[x-k +1][y-ma+1]++;
			}
			r = r->last;
		}
	}
}ac;
void find(char s[],int x){
	int len = m;
	Node *r = ac.ROOT;
	for(int i=1;i<=len;i++){
		if(!('0'<=s[i] && s[i]<='1'))break;
		int c = s[i]-'0';
		r = r->ch[c];
		if(r->end.next)ac.count(r,x,i);
		else ac.count(r->last,x,i);
	}
}
int main(){
	int i,j;char cc;
	n = scan();m = scan();na = scan();ma = scan();
	for(i=1;i<=n;i++)scanf("%s",mat[i]+1);
	int nn = scan();
	while(nn--){
		ac.clear();
		for(i=1;i<=na;i++){
			scanf("%s",str+1);
			ac.insert(str,i);
		}
		ac.makefail();
		for(i=1;i<=n;i++)for(j=1;j<=m;j++)ans[i][j]=0;
		for(i=1;i<=n;i++)find(mat[i],i);
		short ok=0;
		for(i=1;i<=n&&!ok;i++)for(j=1;j<=m&&!ok;j++)if(ans[i][j] == na){ok=1;break;}
		printf("%d\n",ok);
	}
	return 0;
}
/*
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000;
struct list{
	list *nxt;
	int val;
	list(){init();}
	void init(){
		nxt=NULL;
		val=0;
	}
};
int list_cnt=0;
list* newlist(){
	static list a[100000+3];
	if(list_cnt>100000)return new list;
	list* t=&a[list_cnt++];t->init();
	return t;
}
void push(list *l,int val){
	list *t=newlist();
	l->nxt=t;
	t->val=val;
}
char mat[MAXN+3][MAXN+3];
int ans[MAXN+3][MAXN+3];
int n,m,na,ma;
namespace AC{
	const int N=600000;
	int ch[N+3][2],tot=0,fail[N+3],last[N+3];
	list *q[N+3];
	int newnode(){
		tot++;
		fail[tot]=last[tot]=ch[tot][0]=ch[tot][1]=0;
		q[tot]=newlist();
		return tot;
	}
	void init(){
		list_cnt=0;tot=0;q[0]=newlist();fail[tot]=last[tot]=ch[tot][0]=ch[tot][1]=0;
	}
	#define id(x) (x-'0')
	void insert(char s[],int id){
		int cur=0,len=strlen(s+1);
		for(int i=1;i<=len;i++){
			int t=id(s[i]);
			if(t!=0&&t!=1)break;
			if(ch[cur][t]==0){ch[cur][t]=newnode();}
			cur=ch[cur][t];
		}
		push(q[cur],id);
	}
	const int QLEN=600000*10;
	void build(){
		static int Q[QLEN+3],h,t;
		h=1;t=1;
		for(int i=0;i<1;i++){
			if(ch[0][i]){Q[t++]=ch[0][i];fail[ch[0][i]]=last[ch[0][i]]=0;}
			else {ch[0][i]=0;}
		}
		while(h!=t){
			int u=Q[h++];if(h==QLEN+1)h=1;
//			cout<<u<<" "<<ch[u][0]<<" "<<ch[u][1]<<endl;
			for(int i=0;i<1;i++){
				int &v=ch[u][i];
				if(v==0){v=ch[fail[u]][i];continue;}
				int x=fail[u];
				while(x && ch[x][i]==0)x=fail[x];
				fail[v]=ch[x][i];
				last[v]=q[ch[x][i]]->nxt ? ch[x][i] : last[ch[x][i]];
				Q[t]=v;t++;if(t==QLEN+1)t=1;
			}
		}
	}
	void count(int p,int x,int y){
		while(q[p]->nxt){
//			cout<<p<<endl;
			for(list* i=q[p]->nxt;i!=NULL;i=i->nxt){
				int v=i->val;
				if(x-v+1>=1)ans[x-v+1][y-ma+1]++;
			}
			p=last[p];
//			cout<<p<<endl;
//			if(q[p]==NULL){cout<<"TAT"<<endl;}
		}
	}
	void output(){
		for(int i=0;i<=tot;i++){
			cout<<i<<" "<<ch[i][0]<<" "<<ch[i][1]<<endl;
		}
	}
}
void find(char ch[],int x){
	int len=m,cur=0;
	for(int i=1;i<=len;i++){
		int c=ch[i]-'0';
		if(c!=0&&c!=1)break;
		cur=AC::ch[cur][c];if(cur==0)break;
//		cout<<AC::last[cur]<<endl;
		if(AC::q[cur]->nxt)AC::count(cur,x,i);
		else AC::count(AC::last[cur],x,i);
	}
}
void print(){
	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++)printf("%d ",ans[i][j]);
		printf("\n");
	}
}
char str[MAXN+3];
int main(){
	int i,j;char cc;
	scanf("%d%d%d%d",&n,&m,&na,&ma);
	for(i=1;i<=n;i++)
		scanf("%s",mat[i]+1);
	int Q;scanf("%d",&Q);
	while(Q--){
		AC::init();
		for(int i=1;i<=na;i++){
			scanf("%s",str+1);
			AC::insert(str,i);
		}
//		AC::output();
//		cout<<"!!"<<endl;
		AC::build();
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)ans[i][j]=0;
		for(int i=1;i<=n;i++){
			find(mat[i],i);}
		bool flg=0;
		for(int i=1;i<=n&&!flg;i++)
			for(int j=1;j<=m&&!flg;j++)
				if(ans[i][j]==na){flg=1;break;}
		printf("%d\n",flg);
	}
	return 0;
}
*/

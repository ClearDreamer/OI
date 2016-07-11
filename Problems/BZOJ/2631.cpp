#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
#define MOD 51061
const int MAXN=100000,INF=0x3f3f3f3f;
typedef unsigned int LL;
struct LCT{
	struct node{
		node *c[2],*f;
		int size,cn,rev;
		LL val,sum,mul,add;
		void init(){
			val=sum=rev=0;
			add=0;mul=1;size=1;cn=2;
		}
		void add_rev(){
			rev^=1;
			c[0]->cn=1;c[1]->cn=0;
			swap(c[0],c[1]);
		}
		void calc(int m,int a){
			val=(val*m+a)%MOD;
			sum=(sum*m+a*size)%MOD;
			add=(add*m+a)%MOD;
			mul=(mul*m)%MOD;
		}
		inline bool isroot(){
			return cn==2;
		}
		void setroot(){cn=2;}
		void link(node *fa,int _cn){
			f=fa;cn=_cn;
			if(!isroot())f->c[cn]=this;
		}
	}ns[MAXN+105],*nil;
	void update(node *x){
		if(x==nil)return;
		x->sum=(x->c[0]->sum + x->c[1]->sum + x->val)%MOD;
		x->size=x->c[0]->size + x->c[1]->size + 1;
	}
	void down(node* x){
		if(x==nil)return; 
		if(x->rev){
			x->c[0]->add_rev();x->c[1]->add_rev();x->rev=0;
		}
		int m=x->mul,a=x->add;
		x->mul=1;x->add=0;
		if(m!=1 || a!=0){//child canbe nil
			if(x->c[0]!=nil)x->c[0]->calc(m,a);
			if(x->c[1]!=nil)x->c[1]->calc(m,a);
		}
	}
	int tot;
	void init(){
		nil=ns;tot=0;nil->init();nil->size=0;
		nil->c[0]=nil;nil->c[1]=nil;
	}
	void newnode(int v){
		node *t=ns+(++tot);
		t->init();t->val=t->sum=v;
		t->c[0]=t->c[1]=t->f=nil;
	}
	void rotate(node *x){
		node *y=x->f,*z=y->f;int nx=x->cn,ny=y->cn;
		x->link(z,ny);x->c[!nx]->link(y,nx);y->link(x,!nx);
		update(y);
	}
	void relax(node *x){
		if(!x->isroot())relax(x->f);
		down(x);
	}
	void splay(node *x){
		relax(x);
		while(!x->isroot()){
			x->cn==x->f->cn?rotate(x->f):rotate(x);
			if(!x->isroot())rotate(x);
		}
		update(x);
	}
	node* access(node *x){
		node *y=nil;
		while(x!=nil){
			splay(x);
			x->c[1]->setroot();y->link(x,1);update(x);
			y=x;x=x->f;
		}
		return y;
	}
	void make_root(node *x){
		access(x);splay(x);x->add_rev();
	}
	node *get_root(node *x){
		access(x);splay(x);down(x);
		while(x->c[0]!=nil){
			x=x->c[0];down(x);
		}
		return x;
	}
	void link(node *x,node *y){
//		if(get_root(x)==get_root(y))return;
		make_root(x);
		x->f=y;
	}
	void cut(node *x,node *y){
		make_root(x);access(y);splay(y);
//		if(y->c[0]!=x)return;
		y->c[0]=nil;
		x->link(nil,2);
		update(y);
	}
	node *get_path(node *x,node *y){
		make_root(x);
		access(y);
		splay(y);
		return y;
	}
	void Val(int _x,int v){
		node* x=ns+_x;
		make_root(x);splay(x);
		x->val=v;update(x);
	}
	void Mul(int u,int v,int mul){
		node *x=ns+u,*y=ns+v;
		node *r=get_path(x,y);
		r->calc(mul,0);
	}
	void Add(int u,int v,int add){
		node *x=ns+u,*y=ns+v;
		node *r=get_path(x,y);
		r->calc(1,add);
	}
	LL query(int u,int v){
		return get_path(ns+u,ns+v)->sum;
	}
	void link(int u,int v){link(ns+u,ns+v);}
	void cut(int u,int v){cut(ns+u,ns+v);}
}lct;
int n,q;
char str[5];
int main(){
	scanf("%d%d",&n,&q);
	lct.init();
	for(int i=1;i<=n;i++){
		lct.newnode(1);
	}
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		lct.link(u,v);
	}
	for(int i=1,u,v,c;i<=q;i++) {
		scanf("%s%d%d",str,&u,&v);
		switch(str[0]){
			case '+':
				scanf("%d",&c);
				lct.Add(u,v,c);
				break;
			case '-':
				lct.cut(u,v);
				scanf("%d%d",&u,&v);
				lct.link(u,v);
				break;
			case '*':
				scanf("%d",&c);
				lct.Mul(u,v,c);
				break;
			case '/':
				printf("%u\n",lct.query(u,v));
				break;
		}
	}
	return 0;
}
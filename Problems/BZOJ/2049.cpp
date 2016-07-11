#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=10000,INF=0x3f3f3f3f;
struct LCT{
	struct node{
		node *c[2],*f;
		int rev,cn;
		void add_rev(){
			rev^=1;
			c[0]->cn=1;c[1]->cn=0;
			swap(c[0],c[1]);
		}
		void down(){
			if(rev){
				c[0]->add_rev();
				c[1]->add_rev();
				rev=0;
			}
		}
		inline bool isroot(){
			return cn==2;
		}
		void setroot(){
			cn=2;
		}
		void link(node *fa,int _cn){
			f=fa;cn=_cn;
			if(!isroot())f->c[cn]=this;
		}
	}ns[MAXN+105],*nil;
	int tot;
	void init(){
		nil=ns;tot=0;
		nil->c[0]=nil;nil->c[1]=nil;
	}
	void newnode(){
		node *t=ns+(++tot);
		t->cn=2;
		t->c[0]=t->c[1]=t->f=nil;t->rev=0;
	}
	void rotate(node *x){
		node *y=x->f,*z=y->f;int nx=x->cn,ny=y->cn;
		x->link(z,ny);x->c[!nx]->link(y,nx);y->link(x,!nx);
	}
	void relax(node *x){
		if(!x->isroot())relax(x->f);
		x->down();
	}
	void splay(node *x){
		relax(x);
		while(!x->isroot()){
			x->cn==x->f->cn?rotate(x->f):rotate(x);
			if(!x->isroot())rotate(x);
		}
	}
	node* access(node *x){
		node *y=nil;
		while(x!=nil){
			splay(x);
			x->c[1]->setroot();y->link(x,1);
			y=x;x=x->f;
		}
		return y;
	}
	void make_root(node *x){
		access(x);
		splay(x);
		x->add_rev();
	}
	node* get_root(node *x){
		access(x);splay(x);x->down();
		while(x->c[0]!=nil){
			x=x->c[0];x->down();
		}
		return x;
	}
	bool query(node *x,node *y){
		return get_root(x)==get_root(y);
	}
	void link(node *x,node *y){
		if(query(x,y))return;
		make_root(x);
		x->f=y;
	}
	void cut(node *x,node *y){
		make_root(x);access(y);splay(y);
		if(y->c[0]!=x)return;
		y->c[0]=nil;
		x->link(nil,2);
	}
	bool query(int u,int v){return query(ns+u,ns+v);}
	void link(int u,int v){link(ns+u,ns+v);}
	void cut(int u,int v){cut(ns+u,ns+v);}
}lct;
char str[20];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	lct.init();
	for(int i=1;i<=n;i++){
		lct.newnode();
	}
	for(int i=1,u,v;i<=m;i++){
		scanf("%s%d%d",str,&u,&v);
		switch(str[0]){
			case 'C':lct.link(u,v);break;
			case 'D':lct.cut(u,v);break;
			case 'Q':puts(lct.query(u,v)?"Yes":"No");break;
		}
	}
	return 0;
}

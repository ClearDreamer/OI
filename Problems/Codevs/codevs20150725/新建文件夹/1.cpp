/*

*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN=50,INF=0x3f3f3f3f;
struct bign{
	int v[MAXN+3],len;
	
	bign(){init();}
	
	bign(int t){
		init();
		*this=t;
	}
	
	void init(){
		memset(v,0,sizeof(v));
		len=0;
	}
	
	void clear(){
		while(!v[len-1] && len>1)len--;
	}
	
	bign operator = (const bign &t){
		memcpy(v,t.v,(t.len+5)*sizeof(int));
		len=t.len;
		return *this;
	}
	
	bign operator = (int val){
		init();
		if(val==0)len=1;
		while(val){
			v[len++]=val%10;
			val/=10;
		}
		return *this;
	}
	
	bool operator < (const bign &t)const{
		if(len!=t.len)return len<t.len;
		for(int i=len-1;i>=0;i--){
			if(v[i]!=t.v[i])return v[i]<t.v[i]; 
		}
		return false;
	}
	
	bool operator > (const bign &t)const{
		if(len!=t.len)return len>t.len;
		for(int i=len-1;i>=0;i--){
			if(v[i]!=t.v[i])return v[i]>t.v[i]; 
		}
		return false;
	}
	
	bool operator == (const bign &t)const{
		if(len!=t.len)return false;
		for(int i=len-1;i>=0;i--){
			if(v[i]!=t.v[i])return false;
		}
		return true;
	}
	
	bool operator >= (const bign &t)const{
		return *this>t||*this==t;
	}
	
	bool operator <= (const bign &t)const{
		return *this<t||*this==t;
	}
	
	bool operator != (const bign &t)const{
		return !(*this==t);
	}
	
	bign operator + (const bign &t)const{
		bign ans;ans.len=max(len,t.len);
		int lm=min(len,t.len);
		for(int i=0;i<lm;i++)ans.v[i]=v[i]+t.v[i];
		const int *s=(len<t.len?t.v:v);
		for(int i=lm;i<ans.len;i++){
			ans.v[i]=s[i];
		}
		ans.simply();
		return ans;
	}
	
	void input(){
		char c[MAXN+3];
		init();
		scanf("%s",c);
		input(c,0,strlen(c)-1);
	}
	
	bign operator * (const bign &t)const{
		bign ans;ans.len=len+t.len;
		for(int i=0;i<len;i++){
			for(int j=0;j<t.len;j++){
				ans.v[i+j]+=v[i]*t.v[j];
			}
		}
		ans.simply();
		ans.clear();
		return ans;
	}
	
	void simply(){
		v[len+1]=0;
		for(int i=0;i<len;i++){
			if(v[i]>=10){
				v[i+1]+=v[i]/10;
				v[i]%=10;
			}
		}
		if(v[len])len++;
	}
	
	void input(char *s,int l,int r){
		init();
		while(r>=l){
			v[len++]=s[r--]-'0';
		}
	}
	
	void output(){
		for(int i=len-1;i>=0;i--)putchar(v[i]+'0');
	}
};
bign m,sum=0;
inline int getbase(bign &t){
	for(int i=0;i<t.len;i++)if(t.v[i]!=0&&t.v[i]!=1)return i;
	return -1;
}
const int D1[10]={0,0,-1,7,-1,-1,-1,3,-1,9};
const int D0[10]={0,0,5,10,5,2,5,10,5,10};
int main(){
	m.input();sum=m;
	int tme=0,e;
	while((e=getbase(sum))!=-1){
		sum=sum+m;
		if(sum.len>20)break;
	}
	if((e=getbase(sum))!=-1)puts("Impossible");
	else sum.output();
	return 0;
}


/*
A(n,n)*(A(n+1,2)*A(n+3,m)+A(m,1)*A(2,2)*A(n+1,1)*A(n+2,m-1))
首先我们观察，男生无限制，先把男生排好即A(n,n)
然后我们排老师，老师不能相邻，n个男生有n+1个空位
如果老师被男生隔开，即有A(n+1,2)的方案
现在有了n+3个空位，还要放m个女生
即A(n+3,m)这就是式子加号前的部分
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
const int R=1000;
struct bign{  
    int v[10003],len;
    bign(){init();}
    void adjust(){
		while (len>1&&!v[len-1]) len--;
		for(int i=0;i<len;i++){
			if(v[i]>=R){
				v[i+1]+=v[i]/R;
				v[i]%=R;
				if(i+1==len)len++;
			}
		}
	}  
    void init(){memset(v,0,sizeof(v)),len=1;}  
    bign operator *(const bign &b){  
        bign c;c.len=len+b.len;
        for (int i=0;i<len;i++)
            for (int j=0;j<b.len;j++)
                c.v[i+j]+=v[i]*b.v[j];
        c.adjust();return c;  
    }  
    bign operator +(const bign &b){  
        bign c;c.len=max(len,b.len)+1;
        for (int i=0;i<c.len;i++)
            c.v[i]+=v[i]+b.v[i];
        c.adjust();return c; 
    }  
    inline void output(){  
        printf("%d",v[len-1]);
        for (int i=len-2;i>=0;i--)printf("%03d",v[i]);
    }  
};
bign fact(int a,int b){  
    bign res; 
    if(a>b)return res;  
    res.v[0]=1;  
    for (int i=a;i<=b;i++){  
        bign pp;pp.v[0]=i;  
        res=res*pp;
    }
    return res;
}  
bign A(int n,int m){  
    if(m==0){  
        bign res;res.v[0]=1;  
        return res;
    }
    if (m>n)return bign(); 
    return fact(n-m+1,n);
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);  
    bign ans=A(n,n)*(A(n+1,2)*A(n+3,m)+A(m,1)*A(2,2)*A(n+1,1)*A(n+2,m-1));  
    ans.output();puts("");
	return 0;
}
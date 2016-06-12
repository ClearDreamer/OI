#include<iostream>
#include<cstring>
using namespace std;
int s,m,c,a[203],t,ans=0;
struct qj{
	int from,last;
	bool used;
}qjs[203];
int qn=0;
int getnext(int x){
	while(qjs[x].used&&x<=qn)x++;
	//cout<<x<<endl;
	return x;
}
qj getmin(){
	int i=1,mi=1<<20,p=qn+1,q=qn+1;
	while(i<=qn){
		if(!qjs[i].used){
			int t=getnext(i+1);
			if(t>qn){//cout<<"abs"<<p<<endl;
				if(p==qn+1){
					p=i;q=i;break;
				}
			}
			else if(qjs[t].from-qjs[i].last<mi){
				//cout<<i<<"!!!"<<t<<endl;
				mi=qjs[t].from-qjs[i].last;
				p=i;
				q=t;
			}
			i=t;
		}
		else i++;
	}
	return (qj){p,q,false};
}
int hb(int i,int j){
	if(i==j){
		qjs[i].used=true;
		return 0;
	}
	qjs[j].used=true;
	
	//cout<<"!!!"<<qjs[j].from<<" "<<qjs[i].last<<endl;
	int an=qjs[j].from-qjs[i].last-1;
	qjs[i].last=qjs[j].last;
	return an;
}
int main(){
	cin>>m>>s>>c;
	memset(a,0,sizeof(a));
	for(int i=1;i<=c;i++){
		cin>>t;a[t]=1;
	}
	t=0;int k=1;
	while(k<=s){
		if(a[k]){
			qn++;
			qjs[qn].from=k;
			while(a[k])k++;
			qjs[qn].last=k-1;
			qjs[qn].used=false;
		}
		k++;
	}
	//cout<<qn;
	ans=c;
	/*cout<<ans<<endl;
	for(int i=1;i<=qn;i++){
		cout<<qjs[i].from<<' '<<qjs[i].last<<endl;
	}
	cout<<endl;*/
	int qnn=qn;
	if(qn<=m)cout<<ans;
	else{
		qj e=getmin();
		while(e.from<=qn){
			//cout<<e.from<<" "<<e.last<<endl;
			ans+=hb(e.from,e.last);
			qnn--;
			//cout<<qn<<m<<" "<<ans<<endl;
			if(qnn<=m)break;
			e=getmin();
		}
		cout<<ans;
	}
	return 0;
}

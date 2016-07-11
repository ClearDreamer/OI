#include<cstdio>
#include<map>
using namespace std;
typedef pair<int,int> P;
typedef map<P,int>::value_type mt;
map<P,int> mp;
map<P,int>::iterator it;
int A,B,C,n,ans=0;
char str[200000+3];
int main(){
	scanf("%d",&n);
	scanf("%s",str+1);
	mp.insert(mt(make_pair(0,0),0));
	for(int i=1;i<=n;i++){
		switch(str[i]){
			case 'J':A++;break;
			case 'O':B++;break;
			case 'I':C++;break;
		}
		P t=make_pair(A-B,B-C);
		it=mp.find(t);
		if(it==mp.end())mp.insert(mt(t,i));
		else ans=max(ans,i-(it->second));
	}
	printf("%d\n",ans);
	return 0;
}
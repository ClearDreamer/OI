/*
��ţ��
*/ 
#include<iostream>
#include<algorithm>
using namespace std;
int f[5003],e[5003],r[5003],n,ll=0,kk=0;
bool cmp(const int i,const int j){
	return (f[i]<f[j])||(f[i]==f[j]&&e[i]>e[j]);//����˵�������˵����ʱ�Գ���������� 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>f[i]>>e[i];
		r[i]=i;
	}
	sort(r+1,r+n+1,cmp);
	int fr=0,en=0;
	if(n==1){cout<<e[1]-f[1]<<" "<<0;return 0;}
	fr=f[r[1]];//�����һ�� 
	en=e[r[1]];
	ll=en-fr;
	for(int i=2;i<=n;i++){
		int t=r[i];
		if(f[t]>=fr&&e[t]<=en)continue;//�������Ѱ��� 
		if(f[t]<=en)en=e[t];//�����������ڵ�ǰ�����ڣ���չ�Ҷ˵� 
		else{//�����˶Ͽ����� 
			ll=max(ll,en-fr);//��¼����� 
			kk=max(kk,f[t]-en);//��¼����ȱ 
			fr=f[t];en=e[t];//��ʼ�������� 
		}
	}
	cout<<ll<<" "<<kk;
	return 0;
}

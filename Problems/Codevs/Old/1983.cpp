#include<iostream>
using namespace std;
int f[10],ans=0,n;
bool check(){//���� 
	int sum=0,t=0;
	//cout<<f[0]+f[1]+f[2]+f[3]+f[4]+f[5]+f[6]+f[7]<<" ";
	//if(f[0]+f[1]+f[2]+f[3]+f[4]+f[5]+f[6]+f[7]==0)cout<<"!!!";
	for(int i=0;i<=8;){//ö��ÿһ���ո� 
		int j=i+1;//������ո����һ����ʼ��һ����Ŀո����� 
		while(f[j]==0)j++;
		//cout<<j<<endl;
		t=0;
		for(int k=i+1;k<=j;k++){//������һ�εĺ�
		//ʵ���ϵ�i����λǰ������־���i 
			t=t*10+k;
		}
		if(f[i]==1)sum+=t;
		else sum-=t;
		i=j;
	}
	//cout<<sum<<" ";
	if(sum==n)return true;
	return false;
}
void dfs(int c){
	if(c==9){
		if(check()){
			ans++;
		}
	}
	else{
		for(int i=0;i<=2;i++){
			f[c]=i;dfs(c+1);
			//cout<<i<<endl;
		}
	}
}
int main(){
	cin>>n;
	f[0]=f[9]=1;
	/*for(int i=1;i<=8;i++){
		f[i]=2;
	}
	check();*/
	dfs(1);
	cout<<ans;
	return 0;
}

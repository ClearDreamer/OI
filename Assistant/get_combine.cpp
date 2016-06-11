#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
vector<int> v1,v2;
int main(){
    int x=0;
    while(1){
        cin>>x;
        if(x==0)break;
        v1.push_back(x);
    }
    while(1){
        cin>>x;
        if(x==0)break;
        v2.push_back(x);
    }
    for(int i=0;i<v2.size();i++){
        int f=1;
        for(int j=0;j<v1.size();j++){
            if(v2[i]==v1[j]){f=0;break;}
        }
        if(f)cout<<v2[i]<<" ";
    }
}
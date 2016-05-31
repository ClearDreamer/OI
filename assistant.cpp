#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;
FILE *in;
vector<int> pros;
void input_pro(){
    in=fopen("pros.txt","r");
    pros.clear();
    int x;
    while(fscanf(in,"%d",&x)!=-1){
        pros.push_back(x);
    }
    sort(pros.begin(),pros.end());
    fclose(in);
}
void save_pro(){
    in=fopen("pros.txt","w");
    pros.clear();
    int x;
    for(int i=0;i<pros.size();i++)fprintf(in,"%d ",pros[i]);
    fclose(in);
}
void out(int x){
    printf("%d\n",x);
}
void out_allpro(){
    for_each(pros.begin(),pros.end(),out);
}
int Rand(int up=RAND_MAX){
    return rand()%up;
}
char str[100];
int main(){
    input_pro();
    while(1){
        printf("There are %d problems.\n",pros.size());
        puts("Press to get a problem:");
        char c=getchar();
        if(c=='\n'){
            int x=Rand(pros.size());
            printf("Problem ID: %d, Do you solve it?",pros[x]);
            sprintf(str,"start http://www.lydsy.com/JudgeOnline/problem.php?id=%d",pros[x]);
            system(str);
            c=getchar();
            while(c!='y'&&c!='n')c=getchar();
            if(c=='y')pros.erase(pros.begin()+x);
        }
        if(c=='q'){save_pro();break;}
        else{
            if(c=='a'){
                out_allpro();
            }
            else if(c=='c'){
                system("cls");
            }
        }
    }
    return 0;
}
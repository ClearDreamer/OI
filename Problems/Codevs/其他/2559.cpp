/*
小明想睡觉
*/
#include<cstdio>
int main(){
	int x,y;
	scanf("%d%d", &x,&y); 
	if(x*3+60*y>=480)printf("YES");
	else printf("No");
	return 0;   
}

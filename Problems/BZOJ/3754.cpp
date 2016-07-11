#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define EPS (1.0 / (points - 1))
using namespace std;
#define sqr(x) ((x)*(x))
struct edge{
	int x,y,len;
	double temp;
	bool operator <(const edge &a)const {
		return len < a.len;
	}
	void read() {scanf("%d%d%d",&x,&y,&len);}
}es[2003];
int points,edges;
int father[103];
int find(int x){
	if(father[x] == x)	return x;
	return father[x] = find(father[x]);
}
inline int MST(){
	for(int i = 1; i <= points; ++i)father[i] = i;
	int re = 0;
	for(int i = 1; i <= edges; ++i) {
		int fx = find(es[i].x),fy = find(es[i].y);
		if(fx != fy) {
			father[fx] = fy;
			re += es[i].len;
		}
	}
	return re;
}
bool cmp(const edge &a,const edge &b){
	return a.temp < b.temp;
}
inline double calc(double average){
	for(int i = 1; i <= points; ++i)father[i] = i;
	for(int i = 1; i <= edges; ++i)es[i].temp = sqr(average - es[i].len);
	sort(es + 1,es + edges + 1,cmp);
	double re = 0.0;
	for(int i = 1; i <= edges; ++i) {
		int fx = find(es[i].x),fy = find(es[i].y);
		if(fx != fy) {
			father[fx] = fy;
			re += es[i].temp;
		}
	}
	return sqrt(re / (points - 1));
}
int main(){
	cin >> points >> edges;
	for(int i = 1; i <= edges; ++i)es[i].read();
	sort(es + 1,es + edges + 1);
	double range_min = (double)MST() / (points - 1);
	reverse(es + 1,es + edges + 1);
	double range_max = (double)MST() / (points - 1);
	double ans = 0x3f3f3f3f;
	for(int i = 0; EPS * i + range_min <= range_max; ++i)
		ans = min(ans,calc(EPS * i + range_min));
	cout << fixed << setprecision(4) << ans << endl;
	return 0;
}
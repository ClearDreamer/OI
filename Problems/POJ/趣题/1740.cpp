/*
A New Stone Game
题意：对于n堆石子，每堆若干个，两人轮流操作，每次操作分两步，第一步从某堆中去掉至少一个，第二步（可省略）把该堆剩余石子的一部分分给其它的某些堆。
	  最后谁无子可取即输。
分析：首先我们考虑两堆相等的情况，一定是谁取谁输，因为对方永远可以做对称的操作。对于四堆，1、2堆相等，3、4堆相等的情况，一定也是先手输，后手也只需要做对称的操作（在先手取石子的对称堆中取相同多的石子，并把和先手等量的石子分给先手分配给的堆的对称堆。（若先手在3堆取，并分给1堆，那后手就在4堆取，分给2堆）。也就是说对于任意的一对一对相等的情况来说，一定是后手必胜。
	  我们接下来来证明除上述情况外，所有情况都是先手必胜。因为任何一种情况都可以转化为一对一对相等的情况。若总堆数为奇数的情况，可以把石子最多的一堆的石子分配给其它堆，使得其它堆两两相等。最多一堆的石子绝对是足够多，可以完成这个补齐的任务的。因为我们把石子从小到大排序后画成条形统计图。把相邻两个分成一组（1和2一组，3和4一组……）我们需要用第n堆填补1，3，5……堆我们把需要填补的这些差距（2比1高出的部分，4比3高出的部分……）投影到统计图左侧的y轴上，我们会发现这是一些不连续的区间，其长度总和明显小于第n堆。所以可以补齐。
	  对于堆数为偶数的情况。我们把最多的一堆削弱到和最少的一堆一样多，并把拿掉的石子分给别的堆，使其一对一对地相等。可行性于前面奇数情况同理。
	  所以只要判断是不是一对一对的相等的情况即可。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;
const int MAXN=100;
bitset<MAXN+3> vis;
int n,ans,x;
int main(){
	while(scanf("%d",&n),n){
		vis=0;ans=0;
		while(n--){
			scanf("%d",&x);
			if(vis[x])ans--;
			else ans++;
			vis[x]=!vis[x];
		}
		printf("%d\n",ans!=0);
	}
	return 0;
}


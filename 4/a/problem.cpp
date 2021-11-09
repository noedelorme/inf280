#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

#define INFTY 100001

map<int, pair<int, unsigned int>> Sets;

void MakeSet(int x){
	Sets[x] = {x,0};
}
int Find(int x){
	if(Sets[x].first == x){ return x;}
	else{ return Sets[x].first = Find(Sets[x].first); }
}
void Union(int x, int y) {
	int parentX = Find(x), parentY = Find(y);
	int rankX = Sets[parentX].second, rankY = Sets[parentY].second;
	if (parentX == parentY){ return; }
	else if(rankX < rankY){
		Sets[parentX].first = parentY;
	}else{
		Sets[parentY].first = parentX;
	}
	if(rankX == rankY){
		Sets[parentX].second++;
	}
}

int main(){

	int x,y;
	while(scanf("%i ", &x)==1){
		int refusals = 0;
		
		while(scanf("%i\n", &y)==1){
			if(x==0){ x=INFTY; }
			if(y==0){ y=INFTY; }
			if(Find(x)==0){ MakeSet(x); }
			if(Find(y)==0){ MakeSet(y); }

			if(Find(x)==Find(y)){
				refusals++;
			}
			else{
				Union(x,y);
			}

			scanf("%i ", &x);
			if(x==-1){
				Sets.clear();
				break;
			}
		}
		cout << refusals << endl;

	}
	
	return 0;
}

/*

On lit "x y", si x et y sont déjà dans la
même classe d'équivalence, on refuse le couple,
sinon on les met dans la même classe.

*/
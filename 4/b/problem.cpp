#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

int G[51][51];
int degree[51];

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

void printOrder(int n){
	for(int i=1; i<51; i++){
		if(G[n][i]){
			G[n][i]--; G[i][n]--;
			printOrder(i);
			cout << i << " " << n <<endl;
		}
	}
}

int main(){
	
	int nb = 0;
	int t, n;
	scanf("%i\n", &t);
	while(t--){
		cout << "Case #" << ++nb << endl;
		scanf("%i\n", &n);

		//Reset de Stes, G et degree
		Sets.clear();
		for(int i=0; i<51; i++){
			for(int j=i; j<51; j++){
				G[i][j]=0; G[j][i]=0;
			}
		}
		fill_n(degree, 51, 0);

		//Lecture input
		for(int i=0; i<n; i++){
			int x,y;
			scanf("%i %i\n", &x, &y);

			if(Find(x)==0){ MakeSet(x); }
			if(Find(y)==0){ MakeSet(y); }

			G[x][y]++; G[y][x]++;
			degree[x]++; degree[y]++;
			Union(x,y);
		}

		//Si une couleur à un degree impair c'est qu'on a forcement perdu une perle
		bool loss = false;
		int last;
		for(int i=1; i<51; i++){
			if(degree[i]>0){ last=i; }
			if(degree[i]%2!=0){
				loss = true;
				break;
			}
		}
		//Si une couleur n'est pas dans la mm classe d'équivalence qu'une autre, 
		//c'est qu'on a perdu une perle
		if(!loss){
			for(int i=1; i<51; i++){
				if(degree[i]!=0){
					if(Find(i)!=Find(last)){
						loss = true;
						break;
					}
				}
			}
		}
		if(loss){
			cout << "some beads may be lost" <<endl;
		}else{
			//Afficher l'ordre des perles
			printOrder(last);
		}
		printf("\n");
	}

	return 0;
}

/*
	"Un graphe connexe admet un circuit eulérien si et seulement si tous ses sommets sont de degré pair."
*/
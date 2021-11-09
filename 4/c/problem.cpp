#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <queue>
#include <unordered_map>

using namespace std;


/***********************************************************************************/
#define MAXY 101
#define MAXX 101

#define NIL -1
#define INF numeric_limits<unsigned int>::max()
vector<int> X, Y;
vector<int> Adj[MAXX];
int PairX[MAXX];
int PairY[MAXY];
unsigned int Dist[MAXX];


bool BFS() {
	queue<int> Q;
	Dist[NIL] = INF;
	for(auto x : X) { // start from nodes that are not yet matched
		Dist[x] = (PairX[x] == NIL) ? 0 : INF;
		if (PairX[x] == NIL)
			Q.push(x);
	}
	while (!Q.empty()) { // find all shortest paths to NIL
		int x = Q.front(); Q.pop();
		if (Dist[x] < Dist[NIL]) // can this become a shorter path?
			for (auto y : Adj[x])
				if (Dist[PairY[y]] == INF) {
					Dist[PairY[y]] = Dist[x] + 1; // update path length
					Q.push(PairY[y]);
				}
	}
	return Dist[NIL] != INF; // any shortest path to NIL found?
}
bool DFS(int x) {
	if (x == NIL)
		return true; // reached NIL
	for (auto y : Adj[x])
		if (Dist[PairY[y]] == Dist[x] + 1 &&
		DFS(PairY[y])) { // follow trace of BFS
			PairX[x] = y; // add edge from x to y to matching
			PairY[y] = x;
			return true;
		}
	Dist[x] = INF;
	return false; // no augmenting path found
}
int HopcroftKarp() {
	fill_n(PairX, MAXX, NIL); // initialize: empty matching
	fill_n(PairY, MAXY, NIL);
	int Matching = 0; // count number of edges in matching
	while (BFS()) { // find all shortest augmenting paths
		for(auto x : X) // update matching cardinality
			if (PairX[x] == NIL && // node not yet in matching?
				DFS(x)) // does an augmenting path start at x?
				Matching++;
	}
	return Matching;
}
/***********************************************************************************/

int r,c;
long int maxRow[MAXX];
long int maxCol[MAXY];


long int maximumRow(vector<vector<int>> room, int r, int c, int i){
	long int max = 0;
	for(int j=0; j<c; j++){
		if(room[i][j]>max){ max = room[i][j]; }
	}
	return max;
}

long int maximumCol(vector<vector<int>> room, int r, int c, int j){
	long int max = 0;
	for(int i=0; i<r; i++){
		if(room[i][j]>max){ max = room[i][j]; }
	}
	return max;
}

void printMap(vector<vector<int>> room){
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			cout<<room[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(){

	while(scanf("%i %i\n", &r, &c)==2){

		fill_n(maxRow, MAXX, 0);
		fill_n(maxCol, MAXY, 0);
		X.clear();
		Y.clear();
		fill_n(Dist, MAXX, 0);
	 	for(int i=0; i<MAXX; i++){
			Adj[i].clear();
		}

		/*
			- création de room (tableau des valeurs)
			- calcul des valeurs max lignes colonnes
			- initialisation de maxCrates au nb total de caisses
		*/
		long int maxCrates = 0;
		vector<vector<int>> room(r);
		long int v;
		for(int i=0; i<r; i++){
			room[i] = vector<int>(c);
			for(int j=0; j<c; j++){
				scanf("%li", &v);
				room[i][j] = v;
				maxRow[i] = max(maxRow[i], v);
				maxCol[j] = max(maxCol[j], v);
				if(v){ maxCrates+=v-1; }
			}
		}

		/*
			On créé un graphe bipartie (ligne, colonne) qui comporte
			un arc entre i et j si le max de i = max de j. Puis on
			compute le maching (on veux, au final un ensemble d'arc
			minimum qui couvre toutes les lignes et toutes les colonnes,
			ce qui est revient à chercher le matching max et r). 
		*/
		for(int i=0; i<r; i++){
			for(int j=0; j<c; j++){
				if(maxRow[i]==maxCol[j] && room[i][j]){
					X.push_back(i);
					Y.push_back(j);
					Adj[i].push_back(j);
				}
			}
		}
		HopcroftKarp();


		/*
			On décompte deux fois (une fois par ligne et une fois par
			colonne) les valeurs maximales (pour lesquels on ne pourra 
			pas rétirer de caisse sans que els caméras ne le voit).
		*/
		for(int i=0; i<r; i++){
			if(maxRow[i]){ maxCrates-=maxRow[i]-1; }
		}
		for(int j=0; j<c; j++){
			if(maxCol[j]){ maxCrates-=maxCol[j]-1; }
		}

		/*
			Pour tout les arc du matching, on rajoute la valeur max
			correspondante (-1) (car dans ce cas, la pile de caisse
			est utile pour les lignes ET les colonnes).
		*/
		for(int i=0; i<r; i++){
			if(maxRow[i] && PairX[i]!=NIL){ maxCrates+=maxRow[i]-1; }
		}

		cout<<maxCrates<<endl;
	}

	return 0;
}

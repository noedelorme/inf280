#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef struct Loc{
	int x, y, w;
} Loc;

int* trips;

/* Revoie la somme les poids entre a et b inclus */
int weight(Loc* locs, int a, int b){
	int w=0;
	for(int i=a; i<=b; i++){
		w += locs[i].w;
	}
	return w;
}

/* Renvoie la distance du chemin de a à b */
int dist(Loc* locs, int a, int b){
	int d=0;
	for(int i=a; i<b; i++){
		d += abs(locs[i+1].x - locs[i].x) + abs(locs[i+1].y - locs[i].y);
	}
	return d;
}

/* Renvoie (récurrence) la distance optimale jusqu'à b */
int trip(int* trips, Loc* locs, int C, int b){
	if(b < 0){
		return 0;
	}else if(b == 0){
		return 2*(abs(locs[0].x)+abs(locs[0].y));
	}else{
		int min;
		if(trips[b-1]){
			min = trips[b-1] + 2*(abs(locs[b].x)+abs(locs[b].y));
		}else{
			trips[b-1] = trip(trips, locs, C, b-1);
			min = trips[b-1] + 2*(abs(locs[b].x)+abs(locs[b].y));
		}
		int a = b-1;
		while(weight(locs, a, b)<=C && a>=0){
			int value;
			if(a==0){
				value = 0 + (abs(locs[a].x)+abs(locs[a].y)) + dist(locs, a, b) + (abs(locs[b].x)+abs(locs[b].y));
			}else if(trips[a-1]){
				value = trips[a-1] + (abs(locs[a].x)+abs(locs[a].y)) + dist(locs, a, b) + (abs(locs[b].x)+abs(locs[b].y));
			}else{
				trips[a-1] = trip(trips, locs, C, a-1);
				value = trips[a-1] + (abs(locs[a].x)+abs(locs[a].y)) + dist(locs, a, b) + (abs(locs[b].x)+abs(locs[b].y));
			}

			if(value < min){ min = value; }
			a--;
		}
		return min;
	}
}

/*
Equation de récurrence:
dists[b] = min{ dists[a] + dist(0,a) + dist(a,b) + dist(b,0) }
Pour tout a t.q. weight(a,b)<=C
*/
int main(){

	int cases;
	scanf("%i\n", &cases);
	scanf("\n");

	for(int k=0; k<cases; k++){

		int C,N;
		scanf("%i\n", &C);
		scanf("%i\n", &N);
		trips = new int[N];
		Loc locs[N];
		
		for(int i=0; i<N; i++){
			int x, y, w;
			scanf("%i %i %i\n", &x, &y, &w);
			locs[i].x = x;
			locs[i].y = y;
			locs[i].w = w;
		}

		scanf("\n");
		printf("%i\n", trip(trips, locs, C, N-1));
		if(k!=cases-1){
			printf("\n");
		}
	}


	return 0;
}
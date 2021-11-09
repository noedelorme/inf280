#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

int G[52][52];
int visited[52];

bool dfs(int n){
	visited[n] = -1;
	for(int i=0; i<52; i++){
		if(G[n][i]!=0){
			if(visited[i]==-1){ return true; }
			if(visited[i]==0 && dfs(i)){ return true; }
		}
	}
	visited[n] = 1;
	return false;
}

int main(){

	int n;
	while(scanf("%i", &n)==1){
		
		// reset de la matrice d'adjacence
		for(int i=0; i<52; i++){
			for(int j=0; j<52; j++){
				G[i][j] = 0;
			}
		}

		for(int i=0; i<n; i++){
			string cell;
			cin >> cell;
			
			// A+=0 ; A-=1 ; B+=2 ; B-=3 ; C+=4 ; ...
			int icell[4] = {-1, -1, -1, -1};
			for(int j=0; j<4; j++){
				char a = cell[2*j];
				char b = cell[2*j+1];
				if(a!='0'){
					int ia = (a-'A')*2;
					int ib = b!='+';
					icell[j] = ia+ib;
					//cout<<a<<b<<" "<<ia<<" "<<ib<<" "<<ia+ib<<endl;
				}
			}

			
			// Arc entre les connecteurs d'une même cellule
			for(int j=0; j<4; j++){
				for(int k=0; k<4; k++){
					if(j!=k && icell[j]!=-1 && icell[k]!=-1){
						// A+ => A- ; B- => B+ ; ...
						int other = pow((-1), icell[j]%2) + icell[j];
						G[other][icell[k]] = 1;
					}
				}
			}
		}

		fill_n(visited, 52, 0);
		bool hasCycle = false;
		for(int i=0; i<52; i++){
			if(visited[i]==0){
				hasCycle = dfs(i);
				if(hasCycle){ break; }
			}
		}

		if(hasCycle){
			printf("unbounded\n");
		}else{
			printf("bounded\n");
		}
	}

	return 0;
}
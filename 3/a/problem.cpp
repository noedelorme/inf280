#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct Node{
	string name;
} Node;

int main(){

	int nb=0;
	int P, R;
	cin >> P;
	while(P){
		nb++;
		cin >> R;

		if(P==0 && R==0){ break; }

		unordered_map<string, int> names;
		vector<int> adj[P];
		
		int currentP = 0;
		for(int i=0; i<R; i++){
			string name1, name2;
			cin >> name1 >> name2;

			if(names.find(name1)==names.end()){
				names[name1] = currentP;
				currentP++;
			}
			if(names.find(name2)==names.end()){
				names[name2] = currentP;
				currentP++;
			}
			
			adj[names[name1]].push_back(names[name2]);
			adj[names[name2]].push_back(names[name1]);
		}

		/* Floyd-Warshall Algorithm */
		int Dist[P][P];
		fill_n((int*)Dist, P*P, 100000000);
		for(int u=0; u<P; u++){
			Dist[u][u] = 0;
			for (auto& tmp : adj[u]){
				Dist[u][tmp] = 1;
			}
		}
		for(int k=0; k < P; k++){
			for(int i=0; i < P; i++){
				for(int j=0; j < P; j++){
					Dist[i][j] = min(Dist[i][j], Dist[i][k] + Dist[k][j]);
				}
			}
		}

		int max = 0;
		for(int i=0; i<P; i++){
			for(int j=i+1; j<P; j++){
				if(max<Dist[i][j]){ max = Dist[i][j]; }
			}
		}
		

		if(max<100000000){
			printf("Network %i: %i\n\n", nb, max);
		}else{
			printf("Network %i: DISCONNECTED\n\n", nb);
		}
		
		cin >> P;
	}

	return 0;
}
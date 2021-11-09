#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

int n,m;
bool flag = false;
int adj[21];
bool visited[1<<21];
queue<int> Q;
pair<int, int> steps[1<<21]; //steps[i] = (arbre précedents ; config précedente)

void BFS(){
	Q.push((1<<n)-1); //Initialement, le singe peut être de partout (que des 1)
	visited[(1<<n)-1] = true; 
	while (!Q.empty() && !flag) {
		int config = Q.front();
		Q.pop();
		for(int i=0; i<n; i++){ //On regarde sur quel arbre le singe peut sauter à partir de la config actuelle
			int trees = 0;
			if(config&(1<<i)){ //Si i est dans config
				for(int j=0; j<n; j++){
					if(i!=j){
						if(config&(1<<j)){ //Si j est aussi dans config
							trees |= adj[j]; //Le singe peut aller vers les sommet adjacents de j
						}
					}
				}

				if(!visited[trees]){ //Si on a pas encore traité la config
					steps[trees] = {i,config};

					visited[trees] = true;
					Q.push(trees);
					if(!trees){ //Si le singe ne peut être sur aucun arbre, on a trouvé une stratégie
						flag = true;
						break;
					}
				}
			}
		}
	}
}

void printStrategie(){
	vector<int> strat;
	int config = 0;
	while(steps[config].second != 0){
		strat.push_back(steps[config].first);
		config = steps[config].second;
	}
	printf("%li: ", strat.size());
	for(int i=strat.size()-1; i>0; i--){
		printf("%i ", strat[i]);
	}
	printf("%i", strat[0]);
	printf("\n");
}

int main(){

	while(scanf("%i %i\n", &n, &m)==2){
		if(n==0 && m==0){ break; }

		fill_n(adj, 21, 0);
		fill_n(visited, 1<<n, false);
		flag = false;
		while(!Q.empty()){ Q.pop();}
		for(int i=0; i<(1<<21); i++){
			steps[i] = {0,0};
		}

		int x,y;
		for(int i=0; i<m; i++){
			scanf("%i %i\n", &x, &y);
			adj[x] |= 1<<y; adj[y] |= 1<<x;
		}

		BFS();
		if(flag){
			printStrategie();
		}else{
			printf("Impossible\n");
		}
		
	}

	
	return 0;
}


/*

 L'état initial est bien sûr 1 pour chaque point. Lors du déplacement, 
 on énumère tous les points sur lesquels on peut tirer (en choisissant 
 le point où le singe peut exister, bien sûr), puis on simule où le 
 singe peut se déplacer à chaque point après le tir. Ici, nous mettons 
 en place un tableau de nxt, et si edge(u,v) existe, alors 
 nxt[u]|=(1<<v),nxt[v]|=(1<<u). De cette façon, nxt[i] préserve tous les 
 déplacements possibles du singe à partir du point i. Nous utilisons 
 bfs pour continuer à étendre l'état, en le déplaçant pas à pas, et en 
 enregistrant le chemin du tir en même temps, jusqu'à ce qu'il y ait un 
 état où tous les emplacements sont 0, c'est-à-dire que tous les 
 emplacements ne peuvent pas avoir de singe, ce qui indique que le singe 
 n'a plus de chemin

*/

/*

La première chose qu'on se dit en lisant l'énnoncé, c'est que si il y a un 
cycle, le singe pourra toujours s'échaper.

Donc pour trouver une strétégie on travail avec un graphe sans cycle, i.e. un arbre

L'idée c'est de calculer l'ensemble des emplacement ou peut se trouver le singe 
étape après étape. Pour ça, on créer un arbre de configuration. une configuration c'est
un ensemble d'arbre sur leqeul le singe peut se trouver. nombre de 21bit qui représente l'ensemble
On créer l'arbre avec un BFS pour garantir qu'on trouve la plus petite stratégie possible.

Initialement le singe peut se trouver sur tous les arbres donc la première configuration
est que des 1. Et on dévloppe l'arbre des configurations en regardant où le singe peut aller
à partir des positions ou il pouvait être à l'étape d'avant.

Si au bout d'un moment, le singe ne peut être sur aucun arbre (i.e. une fongiguration==0)
alors c'est qu'on à une stratégie pour le chasser.

*/
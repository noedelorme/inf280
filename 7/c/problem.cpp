#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

double winPoint, winGame, winTie, winSet, winMatch;

double game(int scoreA, int scoreB){
	// A gagne avec au moins deux points d'écart
	if(scoreA==4 && scoreA-scoreB>=2){ return 1; }
	// B gagne avec au moins deux points d'écart
	else if(scoreB==4 && scoreB-scoreA>=2){ return 0; }
	// 40-40
	else if(scoreA==3 && scoreB==3){ return winPoint*winPoint/(1-winPoint*(1-winPoint)-(1-winPoint)*winPoint); }
	// Balle normale
	else{ return winPoint*game(scoreA+1,scoreB) + (1-winPoint)*game(scoreA,scoreB+1); }
}

double tie(int scoreA, int scoreB){
	// A gagne avec au moins deux points d'écart
	if(scoreA==7 && scoreA-scoreB>=2){ return 1; }
	// B gagne avec au moins deux points d'écart
	else if(scoreB==7 && scoreB-scoreA>=2){ return 0; }
	// 6-6
	else if(scoreA==6 && scoreB==6){ return winPoint*winPoint/(1-winPoint*(1-winPoint)-(1-winPoint)*winPoint); }
	// Balle normale
	else{ return winPoint*tie(scoreA+1,scoreB) + (1-winPoint)*tie(scoreA,scoreB+1); }
}

double set(int scoreA, int scoreB){
	// A gagne avec au moins deux jeux d'écart
	if((scoreA==6 || scoreA==7) && scoreA-scoreB>=2){ return 1; }
	// B gagne avec au moins deux jeux d'écart
	else if((scoreB==6 || scoreB==7) && scoreB-scoreA>=2){ return 0; }
	// 6-6
	else if(scoreA==6 && scoreB==6){ return tie(0,0); }
	// Jeu normal
	else{ return winGame*set(scoreA+1,scoreB) + (1-winGame)*set(scoreA,scoreB+1); }
}

int main(){

	while(scanf("%lf\n", &winPoint)==1 && winPoint>=0){

		winGame = game(0,0);
		winSet = set(0,0);
		winMatch = winSet*winSet + winSet*(1-winSet)*winSet + (1-winSet)*winSet*winSet;

		printf("%.11lf %.11lf %.11lf\n", winGame, winSet, winMatch);

	}

	return 0;
}

/*

On plonge le problème de calcul de probabilité de gagner un jeu dans l'ensemble de problème: 
gagner à partir d'un certain score. De cette manière on calcul récurcivement la probabilité de ganer un jeu.
On distingue les cas (2 pts d'écrta, 40Av, ...).

On fait de même pour le tie-break (c'est le mm code avec 7 au lieu de 4).

On applique la même méthode pour la proba de gagner un set.

Finalement la proba de gagner le match c'est la proba de gagner les deux premeirs set, gagner le premier et le troisème,
ou gagner les deux derniers.

*/
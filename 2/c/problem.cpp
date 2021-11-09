#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef struct Drive{
	double a,b;
	Drive(int _a, int _b): a(_a), b(_b) {};
} Drive;

int compareGoodDrive(const Drive &d1, const Drive &d2){
    return d1.a < d2.a;
}

int compareBadDrive(const Drive &d1, const Drive &d2){
    return d1.b > d2.b;
}

int main(){

	int n;
	while(scanf("%i\n", &n)==1){
		/*
			goodDrives contient les nbGood drives qui gagnent de la mémoire (large)
			badDrives contient les nbBad drives qui perdent de la mémoire (strict)
		*/
		vector<Drive> goodDrives, badDrives;
		int nbGood=0;
		int nbBad=0;
		//int pas assez grand a priori
		long int extra = 0; //extra: capacité minimal à ajouter
		long int current = 0; //current: mémoire totale disponible

		for(int i=0; i<n; i++){
			int a,b;
			scanf("%i %i\n", &a, &b);
			if(b-a>=0){
				goodDrives.push_back({a,b});
				nbGood++;
			}else{
				badDrives.push_back({a,b});
				nbBad++;
			}
		}

		/*
			On tri les goodDrives selon les a croissant
			On tri les badDrives selon les b décroissant
		*/
		sort(goodDrives.begin(), goodDrives.end(), compareGoodDrive);
		sort(badDrives.begin(), badDrives.end(), compareBadDrive);

		/*
			On traite en premier les drives qui "donnent" de la mémoire
		*/
		for(int i=0; i<nbGood; i++){
			if(current < goodDrives[i].a){
				extra += goodDrives[i].a - current;
				current = goodDrives[i].a;
			}
			current += goodDrives[i].b - goodDrives[i].a;
		}
		/*
			Puis on traite en premier les drives qui "prennent" de la mémoire
		*/
		for(int i=0; i<nbBad; i++){
			if(current < badDrives[i].a){
				extra += badDrives[i].a - current;
				current = badDrives[i].a;
			}
			current += badDrives[i].b - badDrives[i].a;
		}

		printf("%li\n", extra);
	}

	return 0;
}
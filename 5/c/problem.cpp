#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

int n,s;

int KnuthMorrisPratt(string p){
	int T[p.size()+1]; int np = p.size();
	T[0] = -1;
	int max = -1;
	int cnd = 0;
	for (int i = 1; i <= np; i++) {
		if(cnd>max){ max = cnd; }
		T[i] = cnd;
		while (cnd >= 0 && p[cnd] != p[i]){ cnd = T[cnd]; }
		cnd++;
	}

	return max;
}

int main(){

	while(scanf("%i %i\n", &n, &s)==2){
		string pres[s];
		for(int i=0; i<s; i++){
			cin >> pres[i];
		}
		int len = pres[0].size();
		if(len>1){
			vector<string> probs[n];

			for(int i=0; i<s; i++){
				int l = KnuthMorrisPratt(pres[i]);
				int k = 1+floor((n-len)/(len-l));
				//cout<<pres[i]<<" "<<l<<" "<<k<<endl;
				probs[k].push_back(pres[i]);
			}

			for(int i=0; i<n; i++){
				for(auto p : probs[i]){
					cout<<p<<endl;
				} 
			}
		}else{
			for(int i=0; i<s; i++){
				cout << pres[i]<<endl;
			}
		}
	}

	return 0;
}

/*

Premièrement je me suis dit que comme le rival joue aléatoirmeent, toute
prediction de même taille peut apparraitre avec mm proba.

Puis je me suis dit que certainnes predictions pouvais s'auto contenir
i.e. une prediction peut avoir un prefix qui est aussi suffixe et donc que ça boulverse les probabilités.

Donc pour chauqe prédiction je calcule la longeur maximale d'un prefixe qui est aussi suffixe. (avec KnuthMorrisPratt)
Ce qui me fournit un entier à partir du quel je peux trié les prédiction et les afficher dans le bon ordre

*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

char lign[1000000];
char c;

bool isDigit(char c){ return c >= '0' && c <= '9'; }

int main(){

	while(cin >> lign){
		int i=0;
		long int nb = 0;
		while(lign[i]){
			if(isDigit(lign[i])){
				int substrs[3] = {0, 0, 0};
				while(isDigit(lign[i])){
					int digit = lign[i]%3;
					int oldSubstrs[3] = {substrs[0], substrs[1], substrs[2]};
					substrs[(digit+0)%3] = oldSubstrs[0]+1;
					substrs[(digit+1)%3] = oldSubstrs[1];
					substrs[(digit+2)%3] = oldSubstrs[2];
					nb += substrs[0];
					i++;
				}
				i--;
			}
			i++;
		}
		printf("%ld\n", nb);
	}

	return 0;
}

/*

//nombre divisible par 3 ssi somme chiffres divisible par 3

On lit char après char jusqu'à tomber sur un digit. Et on s'intérèsse
à tous les digit directement après (i.e. on étudie successivement
les regroupement de digits).

On utilise la programmation dynamique. On calcule le problème
"Nombre de substhreeng (donc de substring divisible par 3)"
a partir de
"nombre de substring modulo 3 qui termine à la position précedente pour chaque valeur possible du modulo (0,1,2)"

Pour traiter le digit courant, on calcule son modulo 3, 
si c'est 1, alors des substring qui terminaient à la pos précedente avec un modulo 1 termine maintenant avec un modulo 2,
substring qui terminaient à la pos précedente avec un modulo 2 termine maintenant avec un modulo 0
et substring qui terminaient à la pos précedente avec un modulo 0 termine maintenant avec un modulo 1 
et dans ce cas on ajoute 1 car on peut prendre le digit tout seul.

Quand on a calculer ça, on à trouver substrs[0] nouveaux substhreeng (le nb de substring qui ont un modulo 3 = 0 (i.e. les substhreeng))

*/
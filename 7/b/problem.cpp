#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

long int A,B;

long int C(long int k){
	/* Conversion en binaire */
	int n = floor(log2(k))+1;
	vector<int> binary(n);
	long int temp = k;
	for(int i=n-1; i>=0; i--){
		if(temp>=(long int)1<<i){ binary[i]=1; temp-=(long int)1<<i; }
		else{ binary[i]=0; }
	}

	/* On calcule la somme */
	long int sum = 0;
	for(int i=0; i<n; i++){
		if(binary[i]){
			sum += i*((long int)1<<(i-1)) + k;
			for(int j=i; j<n; j++){
				if(binary[j]){
					sum -= (long int)1<<j;
				}
			}
		}
	}

	return sum;
}


int main(){

	while(scanf("%li %li\n", &A, &B)==2){
		printf("%li\n", C(B+1)-C(A));
	}

	return 0;
}

/*

Nouveau problème: Calculer C(k) le nombre de 1 qu'il y a dans la représentation binaire 
de tous les nombres strictement plus petits que k.

On résoud le pb initial avec C(B+1)-C(A)
---------------
On peut facilement calculer Cn = C(2^n). C'est le nombre de 1 qu'il ya dans la représentation
binaire de tous les nombres que l'on peut écrire avec au maximum n bits.
On trouve : Cn=n*2^(n-1)
---------------
Obtient la formule suivante:
n := nb de bits necessaire pour coder k
k := k1*2^1 + ... + kn*2^n
C(k) = SUM(pour 0<=i<=n) ki*( Ci + k - SUM(pour i<=j<=n) kj*2^j ) )



*/

/*

Nouveau problème: Calculer C(k) le nombre de 1 qu'il y a dans la représentation binaire 
de tous les nombres strictement plus petits que k.

On résoud le pb initial avec C(B+1)-C(A)
---------------
On peut facilement calculer Cn = C(2^n). C'est le nombre de 1 qu'il ya dans la représentation
binaire de tous les nombres que l'on peut écrire avec au maximum n bits.
On trouve une relation de récurence sur ce nombre C_n+1 = 2*C_n * 2^n
(Une fois C_n en mettant un 0 devant les nombre s'écrivant sur n bits, une fois C_n en mettant
un 1, et on a rajouté 2^n 1).

En écrivant les premiers termes (0,1,4,12,32,80,224,...), on conjecture Cn=n*2^(n-1)
Ce qui se vérifie très bien par récurence. (ou bien on peut passer par l'écriture en série
entière vue en mitro205).
---------------
Maintenant qu'on à ce nombre pour les puissances de 2, on va calculer ce nombre pour n'importe
quel entier (en se servant de sa décomposition binaire).

Prenons l'exemple de 13 = 2^3 + 2^2 + 2^0
On considère la première puissance (2^3), 

Pour chaque puissance 2^i qui apparait dans la représentation binaire de k, on ajoute au nb de 1:
* Ci + (k-2^i-2^...)

Ainsi on obtient la formule suivante:
n := nb de bits necessaire pour coder k
k := k1*2^1 + ... + kn*2^n
C(k) = SUM(pour 0<=i<=n) ki*( Ci + k - SUM(pour i<=j<=n) kj*2^j ) )



*/
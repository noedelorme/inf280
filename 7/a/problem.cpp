#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>
#include <unordered_map>

using namespace std;


/* Calcule les 63 premiers entiers premiers */
vector<unsigned long long> ps;
void primes(){
	bitset<10000001> P;
	P.set();
	P[0] = P[1] = 0;
	for(long long i = 2; i<1e5 ; i++){
		if (P[i]) {
			for (long long j=i*i; j<1e5; j+=i)
				P[j]=0;
			ps.push_back(i);
			if(ps.size()>=63){ return; }
		}
	}
}

/* Calcule le coefficient binomial (n k) */
unsigned long long binomialCoeffs[63][63];
unsigned long long binomialCoeff(int n, int k) {
	if(binomialCoeffs[n][k]==0){
	   	if(k==0 || k==n){ return binomialCoeffs[n][k]=1; }
	   	unsigned long long temp = binomialCoeff(n-1, k-1) + binomialCoeff(n-1, k);
	   	binomialCoeffs[n][k] = temp;
		return temp;
	}else{ return binomialCoeffs[n][k]; }
}

/* Calcule le coefficient multinomial à partir des coefficients binomiaux */
unsigned long long multinomialCoeff(vector<unsigned long long> es){
	vector<int> M = {};
	int n = 0;
	for(auto& e : es){
		if (e!=0){ M.push_back(e); n += e; }		
	}
	unsigned long long ret = 1; int sum = 0;
	for(auto& m : M){
		sum += m;
		ret *= binomialCoeff(sum,m);
	}	
	return ret;
}

/* Calcule toute les valeurs possibles de k */
unordered_map<unsigned long long, unsigned long long> result;
int MAX = 63;
unsigned long long p63 = (unsigned long long) 1<<MAX;
vector<unsigned long long> ks;
void enumerate(){
	vector<unsigned long long> es(MAX,0); es[0]=1;
	unsigned long long k = 2;
	int cursor = 1;

	while(k != p63){
		unsigned long long n = multinomialCoeff(es);
		if(result.find(n)==result.end()){ result[n] = k; }
		else{ result[n] = min(k,result[n]); }

		ks.push_back(k);
		unsigned long long quo = p63/k;

		while(cursor>0 && ps[cursor]>quo){
			for(unsigned long long i=0; i<es[cursor]; i++){ k /= ps[cursor]; }
			es[cursor]=0;
			cursor--;
			while(cursor>0 && es[cursor-1]==es[cursor]){
				for(unsigned long long i=0; i<es[cursor]; i++){ k /= ps[cursor]; }
				es[cursor]=0;
				cursor--;
			}
			quo = p63/k;
		}

		es[cursor]++;
		k *= ps[cursor];
		cursor++;
	}
}

int main(){

	primes();
	enumerate();

	unsigned long long n;
	while(scanf("%lli\n", &n)==1){ printf("%lli %lli\n", n, result[n]); }

	return 0;
}

/*

Je résouds le problème en brut force.
L'idée c'est de construire k tel que f(k)=n. Donc on veut utiliser des premiers les
plus petits possibles.

Ainsi on cherche tous les entiers k entre 1 et 2^63 qui s'écrivent comme puissance des
63 entiers premiers (63 par ce que 2*2*2*2*... avec 63 2 minimise le pire cas) par 
puissances décroissantes. k = 2^e1 + 3^e2 + 5^e3 ... avec e1 ≥ e2 ≥ e3 ≥ ...

Pour ce fait, je commence à e1,e2,e3,...=1,0,0,,... et j'incrémente les puissance avec
un curseur de manière à garantir que tous les entiers que j'énumère son de la forme 
décrite plus haut.

Le fait est qu'il n'y en a pas tant que ça (environ 43000)

Maintenant que j'ai la décomposition en facteurs premiers de tout ces entiers k. Il
suffit que je calcule le nombre d'arrangementq ue je peux faire avec ses facteurs.
Pour ça j'utilise les coefficient multinomiaux (merci mitro205). Plus précisement
je calcule les coefficients multinomiaux avec les coefficient binomiaux en ne les
calculant qu'une seule fois (stockage dans un tableau).

Ainsi le créer une tableau association qui pour chaque valeur possibles de n stocke
le plus petit entier k que j'ai énuméré.

https://www.csc.kth.se/~austrin/icpc/finals2013solutions.pdf

https://blog.csdn.net/weixin_30332241/article/details/96302648

*/
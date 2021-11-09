#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

#define EPS 1e-8
#define INF 1e20
#define PI acos(-1)

using namespace std;

typedef struct Point{
	double x, y;
	double angl;
	Point(){ x=0.0; y=0.0; angl=0.0; }
	Point(double in_x, double in_y, double in_angl): x(in_x), y(in_y), angl(in_angl) {}
	bool operator == (Point pt2) const{ return (fabs(x - pt2.x) < EPS && (fabs(y - pt2.y) < EPS)); }
} Point;

bool compareAngle(Point const& pt1, Point const& pt2){ return pt1.angl<pt2.angl; }

int c(double a, double b){
	if(fabs(a-b)<EPS){ return 0; }
	else if(a>b){ return 1; }
	else{ return -1; }
}

int n, lower, upper, j2, j4, bestPts, worstPts;
Point maria;
Point pts[100000];
Point relativePts2[100000];
Point relativePts4[100000];

int main(){

	while(scanf("%i\n", &n)==1){
		/* RESET */
		lower=100001; upper=100001; j2=0; j4=0; bestPts=0; worstPts=0;

		scanf("%lf %lf\n", &maria.x, &maria.y);
		for(int i=1; i<n; i++){
			scanf("%lf %lf\n", &pts[i-1].x, &pts[i-1].y);
			double angle = atan2(pts[i-1].y-maria.y,pts[i-1].x-maria.x);
			pts[i-1].angl = angle;

			// Premier quadrant
			if(angle>0 && angle<PI/2){
				bestPts++;
			}
			// Deuxième quadrant
			if(angle>=PI/2 && angle<=PI){
				relativePts2[j2++] = pts[i-1];
			}
			// Troisième quadrant
			if(angle>-PI && angle<-PI/2){
				worstPts++;
			}
			// Quatrième quadrant
			if(angle>=-PI/2 && angle<=0){
				relativePts4[j4++] = pts[i-1];
			}
		}

		/* TRI */
		sort(pts, pts+n-1, compareAngle);
		sort(relativePts2, relativePts2+j2, compareAngle);
		sort(relativePts4, relativePts4+j4, compareAngle);

		if(j2==0 && j4==0){
			printf("1 1\n");
			continue;
		}


		/* BALAYAGE */
		int kl4=0, ku4=j4;
		for(int i=0; i<j2; i++){
			int u = i;
			int l = j2-1-i;

			while(c(relativePts4[kl4].angl, relativePts2[i].angl-PI)==-1 && kl4<j4){ kl4++; }
			while(c(relativePts4[ku4-1].angl, relativePts2[i].angl-PI)==-1 && ku4>0){ ku4--; }

			u += ku4;
			l += kl4;

			/*for(int j=0; j<j4; j++){
				if(c(relativePts4[j].angl, relativePts2[i].angl-PI)==1){
					u++;
				}
				if(c(relativePts4[j].angl, relativePts2[i].angl-PI)==-1){
					l++;
				}
			}*/
			lower = min(lower, worstPts+l);
			upper = min(upper, bestPts+u);
		}

		int kl2=j2, ku2=0;
		for(int i=0; i<j4; i++){
			int u = j4-1-i;
			int l = i;

			while(c(relativePts2[kl2-1].angl, relativePts4[i].angl+PI)==-1 && kl2>0){ kl2--; }
			while(c(relativePts2[ku2].angl, relativePts4[i].angl+PI)==-1 && ku2<j2){ ku2++; }

			u += ku2;
			l += kl2;


			/*for(int j=0; j<j2; j++){
				if(c(relativePts2[j].angl, relativePts4[i].angl+PI)==-1){
					u++;
				}
				if(c(relativePts2[j].angl, relativePts4[i].angl+PI)==1){
					l++;
				}
			}*/
			lower = min(lower, worstPts+l);
			upper = min(upper, bestPts+u);
		}

		int best = upper+1;
		int worst = n-lower;
		printf("%i %i\n", best, worst);

	}

	return 0;
}

/*

L'idée c'est de voir chaque téléphone comme un point dans le plan ( les coos sont les notes x1 et x2).
Ainsi on peut donner une signification géométrique à s=w1*x1+w2*x2, c'est une droite. Si on considère
le premier point (celui de Maria), pour une certaine valeur du vecteur w, la droite passe par lui et 
divise le plan en deux, les points au dessus à la droite, et les points en dessous.

On considère le repère qui a pour origine le premier point (celui de maria) et, pour chaque point, on calcule son angle.
En divisant le repère en 4 quadrants. On remarque que d'après les conditions qu'on a sur w, les points
qui sont dans le premier quadrant (sens trigo) seront toujours meilleur que celui de Maria. Les points
dans le 3ème quadrant seront toujours moins bons que celui de Maria (donc on calcule bestPts et WorstPts).

Les seuls points sur lesquel on peut travailer sont les points qui sont dans le deuxième et 4ème 
quadrants. 

On effectue un balayage selon l'angle de ces points (en calculant à chauqe fois le nombre de points au
dessus et en dessous de la droite). On retient le nombre minimum de point meilleur et le nombre minimum
de point moins bon. On en deduis le rank min et max.

Malheureusement, pour une raison que j'ignore, le programme n'est pas accepted. Il fonctionne pourtant sur
tous les exemples de Udebug et tous les exemples que j'ai pu créer. J'ai même créé un exemple avec tout
les cas dégénéré que j'ai pu pensé, et j'obetnais une bonne réponse.

*/
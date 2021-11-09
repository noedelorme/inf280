#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

#define EPS 1e-8
#define INF 1e20

using namespace std;

typedef struct Point{
	double x, y;
	Point(){ x=0.0; y=0.0; }
	Point(double in_x, double in_y): x(in_x), y(in_y) {}
	bool operator == (Point pt2) const{ return (fabs(x - pt2.x) < EPS && (fabs(y - pt2.y) < EPS)); }
} Point;

Point pts[100];
double area;
double lower, upper;
int ilower, iupper;
double min_x, max_x;
double G_x;
int n;

int main(){

	while(scanf("%i\n", &n)==1){
		/* Reset */
		min_x = 4000; max_x = -4000;
		area = 0; G_x = 0;
		upper = INF; lower = 0;

		/* Lecture du fichier input
		 * Calcule de min_x et max_x */
		for(int i=0; i<n; i++){ 
			scanf("%lf %lf\n", &pts[i].x, &pts[i].y);
			if(pts[i].y == 0){
				min_x = min(min_x, pts[i].x);
				max_x = max(max_x, pts[i].x);
			}
		}

		/* Calcule aire et centre gravité */
		for(int i=0; i<n; i++){
			area += pts[i].x*pts[(i+1)%n].y-pts[(i+1)%n].x*pts[i].y;
			G_x += (pts[i].x*pts[(i+1)%n].y-pts[(i+1)%n].x*pts[i].y)*(pts[i].x+pts[(i+1)%n].x);
		}
		G_x /= 6*0.5*area;
		area = 0.5*fabs(area);

		bool unstable = false;

		/* Cas ou x0 est à gauche de la base */
			// Si x0 à gauche de la base
		if(pts[0].x < min_x){
			upper = min(upper, (G_x-min_x)/(min_x-pts[0].x)*area);
		}
			// Si x0 pas à gauche de la base
		else if(pts[0].x > min_x){
			lower = max(lower, (G_x-min_x)/(min_x-pts[0].x)*area);
		}
		
		/* Cas ou x0 est à droite de la base */
			// Si x0 à droite de la base
		if(pts[0].x > max_x){
			upper = min(upper, (G_x-max_x)/(max_x-pts[0].x)*area);
		}
			// Si x0 pas à droite de la base
		else if(pts[0].x < max_x){
			lower = max(lower, (G_x-max_x)/(max_x-pts[0].x)*area);
		}

		/* Cas ou x0 sur la frontière de la base */
			// Si x0 sur le bord de la base et G à gauche
		if(pts[0].x == min_x && G_x < min_x){ unstable = true; }
			// Si x0 sur le bord de la base et G à droite
		if(pts[0].x == max_x && G_x > max_x){ unstable = true; }

		

		if(upper < lower){ unstable = true; }
		ilower = floor(lower);
		iupper = ceil(upper);
		if(unstable){
			printf("unstable\n");
		}else{
			if(upper>=INF){
				printf("%i .. inf\n", ilower);
			}else{
				printf("%i .. %i\n", ilower, iupper);
			}
		}
	}

	return 0;
}

/*

On lit le fichier d'input en stoquant les points et en calculant 
la base de la grue (i.e. se qui touche le sol).

On calcule l'aire du polygone (qui est aussi la masse), et le
centre de gravité du polygone.

Selon les cas, on calcule la masse maximum qu'on peut ajouter au
point 0 pour que le centre de gravité reste entre min_x et max_x.
(si on sort de cette zone c'est que c'est instable). On fait ce 
calcul en calculant le cas limite du nouveau centre de gravité
(calculer avec les pondération entre l'ancien centre de gravité
multiplié par la masse du polygone et l'objet qu'on rajoute).

*/
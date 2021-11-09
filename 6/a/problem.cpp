#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>

#define EPS 1e-8

using namespace std;

typedef struct Point{
	double x, y;
	Point(){ x=0.0; y=0.0; }
	Point(double in_x, double in_y): x(in_x), y(in_y) {}
	bool operator == (Point pt2) const{ return (fabs(x - pt2.x) < EPS && (fabs(y - pt2.y) < EPS)); }
} Point;

Point p1,p2,p3;

double multiple(double a, double b){
	a = fabs(a);
	b = fabs(b);
	while(a>b){
		a-=b;
	}
	if(fabs(a-b)<a){
		return fabs(a-b);
	}else{
		return a;
	}
}

int main(){

	double pi = acos(-1);

	while(scanf("%lf %lf\n%lf %lf\n%lf %lf\n", &p1.x, &p1.y, &p2.x, &p2.y,&p3.x, &p3.y)==6){
		double agl213 = fabs(atan2(p2.y-p1.y,p2.x-p1.x)-atan2(p3.y-p1.y,p3.x-p1.x));
		double agl123 = fabs(atan2(p1.y-p2.y,p1.x-p2.x)-atan2(p3.y-p2.y,p3.x-p2.x));
		double agl132 = fabs(atan2(p1.y-p3.y,p1.x-p3.x)-atan2(p2.y-p3.y,p2.x-p3.x));
		
		for(int i=3; i<1001; i++){
			if(multiple(agl213,pi/i)<EPS && multiple(agl123,pi/i)<EPS && multiple(agl132,pi/i)<EPS){
				printf("%i\n", i);
				break;
			}
		}
	}

	return 0;
}


/*

On remarque que, dans un polygone régulier à n points, l'angle qui pointe 
vers un point quelconque et qui proviens de deux points consécutifs est PI/n.

Si les 3 points de l'input sont dans ce polygone à n points, alors que les 
3 angles du triangle qu'ils forment doivent être des multiple de PI/n.

Donc on calcule ces 3 angles du triangles. Et pour chaque valeur de n, on
vérifie si les 3 points de l'input peuvent être sur le mm polygone à n points.

*/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef struct Hole{
	double r, x, y, z;

	double v(){ return r*r*r*acos(-1)*4/3; }

	Hole(double _r, double _x, double _y, double _z): r(_r/1000), x(_x/1000), y(_y/1000), z(_z/1000) {};
} Hole;

typedef struct Slice{
	double z1, z2, minusV;

	double v(){ return 100*100*(z2-z1) - minusV; }

	bool intersectHole(Hole* hole){
		double r = hole->r;
		double z = hole->z;
		return z1<z+r && z2>z-r;
	}

	void minusHole(Hole* hole){
		double r = hole->r;
		double z = hole->z;
		double from = max(z1, z-r);
		double to = min(z2, z+r);
		if(from-z>=0){
			minusV += (r*r*(to-z)-(to-z)*(to-z)*(to-z)/3)*acos(-1) - (r*r*(from-z)-(from-z)*(from-z)*(from-z)/3)*acos(-1);
		}else if(to-z<=0){
			minusV += (r*r*(z-from)-(z-from)*(z-from)*(z-from)/3)*acos(-1) - (r*r*(z-to)-(z-to)*(z-to)*(z-to)/3)*acos(-1);
		}else{
			minusV += (r*r*(to-z)-(to-z)*(to-z)*(to-z)/3)*acos(-1) + (r*r*(z-from)-(z-from)*(z-from)*(z-from)/3)*acos(-1);
		}
	}

	Slice(double _z1, double _z2): z1(_z1), z2(_z2), minusV(0) {};
} Slice;


int main(){

	int n,s;
	while(scanf("%d %d", &n, &s)==2){

		double V = 100*100*100;	

		vector<Hole*> holes(n);
		for(int i=0; i<n; i++){
			double r,x,y,z;
			scanf("%lf %lf %lf %lf", &r, &x, &y, &z);
			holes[i] = new Hole(r, x, y, z);
			V -= holes[i]->v();
		}

		double sliceV = V/s;

		double z=0;
		for(int i=0; i<s; i++){
			double a=z, b=100;
			Slice* currentSlice = new Slice(a,b);

			while(fabs(b-a)>=pow(10,-12)){
				double m = (a+b)/2;
				currentSlice->z2 = m;
				currentSlice->minusV = 0;
				for(int j=0; j<n; j++){
					if(currentSlice->intersectHole(holes[j])){
						currentSlice->minusHole(holes[j]);
					}
				}
				if(currentSlice->v()>sliceV){
					b=m;
				}else{
					a=m;
				}
			}
			printf("%.9f\n",(a+b)/2-z);
			z=(a+b)/2;
		}
	}

	return 0;
}
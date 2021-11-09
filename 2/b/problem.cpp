#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

typedef struct Balloon{
	double r, x, y, z;

	double v(){ return r*r*r*acos(-1)*4/3; }

	int minDistWalls(int x1, int y1, int z1, int x2, int y2, int z2){
		bool in = min(x1,x2)<x && x<max(x1,x2);
		in &= min(y1,y2)<y && y<max(y1,y2);
		in &= min(z1,z2)<z && z<max(z1,z2);
		if(in){
			int dx = min(abs(x2-x), abs(x1-x));
			int dy = min(abs(y2-y), abs(y1-y));
			int dz = min(abs(z2-z), abs(z1-z));
			return min(dx,min(dy,dz));
		}else{ return 0; }
	}

	double distBalloon(Balloon bal){
		double distRadius = sqrt(pow((x-bal.x),2)+pow((y-bal.y),2)+pow((z-bal.z),2));
		if(distRadius>bal.r){ return distRadius - bal.r; }else{ return 0; }
	}

} Balloon;

double inflate(Balloon* bals, int* index, int n, int x1, int y1, int z1, int x2, int y2, int z2){
	for(int i=0; i<n; i++){
		double minRadius = bals[index[i]].minDistWalls(x1, y1, z1, x2, y2, z2);
		for(int j=0; j<i; j++){
			double value = bals[index[i]].distBalloon(bals[index[j]]);
			if(value<minRadius){ minRadius=value; }
		}
		bals[index[i]].r = minRadius;
	}
	double V = abs(x2-x1)*abs(y2-y1)*abs(z2-z1);
	for(int i=0; i<n; i++){
		V -= bals[index[i]].v();
	}
	return V;
}

int main(){

	int nb = 1;

	int n;
	scanf("%i", &n);
	while(n!=0){
		int x1, y1, z1, x2, y2, z2;
		scanf("%i %i %i\n%i %i %i\n", &x1, &y1, &z1, &x2, &y2, &z2);

		Balloon bals[n];
		int index[n];

		for(int i=0; i<n; i++){
			int x, y, z;
			scanf("%i %i %i\n", &x, &y, &z);
			bals[i].x = x;
			bals[i].y = y;
			bals[i].z = z;
			bals[i].r = 0;
			index[i] = i;
		}
		double min = -1;

		do{

			if(min == -1){
				min = inflate(bals, index, n, x1, y1, z1, x2, y2, z2);
			}else{
				double value = inflate(bals, index, n, x1, y1, z1, x2, y2, z2);
				if(value < min){ min = value; }
			}

		}while(next_permutation(index, index+n));

		
		printf("Box %i: %li\n\n", nb, lround(min));

		scanf("%i", &n);
		nb++;
	}

	return 0;
}
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[]){

	string s, input;
	while(getline(cin, s)){
		int area = 0;
		float  w = stof(s);
		getline(cin, s);
		float  n = stof(s);

		for(int i=0; i<n; i++){
			getline(cin, s);
			float wi = stof(s.substr(0, s.find(" ")));
			float li = stof(s.substr(s.find(" ")+1, s.size()));
			area += wi*li;
		}

		float l = area/w;
		cout << l << endl;
	}

	

	return 0;
}
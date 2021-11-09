#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[]){

	bool newset = true;

	string s, input;
	int line = 1;
	int t;

	while(getline(cin, s)){ 
		if(line%2 == 1){
			t = stoi(s);
		}else{
			int n = 0;

			int p1 = stoi(s.substr(0,1));
			int p2 = stoi(s.substr(2,3));
			int p3 = stoi(s.substr(4,5));
			int p4 = stoi(s.substr(6,7));
			int p5 = stoi(s.substr(8,9));

			if(p1 == t){ n++; }
			if(p2 == t){ n++; }
			if(p3 == t){ n++; }
			if(p4 == t){ n++; }
			if(p5 == t){ n++; }

			cout << n << endl;
		}

		line++;
	}

	return 0;
}
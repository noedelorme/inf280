#include <iostream>
#include <string>
#include <list>

using namespace std;

int main(){

	int nb=1;
	string s;
	while(getline(cin, s)){
		if(s.substr(0,3)=="0 0"){ return 0; }

		cout << "Case " << nb << ":" << endl;
		nb++;

		int p = stoi(s.substr(0, s.find(" ")));
		int c = stoi(s.substr(s.find(" ")+1, s.size()));

		list<int> file;
		for(int i=1; i<=min(p,c); ++i){
			file.push_back(i);
		}

		for(int i=0; i<c; ++i){
			getline(cin, s);
			if(s.substr(0,1)=="N"){
				cout << file.front() << endl;
				file.push_back(file.front());
				file.pop_front();
			}else{
				int x = stoi(s.substr(s.find(" ")+1, s.size()));
				file.remove(x);
				file.push_front(x);
			}
		}
	}

	return 0;
}
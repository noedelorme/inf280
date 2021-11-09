#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> Node;
#define INFTY 20000000

void deleting(vector<Node>* Adj, vector<int>* parents, int node){
	for(auto p : parents[node]){
		for(auto& n : Adj[p]){
			if(n.second==node){
				n.first = INFTY;
			}
		}
		deleting(Adj, parents, p);
	}
}

int Dijkstra(vector<Node>* Adj, int* Dist, priority_queue<Node, vector<Node>, greater<Node>> Q, int N, int S, int D){
	vector<int> parents[N];
	fill_n(Dist, N, INFTY);
	Dist[S] = 0;
	Q.push({0,S});
	while (!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		for (auto tmp : Adj[u]){
			int v = tmp.second;
			int weight = tmp.first;
			if(Dist[v] == Dist[u] + weight){
				parents[v].push_back(u);
			}else if(Dist[v] > Dist[u] + weight){
				Dist[v] = Dist[u] + weight;
				parents[v].clear();
				parents[v].push_back(u);
				Q.push({Dist[v],v});
			}
		}
	}

	deleting(Adj, parents, D);

	return Dist[D];
}

int main(){

	int N, M, S, D;
	while(scanf("%i %i\n%i %i", &N, &M, &S, &D)==4){
		vector<Node> Adj[N];
		for(int i=0; i<M; i++){
			int from, to, w;
			scanf("%i %i %i\n", &from, &to, &w);
			Adj[from].push_back({w,to});
		}

		int Dist[N];
		priority_queue<Node, vector<Node>, greater<Node>> Q;

		Dijkstra(Adj, Dist, Q, N, S, D);
		int almost = Dijkstra(Adj, Dist, Q, N, S, D);

		if(almost>=INFTY){
			printf("-1\n");
		}else{
			printf("%i\n", almost);
		}
	}

	return 0;
}
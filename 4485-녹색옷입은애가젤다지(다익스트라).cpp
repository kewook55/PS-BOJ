#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

struct Info {
	int node, cost;
	
	bool operator < (const Info &ipt) const {
		return cost > ipt.cost;
	}
};

const int INF = 124 * 10 + 1;
int N, map[126][126], dist[126*126];
int dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 };
bool check[126 * 126];
vector<Info> adj[126 * 126];

int main(void) {
	ios::sync_with_stdio(NULL);
	cin.tie(NULL); cout.tie(NULL);
	
	int T = 1;
	while (true) {
		cin >> N;
		if (!N)break;
		
		for (int i = 0; i <= N*N; i++)adj[i].clear();
		memset(check, false, sizeof(check));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)cin >> map[i][j];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k], nx = j + dx[k];
					if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
					adj[i*N + j + 1].push_back({ ny*N + nx + 1, map[ny][nx] });
				}
			}
		}

		for (int i = 1; i <= N * N; i++)dist[i] = INF;
		
		priority_queue<Info> pq;
		pq.push({ 1, map[0][0] });
		dist[1] = map[0][0];
		
		while (!pq.empty()) {
			int node = pq.top().node, cost = pq.top().cost;
			pq.pop();
			if (check[node])continue;
			
			check[node] = true;

			for (Info &info : adj[node]) {
				int next = info.node, ncost = info.cost;
				if (dist[next] > dist[node] + ncost) {
					dist[next] = dist[node] + ncost;
					pq.push({ next ,dist[next] });
				}
			}
		}
		cout << "Problem " << T << ": " << dist[N*N] << "\n";
		++T;
	}
	
	return 0;
}
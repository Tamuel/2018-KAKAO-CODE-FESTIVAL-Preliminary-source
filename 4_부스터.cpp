#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <set>
#include <list>

using namespace std;

// 2018
// 4. 부스터
typedef struct disjointset {
	disjointset* parent;
	int rank;
} disjointset;

disjointset* makeDisSet() {
	disjointset* node = new disjointset();
	node->parent = node;
	node->rank = 0;
	return node;
}

disjointset* findDis(disjointset* set) {
	if (set->parent == set)
		return set;
	set->parent = findDis(set->parent);
	return set->parent;
}

void mergeDisSet(disjointset* set1, disjointset* set2) {
	disjointset* parent1 = findDis(set1);
	disjointset* parent2 = findDis(set2);

	if (parent1 != parent2) {  // Union by rank
		if (parent1->rank > parent2->rank) {
			parent2->parent = parent1;
		}
		else if (parent1->rank == parent2->rank) {
			parent2->parent = parent1;
			parent1->rank++;
		}
		else {
			parent1->parent = parent2;
		}
	}
}

void booster() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, Q;
	cin >> N >> Q;
	vector<vector<int>> checkPointsX(N);  // X 정렬
	vector<vector<int>> checkPointsY(N);  // Y 정렬
	vector<vector<int>> queries(Q);
	vector<bool> answer(Q);
	vector<disjointset*> nodes(N);
	typedef pair<int, pair<int, int>> pa;
	priority_queue<pa, vector<pa>, greater<pa>> pq;  // 좌표차, ID

	int x, y;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		checkPointsX[i] = vector<int>{ x, y, i + 1 };
		checkPointsY[i] = vector<int>{ y, x, i + 1 };
		nodes[i] = makeDisSet();
	}
	auto pred = [&](vector<int>& a, vector<int>& b) {
		return a[0] < b[0];
	};
	sort(checkPointsX.begin(), checkPointsX.end(), pred);
	sort(checkPointsY.begin(), checkPointsY.end(), pred);

	int start, end, X;
	for (int q = 0; q < Q; q++) {
		cin >> start >> end >> X;
		queries[q] = vector<int>{ X, start, end, q };
	}
	sort(queries.begin(), queries.end(), pred);

	for (int i = 0; i < checkPointsX.size() - 1; i++) {
		pq.push({
			abs(checkPointsX[i][0] - checkPointsX[i + 1][0]),
			{
				checkPointsX[i][2],
				checkPointsX[i + 1][2]
			}
		});
		pq.push({
			abs(checkPointsY[i][0] - checkPointsY[i + 1][0]),
			{
				checkPointsY[i][2],
				checkPointsY[i + 1][2]
			}
		});
	}

	for (auto q : queries) {
		X = q[0];
		start = q[1];
		end = q[2];

		if (findDis(nodes[start - 1]) != findDis(nodes[end - 1])) {
			while (!pq.empty()) {
				int t = pq.top().first;
				pair<int, int> p = pq.top().second;
				if (t > X) break;
				mergeDisSet(nodes[p.first - 1], nodes[p.second - 1]);
				pq.pop();
			}
		}
		answer[q[3]] = (findDis(nodes[start - 1]) == findDis(nodes[end - 1]));
	}

	for (bool a : answer)
		if (a)
			cout << "YES\n"; // endl 넣으면 시간 초과됨...
		else
			cout << "NO\n";
}

int main() {
	booster();

	return 0;
}
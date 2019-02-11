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
// 5. ���� ��õ
typedef long long dtype;
// for Fenwick tree
// https://www.acmicpc.net/blog/view/21
dtype mergedSum(vector<dtype>& tree, int i) {
	dtype ans = 0;
	while (i > 0) {
		ans += tree[i];
		i -= (i & -i);
	}
	return ans;
}

void update(vector<dtype>& tree, int i, dtype val) {
	while (i < tree.size()) {
		tree[i] += val;
		i += (i & -i);
	}
}

typedef struct dfsNode {
	int parent;
	vector<int> childs;
} dfsNode;

int dfs(int index, vector<dfsNode>& graph, vector<int>& affects, vector<int>& dfsTree,
	vector<int>& dfsIndices, vector<bool>& visited) {

	visited[index] = true;
	dfsIndices[index] = dfsTree.size();
	dfsTree.push_back(index);

	int affect = 1;
	for (int child : graph[index].childs)
		if (!visited[child])
			affect += dfs(child, graph, affects, dfsTree, dfsIndices, visited);

	affects[index] = affect;
	return affect;
}

void musicRecommend() {
	int N, K;
	dtype J;
	scanf_s("%d %d %lli", &N, &K, &J);

	vector<dfsNode> nodes(N + 1); // DFS�� ���� ��� ��ü��
	vector<vector<int>> singerSongs(N + 1); // ���� �� �뷡
	vector<int> singers(N + 1); // �뷡 �� ����
	vector<int> dfsIndices(N + 1); // DFS Ʈ���� �ε���
	vector<bool> visited(N + 1); // DFS ��
	vector<int> dfsTree(1); // DFS Ʈ��
	vector<int> affects(N + 1, 1); // �ڱ� �ڽź��� ���� �� ������ ���� ��ġ����

	// Tree
	for (int i = 2; i <= N; i++) { // O(N)
		int parent;
		scanf_s("%d", &parent);
		nodes[i].parent = parent;
		nodes[parent].childs.push_back(i);
	}

	// DFS
	dfs(1, nodes, affects, dfsTree, dfsIndices, visited);

	// Singer
	for (int i = 1; i <= N; i++) {
		int singer;
		scanf_s("%d", &singer);
		singerSongs[singer].push_back(i);
		singers[i] = singer;
	}

	// Queries
	vector<pair<int, pair<int, dtype>>> queries(K + 1); // ����
	int T, P;
	dtype S;
	for (int q = 1; q <= K; q++) {
		scanf_s("%d %d %lli", &T, &P, &S);
		queries[q] = { T,{ P, S } };
	}
	sort(queries.begin(), queries.end());

	// Parallel binary search
	vector<dtype> scores(N + 1); // ��� �����ϱ⿡�� �ʹ� ������ ŭ (100000 * 100000 * 8) = 75�Ⱑ ����
	vector<pair<int, int>> boundaries(N + 1); // ���� ���� �˻��� ���� ����, ����
	for (int i = 1; i <= N; i++)
		boundaries[i] = { (singerSongs[i].size() > 0 ? 1 : K + 1), K + 1 }; // ���������� ������ K + 1

	vector<queue<int>> checkPerQuery(K + 1); // ������, � ������ üũ�ؾ��ϴ���
	while (true) {
		bool stop = true;
		for (int i = 1; i <= N; i++)
			if (boundaries[i].first != boundaries[i].second) {
				checkPerQuery[(boundaries[i].first + boundaries[i].second) / 2].push(i);
				stop = false;
			}
		if (stop) break;

		for (int q = 1; q <= K; q++) {
			int nodeId = queries[q].second.first;
			dtype score = (queries[q].second.second / ((dtype)affects[nodeId])); // ���� ��ŭ��
																				 // ������ ������Ʈ
			update(scores, dfsIndices[nodeId], score);
			update(scores, dfsIndices[nodeId] + affects[nodeId], -score);

			while (checkPerQuery[q].size() != 0) {
				int singer = checkPerQuery[q].front(); checkPerQuery[q].pop();
				dtype goal = (dtype)J * (dtype)(singerSongs[singer].size());
				dtype sum = 0;
				for (int song : singerSongs[singer]) {
					sum += mergedSum(scores, dfsIndices[song]);
					if (sum > goal) break;
				}

				if (sum > goal) boundaries[singer].second = q;
				else boundaries[singer].first = q + 1;
			}
		}

		fill(scores.begin(), scores.end(), 0);
	}

	for (int i = 1; i <= N; i++) {
		if (boundaries[singers[i]].first <= K)
			printf("%d\n", queries[boundaries[singers[i]].first].first);
		else
			printf("-1\n");
	}
}

int main() {
	musicRecommend();

	return 0;
}
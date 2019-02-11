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
// 1. ªÛ±› «Â≈Õ
int calc(int rank, vector<int> peoples, vector<int> prizes) {
	if (rank == 0)
		return 0;
	int sum = 0;
	for (int i = 0; i < peoples.size(); i++) {
		rank -= peoples[i];
		if (rank <= 0) {
			sum += prizes[i];
			break;
		}
	}
	return sum;
}
void prizeHunter() {
	vector<vector<int>> input = {
		{ 8, 4 },
		{ 13, 19 },
		{ 8, 10 },
		{ 18, 18 },
		{ 8, 25 },
		{ 13, 16 }
	};
	int a, b;
	for (auto inp : input) {
		a = inp[0], b = inp[1];
		int sum = 0;
		sum += calc(
			a,
			{ 1, 2, 3, 4, 5, 6 },
			{ 500, 300, 200, 50, 30, 10 });
		sum += calc(
			b,
			{ 1, 2, 4, 8, 16 },
			{ 512, 256, 128, 64, 32 });
		cout << sum * 10000 << endl;
	}
}

int main() {
	prizeHunter();

	return 0;
}
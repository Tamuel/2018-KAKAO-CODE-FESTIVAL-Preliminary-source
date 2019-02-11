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
// 2. 인형들
// accumulate 와 inner_product에 (ld)0 로 형변환 안하면 오버플로우 발생
typedef long double ld;

void dolls() {
	int N = 10, k = 3;
	vector<ld> preference = { 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };

	ld min = 0;
	for (int _k = k; _k <= N; _k++) {
		ld sum = accumulate(preference.begin(), preference.begin() + _k - 1, (ld)0);
		ld sqrSum = inner_product(preference.begin(), preference.begin() + _k - 1, preference.begin(), (ld)0);
		for (int i = 0; i <= preference.size() - _k; i++) {
			sum -= i > 0 ? preference[i - 1] : 0;
			sqrSum -= i > 0 ? preference[i - 1] * preference[i - 1] : 0;
			sum += preference[i + _k - 1];
			sqrSum += preference[i + _k - 1] * preference[i + _k - 1];
			ld stdDeviation = sqrtl((sqrSum / _k) - (sum / _k) * (sum / _k));
			if ((_k == k && i == 0) || min > stdDeviation) min = stdDeviation;
		}
	}
	cout.precision(11);
	cout << min << endl;
}

int main() {
	dolls();

	return 0;
}
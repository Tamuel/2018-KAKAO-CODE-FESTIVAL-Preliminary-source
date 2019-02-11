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
// 6. 프로도의 100일 준비
// 원점시작, 히스토그램 모양

typedef long long ll;

typedef struct point {
	ll x;
	ll y;
	bool operator==(const point& pts) {
		return (x == pts.x && y == pts.y);
	}
} point;

// Slope = point.y, Basis = -point.x * point.y
double crossXpts(point& pts1, point& pts2, bool right) {
	// Basis가 음수이므로 반대로
	if (right)
		return ((double)(pts2.x * pts2.y - pts1.x * pts1.y) / (double)(pts1.y - pts2.y));
	else
		return ((double)(pts1.x * pts1.y - pts2.x * pts2.y) / (double)(pts1.y - pts2.y));
}

// Convex Hull Trick
// 기울기가 낮은 것부터 높은 것 순서대로 넣어야함
void insertCht(deque<point>& stack, deque<point>& persistent, point& pts, bool right) {
	if (stack.size() < 2) {
		stack.push_back(pts);
	}
	else {
		auto be = stack.end() - 1;
		while (stack.size() > 1 && crossXpts(pts, *be, right) < crossXpts(*be, *(be - 1), right)) {
			persistent.push_back(stack.back());
			stack.pop_back();
			be = stack.end() - 1;
		}
		stack.push_back(pts);
	}
}

void removePts(list<point>& lists, deque<point>& cht, deque<point>& per, int basisY, bool right) {
	if (lists.size() != 0) {
		while (lists.size() > 0 && lists.front().y >= basisY) {
			if (cht.size() > 0 && lists.front() == cht.back())
				cht.pop_back();
			if (per.size() > 0 && lists.front() == per.back())
				per.pop_back();
			lists.pop_front();
		}

		if (per.size() > 0) {
			stack<point> temp;
			while (per.size() > 0 && per.back().y >= lists.front().y) {
				temp.push(per.back());
				per.pop_back();
			}
			while (temp.size() > 0) {
				insertCht(cht, per, temp.top(), right);
				temp.pop();
			}
		}
	}
}

bool searchSide(list<point>& lists, list<point>::iterator& begin,
	list<point>::iterator& last, vector<point>& points, int i, int j, int firstSize) {

	if (firstSize > 0 && points[j].y <= begin->y) {
		last->x = points[j].x;
		return true;
	}
	if (points[j].y < last->y) {
		last->x = points[j].x;
		last = lists.insert(begin, points[j]);
	}
	return false;
}

int binarySearch(deque<point>& cht, int goal, bool right) {
	int lo = 0, hi = cht.size() - 1, center;
	if (cht.size() > 1)
		while (lo != hi) {
			center = (lo + hi) / 2;
			if (crossXpts(cht[center], cht[center + 1], right) < goal)
				lo = center + 1;
			else hi = center;
		}

	return lo;
}

void bruteForce(list<point>& left, list<point>& right, ll& lMax, ll& rMax, int currentX) {
	long curSize;

	// 좌측 Max
	lMax = 0;
	for (point& l : left) {
		curSize = l.y * (currentX - l.x);
		if (lMax < curSize)
			lMax = curSize;
	}

	// 우측 Max
	rMax = 0;
	for (point& r : right) {
		curSize = r.y * (r.x - currentX);
		if (rMax < curSize)
			rMax = curSize;
	}
}

void anniversary() {
	int N;
	vector<point> points;
	scanf_s("%d", &N);
	int x, y;
	for (int i = 0; i < N; i++) {
		scanf_s("%d %d", &x, &y);
		points.push_back({ x, y });
	}

	// 최댓값 탐색
	list<point> left, right;
	deque<point> leftCht, rightCht, leftPer, rightPer;
	list<point>::iterator last, leftBegin, rightBegin;
	left.push_back(points[0]);
	right.push_back(*(points.end() - 1));
	ll lMax, rMax, currentX, max = 0, curSize;

	for (int i = 2; i < N - 2; i += 2) {
		// 이전 것 중에 필요 없는 점 삭제
		removePts(left, leftCht, leftPer, points[i].y, false);
		removePts(right, rightCht, rightPer, points[i + 1].y, true);

		currentX = points[i].x;

		// 좌측 탐색
		leftBegin = left.begin(); curSize = left.size();
		last = left.insert(leftBegin, points[i]);
		for (int j = i - 2; j >= 0; j -= 2)
			if (searchSide(left, leftBegin, last, points, i, j, curSize)) break;

		// 우측 탐색
		rightBegin = right.begin(); curSize = right.size();
		last = right.insert(rightBegin, points[i + 1]);
		for (int j = i + 3; j < N; j += 2)
			if (searchSide(right, rightBegin, last, points, i, j, curSize)) break;


		// Convex Hull Trick
		while (leftBegin != left.begin())
			insertCht(leftCht, leftPer, (*--leftBegin), false);

		while (rightBegin != right.begin())
			insertCht(rightCht, rightPer, (*--rightBegin), true);

		int maxIdx = binarySearch(leftCht, currentX, false);
		lMax = leftCht[maxIdx].y * (currentX - leftCht[maxIdx].x);

		maxIdx = binarySearch(rightCht, currentX, true);
		rMax = rightCht[maxIdx].y * (rightCht[maxIdx].x - currentX);

		if (max < lMax + rMax)
			max = lMax + rMax;
	}

	printf("%lli\n", max);
}

int main() {
	anniversary();

	return 0;
}
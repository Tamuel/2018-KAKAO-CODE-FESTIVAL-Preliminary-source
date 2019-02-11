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
// 3. 숏코딩
// 조건문 S
// 변수 = 영어 소문자, 대문자
// 정수 = -10^9 ~ 10^9, 0은 하나, 0으로 시작하는 수는 0 뿐임
// 단항식 = 변수 or 정수
// 논리식 = 같음 (==) or 다름 (!=)
// 논리식의 좌변과 우변은 오직 단항식만
// && 으로 논리식 연결 가능, 모두 true 일 때 true, 아니면 false
// S와 동치이면서 가장 짧은 S' 만들기

enum type { INT, VAR };

struct formula {
	string key1;
	type type1;
	string key2;
	type type2;
	bool equal;

	bool same(struct formula* f) {
		if (f->key1 == key1 && f->key2 == key2)
			return true;
		else if (f->key1 == key2 && f->key2 == key1)
			return true;
		else
			return false;
	}
};
typedef struct formula form;

bool isNumber(string s) {
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '-')
		return true;
	else
		return false;
}

type getType(string s) {
	if (isNumber(s))
		return INT;
	else
		return VAR;
}

void shortCoding() {
	string S = "festival==kakao&&festival==2018&&haha==123456&&hoho!=123456";

	vector<string> dividedS;
	int start = 0;
	for (int i = 0; i < S.size(); i++) {
		if (S[i] == '&') {
			dividedS.push_back(S.substr(start, i - start));
			start = i + 2;
			i++;
		}
		else if (i == S.size() - 1)
			dividedS.push_back(S.substr(start, i - start + 1));
	}

	int keyLast = 0;
	vector<form> formulas;
	map<string, int> keyId;
	map<int, set<string>> idKeys;

	// Parsing
	for (string& s : dividedS) {
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '!' || s[i] == '=') {
				string key1 = s.substr(0, i);
				string key2 = s.substr(i + 2);
				bool equal = (s[i] == '=' ? true : false);
				formulas.push_back({ key1, getType(key1), key2, getType(key2), equal });
				break;
			}
		}
	}

	if (formulas.size() == 1) {
		if (formulas[0].type1 == INT && formulas[0].type2 == INT) {
			if (stoi(formulas[0].key1) == stoi(formulas[0].key2)) {
				if (formulas[0].equal)
					cout << "0==0" << endl;
				else
					cout << "1==0" << endl;
				return;
			}
			else {
				if (formulas[0].equal)
					cout << "0==1" << endl;
				else
					cout << "0==0" << endl;
				return;
			}
		}
		else {
			cout << S << endl;
			return;
		}
	}

	// Parse formulas
	for (form& f : formulas) {
		if (f.equal) {
			bool key1Find = (keyId.find(f.key1) != keyId.end());
			bool key2Find = (keyId.find(f.key2) != keyId.end());
			if (!key1Find && !key2Find) {
				keyId[f.key1] = keyLast;
				keyId[f.key2] = keyLast;
				idKeys[keyLast] = set<string>{ f.key1, f.key2 };
				keyLast++;
			}
			else if (key1Find && !key2Find) {
				idKeys[keyId[f.key1]].insert(f.key2);
				keyId[f.key2] = keyId[f.key1];
			}
			else if (!key1Find && key2Find) {
				idKeys[keyId[f.key2]].insert(f.key1);
				keyId[f.key1] = keyId[f.key2];
			}
			else if (key1Find && key2Find) {
				if (keyId[f.key1] != keyId[f.key2]) {
					int temp = keyId[f.key2];
					idKeys[keyId[f.key1]].insert(idKeys[keyId[f.key2]].begin(), idKeys[keyId[f.key2]].end());
					for (auto& i : idKeys[keyId[f.key2]])
						keyId[i] = keyId[f.key1];
					idKeys.erase(temp);
				}
			}
		}
	}

	for (form& f : formulas) {
		if (!f.equal) {
			bool key1Find = (keyId.find(f.key1) != keyId.end());
			bool key2Find = (keyId.find(f.key2) != keyId.end());
			if (!key1Find && !key2Find) {
				keyId[f.key1] = keyLast;
				keyId[f.key2] = keyLast + 1;
				idKeys[keyLast] = set<string>{ f.key1 };
				idKeys[keyLast + 1] = set<string>{ f.key2 };
				keyLast += 2;
			}
			else if (key1Find && !key2Find) {
				keyId[f.key2] = keyLast;
				idKeys[keyLast] = set<string>{ f.key2 };
				keyLast++;
			}
			else if (!key1Find && key2Find) {
				keyId[f.key1] = keyLast;
				idKeys[keyLast] = set<string>{ f.key1 };
				keyLast++;
			}
			else if (key1Find && key2Find) {
				if (keyId[f.key1] == keyId[f.key2]) {
					cout << "1==0" << endl;
					return;
				}
			}
		}
	}

	// False
	map<int, bool> checkInteger;
	for (auto& i : idKeys) {
		set<string>& keys = i.second;
		checkInteger[i.first] = false;
		int countInteger = 0;
		for (string k : keys) {
			if (isNumber(k)) {
				checkInteger[i.first] = true;
				countInteger++;
			}
		}
		if (countInteger >= 2) {
			cout << "1==0" << endl;
			return;
		}
	}

	map<int, multimap<int, string>> idMaps; // For sorting
	for (auto& i : idKeys)
		for (auto& j : i.second)
			idMaps[i.first].insert(pair<int, string>(j.size(), j));

	vector<form> newFormulas;
	for (auto& s : idMaps) {
		multimap<int, string>& pairs = s.second;
		if (pairs.size() > 2) {
			string shortest = pairs.begin()->second;
			for (multimap<int, string>::iterator p = (++pairs.begin()); p != pairs.end(); p++)
				newFormulas.push_back({ p->second, getType(p->second), shortest, getType(shortest), true });
		}
		else if (pairs.size() == 2) {
			string key1 = pairs.begin()->second;
			string key2 = (++pairs.begin())->second;
			newFormulas.push_back({ key1, getType(key1), key2, getType(key2), true });
		}
	}
	set<pair<int, int>> check;
	for (form& f : formulas) {
		if (!f.equal) {
			if (keyId[f.key1] == keyId[f.key2]) {
				cout << "1==0" << endl;
				return;
			}
			if (checkInteger[keyId[f.key1]] && checkInteger[keyId[f.key2]])
				continue;

			string key1 = idMaps[keyId[f.key1]].begin()->second;
			string key2 = idMaps[keyId[f.key2]].begin()->second;
			int id1 = keyId[f.key1];
			int id2 = keyId[f.key2];
			if (check.insert(pair<int, int>(id1 < id2 ? id1 : id2, id1 < id2 ? id2 : id1)).second)
				newFormulas.push_back({ key1, getType(key1), key2, getType(key2), false });
		}
	}

	if (newFormulas.size() >= 1) {
		string output = "";
		for (vector<form>::iterator f = newFormulas.begin(); f != newFormulas.end(); f++) {
			string last = (f == newFormulas.end() - 1 ? "" : "&&");
			string connect = (f->equal ? "==" : "!=");
			output += f->key1 + connect + f->key2 + last;
		}
		cout << output << endl;
	}
	else {
		cout << "0==0" << endl;
	}
}

int main() {
	shortCoding();

	return 0;
}
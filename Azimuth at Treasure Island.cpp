// https://www.codeabbey.com/index/task_view/azimuth-at-treasure-island
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <cmath>
#include <cassert>
#include <limits>
#include <numeric>
#include <tuple>
#include <regex> 

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "1.0"

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

vector<vector<int>> Parse(vector<string> raw);
tuple<int, int> Travel(vector<vector<int>> data);

int main() {
	auto t1 = high_resolution_clock::now();
	cout << "Azimuth at Treasure Island v" << VERSION << "!\n\n";
	//string path = "Test.txt";
	string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	//printVector(raw_data);
	/***********************/

	vector<vector<int>> data = Parse(raw_data);
	int X, Y;
	tie(X, Y) = Travel(data);
	cout << "\nSolution: " << X << " " << Y << endl;

	/***********************/
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	cout << "Execution time: " << ms_int.count() << " ms" << endl;
}

tuple<int, int> Travel(vector<vector<int>> data) {
	float X = 0.0;
	float Y = 0.0;
	for (auto command : data) {
		X += float(command[0]) * sin(to_radians(float(command[1])));
		Y += float(command[0]) * cos(to_radians(float(command[1])));
	}
	return make_tuple(round(X), round(Y));
}

vector<vector<int>> Parse(vector<string> raw) {
	vector<vector<int>> data;
	regex pattern("\\d+");

	for (auto line : raw) {
		vector<int> dir;
		smatch m;

		while (regex_search(line, m, pattern)) {
			dir.push_back(stoi(m[0].str().c_str()));
			line = m.suffix();
		}
		if (dir.size() > 0) data.push_back(dir);
	}

	return data;
}
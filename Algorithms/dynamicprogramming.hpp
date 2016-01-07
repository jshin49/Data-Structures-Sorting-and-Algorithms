#include <vector>

using namespace std;

int fibonacci(int n) {
	vector<int> vec;
	vec.resize(n);
	vec[0] = 1;
	if (n > 1) vec[1] = 1;

	for (int i = 2; i < n; ++i) {
		vec[i] = vec[i - 1] + vec[i - 2];
	}

	return vec[n - 1];
}

int max_sub_array(vector<int> vec) {
	// Dynamic Programming O(n)

	int temp_max = vec[0];
	int max_so_far = temp_max;
	for (int i = 1; i < vec.size(); ++i) {
		temp_max = max(vec[i], temp_max + vec[i]);
		max_so_far = max(max_so_far, temp_max);
	}
	return max_so_far;
}
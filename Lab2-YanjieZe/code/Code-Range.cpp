#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
You need to complete the implementation of
binary_search_for_m and binary_search_for_n.
*/

int binary_search_for_m(vector<long>& sum, long sum_i, int LOWER, int low, int high) {
	/*
	Find the smallest m in [low, high - 1]
	such that sum[m] - sum_i >= LOWER
	using binary search. If not found,
	return high.
	*/
	int mid = (low+high)/2;
	if(mid==low)
		if(sum[mid]-sum_i>=LOWER)
			return mid;
		else 
			return high;
	
	if(sum[mid]-sum_i==LOWER)
		return mid;
	else if(sum[mid]-sum_i<LOWER)
		return binary_search_for_m(sum, sum_i, LOWER, mid+1, high);
	else 
		return binary_search_for_m(sum, sum_i, LOWER, low, mid);
}

int binary_search_for_n(vector<long>& sum, long sum_i, int UPPER, int low, int high) {
	/*
	Find the smallest n in [low, high - 1]
	such that sum[n] - sum_i > UPPER
	using binary search. If not found,
	return high.
	*/
	int mid = (low+high)/2;
	if(mid==low)
		if(sum[mid]-sum_i>UPPER)
			return mid;
		else 
			return high;
	
	if(sum[mid]-sum_i<=UPPER)
		return binary_search_for_n(sum, sum_i, UPPER, mid+1, high);
	else 
		return binary_search_for_n(sum, sum_i, UPPER, low, mid);
}

int merge_count(vector<long>& sum, int low, int high, int LOWER, int UPPER) {
	int mid = (low + high) / 2;
	if (mid == low)
		return 0;
	int count = merge_count(sum, low, mid, LOWER, UPPER)
		+ merge_count(sum, mid, high, LOWER, UPPER);
	int m_low = mid, m_high = high, n_low = mid, n_high = high;
	for (int i = low; i < mid; i++) {
		int m = binary_search_for_m(sum, sum[i], LOWER, m_low, m_high);
		int n = binary_search_for_n(sum, sum[i], UPPER, n_low, n_high);
		count += n - m;
	}
	sort(sum.begin() + low, sum.begin() + high); // You may assume the time complexity here is O(nlog(n)).
	return count;
}

int main() {
	int N, LOWER, UPPER;
	vector<int> A;
	vector<long> sum(1, 0);	// sum[i]: sum of the first i elements in A

	cin >> N >> LOWER >> UPPER;
	for (int tmp, i = 0; i < N; i++) {
		cin >> tmp;
		A.push_back(tmp);
		sum.push_back(sum.back() + A.back());
	}

	cout << merge_count(sum, 0, N + 1, LOWER, UPPER) << endl;

	return 0;
}

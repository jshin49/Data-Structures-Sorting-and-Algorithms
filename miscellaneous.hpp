//
//
//long long mergeAndCount(vector<int>& vec, int p, int q, int r) {
//	long long count = 0;
//
//	//if (r - p == 1) {
//	//	if (vec[p] > vec[r]) {
//	//		int temp = vec[p];
//	//		vec[p] = vec[r];
//	//		vec[r] = temp;
//	//		++count;
//	//	}
//	//	return count;
//	//}
//
//	vector<int> L, R;
//	for (int i = p; i <= q; ++i) L.push_back(vec[i]);
//	for (int j = q + 1; j <= r; ++j) R.push_back(vec[j]);
//
//	L.push_back(numeric_limits<int>::max()); //sentinel element
//	R.push_back(numeric_limits<int>::max());
//
//	int i = 0, j = 0;
//
//	for (int k = p; k <= r; ++k) {
//		if (L[i] <= R[j]) {
//			vec[k] = L[i];
//			++i;
//		}
//		else {
//			if (L[i] != L.back() && R[j] != R.back())
//				count += q - p + 1 - i;
//			vec[k] = R[j];
//			++j;
//		}
//	}
//	return count;
//	//vector<int> L, R;
//	//for (int a = p; a <= q; ++a) L.push_back(vec[a]);
//	//for (int b = q + 1; b <= r; ++b) R.push_back(vec[b]);
//
//	//L.push_back(numeric_limits<int>::max()); //sentinel element
//	//R.push_back(numeric_limits<int>::max());
//
//	//int i = 0, j = 0;
//
//	//for (int k = p; k <= r; ++k) {
//	//	if (L[i] <= R[j]) {
//	//		vec[k] = L[i];
//	//		++i;
//	//	}
//	//	else {
//	//		if (L[i] != L.back() && R[j] != R.back())
//	//			count += q - p + 1 - i;
//	//		vec[k] = R[j];
//	//		++j;
//	//	}
//	//}
//	//return count;
//}
//
//long long merger(vector<int>& vec, int left, int mid, int right)
//{
//	int i, j, k;
//	vector<int> temp = vec;
//	long long inv_count = 0;
//
//	i = left; /* i is index for left subarray*/
//	j = mid;  /* i is index for right subarray*/
//	k = left; /* i is index for resultant merged subarray*/
//	while ((i <= mid - 1) && (j <= right))
//	{
//		if (vec[i] <= vec[j])
//		{
//			temp[k++] = vec[i++];
//		}
//		else
//		{
//			temp[k++] = vec[j++];
//
//			/*this is tricky -- see above explanation/diagram for merge()*/
//			inv_count = inv_count + (mid - i);
//		}
//	}
//
//	/* Copy the remaining elements of left subarray
//	(if there are any) to temp*/
//	while (i <= mid - 1)
//		temp[k++] = vec[i++];
//
//	/* Copy the remaining elements of right subarray
//	(if there are any) to temp*/
//	while (j <= right)
//		temp[k++] = vec[j++];
//
//	/*Copy back the merged elements to original array*/
//	for (i = left; i <= right; i++)
//		vec[i] = temp[i];
//
//	return inv_count;
//}
//
//long long inversion(vector<int>& vec, int p, int r) {
//	//vector<pair<int, int>> pairs;
//	long long count = 0;
//
//	// Brute Force
//	// 2407905288
//
//	//for (int i = 0; i < vec.size(); ++i)
//	//	for (int j = i + 1; j < vec.size(); ++j)
//	//		if (vec[i] > vec[j])
//	//			++count;
//
//	// Divide and Conquer
//
//	if (p < r) {
//		int q = (p + r) / 2;
//		count += inversion(vec, p, q);
//		count += inversion(vec, q + 1, r);
//		count += mergeAndCount(vec, p, q, r);
//	}
//
//	return count;
//}
//
//int max(int a, int b) {
//	return b > a ? b : a;
//}
//
//int max(int a, int b, int c) {
//	return max(max(a, b), c);
//}
//
//// Find the maximum possible sum in arr[] auch that arr[m] is part of it
//pair<pair<int, int>, int> maxCrossingSum(vector<int> vec, int l, int m, int r)
//{
//	// Include elements on left of mid.
//	int leftIndex = l;
//	int sum = 0;
//	int left_sum = INT_MIN;
//	for (int i = m; i >= l; --i) {
//		sum = sum + vec[i];
//		if (sum > left_sum) {
//			left_sum = sum;
//			leftIndex = i;
//		}
//	}
//
//	// Include elements on right of mid
//	int rightIndex = r;
//	sum = 0;
//	int right_sum = INT_MIN;
//	for (int j = m + 1; j <= r; ++j) {
//		sum = sum + vec[j];
//		if (sum > right_sum) {
//			right_sum = sum;
//			rightIndex = j;
//		}
//	}
//
//	// Return sum of elements on left and right of mid
//	return make_pair(make_pair(leftIndex, rightIndex), left_sum + right_sum);
//}
//
//// Returns sum of maxium sum subarray in aa[l..h]
//pair<pair<int, int>, int> maxSubArraySum(vector<int> vec, int l, int r)
//{
//	// Base Case: Only one element
//	if (l == r)
//		return make_pair(make_pair(l, r), vec[l]);
//
//	// Find middle point
//	int m = (l + r) / 2;
//
//	/* Return maximum of following three possible cases
//	a) Maximum subarray sum in left half
//	b) Maximum subarray sum in right half
//	c) Maximum subarray sum such that the subarray crosses the midpoint */
//	pair<pair<int, int>, int> left = maxSubArraySum(vec, l, m);
//	pair<pair<int, int>, int> right = maxSubArraySum(vec, m + 1, r);
//	pair<pair<int, int>, int> mid = maxCrossingSum(vec, l, m, r);
//	int maxSum = max(left.second, right.second, mid.second);
//
//	return make_pair(mid.first, maxSum);
//}
//
//long long maxSubArray(vector<int> vec) {
//	// Dynamic Programming O(n)
//
//	long long tempMax = vec[0];
//	long long maxSoFar = tempMax;
//	for (int i = 1; i < vec.size(); ++i) {
//		tempMax = max(vec[i], tempMax + vec[i]);
//		maxSoFar = max(maxSoFar, tempMax);
//	}
//	return maxSoFar;
//}

#include "prime_judge.h"

#include <iostream>
#include <numeric>
#include <algorithm>

template <typename Iterator>
size_t count_seq(Iterator first, Iterator last, const prime_judge &judge)
{
	return std::count_if(first, last, judge);
}

int main()
{
	using namespace std;
	prime_judge judge(1000);

	vector<int> data(100000);
	iota(data.begin(), data.end(), 1); // data を 1, 2 ... 99999 で埋める

	size_t count = count_seq(data.begin(), data.end(), judge);
	cout << count << " primes found.\n";
}

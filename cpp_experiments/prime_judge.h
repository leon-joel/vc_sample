#pragma once

#include <algorithm>
#include <vector>
#include <stdexcept>

class prime_judge
{
  private:
	std::vector<int> primes_;

  public:
	prime_judge(int N)
	{
		primes_.push_back(2);
		// 奇数 3, 5, 7 ... に対し
		for (int n = 3; n <= N; n += 2)
		{
			// primes＿の中に n を割り切る数がなければ
			if (std::none_of(primes_.begin(), primes_.end(),
							 [n](int p) { return n % p == 0; }))
			{
				// nは素数だからprimes_に追加する
				primes_.push_back(n);
			}
		}
	}

	// nが素数ならtrueを返す
	bool operator()(int n) const
	{
		if (n > primes_.back() * primes_.back())
		{
			throw std::domain_error("too big to determine.");
		}
		if (n < 2)
			return false;
		return binary_search(primes_.begin(), primes_.end(), n) || std::none_of(primes_.begin(), primes_.end(),
																				[n](int p) { return n % p == 0; });
	}
};

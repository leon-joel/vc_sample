#include "prime_judge.h"
#include "measure.h"

#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>

/*
 * 順次処理
 */
template <typename Iterator>
size_t count_seq(Iterator first, Iterator last, const prime_judge &judge)
{
	return std::count_if(first, last, judge);
}

/*
 * 自前でスレッド分割
 */
#include <thread>
#include <future>
#include <iterator>

template <typename Iterator>
size_t count_par_byhand(Iterator first, Iterator last, const prime_judge &judge)
{
	// 物理的に並行動作可能なスレッド数
	unsigned int num_threads = std::thread::hardware_concurrency();

	// 1つのスレッドが受け持つtask数
	size_t step = std::distance(first, last) / num_threads;

	std::vector<std::future<size_t>> futures(num_threads);
	auto count_prime = [&](Iterator f, Iterator l) -> size_t {
		return std::count_if(f, l, judge);
	};

	Iterator tfirst = first;
	Iterator tlast;
	for (unsigned int i = 0; i < num_threads; ++i)
	{
		tlast = (i + 1 == num_threads) ? last : std::next(tfirst, step);
		futures[i] = std::async(count_prime, tfirst, tlast); // スレッド起動
		tfirst = tlast;
	}

	// 各スレッドで求めた数を積算する
	size_t count = 0;
	for (auto &fut : futures)
	{
		count += fut.get();
	}
	return count;
}

/*
 * Parallel Patterns Library
 */
// #include <ppl.h>
// #include <atomic>

// template <typename Iterator>
// size_t count_par_ppl(Iterator first, Iterator last, const prime_judge &judge)
// {
// 	std::atomic<size_t> count = 0;
// 	concurrency::parallel_for_each(first, last,
// 								   [&](int n) { // nが素数ならcount+1
// 									   if (judge(n))
// 									   {
// 										   ++count;
// 									   }
// 								   });
// 	return count;
// }

/*
 * C++17 parallel algorithms
 */
#include <execution>

template <typename Iterator>
size_t count_par_cpp17(Iterator first, Iterator last, const prime_judge &judge)
{
	return count_if(std::execution::par, first, last, judge);
}

/*--------------------------------------------------*/

void run()
{
	using namespace std;
	prime_judge judge(1000);

	vector<int> data(100000);
	iota(data.begin(), data.end(), 1);

	size_t count;
	long long par_dur;
	long long seq_dur;
	auto percent_change = [](long long o, long long n) { return (o - n) * 100 / n; };

	cout << "sequential:             ";
	seq_dur =
		measure([&]() {
			count = count_seq(data.begin(), data.end(), judge);
		});
	cout << count << " primes found in " << seq_dur << "[us]\n";

	cout << "parallelism by hand:    ";
	par_dur = measure([&]() {
		count = count_par_byhand(data.begin(), data.end(), judge);
	});
	cout << count << " primes found in " << par_dur << "[us] "
		 << setw(3) << percent_change(seq_dur, par_dur) << "%\n";

	// cout << "Parallel Patterns Lib.: ";
	// par_dur = measure([&]() {
	// 	count = count_par_ppl(data.begin(), data.end(), judge);
	// });
	// cout << count << " primes found in " << par_dur << "[us] "
	// 	 << setw(3) << percent_change(seq_dur, par_dur) << "%\n";

	cout << "c++17 parallel algo.:   ";
	par_dur = measure([&]() {
		count = count_par_cpp17(data.begin(), data.end(), judge);
	});
	cout << count << " primes found in " << par_dur << "[us] "
		 << setw(3) << percent_change(seq_dur, par_dur) << "%\n";

	cout << endl;
}

int main()
{
	run();
	run();
	run();
	run();
	run();
	run();
	run();
	run();
	run();
	run();
}

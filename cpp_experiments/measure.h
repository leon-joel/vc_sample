#pragma once
#include <chrono>

template<typename Function>
long long measure(Function fun, int repeat =1) {
  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  while ( repeat-- ) fun();
  auto stop = high_resolution_clock::now();
  return duration_cast<microseconds>(stop - start).count();
}

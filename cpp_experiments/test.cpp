#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class MyLargeClass {
  int size = 0;
  char* ptr;
public:
  MyLargeClass() { cout << "ctor" << endl; };
  MyLargeClass(int size) {
    cout << "ctor2" << endl;
    ptr = new char[size];
  }
  MyLargeClass(const MyLargeClass& rhs){
    cout << "copy ctor" << endl;
    size = rhs.size;
    std::memcpy(ptr, rhs.ptr, sizeof(char) * size);
  }
  MyLargeClass(MyLargeClass&& rhs) noexcept {
    cout << "move ctor" << endl;
    size = rhs.size;
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
  }
  ~MyLargeClass() {
    cout << "dtor" << endl;
    delete ptr;
  }
};

int main() {
  cout << "test" << endl;
  vector<MyLargeClass> v;
  // 2要素分のメモリーが確保されるだけで、要素はまだ入っていない
  // v.reserve(2);

  // 最初から2要素がセットされる
  // 最初に MyLargeClass(2) で1つ作って、これを2回コピーし、最初の1個をdestructする
  v.resize(2, 2);

  // これだと push_back を2回行ったのと同じことなので、reserveしてemplaceするほうが効率がいい
  // vector<MyLargeClass> v { 1, 2 };

  // v.emplace_back(1); // ctor しか走らない
  // v.emplace_back(1);

  // v.push_back({1});  // ctor -> move -> dtor が走る
  // v.push_back({1});

  cout << "v.count: " << v.size() << endl;
  v.pop_back();
}

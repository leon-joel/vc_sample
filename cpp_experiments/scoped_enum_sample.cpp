#include <iostream>

class FooBar {
  
public:
  // unscoped enum （従来からあるenumとほぼ同じ）
  enum Foo
  {
      none,        // 0
      symbolA,     // 1
      symbolB      // 2
  };

  // scoped enum （C++11から）
  enum struct Bar
  {
      None=10,     // 10
      bar1,        // 11
      bar2         // 12
  };
};

int main()
{
  //int temp = Foo::none + Bar::none;
  //std::cout << "foo::none =" << Foo::none << "\n";
  std::cout << "test" << std::endl;

  // unscoped enum
  FooBar::Foo foo = FooBar::symbolA;

  // scoped enum
  // enum名の namespace で修飾する必要がある
  FooBar::Bar bar = FooBar::Bar::bar1;

  std::cout << (int)foo << std::endl;
  std::cout << (int)bar << std::endl;
  
  return 0;
}

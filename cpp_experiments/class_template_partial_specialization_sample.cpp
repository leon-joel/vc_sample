#include <iostream>
#include "typename.h"
 
// プライマリー・テンプレート
template<typename tType>
struct Foo
{
    Foo() {std::cout << "primary template       : Foo<" << TYPENAME(tType) << ">\n";}
};
 
// ポインタ型用の部分特殊化テンプレート
template<typename tType>
struct Foo<tType*>
{
    Foo() {std::cout << "partial specialization : Foo<" << TYPENAME(tType) << "*>\n";}
};

template<>
struct Foo<char*>
{
    Foo() {std::cout << "explicit instantiation : Foo<" << "char" << "*>\n";}
};

 
int main()
{
    Foo<int> foo0;    // プライマリーテンプレートから実体化
    Foo<short> foo2;  //
    Foo<int*> foo1;   // ポインタ型用の部分特殊化テンプレートから実体化
    Foo<short*> foo3;
    Foo<char*> foo4;  // char*用の明示的実体化を使用
}

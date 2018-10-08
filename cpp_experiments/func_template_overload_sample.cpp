#include <iostream>
#include "typename.h"
 
// 1つめのオーバーロードした関数テンプレート
template<typename tType>
tType max(tType a, tType b)
{
    std::cout << "[0] "
              << TYPENAME(tType) << " max("
              << TYPENAME(tType) << " " << a << ", "
              << TYPENAME(tType) << " " << b << ") -> ";
    return (a >= b)?a:b;
}
 
// 2つめのオーバーロードした関数テンプレート
template<typename tType>
tType* max(tType* a, tType* b)
{
    std::cout << "[1] "
              << TYPENAME(tType) << "* max("
              << TYPENAME(tType) << "* a, "
              << TYPENAME(tType) << "* b) -> ";
    return (*a >= *b)?a:b;
}

// const char* 用に通常関数でオーバーロード
char const* max(char const* a, char const* b)
{
    std::cout << "[2] "
              << "char const* max(char const* a, char const* b) -> ";
    return (std::string(a) >= std::string(b))?a:b;
}

// // 明示的特殊化
// // ★狙い通りに使用されないので、これは避けるべき！通常関数でオーバーロードするのがいい。
// template<>
// char const* max<char const*>(char const* a, char const* b)
// {
//     std::cout << "[2] "
//               << "char const* max<char const*>(char const* a, char const* b) -> ";
//     return (std::string(a) >= std::string(b))?a:b;
// }

int main()
{
    std::cout << max(11, 22) << "\n";
    int x=123;
    int y=456;
    std::cout << *max(&x, &y) << "\n";

    // const char* 用に通常関数でオーバーロードした場合は狙い通りにそれが使用されるが、
    // 明示的特殊化（実体化）した場合はそれが使用されず、汎用ポインタ用テンプレートが使用される。
    std::cout << max("aaa", "abcde") << "\n";


    std::cout << max((char*)"aaa", (char*)"abcde") << "\n";
}
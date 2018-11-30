#include <iostream>
#include <type_traits>
#include "typename.h"

// プライマリ・テンプレート
template<typename tType, class tEnable=void>
struct Template{
    static tType max(tType a, tType b){
        std::cout << "[0] "
                  << TYPENAME(tType) << " max("
                  << TYPENAME(tType) << " " << a << ", "
                  << TYPENAME(tType) << " " << b << ") -> ";
        return (a >= b)?a:b;
    }
};

// 部分特殊化１ char*, const char* 以外の汎用ポインタ用
template<typename tType>
struct Template
<
//部分特殊化同士の優劣はないので、以下if1 を if0 にしてしまうと、anbiguous になってしまう！
#if 1
    tType*,
    typename std::enable_if
    <
        !(std::is_same<tType, char>::value||std::is_same<tType, char const>::value)
    >::type
#else
    tType*
#endif
>{
    static tType* max(tType* a, tType* b){
        std::cout << "[1] "
                  << TYPENAME(tType*) << " max("
                  << TYPENAME(tType*) << " a, "
                  << TYPENAME(tType*) << " b) -> ";
        return (*a >= *b)?a:b;
    }
};

// 部分特殊化２ char*, const char* 用
template<typename tType>
struct Template
<
    tType*,
    typename std::enable_if
    <
        std::is_same<tType, char>::value||std::is_same<tType, char const>::value
    >::type
>{
    static tType* max(tType* a, tType* b){
        std::cout << "[2] "
                  << TYPENAME(tType*) << " max("
                  << TYPENAME(tType*) << " a, "
                  << TYPENAME(tType*) << " b) -> ";
        return (std::string(a) >= std::string(b))?a:b;
    }
};

template<typename T>
T max(T iLhs, T iRhs){
    return Template<T>::max(iLhs, iRhs);
}

int main()
{
    std::cout << max(11, 22) << "\n";
    int x=123;
    int y=456;
    std::cout << *max(&x, &y) << "\n";
    std::cout << max("aaa", "abcde") << "\n";

    char a[]="aaa";
    char b[]="abcde";
    std::cout << max(a, b) << "\n";
}

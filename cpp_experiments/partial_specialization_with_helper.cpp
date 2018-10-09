#include <iostream>
#include <type_traits>
#include "typename.h"

// プライマリ・テンプレート
template<typename tType>
struct Template
{
    static tType max(tType a, tType b)
    {
        std::cout << "[0] "
                  << TYPENAME(tType) << " max("
                  << TYPENAME(tType) << " " << a << ", "
                  << TYPENAME(tType) << " " << b << ") -> ";
        return (a >= b)?a:b;
    }
};

// 部分特殊化
template<typename tType>
struct Template<tType*>
{
    static tType* max(tType* a, tType* b)
    {
        std::cout << "[1] "
                  << TYPENAME(tType) << "* max("
                  << TYPENAME(tType) << "* a, "
                  << TYPENAME(tType) << "* b) -> ";
        return (*a >= *b)?a:b;
    }
};

// 明示的特殊化(char const*)
template<>
struct Template<char const*>
{
    static char const* max(char const* a, char const* b)
    {
        std::cout << "[2] "
                  << "char const* max(char const* a, char const* b) -> ";
        return (std::string(a) >= std::string(b))?a:b;
    }
};

// // 明示的特殊化(char*)
// template<>
// struct Template<char*>
// {
//     static char* max(char* a, char* b)
//     {
//         std::cout << "[3] "
//                   << "char* max(char* a, char* b) -> ";
//         return (std::string(a) >= std::string(b))?a:b;
//     }
// };
// char* に対応するためにオーバーロード
const char* max(char* iLhs, char* iRhs){
	return Template<const char*>::max(iLhs, iRhs);
}

template<typename T>
T max(T iLhs, T iRhs)
{
    return Template<T>::max(iLhs, iRhs);
}


// // オレオレis_sameテンプレートクラス
// template<typename tLhs, typename tRhs>
// struct is_same {
// 	constexpr static bool value = false;
// };
// template<typename tType>
// struct is_same<tType, tType> {
// 	constexpr static bool value = true;
// };

// // オレオレenable_ifテンプレートクラス
// template<bool tCond, typename tType = void>
// struct enable_if {};
// template<typename tType>
// struct enable_if<true, tType>{
// 	typedef tType type;
// };

template<typename tType, class tEnable = void>
struct IsStringImpl{
    static constexpr char const* value="no";
};
template<typename tType>
struct IsStringImpl<
	tType,
	typename std::enable_if<
	    std::is_same<tType, char*>::value || std::is_same<tType, char const*>::value
    >::type
>{
    static constexpr char const* value="yes";
};
 
template<typename tType>
char const* IsString(tType){
    std::cout << "[" << TYPENAME(tType) << "] ";
    return IsStringImpl<tType>::value;
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

	// is_same を使ってみる
	std::cout << std::is_same<int, int>::value << std::endl;
	std::cout << std::is_same<int, short>::value << std::endl;

	// enable_if を使ってみる
	std::cout << TYPENAME(typename std::enable_if<true>::type) << std::endl;
	// std::cout << TYPENAME(typename std::enable_if<false>::type) << std::endl;

	std::cout << IsString("abc") << "\n";
    char temp[]="def";
    std::cout << IsString(temp) << "\n";
    std::cout << IsString(123) << "\n";
}

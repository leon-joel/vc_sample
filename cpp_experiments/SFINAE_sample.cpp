#include <iostream>
 
template<int>
struct Helper
{
	typedef void type;
};

// IsFishクラステンプレート1 （Fish以外用） 
template<class tClass, typename tEnable=void>
struct IsFish
{
	constexpr static bool value = false;
};

// IsFishクラステンプレート2 （Fish用） 
template<class tClass>
struct IsFish<tClass, typename Helper<tClass::filets>::type>
{
	constexpr static bool value = true;
};
 
// 犬
struct Dog
{
	constexpr static int legs = 4;
};
// 鮭
struct Salmon
{
	constexpr static int filets = 8;
};
 
int main()
{
	// IsFishクラステンプレートの実体化を試みる
	// Fish用のクラステンプレートは Helper<...> の tClass::filets の部分がエラーになるので、
	// ★ここでエラーになるが、SFINAEにより、「エラーにせず、単にそのテンプレート（特殊化）を採用しない」ということになる。
	// そして、Fish以外用のIsFishテンプレートが実体化され使用される。
	// Fish以外用は value が false　を返すようになっている。
	std::cout << "Is dog a fish ? " << IsFish<Dog>::value << "\n";

	// Salmonは filets メンバーを持っているので、
	// Fish用クラステンプレートが実体化され使用される。
	std::cout << "Is salmon a fish ? " << IsFish<Salmon>::value << "\n";
}

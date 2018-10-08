#include <iostream>
 
// 型から取り出す
template<class tAnimal>
int getLegs()
{
    return tAnimal::legs;
}
 
// クラスのインスタンスから取り出す
template<class tAnimal>
int getLegs(tAnimal const&)
{
    return tAnimal::legs;
}
 
// 犬
struct Dog
{
    constexpr static int legs = 4;
};
// 猫
struct Cat
{
    // constでも問題なく動く
    const static int legs = 4;
};
// カブトムシ
struct Beetle
{
    // 非constメンバーは ここで初期化できない
    // static int legs = 6;
    static int legs;
    // ↑↓こんな感じならOK
};
int Beetle::legs = 6;

// タコ
struct Octopus
{
    constexpr static int legs = 8;
};
// イカ
struct Squid
{
    constexpr static int legs = 10;
};
 
int main()
{
    // 型から取り出したい時
    std::cout << "Dog    =" << getLegs<Dog>() << "\n";
    std::cout << "Cat    =" << getLegs<Cat>() << "\n";
    std::cout << "Beetle =" << getLegs<Beetle>() << "\n";
    std::cout << "Octopus=" << getLegs<Octopus>() << "\n";
    std::cout << "Squid  =" << getLegs<Squid>() << "\n";
 
    // インスタンスから取り出したい時
    Dog aDog;
    std::cout << "aDog   =" << getLegs(aDog) << "\n";
}
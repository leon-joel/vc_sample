#include <iostream>
 
int main()
{
    int a=10;
    int b=20;
    int c=30;
    a=b=c;
    std::cout << "a=" << a << " b=" << b << " c=" << c << "\n";
 
    a=10;
    b=20;
    c=30;
    a=(b=c);
    std::cout << "a=" << a << " b=" << b << " c=" << c << "\n";
 
    a=10;
    b=20;
    c=30;
    (a=b)=c;
    std::cout << "a=" << a << " b=" << b << " c=" << c << "\n";
 
    // インクリメント演算子
    // 前置は 左辺値を返す
    a = 10;
    (++a) += 1;
    std::cout << "pre a=" << a << std::endl;

    // 後置は 右辺値を返す
    // a = 10;
    // (a++) += 1;  // これは許されない。ビルドエラーに。
    // std::cout << "後置 a=" << a << std::endl;
    return 0;
}

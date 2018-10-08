#include <iostream>
 
class   Foo
{
    int     mData;
public:
    Foo(int iData) : mData(iData)
    {
        std::cout << "Foo::Foo(" << mData << ")     : this=" << this << "\n";
    }
    ~Foo()
    {
        std::cout << "Foo::~Foo(" << mData << ")    : this=" << this << "\n";
    }
};
 
struct Bar
{
    Foo*    mFoo;
    Bar() : mFoo(nullptr)
    {
        std::cout << "Bar::Bar()\n";
    }
    Bar(Foo* iFoo) : mFoo(iFoo)
    {
        std::cout << "Bar::Bar(Foo*) : mFoo=" << mFoo << "\n";
    }
    ~Bar()
    {
        std::cout << "Bar::~Bar()    : mFoo=" << mFoo << "\n";
        delete mFoo;
    }
 
    // ムーブ・コンストラクタ
    Bar(Bar&& iRhs) : mFoo(iRhs.mFoo)
    {
        std::cout << "Bar::Bar(Foo&&): mFoo=" << mFoo << "\n";
        iRhs.mFoo = nullptr;
    }
};
 
Bar baz()
{
    std::cout << "baz()\n";
    Bar ret(new Foo(456));          // Fooコンストラクト・・・①
                                    // Barコンストラクト
    std::cout << "return from baz\n";
    return std::move(ret);          // 戻り値へムーブ（ムーブ・コンストラクタ）
}                                   // retデストラクト（ここで①のFooデストラクト）
 
Bar baz_not_move()
{
    std::cout << "baz()\n";
    Bar ret(new Foo(456));          // Fooコンストラクト・・・①
                                    // Barコンストラクト
    std::cout << "return from baz\n";
    // std::moveをつけないようにすると、コンパイラによるNRVO最適化により
    return ret;                     // moveすら発生しない！
}

Bar baz_not_nvro(){
    std::cout << "baz()\n";
    Bar r1(new Foo(456));
    Bar r2(new Foo(789));

    std::cout << "return from baz\n";

    // r1/r2　のどちらが返却されるかわからないので、NVRO最適化は働かず、moveされる。
    if ((long)(&r1) % 2 == 0)
      return r1;
    else
      return r2;
}
void qux(Bar&& iBar)
{
    std::cout << "qux()          : iBar.mFoo=" << iBar.mFoo << "\n";

    // ★★★右辺値参照が【左辺値】であることの確認！！！
    Bar aBar(std::move(iBar));  // aBarへムーブするとムーブ・コンストラクタが走る
    // Bar aBar(iBar);          // ★重要★ aBarへコピーしようとしてもコピー・コンストラクタはないのでエラー

    std::cout << "qux()          : aBar.mFoo=" << aBar.mFoo << "\n";
}    
int main()
{
    // Bar aBar=baz();
    // qux(baz_not_move());
    qux(baz_not_nvro());

    // std::cout << "post baz()     : mFoo=" << aBar.mFoo << "\n";
}                                   // aBarデストラクト（ここで①のFooデストラクト）

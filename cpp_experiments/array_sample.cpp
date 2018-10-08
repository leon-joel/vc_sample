#include <iostream>
#include <iomanip>

int Bar(int arr[3][4]){
  // これだと sizeof(int) が返される！
  return sizeof(arr);
}
int main()
{
    int bar[3][4]={ {0x00, 0x01, 0x02, 0x03}, {0x10, 0x11, 0x12, 0x13}, {0x20, 0x21, 0x22, 0x23} };

    // ここではちゃんと配列全体のバイト数が帰ってくる
    std::cout << sizeof(bar) << std::endl;
    // しかし、関数に渡した時点でその情報が消えてしまう
    std::cout << Bar(bar) << std::endl;

    std::cout << std::hex;
    for (int i=0; i < 3; ++i)
    {
        std::cout << bar[i] << " :";
        for (int j=0; j < 4; ++j)
        {
            std::cout<< ' '  << std::setfill('0') << std::setw(8) << bar[i][j];
        }
        std::cout << "\n";
    }
    return 0;
}

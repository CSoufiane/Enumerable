#include "Enumerable.hpp"


int main()
{
    SFN::Enumerable<int>::Range(-100, 100)
        .Where([](int i) -> bool {
            return i % 15 == 0;
            })
        .Select<char>([](int i) -> int {
                    if(i<0)
                        return 'z';
                    return (char) 'A' + i%27;
                })
        .Foreach([](char a) -> void {
                std::cout << a;
            });
    std::cout << " END 1\n";
    auto a = SFN::ENUMERABLE(int, [], {
                run(1); // yield return 1;
                run(200);
                run(30);
                run(5);
            });
    bool bFirstLoop = true;
    a.Where([](int i) -> bool {
            return i % 2 != 0;
            })
        .Select<int>([](int i) -> int {
                    return 2*i;
                })
        .Foreach([&bFirstLoop](int i) -> void {
                if(bFirstLoop)
                {
                    std::cout << i;
                    bFirstLoop = false;
                }
                    std::cout << "-" << i;
            });
    std::cout << " END 2\n";
    return 0;
}

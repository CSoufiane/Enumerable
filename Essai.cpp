#include <list>
#include "Enumerable.hpp"

int main()
{
    std::list<int> primes;
    SFN::Enumerable<int>::Range(0,10000000)
        .Where([&](int i) -> bool {
            for(auto p : primes)
            {
                if(p>1 && i % p == 0)
                    return false;
            }
            return true;
        })
        .Do([&](int i) -> void { primes.push_back(i); })
        .Where([](int i ) -> bool { return i > 10000; })
        .Take(20)
        .Do([](int i) -> void { std::cout << i << " is a prime number" << std::endl; })
        .Foreach([](int) -> void {});
    return 0;
}

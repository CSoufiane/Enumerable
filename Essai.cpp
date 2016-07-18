#include <list>
#include <string>
#include "Enumerable.hpp"

using namespace std;

int main()
{
    list<int> primes;

    SFN::Enumerable<int>::Range(0,10000000)
        //Filter the prime number
        .Where([&](int i) -> bool {
            for(auto p : primes)
            {
                if( 1 < p && i % p == 0)
                    return false;
            }
            return true;
        })
        //Store the prime number
        .Do([&](int i) -> void { primes.push_back(i); })
        //Process prime number > 10000
        .Where([](int i ) -> bool { return i > 10000; })
        .Take(5)
        .Select<string>([](int i) -> string { return to_string(i); })
        .Do([](string s) -> void { cout << s << " is a prime number" << endl; })
        .Run();

    cout << "Number of prime number found = " << primes.size() << endl;
    return 0;
}

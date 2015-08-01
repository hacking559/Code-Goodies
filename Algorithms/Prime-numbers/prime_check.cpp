
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int x) {

    if(a < 2 || ( a & 1 == 0 and a > 2 ))
        return false;

    for(register int i = 3; 1LL * i * i <= x; i += 2)
        if(x % i == 0)
            return false;

    return true;
}

int main(void) {

    int nr;
    cin >> nr; cout << '\n';

    if(isPrime(nr))
        cout << nr << " is a prime\n";
    else 
        cout << nr << " is not a prime\n";

    return 0;
}

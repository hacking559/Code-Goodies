
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_N = 500000;
int sieve[MAX_N + 1];

/*** CLASSIC SIEVE ***/
void simple_sieve(int nr) {
	
	sieve[0] = sieve[1] = 1;

	for(register int i = 4; i <= nr; i += 2)
		sieve[i] = 1;

	for(register int i = 3; 1LL * i * i <= nr; i += 2)
		if(!sieve[i])
			for(register int j = i * i; j <= nr; j += (i << 1))
				sieve[j] = 1;

}

/*** SPECIAL SIEVE THAT GENEREATES THE BIGGEST PRIME DIVISOR OF EACH NUMBER ***/
void special_sieve(int nr) {

	sieve[0] = sieve[1] = 1;

	for(register int i = 4; i <= nr; i += 2)
		sieve[i] = 2;

	for(register int i = 3; 1LL * i * i <= nr; i += 2)
		if(sieve[i] == 0)
			for(register int j = i * i; j <= nr; j += (i << 1))
				sieve[j] = i;

}

void prime_factorisation(int nr) {
	if(nr == 1) {
		cout << '\n';
		return;
	}

	if(sieve[nr] == 0) {
		cout << nr << "^" << 1 << '\n';
		return;
	}
		
	int div = sieve[nr], exp = 0, no = nr;

	while(nr % div == 0)
		nr /= div, ++ exp;

	cout << div << '^' << exp << ' ';

	prime_factorisation(nr);

}

int main(void) {
	
	ifstream f("sieve.in");
	int N;
	f >> N;
	special_sieve(N);

	for(register int i = 2; i <= N; ++ i)
		cout << i << ':', prime_factorisation(i);
	return 0;

}

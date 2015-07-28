#ifndef _HUGE_H
#define _HUGE_H
#pragma one
#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>
#include <fstream>
#include <deque>
#include <string>
using namespace std;

const static int MAX_DIGITS = 16384;
const static int BASE = 10;

inline int todig(char c) {
	return c - '0';
}

class Huge {
private:
	deque<int> v;
public:

	Huge() {
		v.clear();
		v.push_back(0);
	}

	template<typename T>
	Huge (T n) {

		v.clear();

		do {
			v.push_back(n % 10);
			n /= 10;
		}while(n);
	}

	Huge (deque<int> x) {
		v = x;
	}

	inline int size() const {
		return v.size();
	}

	inline int dig (int pos) const {
		return v[v.size() - pos];
	}

	void operator = (Huge other) {
		v = other.v;
	}
	void operator = (deque<int> other) {
		v = other;
	}

	template<typename T>
	void operator = (T n) {

		v.clear();

		do {
			v.push_back(n % 10);
			n /= 10;
		}while(n);
	}

	void Read(FILE* f) {

		v.clear();

		char s[MAX_DIGITS];
		fscanf(f, "%s", s);

		for(register int i = strlen(s) - 1; i > -1; -- i)
			if(isdigit(s[i]))
				v.push_back(todig(s[i]));
	}

	void Print (FILE* f) {
		for (register int i = v.size() - 1; i > -1; -- i)
			fprintf (f, "%d",v[i]);
	}

	friend istream& operator >> (istream& in, Huge& a);
	friend ostream& operator << (ostream& out, Huge& a);

	// + Operator
	Huge operator + (const Huge& other) {

		int t = 0;

		deque <int> aux = v;

		for (register int i = 0; i < aux.size() || i < other.size() || t != 0; ++ i) {
			if (i == aux.size())
				aux.push_back(0);

			if (i < other.size())
				aux[i] += other.v[i];

			aux[i] += t;
			t = aux[i] / BASE;
			aux[i] %= BASE;

		}

		Huge Ans;
		Ans = aux;
		return Ans;
	}

	template<typename T>
	Huge operator + (T other) {

		Huge x = other;
		return *this + other;
	}

	void operator += (const Huge& other) {

		int t = 0;

		for (register int i = 0; i < v.size() || i < other.size() || t != 0; ++ i) {
			if (i == v.size())
				v.push_back(0);

			if (i < other.size())
				v[i] += other.v[i];

			v[i] += t;
			t = v[i] / BASE;
			v[i] %= BASE;

		}
	}

	template<typename T>
	void operator += (T other) {
		Huge x = other;
		*this += other;
	}

	template<typename T>
	Huge operator / (T y) {

		T t = 0;

    	deque <int> aux = v;

    	for (register int i = aux.size() - 1; i > -1; -- i) {
    		aux[i] += t * BASE;
    		t = aux[i] % y;
    		aux[i] /= y;
    	}

    	while (aux.size() > 1 and aux.back() == 0)
    		aux.pop_back();

    	Huge Ans;
    	Ans = aux;
    	return Ans;
	}

	template<typename T>
	void operator /= (T y) {

		T t = 0;

    	for (register int i = v.size() - 1; i > -1; -- i) {
    		v[i] += t * BASE;
    		t = v[i] % y;
    		v[i] /= y;
    	}

    	while (v.size() > 1 and v.back() == 0)
    		v.pop_back();
	}

	// * operator
	Huge operator * (const Huge& other) {

		int t=0;
    	deque<int> z;
    	z.resize (v.size() + other.size() - 1, 0);

    	for(register int i = 0; i < (int)v.size(); ++ i)
  			for(register int j = 0; j < (int)other.size(); ++ j)
            	z[i + j] += v[i] * other.v[j];

    	for(register int i = 0; i < (int)z.size() || t; ++ i) {
    		if(i == (int)z.size())
            	z.push_back(0);

            z[i] += t;
    		t = z[i] / BASE;
    		z[i] %= BASE;

    	}

   		Huge ans; ans = z;
   		return ans;
	}

	template<typename T>
	Huge operator * (T other) {
		Huge x = other;
		return *this * x;
	}

	void operator *= (const Huge& other) {

		int t=0;
    	deque<int> z;
    	z.resize (v.size() + other.size() - 1, 0);

    	for(int i = 0; i < (int)v.size(); ++ i)
  			for(int j = 0; j < (int)other.size(); ++ j)
            	z[i + j] += v[i] * other.v[j];

    	for(int i = 0; i < (int)z.size() || t; ++ i) {
    		if(i == (int)z.size())
            	z.push_back(0);

            z[i] += t;
    		t = z[i] / BASE;
    		z[i] %= BASE;

    	}

   		v = z;
	}

	template<typename T>
	void operator *= (T other) {
		Huge x = other;
		*this *= x;
	}

	// - operator
	Huge operator - (const Huge& other) {

		int t = 0;
		deque <int> aux = v;

		for (register int i = 0; i < aux.size(); ++ i) {
              aux[i] -= ((i < other.size()) ? other.v[i] : 0) + t;
              aux[i] += (t = aux[i] < 0) * 10;
      	}

      for (; aux.size() > 1 and !aux[aux.size() - 1]; aux.pop_back());

      Huge ans;
  	  ans = aux;
  	  return ans;

	}

	template<typename T>
	Huge operator - (T other) {
		Huge x = other;
		return *this - x;
	}

	void operator -= (const Huge& other) {
		int t = 0;

      for (register int i = 0; i < v.size(); ++ i) {
              v[i] -= ((i < other.size()) ? other.v[i] : 0) + t;
              v[i] += (t = v[i] < 0) * 10;
      	}

      for (; v.size() > 1 and !v[v.size() - 1]; v.pop_back());
	}

	template<typename T>
	void operator -= (T other) {
		Huge x = other;
		*this -= x;
	}

	// equal

	bool operator == (const Huge& other) {

		if (v.size() != other.size())
			return false;

		for (register int i = 0; i < v.size(); ++ i)
			if (v[i] != other.v[i])
				return false;
		return true;
	}

	template<typename T>
	bool operator == (T other) {
		Huge x = other;
		return *this == x;
	}

	bool operator < (const Huge& other) {

		if (other.size() > v.size())
			return true;
		if (other.size() < v.size())
			return false;

		for (int i = v.size() - 1; i > -1; -- i) {
			if (other.v[i] == v[i])
				continue;
			if (other.v[i] > v[i])
				return true;
			return false;
		}

		return false;
	}

	template<typename T>
	bool operator < (T other) {
		Huge x = other;
		return *this < x;
	}


	inline bool operator <= (const Huge& other) {

		if (other.size() > v.size())
			return true;
		if (other.size() < v.size())
			return false;

		Huge aux;
		aux = v;

		if (aux == other)
			return true;

		return aux < other;
	}

	template<typename T>
	inline bool operator <= (T other) {
		Huge x = other;
		return *this <= x;
	}

	inline bool operator > (const Huge& other) {

		if (other.size() > v.size())
			return false;
		if (other.size() < v.size())
			return true;

		for (register int i = v.size() - 1; i > -1; -- i) {
			if (other.v[i] == v[i])
				continue;
			if (other.v[i] > v[i])
				return false;
			return true;
		}

		return false;
	}

	template<typename T>
	inline bool operator > (T other) {
		Huge x = other;
		return *this > x;
	}

	inline bool operator >= (const Huge& other) {

		if (other.size() > v.size())
			return false;
		if (other.size() < v.size())
			return true;

		Huge aux;
		aux = v;
		if (aux == other)
			return true;
		return aux > other;
	}

	template<typename T>
	inline bool operator >= (T other) {
		Huge x = other;
		return *this >= x;
	}

	inline bool operator != (Huge other) {

		Huge aux;
		aux = v;

		if (aux == other)
			return false;
		return true;
	}

	template<typename T>
	inline bool operator != (T other) {
		Huge x = other;
		return *this != x;
	}

	// modulo
	template<typename INTEGER>
	INTEGER operator % (INTEGER B) {
		int t = 0;

		for (register int i = v.size() - 1; i >= 0; -- i)
			t = (t * 10 + v[i]) % B;

		return t;
	}

	template<typename INTEGER>
	void operator %= (INTEGER B) {

		int t = 0;

		for (register int i = v.size() - 1; i >= 0; -- i)
			t = (t * 10 + v[i]) % B;

		v.clear();

		do {
			v.push_back(t % 10);
			t /= 10;
		}while(t);

	}

	template<typename T>
	Huge operator << (T x) {
		deque<int> d = v;
		while(x --)
			d.push_front(0);
	}

	template<typename T>
	Huge operator >> (T x) {
		deque<int> d = v;
		while(x --)
			d.pop_front();
	}

	template<typename T>
	void operator <<= (T x) {
		while(x --)
			v.push_front(0);
	}

	template<typename T>
	void operator >>= (T x) {
		while (x --)
			v.pop_front();
	}

};


istream& operator >> (istream& in, Huge& a) {
	v.clear();
	string s;
	in >> s;

	for(register int i = s.size() - 1; i > -1; -- i)
		if(isdigit(s[i]))
			v.push_back(todig(s[i]));

	return in;
}

ostream& operator << (ostream& out, Huge& a) {
	for(register int i = v.size() - 1; i > -1; -- i)
			out << v[i];
	return out;
}

#endif // _HUGE_H

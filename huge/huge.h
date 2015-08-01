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
			} while(n);
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

		Huge& operator = (const Huge& other) {
			this->v = other.v;
			return *this;
		}
		Huge& operator = (deque<int> other) {
			this->v = other;
			return *this;
		}

		template<typename T>
		Huge& operator = (T n) {
			*this = Huge(n);
			return *this;
		}

		Huge& Read(FILE* f) {
			v.clear();
			char s[MAX_DIGITS];
			fscanf(f, "%s", s);

			for(register int i = strlen(s) - 1; i > -1; -- i)
					if(isdigit(s[i]))
						v.push_back(todig(s[i]));

			return *this;
		}

		Huge& Print (FILE* f) {
			for (register int i = v.size() - 1; i > -1; -- i)
					fprintf (f, "%d",v[i]);

			return *this;
		}

		friend istream& operator >> (istream& in, Huge& a);
		friend ostream& operator << (ostream& out, const Huge& a);

		// + Operator
		Huge operator + (const Huge& other) const {

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

			return Huge(aux);
		}

		template<typename T>
		Huge operator + (T other) const {
			return *this + Huge(other);
		}

		Huge& operator += (const Huge& other) {
			*this = *this + other;
			return *this;
		}

		template<typename T>
		Huge& operator += (T other) {
			return *this += Huge(other);
		}

		template<typename T>
		Huge operator / (T y) const {
			T t = 0;
	    	deque <int> aux = v;

	    	for (register int i = aux.size() - 1; i > -1; -- i) {
		    	aux[i] += t * BASE;
		    	t = aux[i] % y;
		    	aux[i] /= y;
	    	}

	    	while (aux.size() > 1 and aux.back() == 0)
	    		aux.pop_back();

	    	return Huge(aux);
		}

		template<typename T>
		Huge& operator /= (T y) {
			*this = *this / y;
			return *this;
		}

		// * operator
		Huge operator * (const Huge& other) const {

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

	   		return Huge(z);
		}

		template<typename T>
		Huge operator * (T other) const {
			return *this * Huge(other);
		}

		Huge& operator *= (const Huge& other) {
			*this = *this * other;
			return *this;
		}

		template<typename T>
		Huge& operator *= (T other) {
			return *this *= Huge(other);
		}

		// - operator
		Huge operator - (const Huge& other) const {

			int t = 0;
			deque <int> aux = v;

			for (register int i = 0; i < aux.size(); ++ i) {
	            aux[i] -= ((i < other.size()) ? other.v[i] : 0) + t;
	            aux[i] += (t = aux[i] < 0) * 10;
	      	}

	      	for (; aux.size() > 1 and !aux[aux.size() - 1]; aux.pop_back());

	  	  	return Huge(aux);

		}

		template<typename T>
		Huge operator - (T other) const {
			return *this - Huge(other);
		}

		Huge& operator -= (const Huge& other) {
			*this = *this - other;
			return *this;
		}

		template<typename T>
		Huge& operator -= (T other) {
			return *this -= Huge(other);
		}

		// equal
		bool operator == (const Huge& other) const {

			if (v.size() != other.size())
				return false;

			for (register int i = 0; i < v.size(); ++ i)
				if (v[i] != other.v[i])
					return false;
			return true;
		}

		template<typename T>
		bool operator == (T other) const {
			return *this == Huge(other);
		}

		bool operator < (const Huge& other) const {

			if (other.size() > v.size())
				return true;
			if (other.size() < v.size())
				return false;

			for (register int i = v.size() - 1; i > -1; -- i) {
				if (other.v[i] == v[i])
					continue;
				if (other.v[i] > v[i])
					return true;
				return false;
			}

			return false;
		}

		template<typename T>
		bool operator < (T other) const {
			return *this < Huge(other);
		}


		inline bool operator <= (const Huge& other) const {

			if (other.size() > v.size())
				return true;
			if (other.size() < v.size())
				return false;

			Huge aux(v);

			if (aux == other)
				return true;

			return aux < other;
		}

		template<typename T>
		inline bool operator <= (T other) const {
			return *this <= Huge(other);
		}

		inline bool operator > (const Huge& other) const {

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
		inline bool operator > (T other) const {
			return *this > Huge(other);
		}

		inline bool operator >= (const Huge& other) const {

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
		inline bool operator >= (T other) const {
			Huge x = other;
			return *this >= x;
		}

		inline bool operator != (Huge other) const {
			return !(*this == other);
		}

		template<typename T>
		inline bool operator != (T other) const {
			return *this != Huge(other);
		}

		// modulo
		template<typename INTEGER>
		INTEGER operator % (INTEGER B) const {
			int t = 0;

			for (register int i = v.size() - 1; i >= 0; -- i)
				t = (t * 10 + v[i]) % B;

			return t;
		}

		template<typename INTEGER>
		Huge& operator %= (INTEGER B) {
			*this = *this % B;
			return *this;
		}

		template<typename T>
		Huge operator << (T x) const {
			deque<int> d = v;
			while(x --)
				d.push_front(0);
			return Huge(d);
		}

		template<typename T>
		Huge operator >> (T x) const {
			deque<int> d = v;
			while(x --)
				d.pop_front();
			return Huge(d);
		}

		template<typename T>
		Huge& operator <<= (T x) {
			*this = *this << x;
			return *this;
		}

		template<typename T>
		Huge& operator >>= (T x) {
			*this = *this >> x;
			return *this;
		}

};


istream& operator >> (istream& in, Huge& a) {
	a.v.clear();
	string s;

	in >> s;
	for(register int i = s.size() - 1; i > -1; -- i)
		if(isdigit(s[i]))
			a.v.push_back(todig(s[i]));

	return in;
}

ostream& operator << (ostream& out, const Huge& a) {
	for(register int i = a.v.size() - 1; i > -1; -- i)
			out << a.v[i];
	return out;
}

#endif // _HUGE_H

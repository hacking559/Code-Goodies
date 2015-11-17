#ifndef HUGE_H_INCLUDED
#define HUGE_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;

const static int maxDigits = 16384;
const static int base = 10;

class Huge {
private:
  int v[maxDigits];
public:
  inline int size() const{
    return v[0];
  }

  Huge() { memset(v, 0, sizeof v); }

  template<typename Int>
  Huge(Int n) {
    *this = Huge();
    do {
      v[++ v[0]] = n % 10;
      n /= 10;
    }while(n);
  }

  inline int dig(int pos) {
    return v[size() - pos];
  }

  Huge& operator = (const Huge& other) {
    memcpy(v, other.v, sizeof other.v);
    return *this;
  }

  template<typename Int>
  Huge& operator = (const Int& other) {
    *this = Huge(other);
    return *this;
  }

  Huge& Read(FILE* f) {
    *this = Huge();
    char aux[maxDigits];
    fscanf(f, "%s", aux);
    for(register int i = strlen(aux) - 1; i > -1; -- i)
      if(isdigit(aux[i]))
        v[++ v[0]] = aux[i] - '0';
    return *this;
  }

  Huge& Print(FILE* f) {
    for(register int i = v[0]; i > 0; -- i)
      fprintf(f, "%d", v[i]);
    return *this;
  }

  friend istream& operator >> (istream& in, Huge& a);
  friend ostream& operator << (ostream& in, const Huge& a);

  Huge operator + (const Huge& other) const {
    Huge copie = *this;
    int i, t = 0;
    for(i = 1; i <= copie.v[0] || i <= other.v[0] || t; ++ i, t /= 10)
      copie.v[i] = (t += copie.v[i] + other.v[i]) % 10;
    copie.v[0] = i - 1;
    return copie;
  }

  template<typename Int>
  Huge operator + (const Int& other) const {
    return *this + Huge(other);
  }

  Huge& operator += (const Huge& other) {
    *this = *this + other;
    return *this;
  }

  template<typename Int>
  Huge& operator += (const Int& other) {
    return *this += Huge(other);
  }

  template<typename Int>
  Huge operator * (const Int& other) const {
    int i, t = 0;
    Huge copie = *this;
    for(i = 1; i <= copie.v[0] || t; ++ i, t /= 10)
      copie.v[i] = (t += copie.v[i] * other) % 10;
    copie.v[0] = i - 1;
    return copie;
  }

  template<typename Int>
  Huge& operator *= (const Int& other) {
    *this = *this * other;
    return *this;
  }

  Huge operator * (const Huge& other) const {
    int i, j, t;
    Huge C, copie = *this;
    for(i = 1; i <= copie.v[0]; ++ i) {
      for(t = 0, j = 1; j <= other.v[0] || t; ++ j, t /= 10)
        C.v[i + j - 1] = (t += C.v[i + j - 1] + copie.v[i] * other.v[j]) % 10;
      C.v[0] = max(i + j - 2, C.v[0]);
    }
    return C;
  }

  Huge& operator *= (const Huge& other) {
    *this = *this * other;
    return *this;
  }

  Huge operator - (const Huge& other) const {
    Huge copie = *this;
    int i, t = 0;
    for(i = 1; i <= other.v[0]; ++ i) {
      copie.v[i] -= ((i <= other.v[0]) ? other.v[i] : 0) + t;
      copie.v[i] += (t = copie.v[i] < 0) * 10;
    }

    while(copie.v[0] > 1 and !copie.v[copie.v[0]])
      -- copie.v[0];
    return copie;
  }

  template<typename Int>
  Huge operator - (const Int& other) const {
    return *this - Huge(other);
  }

  Huge& operator -= (const Huge& other) {
    *this = *this - Huge(other);
    return *this;
  }

  template<typename Int>
  Huge& operator -= (const Int& other) {
    return *this -= Huge(other);
  }

  template<typename Int>
  Huge operator / (const Int& other) const {
    int i, t = 0;
    Huge copie = *this;
    for(i = copie.v[0]; i > 0; -- i, t %= other)
      copie.v[i] = (t = t * 10 + copie.v[i]) / other;
    while(copie.v[0] > 1 and !copie.v[copie.v[0]])
      -- copie.v[0];
    return copie;
  }

  template<typename Int>
  Huge& operator /= (const Int& other) {
    *this = *this / other;
    return *this;
  }

  template<typename Int>
  Int operator % (const Int& other) const {
    int i, t = 0;
    for(i = v[0]; i > 0; -- i)
      t = (t * 10 + v[i]) % other;
    return t;
  }

  template<typename Int>
  Int& operator %= (const Int& other) {
    *this = *this % other;
    return *this;
  }

  inline bool operator == (const Huge& other) {
    if(v[0] != other.v[0])
      return false;
    return !memcmp(this->v, other.v, sizeof this->v);
  }

  inline bool operator != (const Huge& other) {
    return !(*this == other);
  }

  inline bool operator < (const Huge& other) {
    if(v[0] != other.v[0]) {
      return v[0] < other.v[0];
    }

    for(register int i = v[0]; i > 0; -- i) {
      if(v[i] == other.v[i])
        continue;
      return v[i] < other.v[i];
    }

    return false;
  }

  inline bool operator <= (const Huge& other) {
    return *this < other || *this == other;
  }


  inline bool operator > (const Huge& other) {
    return !(*this <= other);
  }

  inline bool operator >= (const Huge& other) {
    return !(*this < other);
  }
};

istream& operator >> (istream& in, Huge& a) {
  a = Huge();
  string aux;
  in >> aux;
  for(register int i = aux.size() - 1; i > -1; -- i)
    if(isdigit(aux[i]))
      a.v[++ a.v[0]] = aux[i] - '0';
  return in;
}

ostream& operator << (ostream& out, const Huge& a) {
  for(register int i = a.size(); i > 0; -- i)
    out << a.v[i];
  return out;
}

#endif // HUGE_H_INCLUDED

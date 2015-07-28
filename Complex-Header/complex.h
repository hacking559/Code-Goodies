#ifndef _COMPLEX_H
#define _COMPLEX_H
#pragma one
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <limits>
#include <bitset>
#include <list>
#include <forward_list>
#include <set>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
using namespace std;

// Auxiliary functions
inline bool IsInteger (double a) {
    double intpart;
    return modf(a, &intpart) == 0;
}

inline bool FInt (double a) {
    double intpart;
    modf(a, &intpart);
    return intpart <= INT_MAX;
}


// The numbers are written in the form Re + i * Im, where i * i = ( - 1 ).
// The defined operators are : + ; - ; * ; / ; < ; <= ; > ; >= .
// Also += ; -= ; *= ; /= .

class Complex {
    public:
    double Re, Im;
    Complex() { }
    Complex(double a, double b) {
        Re = a, Im = b;
    }

    Complex(const Complex& other) {
        *this = other;
    }

    Complex(double a) {
        Re = a;
    }

    inline Complex operator + (const Complex& other) {
        Complex Ans = other;
        Ans.Re += Re;
        Ans.Im += Im;
        return Ans;
    }
    
    inline Complex operator - (const Complex& other) {
        Complex Ans = other;
        Ans.Re -= Re;
        Ans.Im -= Im;
        return Ans;
    }
    
    inline Complex operator * (const Complex& other) {
        Complex Ans = other;
        Ans.Re *= Re;
        Ans.Im *= Im;
        return Ans;
    }
    
    inline Complex operator / (const Complex& other) {
        Complex Ans = other;
        Ans.Re /= Re;
        Ans.Im /= Im;
        return Ans;
    }
    
    inline Complex cabs (Complex nr) {
        return Complex(fabs(Re), fabs(Im));
    }
    
    inline bool operator == (const Complex& other) {
        return (Re == other.Re and Im == other.Im);
    }
    
    inline bool operator < (const Complex& other) {
        return (Re == other.Re) ? (Im < other.Im) : (Re < other.Re);
    }
    
    inline bool operator > (const Complex& other) {
        return (Re == other.Re) ? (Im > other.Im) : (Re > other.Re);
    }
    
    inline bool operator <= (const Complex& other) {
        if (*this == other)
            return true;
        return *this < other;
    }
    
    inline bool operator >= (const Complex& other) {
        if (*this == other)
            return true;
        return *this > other;
    }
      
    inline void operator += (const Complex& other) {
        *this = *this + other;
    }
    
    inline void operator -= (const Complex& other) {
        *this = *this + other;
    }
    
    inline void operator *= (const Complex& other) {
        *this = *this * other;
    }
    
    void operator /= (const Complex& other) {
        *this = *this / other;
    }
    
    inline bool operator != (const Complex& other) {
        return !(*this == other);
    }
    
    inline bool IsReal () {
        return !Im;
    }
    
    inline bool isInt () {
        return (!Im and IsInteger(Re));
    }
    
    inline bool FitsInt () {
        return (!Im and FInt(Re));
    }

    friend istream& operator >> (istream& in, Complex& c);

};

istream& operator >> (istream& in, Complex& c) {
    in >> c.Re >> c.Im;
    return in;
}


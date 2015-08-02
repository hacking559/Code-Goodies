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

class Complex {
    public:
    double Re, Im;
    Complex() { Re = Im = 0.0; }
    Complex(double a, double b) {
        Re = a, Im = b;
    }

    Complex(const Complex& other) {
        *this = other;
    }

    Complex(double a) {
        Re = a;
    }

    inline Complex operator + (const Complex& other) const {
        return Complex(this->Re + other.Re, this->Im + other.Im);
    }

    inline Complex operator - (const Complex& other) const {
        return Complex(this->Re - other.Re, this->Im - other.Im);
    }

    inline Complex operator * (const Complex& other) const {
        return Complex(this->Re * other.Re, this->Im * other.Im);
    }

    inline Complex operator / (const Complex& other) const {
        return Complex(this->Re / other.Re, this->Im / other.Im)
    }

    inline Complex cabs (Complex nr) {
        return Complex(fabs(Re), fabs(Im));
    }

    inline bool operator == (const Complex& other) const {
        return (this->Re == other.Re and this->Im == other.Im);
    }

    inline bool operator < (const Complex& other) const {
        return (Re == other.Re) ? (Im < other.Im) : (Re < other.Re);
    }

    inline bool operator > (const Complex& other) const {
        return (Re == other.Re) ? (Im > other.Im) : (Re > other.Re);
    }

    inline bool operator <= (const Complex& other) const {
        return *this == other || *this < other;
    }

    inline bool operator >= (const Complex& other) const {
        return *this == other || *this > other;
    }

    inline Complex& operator += (const Complex& other) {
        *this = *this + other;
        return *this;
    }

    inline Complex& operator -= (const Complex& other) {
        *this = *this + other;
        return *this;
    }

    inline Complex& operator *= (const Complex& other) {
        *this = *this * other;
        return *this;
    }

    inline Complex& operator /= (const Complex& other) {
        *this = *this / other;
        return *this;
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

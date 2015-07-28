#ifndef _PARSING_H
#define _PARSING_H
#pragma one
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
using namespace std;
const int maxSize = 1 << 20;

class pfstream {
private:
	int cursor;
	char buf[maxSize];
	FILE *f;
	inline void move() {
		++ cursor;
		if(cursor == maxSize) {
			cursor = 0;
			fread(buf, maxSize, 1, f);
		}
	}
	inline int todig(char c) {
		return c - '0';
	}

public:
	pfstream() {}
	pfstream(const char *fname) {
		f = fopen(fname, "r");
		cursor = 0;
		fread(buf, maxSize, 1, f);
	}

	inline pfstream &operator >> (int& N) {
		char sign = '+';
		while(!isdigit(buf[cursor])) {
			sign = buf[cursor];
			move();
		}

		N = 0;
		while(isdigit(buf[cursor])) {
			N = N * 10 + todig(buf[cursor]);
			move();
		}

		if(sign == '-')
			N = -N;
		return *this;
	}

	inline pfstream &operator >> (float& N) {
		char sign = '+';
		while(!isdigit(buf[cursor])) {
			sign = buf[cursor];
			move();
		}
		N = 0;
		while(isdigit(buf[cursor])) {
			N = N * 10 + todig(buf[cursor]);
			move();
		}

		if(buf[cursor] == '.') {
			float p = 0.1;
			move();
			while(isdigit(buf[cursor])) {
				N = N + p * todig(buf[cursor]);
				p *= 0.1;
				move();
			}
		}

		if(sign == '-')
			N = -N;
		return *this;
	}
};
#endif


#include "huge.h"
#include <cstdio>
#include <iostream>

int main() {
  Huge a(2), b(3);
  printf("%s %s\n", a.c_str(), b.c_str());
  cout << a <<' '<< b << '\n';
  return 0;
}

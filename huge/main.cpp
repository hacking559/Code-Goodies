
#include "huge.h"
#include <iostream>

int main() {
  Huge a(2), b(3);
  b += (a += b);
  cout << a << ' ' << b << '\n';
}

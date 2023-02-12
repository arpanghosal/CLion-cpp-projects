#include <iostream>

int max(int a, int b) {
  return (a > b) ? a : b;
}

double max(double a, double b) {
  return (a > b) ? a : b;
}

int main() {
  std::cout << max(3, 5) << std::endl;
  std::cout << max(3.14, 2.71) << std::endl;

  return 0;
}

// Run it using g++ func_overload.C -o func and then ./func



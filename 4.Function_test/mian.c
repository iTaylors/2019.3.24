#include <stdio.h>
#include <math.h>

int IsPrime(int x) {
  int i = 0;
  for (i = 2;i < x;++i) {
    if (x % i == 0) {
      return 0;
    }
  }
  return 1;
}

int main() {
  printf("%d\n",IsPrime(12));
}

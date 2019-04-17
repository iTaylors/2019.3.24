#include <stdio.h>
#include <stdlib.h>

int main() {
  int arr[3][4] = {
    {11,12,13,14},
    {21,22,23,24},
    {31,32,33,34}
  };
  int i = 0;
  int* p = (int*)&arr[0][0];
  printf("%d\n",*p);
  while (p <= (p + (3 * 4) - 1)) {
    printf("%d ",*p);
    ++i;
    p = p + i;
  }    
  return 0;
}

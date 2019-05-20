#include "Tree.h"

int main() {
  int a[14] = {9,7,85,3,546,5,2,6,74,5,30,1,4,4};
  int i = 0;
  for (;i < 14;++i) {
    printf("%d ",a[i]);
  }
  printf("\n");
#if 0
  int i = 0;
  int length = 10 - 1;
  for (;i < 10;++i) {
    CreateLeastHeap(a,length + 1);
    int t = a[0];
    a[0] = a[length];
    a[length] = t;
    length--;
  }
#endif 
  HeapSort(a,14);

  i = 0;
  printf("desc sorted:\n");
  for (;i < 14;++i) {
    printf("%d ",a[i]);
  }
  printf("\n");
  return 0;
}

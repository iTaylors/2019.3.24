#include "Tree.h"
#include <stdio.h>

//堆是一种逻辑上的完全二叉树 

int main() {
  int array[] = {6,9,13,7,1,8,2,4,5};
  int size = sizeof(array) / sizeof(array[0]);
#if 0
  CreateLeastHeap(array,size);
  // for (;i < 9;++i) {
  //   printf("%d ",array[i]);
  // }
  printf("Xiao Dui Wei:\n");
  int i = 0;
  while(i < 9) {
    printf("%d ",array[i]);
    ++i;
  }
  printf("\n");
#endif 
  
  int i = 0;
  CreateBiggestHeap(array,size);
  printf("Da Dui Wei:\n");
  while (i < 9) {
    printf("%d ",array[i]);
    ++i;
  }
  printf("\n");

  i = 0;
  AdjustUp2(array,size,size - 1);
  printf("Da Dui Wei':\n");
  // while (i < 9) {
  //   printf("%d ",array[i]);
  //   ++i;
  // }
  for (;i < 9;++i) {
    printf("%d ",array[i]);
  }
  printf("\n");

  
  return 0;
}

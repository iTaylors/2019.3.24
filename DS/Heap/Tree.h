#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Heap {
  int array[100];
  int size;//数据个数
} Heap;

typedef struct Node {
  int val;
  struct Node* left;
  struct Node* right;
} Node;


//int rootIdx 表示的是要调整的结点的下标
void AdjustDown(int tree[],int size,int rootIdx) {//传的是数组首元素的地址
                                                  //我要将数组建为 最小堆
  int leftIdx = 2 * rootIdx + 1;
  int rightIdx = 2 * rootIdx + 2;
  if (leftIdx >= size) {
    return;// -> 是叶子,调整结束,直接返回
  }//判断是否为叶子

  int minIdx = leftIdx;
  if (rightIdx < size && tree[rightIdx] < tree[leftIdx]) {
    minIdx = rightIdx;
  }//->如果不是叶子,这就找到最小孩子的下标 -> 最小孩子的下标就是 minIdx 

  if (tree[rootIdx] <= tree[minIdx]) {
    //最小的已经是堆了,满足堆的性质,停止
    return;
  }

  if (tree[rootIdx] > tree[minIdx]) {
    int t = tree[rootIdx];
    tree[rootIdx] = tree[minIdx];
    tree[minIdx] = t;

  }
  
  //如果发生了交换,则下面的树的堆性质可能被破环了,继续调整
  AdjustDown(tree,size,minIdx);

}

void AdjustUp(int tree[],int size,int child) {//这个 向上调整的结果就是 还是最小堆
  if (child == 0) {
    return;
  }

  int parent = (child - 1) / 2;
  if (tree[child] >= tree[parent]) {
    return;
  }

  int t = tree[child];
  tree[child] = tree[parent];
  tree[parent] = t;

  AdjustUp(tree,size,child);
}

//建堆:把无序数组变成满足堆的性质
//从最后一个非叶子结点,一直到 0 进行向下调整
//向下调整的前提是有限制的:必须左右子树已经是堆了,才可以向下调整
//最后一个结点 child 的下标: size - 1
//又因为最后一个非叶子结点一定是最后一个结点(child -> 其下标为 size - 1 )的双亲结点
//所以我这里就用 parent 来表示 最后一个非叶子结点 -> 其下标用 papa 表示
//由公示得: papa = (size - 1 - 1) / 2
// -> papa = (size - 2) / 2
void CreateLeastHeap(int tree[],int size) {//从最后一个非叶子结点,一直到 0 进行向下调整
                                             //其下标用 papa 或 i 来表示
  int i = (size - 2) / 2;
  for (;i >= 0;i--) {
    AdjustDown(tree,size,i);
  }
}

void HeapInit(Heap* pH,int array[],int size) {
  assert(size <= 100);
  memcpy(pH->array,array,size * sizeof(int));//先把数组拷进来
  pH->size =size;
  CreateLeastHeap(pH->array,pH->size);//给这个数组建堆
}



void HeapPush(Heap* pH,int v) {
  pH->array[pH->size++] = v;
  AdjustUp(pH->array,pH->size,pH->size - 1);
}


int HeapPop(Heap* pH) {//每次删除的都是当前的最小值 -> 即就是数组的首元素
  assert(pH);
  int v = pH->array[0];
  pH->array[0] = pH->array[pH->size - 1];
  pH->size--;
  AdjustDown(pH->array,pH->size,0);//删除后可能会破环堆的结构,所以要进行向下调整
  return v;
}


void AdjustDown2(int tree[],int size,int rootIdx) {
  int leftIdx = 2 * rootIdx + 1;
  int rightIdx = 2 * rootIdx + 2;
  if (leftIdx >= size) {
    return;
  }

  int maxIdx = leftIdx;
  if (rightIdx < size && tree[rightIdx] > tree[leftIdx]) {
    maxIdx = rightIdx;
  }

  if (tree[rootIdx] >= tree[maxIdx]) {
    return;
  }

  int t = tree[rootIdx];
  tree[rootIdx] = tree[maxIdx];
  tree[maxIdx] = t;

  AdjustDown2(tree,size,maxIdx);
}

void AdjustUp2(int tree[],int size,int child) {
  if (child ==0) {
    return;
  }

  int parent = (child - 1) / 2;
  if (tree[child] <= tree[parent]) {
    return;
  }

  int t = tree[child];
  tree[child] = tree[parent];
  tree[parent] = t;
  AdjustUp2(tree,size,child);
}

void CreateBiggestHeap(int tree[],int size) {
  int i = (size - 2) / 2;
  while (i >= 0) {
    AdjustDown2(tree,size,i);
    --i;
  }
}






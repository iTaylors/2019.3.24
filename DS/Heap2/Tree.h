#pragma once 
#include <stdio.h>
#include <stdlib.h>


//                     最小堆
void AdjustDown(int tree[],int size,int rootIdx) {//~的向下调整
  int leftIdx = 2 * rootIdx + 1;
  int rightIdx = 2 * rootIdx + 2;
  //当前结点是叶子,就返回
  if (leftIdx >= size) {
    return;
  }

  //当前结点不是叶子,就找出最小结点的下标
  int minIdx = leftIdx;
  if (rightIdx < size && tree[rightIdx] < tree[leftIdx]) {
    minIdx = rightIdx;
  }

  //若当前已经满足堆的性质,就返回
  if (tree[rootIdx] <= tree[minIdx]) {
    return;
  }

  //不满足堆的性质,就交换 tree[rootIdx] 的值与 tree[minIdx] 的值
  int t = tree[rootIdx];
  tree[rootIdx] = tree[minIdx];
  tree[minIdx] = t;

  //如果发生了交换,则下面的树的最小堆性质可能被破坏,所以需要继续调整
  AdjustDown(tree,size,minIdx);
}

void AdjustUp(int tree[],int size,int child) {//~的向上调整
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

  AdjustUp(tree,size,parent);
}

void CreateLeastHeap(int tree[],int size) {//运用向下调整来建最小堆
  //向下调整的前提是:当左右子树已经是堆时,才可以进行向下调整
  int i = (size - 2) / 2;// i 是最后一个非叶子结点
  for (;i >= 0;--i) {
    AdjustDown(tree,size,i);
  }
}

void CreateLeastHeap2(int tree[],int size) {//运用向上调整来建最小堆
  int i = size - 1;
  for (;i >= 0;--i) {
    AdjustUp(tree,size,i);
  }
}


//以上都是最小堆
//以下都是最大堆
//                            最大堆
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
  tree[rootIdx] = tree[rightIdx];
  tree[rightIdx] = t;

  AdjustDown2(tree,size,maxIdx);
}

void AdjustUp2(int tree[],int size,int child) {
  if (child == 0) {
    return;
  }

  int parent = (child - 1) / 2;
  if (tree[child] <= tree[parent]) {
    return;
  }

  int t = tree[child];
  tree[child] = tree[parent];
  tree[parent] = t;

  AdjustUp2(tree,size,parent);
}

void CreateBiggestHeap(int tree[],int size) {
  int i = (size - 2) / 2;
  for (;i >= 0;--i) {
    AdjustDown2(tree,size,i);
  }
}

void CreateBiggestHeap2(int tree[],int size) {
  int i = size - 1;
  for (;i >= 0;--i) {
    AdjustUp2(tree,size,i);
  }
}

//运用堆的找最值的特点,做具体应用
//1->优先级队列
//2->排序(升序时运用建大堆思想,降序时运用建小堆思想)
//3->TopK 问题:给海量数据(个数 N 个,远远大于 100亿),找到其中最大的 K(k << N) 个

void HeapSort(int array[],int size) {// sorted 的结果由具体的 建堆函数 决定 
  CreateLeastHeap(array,size);
  int i = 0;
  for (;i < size;++i) {
    int t = array[0];
    //array[0] = array[size - 1];下面的 减i 是点睛之笔
    array[0] = array[size - 1 - i];
    array[size - 1 - i] = t;

    AdjustDown(array,size - 1 - i,0);

  }
}
















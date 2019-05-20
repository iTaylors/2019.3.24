#pragma once 
#include <stdio.h>
#include <stdlib.h>

void Swap(int array[],int i,int j) {
  int t = array[i];
  array[i] = array[j];
  array[j] = t;
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
  tree[rootIdx] = tree[rightIdx];
  tree[rightIdx] = t;

  AdjustDown2(tree,size,maxIdx);
}

void CreateBiggestHeap(int tree[],int size) {
  int i = (size - 2) / 2;
  for (;i >= 0;--i) {
    AdjustDown2(tree,size,i);
  }
}

void HeapSort(int array[],int size) {
  CreateBiggestHeap(array,size);
  int i = 0;
  for (;i < size;++i) {
    int t = array[0];
    array[0] = array[size - 1 - i];
    array[size - 1 - i] = t;
    AdjustDown2(array,size - 1 - i,0);
  }
}

void InsertSort(int array[],int size) {
  int i = 0;
  for (;i < size;++i) {
    int j = i - 1;
    int key = array[i];

    for (;j >= 0;--j) {
      if (array[j] <= key) {
        break;
      }

      array[j + 1] = array[j];
    }
    array[j + 1] = key;
  }
}

void InsertSortWithGap(int array[],int size,int gap) {
  int i = 0;
  for (;i < size;++i) {
    int key = array[i];
    int j = i - gap;
    for (;j >= 0;j -= gap) {
      if (array[j] <= key) {
        break;
      }
      array[j + gap] = array[j];
    }
    array[j + gap] = key;
  }
}

void ShellSort(int array[],int size) {
  int gap = size;;
  while (1) {
    gap = gap / 3 + 1;
    InsertSortWithGap(array,size,gap);

    if (gap == 1) {
      return;
    }
  }
}

void SelectSort(int array[],int size) {
  int i = 0;
  for (;i < size;++i) {
    int maxIdx = 0;
    int j = 0;
    for (;j < size - 1;++j) {
      if (array[j] > array[maxIdx]) {
        maxIdx = j;
      }
    }
    Swap(array,maxIdx,size - 1 - i);
  }
}

void BubbleSort(int array[],int size) {
  int i = 0;
  int j = 0;
  for (;i < size;++i) {
    int isSorted = 1;
    for (;j < size - 1 - i;++j) {
      if (array[j] > array[j + 1]) {
        Swap(array,j,j + 1);
        isSorted = 0;
      }
    }
  }

}

//快速排序中,如何做到小的左,大的右,一共有三种方式
//1.Hover法:对数组中[low,high]的区间做分组;
//          基准值是array[low];
//          如果基准值在左边,则需要从右边开始执行程序(如果基准值在右边,则需要从左边开始);
//          这样做的目的是一定要保证区间内所有的数都与 基准值 去一一比较
int Partition_1(int array[],int low,int high) {//比基准值小的在左边,比基准值大的在右边
  int begin = low;
  int end = high;
  int pivot = array[low];

  while (begin < end) {// (begin,end) 区间内是没有被比较过的数据
    while (begin < end && array[end] >= pivot) {
      //优先是比较 begin < end 
      --end;//大区间向左扩张
    }//此循环结束(片面的)的条件是:array[end] < array[low](即基准值 pivot)

    if (begin == end) {
      break;
    }
    
    while (begin < end && array[begin] <= pivot) {//右边找完了就开始再在左边找
      ++begin;
    }//此循环结束(片面的)的条件是:array[begin] > array[low](即基准值 pivot)

    //上面两个小循环结束后:array[begin] > array[end]
    //所以要交换两者的值
    Swap(array,begin,end);
  }
  
  //大循环结束后的数组表现为
  // low 旧的基准值
  // [low + 1,begin] 此区间内数据都比基准值小
  // [begin + 1,hign]此区间内数据都比基准值大
  //下面要做的是:修改基准值 -> 把旧的基准值和比它小的最后一个数(array[begin])交换
  //(从而得到新的基准值 int pivot' = array[begin])
  Swap(array,low,begin);
  return begin;//->返回新的基准值的下标
}

//2.挖坑法:思路同上,基准值还是 array[low]
int Partition_2(int array[],int low,int high) {
  int begin = low;
  int end = high;
  int pivot = array[low];//此时 begin 就是坑的下标

  while (begin < end) {
    while (begin < end && array[end] >= pivot) {
      --end;
    }//同上:跳出循环时 array[end] < pivot,我要拿它去填坑了,坑在哪呢,由上知 begin 就是坑的下标 
     //所以直接让 end 变成坑就行了,即:见下一行代码
    array[begin] = array[end];

    while (begin < end && array[begin] <= pivot) {
      ++begin;
    }//循环跳出时:array[begin] > pivot
    array[end] = array[begin];// -> 重新让 begin 充当 坑的角色
  
  }
  array[begin] = pivot;//这就是法一中的"修改基准值"
  return begin;
}

//法3.前后指针法(实质上没有指针,只是这里用到了指针的思想)
//基准值是 array[low];
int Partition_3(int array[],int low,int high) {
  int d = low + 1;
  int i = low + 1;
  int pivot = array[low];
  while (i <= high) {
    if (array[i] >= pivot) {
      ++i;
    } else {
      Swap(array,d,i);
      ++d;
      ++i;
    }
  }

  Swap(array,d - 1,low);
  return d - 1;
}

void __QuickSort(int array[],int low,int high) {//需要排序的区间是[low,high]
  //左闭右闭的情况下跳出函数的条件:直到 size == 0 || size == 1
  if (low > high) {//此时区间内没有元素
    return;
  }
  if (low == high) {//即区间内只有一个元素 -> 天然有序
    return;
  }

  //1.找基准值,选最左边,基准值的下标是 low 
  //2.遍历整个区间,把小的放左,右的放右,返回基准值的下标(pivotIdx)
  
  int pivotIdx = Partition_2(array,low,high);//用找基准值的函数返回基准值的下标
  //3.区间被分成三部分
  //[low,pivotIdx - 1]   小
  //[pivotIdx,pivotIdx]  有序
  //[pivotIdx + 1,high]  大
  //分治算法,分别处理两个小区间(分治 -> 在程序中就是递归算法)
  __QuickSort(array,low,pivotIdx - 1);
  __QuickSort(array,pivotIdx + 1,high);

}
//选基准值由三种方式
//   1.选最边上(左边/右边)
//   2.随机法(降低最坏情况的可能性)
//   3.三数取中法

void QuickSort(int array[],int size) {
  __QuickSort(array,0,size - 1);
}
//时间复杂度:(在快排中指的是 二叉树高度)
//  最好O(n*log(n));
//  平均O(n*log(n));
//  最坏O(n ^ 2);
//空间复杂度:(在快排中指的是 调用栈)
//  最好O(log(n));
//  平均O(log(n));
//  最坏O(n);
//稳定性:不稳定

void Merge(int array[],int left,int mid,int right,int extra[]) {
  int i = left;
  int j = mid;
  int k = 0; // k 表示 数组 extra 的下标
  //int k = left;

  while (i < mid && j < right) {
    if (array[i] < array[j]) {
      extra[++k] = array[++i];
    } else {
      extra[++k] = array[++j];
    }
  }

  while (i < mid) {
    extra[++k] = array[++i];
  }

  while (j < right) {
    extra[++k] = array[++j];
  }//这两个 while 只能走到一个,相当于 while 起到了 if 的作用
  
  //把 extra 的数据移回来
  int x = left;
  for (;x < right;++x) {
    array[x] = extra[x - left];
    //对应的:array[x] = extra[x]
  }
}

//[left,right)
void __MergeSort(int array[],int left,int right,int extra[]) {
  //左闭右开的情况下跳出函数的条件:直到 size == 1 || size == 0
  if (right == left + 1) {
    return;
  }

  if (right <= left) {
    return;
  }

  //1.平分数组[left,mid) 和 [mid,right)
  int mid = left + (right - right) / 2;
  //2.分治:排序左右两部分
  __MergeSort(array,left,mid,extra);
  __MergeSort(array,mid,right,extra);

  //3.合并两个有序数组
  Merge(array,left,mid,right,extra);
}

void MergeSort(int array[],int size) {
  int* extra = (int*)malloc(sizeof(int) * size);
  __MergeSort(array,0,size,extra);
  free(extra);
}

void PrintArray(int array[],int size) {
  int i = 0;
  for (;i < size;++i) {
    printf("%d ",array[i]);
  }
  printf("\n");
}


void Test(){
  int array[] = {3,9,1,4,7,5,2,8,0,10,9};
  int size = sizeof(array) / sizeof(array[0]);
  PrintArray(array,size);
  //BubbleSort(array,size);
  //HeapSort(array,size);
  //InsertSort(array,size);
  //ShellSort(array,size);
  //SelectSort(array,size);
  //QuickSort(array,size);
  MergeSort(array,size);
  PrintArray(array,size);
}











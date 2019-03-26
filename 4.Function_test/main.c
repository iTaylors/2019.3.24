//7种排序和来链表的相关代码一定一定到做到倒背如流
#pragma once // 表示该头文件，不管被 include 几次，实际只进行复制粘贴一次
             // 任何一个 .h 文件，都应该包含这个预处理指令
             // C语言中凡是 # 开头的都是预处理指令
             // .h文件里面放函数的声明
             // .c文件里面放函数的定义
#include <stdio.h>
#include <math.h>
#include <string.h>

int IsPrime(int x) {
  int i = 0;
  if (x == 1) {
    return 0;
  }
  if (x == 2) {
    return 1;
  }
  for (i = 2;i < x;++i) {
    if (x % i == 0) {
      return 0;
    }
    return 1;
  }
}

int IsLeapYear(int year) {
  if (year % 100 == 0) {
    if (year % 400 == 0) {
      return 1;
    }
    return 0;
  }
  if (year % 4 == 0) {
    return 1;
  }
  return 0;
}

int BinarySearch(int arr[],int size,int to_find) {//二分查找函数
  if (size <= 0) {
    return -1;
  }
  int left = 0;
  int right = size - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (to_find < arr[mid]) {
      right = mid - 1;
    } else if (to_find > arr[mid]) {
      left = mid + 1;
    } else {//即 to_find == arr[mid];
      return mid;
    }
  }
  return -1;//表示没找到
}

void Fun(int* num) {//每调用一次这个函数，就会将num的值增加 1
  ++* num;
  //*num = *num + 1;
}

int Fun2(int num) {//同上
  return num + 1;
}

int Strlen2(char str[]) {
  int size = 0;
  while (str[size] != '\0') {
    ++size;
  }
  return size;
}

int Strlen1(char str[]) {//递归就是盗梦空间
  if (str[0] == '\0') {
    return 0;
  }
  return Strlen1(str + 1) + 1;
  //第一次：'a' != '\0',
}

//打印 数字 n 的每一位
void PrintNum(int x) {//递归就是盗梦空间
  if (x > 9) {// 如10 > 9;100 > 9;1000 > 9
    PrintNum(x / 10);
  }
  printf("%d ",x % 10);
}

int Factor(int n) {//求 n 的阶乘
  int result = 1;
  int i = 0;
  for (i = 1;i < n;++i) {
    result *= i;
  }
  return result;
}

int Factor2(int n) {
  if (n == 1) {
    return 1;
  }
  return n * Factor2(n - 1);
}

long long g_count = 0;

int Fib(int n) {//斐波那契数列
  if (n == 3) {
    ++g_count;
  }
  if (n == 1 || n== 2) {
    return 1;
  }
  return Fib(n - 1) + Fib(n - 2);
}

#define ROW 9
#define COL 9

int main() {
  


  //将三个数按照由大到小输出
  int a = 10;
  int b = 20;
  int c = 30;
  if (a < b) {
    int tmp = a;
    a = b;
    b = tmp;
  }
  if (a < c) {
    int tmp = c;
    c = a;
    a = tmp;
  }
  printf("%d > ",a);
  if (b < c) {
    printf("%d >",c);
    printf("%d",b);
  } else {
    printf("%d >",b);
    printf("%d",c);
  }
  printf("\n");


#if 0
  //找出擂台上最大的数
  int arr[] = {1,2,3,4,7,9,5,6};
  int max = arr[0];
  int i;
  for (i = 1;i < sizeof(arr) / sizeof(arr[0]);++i) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  printf("%d\n",max);
#endif 
  //找出擂台上前 k 大的数:  top k 问题
  


#if 0
  //先把规律总结好，并且把规律写下来啊(把规律写下来和记脑瓜里面这是两个完全不同的概念
  //作为一个程序员，是深刻知道自己的缺陷的，既然知道自己的缺陷那么就把它写下来，这样
  //的话减少脑瓜的负担，还能够在以后回过头来看代码时更易看懂)
  //                                                                -------汤神语录
  //打印乘法口诀表
  //1.一共 9 行
  //2.每一行的列数和当前的行号是相同的
  //3.想乘的两个数，第一个数：列数;第二个数：行数
  int row;
  for (row = 1;row <= ROW;++row) {
    int col = 1;
    for (;col <= ROW;++col) {
      if (col > row) {
        continue;
      }
      printf("%d*%d=%d  ",col,row,col * row);
    }
    printf("\n");
  }
#endif 

  //printf("%d\n",Factor(10));
  //printf("%d\n",Factor2(10));
  //PrintNum(1234);

#if 0
  char str[] = "abcd";
  int ret = Strlen1(str);
  printf("%d\n",ret);
#endif 

#if 0
  char str[] = "abcd";//字符数组
                      //字符数组是一个更广义的概念，只有以 \0 结尾的字符数组才能称之为字符串
  int ret = Strlen2(str);
  printf("%d\n",ret);
#endif 

#if 0
  int num = 0;
  int i = 0;
  for (i = 0;i < 10;++i) {
    Fun(&num);
    printf("%d ",num);
  }
  for (i = 0;i < 10;++i) {
    num = Fun2(num);
    printf("%d ",num);
  }
#endif  

#if 0
  int arr[] = {1,2,3,4,5,6};//数组名最好要见名知意
  int size = sizeof(arr) / sizeof(arr[0]);
  int ret = BinarySearch(arr,size,4);// ret 表示数组的下标序号
  printf("ret = %d\n",ret);
#endif 

#if 0
  int year;
  for (year = 1900;year <= 2000;++year) {
    if (IsLeapYear(year)) {
      printf("%d\n",year);
    }
  }
#endif 

#if 0
  int i = 0;
  for (i = 1;i <= 100;++i) {
    //if (IsPrime(i) == 1)//这个写法是错的
    if (IsPrime(i)) {
      printf("%d ",i);
    }
  }
  printf("\n");
#endif







}

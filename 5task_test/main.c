#include <stdio.h>
#include <math.h>
#include <string.h>

// C 和 C++ 的区别
// C++ 变成了一种"联邦语言"，支持多种编程风格，并且一直在持续发展
// 《Effective C++》必读
// 开篇
// 1.兼容 C 语言的部分
// 2.面向对象的部分
// 3.泛型编程
// 4.STL -> standrd template library
// 5.函数式编程的部分

int MaxGongyue(int x,int y) {//公约数函数
  int max_gongyue = 0;//保存了当前的最大公约数

  int num = 1;//num:当前作为公约数来逐步试探
  while (num <= x && num <= y) {
    if (x % num == 0 && y % num == 0) {
      max_gongyue = num;
    }
    ++num;
  }
  return max_gongyue;
}

int NineCount(int x) {//判断两位数 x 的每一位有多少个 9;
  int count = 0;
  if (x % 10 == 9) {
    ++count;
  }
  if (x / 10 == 9) {
    ++count;
  }
  return count;
}

void PrintLine(int blank_cnt,int star_cnt) {//逐行打印菱形的每一行
  int i;
  for (i = 0;i < blank_cnt;++i) {
    printf(" ");
  }
  for (i = 0;i < star_cnt;++i) {
    printf("*");
  }
  printf("\n");
}

int IsShuixian(int num) {//水仙花数
  int tmp = num;
  int x1 = num % 10;
  num /= 10;
  int x2 = num % 10;
  num /= 10;
  int x3 = num % 10;
  if (x1 * x1 * x1 + x2 * x2 * x2 + x3 * x3 * x3 == tmp) {
    return 1;
  }
  return 0;
}

//第一项 2
//第二项 22 => 2 * 10 ^ 1 + 2 * 10 ^ 0
//第三项 222 => 2 * 10 ^ 2 + 2 * 10 ^ 1 + 2 * 10 ^ 0
int CreateNum(int a,int n) {//创建出第 n 项的内容
  if (a > 9 || a <=0 || n <= 0) {
    return 0;
  }
  int num = 0;
  int i;
  for (i = 0;i < n;++i) {
    //num += a * (int)pow(10,i);
  }
  return num;
}

void Init(int arr[],int size) {//数组的初始化
  //把数组中的每个元素都初始化为 0 ；
  memset(arr,0,size * sizeof(arr[0]));//memset函数是一个字节一个字节的填充的
}

void Empty(int arr[],int size) {//数组的清空
  Init(arr,size);
}

void Swap(int* x,int* y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

void Reverse(int arr[],int size) {//数组的逆置:1 2 3 4 -> 4 3 2 1
  if (size <= 1) {
    return;
  }
  int left = 0;
  int right = size - 1;
  while (left < right) {
    Swap(&arr[left],&arr[right]);//交换两个下标所代表的元素
    ++left;
    --right;
  }
}

int Fib(int n) {//递归实现斐波那契数列
  if (n == 1 || n == 2) {
    return 1;
  }
  return Fib(n - 1) + Fib(n - 2);
}
int Fib2(int n) {//循环实现斐波那契数列
  if (n == 1 || n == 2) {
    return 1;
  }
  int n_1 = 1;
  int n_2 = 1;
  int n_i;
  int i;
  for (i = 3;i <= n;++i) {
    n_i = n_2 + n_1;
    n_2 = n_1;
    n_1 = n_i;
  }
  return n_i;
}
//循环和递归这两种代码的实现形式可以相互转换，有些场景下使用循环更简单，
//有些场景下使用递归更简单(从代码实现的角度)
//但是多数场景下，循环版本代码的执行效率，要高于递归版本的执行效率。

//void*
//1.万金油，可以存储任何类型变量的地址
//2.不能解引用
//3.不能进行算术运算

int main() {
  printf("%d\n",Fib2(10));

#if 0
  int arr[] = {1,2,3,4};
  //Init(arr,sizeof(arr) / sizeof(arr[0]));
  Reverse(arr,sizeof(arr) / sizeof(arr[0]));
  int i;
  for (i = 0;i < sizeof(arr) / sizeof(arr[0]);++i) {
    printf("%d\n",arr[i]);
  }
#endif 
  
#if 0  
  int a = 10;
  char b = 20;
  void* p = &a;
  p = &b;
  printf("%c\n",*p);//非法的解引用操作 -> 即 void* 不能解引用
  printf("%p\n",p);
  printf("%p\n",p + 1);// void* 是未知的大小 -> void* 不能进行算术运算
#endif 

#if 0
  while (1) {
    int c = getchar();
   if (c == EOF) {
      break;
    }
    if (c >= 'a' && c <= 'z') {
      putchar(c - ('a' - 'A'));
    } else if (c >= 'A' && c <= 'Z') {
      putchar(c + ('a' - 'A'));
    } else if (c >= '0' && c <= '9'){
      continue;
    } else {
      putchar(c);
    }
  }
#endif 

  //printf("%d\n",CreateNum(2,1) + CreateNum(2,2) + CreateNum(2,3) + CreateNum(2,4));
#if 0
  int i;
  for (i = 100;i < 999;++i) {
    if (IsShuixian(i)) {
      printf("%d\n",i);
    }
  }
#endif 

#if 0 
  //打印菱形：上半部分 
  //          第1行：6空格，1星号
  //          第2行：5空客，3星号 
  //          第3行：4空格，5星号 
  //          第i行：(7 - i) 空格，(2 * i - 1)星号 
  int i;
  for (i = 1;i <= 6;++i) {//打印上半部分
    PrintLine(7 - i,2 * i - 1);
  }
  PrintLine(0,2 * 7 - 1);//打印中间部分
  for (i = 6;i >= 1;--i) {//打印下半部分
    PrintLine(7 - i,2 * i - 1);
  }
#endif 

#if 0
  //数一下 1 - 100 中 9 出现的次数
  int i = 0;
  int count = 0;
  for (i = 1;i < 100;++i) {
    count += NineCount(i);
  }
  printf("%d\n",count);
#endif 

#if 0
  double sum = 0;
  int i = 0;
  for (i = 1;i <= 100;++i) {
    if (i % 2 == 1) {
      sum += (double)1 / (double)i;
    } else {
      sum -= (double)1 / (double)i;
    }
  }
  printf("%d\n",sum);//注意格式
  printf("%f\n",sum);//%f 可输出 float 和 double 型
#endif 

#if 0 
  //交换两个长度相同的数组元素
  int arr1[] = {1,2,3,4};
  int arr2[] = {4,3,2,1};
  int i = 0;
  for (i = 0;i < sizeof(arr1) / sizeof(arr1[0]);++i) {
    int tmp = arr1[i];
    arr1[i] = arr2[i];
    arr2[i] = tmp;
  }
  printf("arr1[]:");
  for (i = 0;i < sizeof(arr1) / sizeof(arr1[0]);++i) {
    printf("%d ",arr1[i]);  
  }
  printf("\n");
  printf("arr2[]:");
  for (i = 0;i < sizeof(arr1) / sizeof(arr1[0]);++i) {
    printf("%d ",arr2[i]);
  }
  printf("\n");
#endif

  //printf("%d\n",MaxGongyue(33,45));
}

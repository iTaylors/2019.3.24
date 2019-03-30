//读书是一种习惯    ------汤神
//C++提供的智能指针，不支持算术运算
// == != < > <= >= 这些称之为关系运算
//void* 未知的大小：指向的房间的大小是未知的
//未定义行为:只有越界访问非法内存，才是未定义行为

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int PointerSame(void* x,void* y) {//判断两个指针是否相等的函数
                                  //实质上比较的是指针指向的地址房间号是否相同
                                  //由于void*不关注房间大小,其可以保存各种类型的地址如int*char*
                                  
  if (x == y) {
    return 1;
  }
  return 0;
}
//而 strcmp 这个函数的实现实际上运用的就是这个思想：它依次比较的是指针指向的房间号
//是否相同，而不去关心房间中的内容
//因为在内存的世界中，每个房间号都是独一无二的，(进一步理解：但房间中的内容不一定是独一无二的)
//如 0x500 中存的是数字 7(0000 0111)，0x5000中也可能存的是数字 7(0000 0111)
//只要两个指针指向的房间号相同，那么
//这两个指针就指向了同一个房间号，其内容当然就是一样的喽！！！！

int main() {
  //注意：64位操作系统下所有指针都占8个字节，其他如int,char,shortdouble,long所占的字节数不变
#if 0
  int a[3][4] = {0};
  printf("%d\n",sizeof(a[0]));//16 -> a[0]得到的不是指针，而是一行四列的一维数组
  printf("%d\n",sizeof(a[0] + 1));//8 -> 一维数组名(即a[0])隐式转化为指针
  /*
  printf("%d\n",sizeof(*(a[0] + 1)));//16 -> a[0] + 1是指向第二行一维数组的指针.......
  很可惜这样的理解是错的，因为你忘记了有一个公式是这样的: *(p + 1) = p[1]
  */
  printf("%d\n",sizeof(*(a[0] + 1)));//4 -> *(a[0] + 1) 等价于 a[0][1];
  printf("%d\n",sizeof(a));//48 -> 3 * 4 * 4
  printf("%d\n",sizeof(a + 1));//8 -> 二维数组名参与运算，隐士转化为指针
  printf("%d\n",sizeof(*(a + 1)));//16 -> *(a + 1) = a[1];求第二行一维数组的大小。即为4 * 4
  printf("%d\n",sizeof(&a[0]) + 1);//8 -> 只要是指针，不管它是普通指针,二级指针,还是数组指针
                                   //只要是指针，就不要多想，通通都是 8 
  printf("%d\n",sizeof(*(&a[0]) + 1));//16 -> 对上一行的解引用
  printf("%d\n",sizeof(*a));//16 -> *a 等价于 a[0];
                            //对于 n 维数组(假设其数组明是arr),*arr这个操作的结果都是求取
                            //这个 n 维数组的"第一个"元素
#endif 

#if 0  
  char a[] = "abcdef";
  printf("%d\n",sizeof(a));//7 -> 因为 '\0' 也要用一个字节来保存，所以将 '\0' 计算在内
  printf("%d\n",strlen(a));//6 -> 数组名参与运算时隐士转化为char*型的指针，且一开始指向'a'
  printf("%d\n",strlen(&a[0] + 1));//5 -> char* 一开始指向'b',然后一个一个指下去直到触发跳出
  printf("%d\n",strlen(*a));//未定义行为，char 与 char* 类型不匹配
  printf("%d\n",strlen(a[1]));//同上
  printf("%d\n",strlen(&a));//未定义行为，(char*)[6] 与 char* 类型不匹配
  printf("%d\n",strlen(&a + 1));//数组"访问(通过数组指针来进行访问)"越界，&a再加1就指到'f'后了  
                                //同时数组指针(char*)[6] 与 char* 类型不匹配 
#endif 

#if 0
  char* s = "abcdef";
  printf("%d\n",sizeof(s));//8 -> 一级指针。(就是char*)
  printf("%d\n",sizeof(*s));//1->对数组名进行解引用，会隐式转化为指针，*后即表示第一个元素'a';
  printf("%d\n",sizeof(s[0]));//1 -> s[0] == 'a';
  printf("%d\n",sizeof(&s));//8 -> 二级指针.(就是char**)
  printf("%d\n",sizeof(&s[0] + 1));//8 -> 一级指针
  printf("%d\n",strlen(s));//6 -> strlen在计算字符串长度时，遇到'\0'时就跳出，不会把'\0'算进去
  printf("%d\n",strlen(s + 1));//5 -> 
  printf("%d\n",strlen(&s[0] + 1));//5 -> 一级指针char* 一开始指向'b',然后一个一个指下去
  printf("%d\n",strlen(*s));//char型的'a'与strlen 的参数char*类型不兼容->未定义行为
  printf("%d\n",strlen(&s));//身为二级指针的'&s'与strlen的参数char*类型不兼容
#endif 

#if 0
  char a[6] = {'a','b','c','d','e','f'};
  printf("%d\n",sizeof(a + 0));//char*,它指向的房间的大小为 1(char型) 个字节
  printf("%d\n",sizeof(&a));//(char*)[6],(在此题中)它指向的房间的大小为 6(1 * 6) 个字节
  printf("%d\n",strlen(a));//数组越界就叫未定义行为
  printf("%d\n",strlen(a + 0));//未定义行为
  printf("%d\n",strlen(&a[0] + 1));//未定义行为·
  //printf("%d\n",strlen(*a));// *a -> 'a'(是char型),而strlen函数的参数是char*,二者类型不兼容
  //printf("%d\n",strlen(a[1]));//同上，类型不兼容
  //printf("%d\n",strlen(&a));//(char*)[6]与strlen 的参数char*类型不兼容
  //printf("%d\n",strlen(&a + 1));//同上
#endif 

#if 0
  int a[] = {1,2,3,4};
  printf("%d\n",sizeof(a + 0));//int*,它指向的房间的大小为 4(int型) 个字节
  printf("%d\n",sizeof(&a));//(int*)[4],(在此题中)它指向的房间的大小为 16(4 * 4) 个字节
  printf("%p\n",&a);//取到的是指针变量 p = &a 这一数组指针的地址
  printf("%p\n",&a[0]);//取到的是数组首元素的地址
  //这两个地址虽然在外在表现上完全一样，但它俩的本质不同，注意区分
  printf("%d\n",sizeof(&a[0]));//8
  printf("%d\n",sizeof(*&a));//16 -> * 和 & 是互逆运算，抵消的结果是普通的一维数组(占16个字节)
#endif 
  
  //指针数组
  //int* a[1] = {0};// -> int* a[1] = {NULL};
   
#if 0
  //二级指针
  int a = 10;
  int* p = &a;
  int** pp = &p;
  printf("%p\n",p);
  printf("%p\n",pp);
#endif 

#if 0
  int a = 10;
  const int* p = &a;// p 指向的内容不能修改
  //(int const * p = &a;同上)
  int* const p = &a;// p 的指向不能修改
#endif 

#if 0
  int a = 10;
  void* p = &a;
  printf("%d\n",*p);//void* 类型的指针不能解引用
  printf("%p\n",p);//这个可以实现，不会报错
  printf("%p\n",p + 1);//void* 类型的指针不能和整数进行相加减 
#endif 

#if 0
  int arr[4] = {1,2,3,4};
  printf("%p\n",arr + 1);
  printf("%p\n",&arr + 1);//&arr 是一个指向整个数组的指针，称为数组指针
                          
  //数组是数据类型:如arr[4] 与 brr[5]是两种不同的数据类型
  int brr[5] = {1,2,3,4,5}
#endif 

#if 0
  //下面这俩货等价
  if (p == NULL) {

  }
  if (!p) {// 判定 p 是否为 NULL 
           //如果 (p != NULL) p 是一个非空的指针，则为真(非0)，再逻辑取反后就为假(0), if 条件就进不去了
           //如果 p == NULL ，则为假(0)，再逻辑取反后就为真(非0)，进入  if 条件

  }

  //下面这俩货也等价
  if (p != NULL) {

  }
  if (p) {//判定 p 是否非空 

  }
#endif 

#if 0
  char arr1[] = "hehe";
  char arr2[] = "hehe";
  char* p1 = arr1;
  char* p2 = arr1;
  printf("%d\n",PointerSame(p1,p2));
  printf("%d\n",PointerSame(arr1,arr2));

  if (strcmp(arr2,arr1) == 0) {
    printf("ok\n");
  } else {
    printf("failed\n");
  }
#endif 

#if 0
  //指针的相减:是指针加减整数的逆运算 -> 其结果是两个指针之间隔了多少个元素
  //只有两个指针指向了同一个连续的内存空间，此时才是有意义的
  int arr[] = {1,2,3,4};
  int* p1 = arr;
  int* p2 = arr + 3;
  printf("%d\n",p2 - p1);
#endif 

#if 0
  int arr[] = {1,2,3,4};
  //取到数组中第三个元素有三种方法：
  printf("%d\n",arr[2]);
  int* p = arr;
  printf("%d\n",p[2]);//可以理解为 p 先加 2，再解引用 
  printf("%d\n",*(p + 2));

  int* q = arr + 3;
  printf("%d\n",q[-1]);// [] 中也可以填负数(前提是 q 必须指向有效的内存)
#endif 
  
#if 0
  int arr[] = {1,2,3,4};
  //取数组首地址有两种方法
  printf("%p\n",&arr);
  printf("%p\n",&arr[0]);
#endif 

#if 0
  //不同类型指针加减整数的运算结果如下:
  //不同类型指针的本质区别：其所指向的房间的大小
  //char*    -> 1
  //short*   -> 2
  //int*     -> 4
  //double*  -> 8
  //void*    -> Unknown
  
  //char* p = NULL;// 0
  //p = p + 1;
  //printf("%p\n",p); //-> 0x1

  //short* p = NULL;//0
  //p = p + 1;
  //printf("%p\n",p);// -> 0x2
  
  //int* p = NULL;// 0
  //p = p + 1;
  //printf("%p\n",p);// -> 0x4
  
  double* p = NULL;// 0
  p = p + 1;
  printf("%p\n",p);//   -> 0x8
#endif 

#if 0
  int a = 10;
  char* p = &a;
  printf("%x\n",*p);
  
  //大端序：低位在高地址上 -> 高位在低地址上(只记大端序！小端序不记！！！！) 
  //小端序：低位在低地址上
#endif 

  //32位操作系统上的指针是32位的(占4个字节)，能够表示 4G 个房间号
  //64位操作系统上的指针是64位的(占8个字节)，能够表示 16E 个房间号   
  //2^64=2^10 * 2^10 * 2^10 * 2^10 * 2^10 * 2^10 * 2^4
  //    =              1GB   * 1KB   * 1KB   * 1KB   * 16
  //    =                      1TB   * 1KB   * 1KB   * 16
  //    =                              1PB   * 1KB   * 16
  //    =                                      1EB   * 16
  //    =                                              16EB
#if 0
  int a = 10;
  int* p = &a;
  int** q = &p;
  printf("%d ,%d\n",p,q);
  printf("%x ,%x\n",p,q);//用十六进制来打印
  printf("p 的地址是:%p ,q 的地址是:%p\n",p,q);//%p 这个格式化字符串是专门用于打印 指针类型 变量的
  printf("%d\n",*p);
  printf("%d\n",*q);
#endif 
  return 0;
}





















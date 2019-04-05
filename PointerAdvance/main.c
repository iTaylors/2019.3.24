//编译：将 .c 文件转化为 .exe 文件( -> 二进制的指令)(所有的文件都是放在外存中的)



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//I.当一个函数的参数部分为一级指针的时候，函数能接受什么参数?
//II.当一个函数的参数部分为二级指针的时候,函数能接受什么参数?

// Makefile 的功能是编译(对照 VS 中的"重新生成解决方案")
// int (*arr)[5]        // 数组指针的应用很少,多数情况下只是被用作"二维数组传参" 

                 /* 作为函数形参时 int** 与 int* arr[5] 是可以相互转换的 */
                 /* 同理，作为.... int*  与 int arr[5] 是可以相互转换的  */
void Test(int (*arr)[5]) {// -> 这个函数的形参是数组指针.
  (void)arr;
}

void Test1(int arr[3][5]) {// 这样的参数更易理解,与上面的函数对照理解就会体会更深
  (void)arr;
}

void Test2(int arr[100]) {// -> int* arr 因为数组名被当作参数传递的时候，会隐式转化为指针
  (void)arr;
}

void Test3(int* arr[20]) {
  (void)arr;
}

typedef int* T;   //将 int* 重定义为 T
void Test4(T* arr) {
  (void)arr;
}

int Func() {
  printf("hehe\n");
  return 10;
}

int Add(int x,int y) {
  return x + y;
}

int Sub(int x,int y) {
  return x - y;
}

int Mul(int x,int y) {
  return x * y;
}

int Div(int x,int y) {
  return x / y;
}

int Menu() {
  printf("1.add\n");
  printf("2.sub\n");
  printf("3.mul\n");
  printf("4.div\n");
  int choice = 0;
  scanf("%d",&choice);
  return choice;
}

void Swap(int* x,int* y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

#if 0
void BubbleSort(int arr[],int size,int is_desc) {
  for (int bound = 0; bound < size;++bound) {
    for (int cur = size - 1;cur > bound;--cur) {
      if (is_desc == 1) {
        if (arr[cur - 1] < arr[cur]) {
          Swap(&arr[cur - 1],&arr[cur]);
        }
      } else if (is_desc == 0) {
        if (arr[cur - 1] > arr[cur]) {
          Swap(&arr[cur - 1],&arr[cur]);
        }
      }
      
    }
  }
}
#endif 

#if 0
typedef int(*T)(int,int);
void BubbleSort2(int* arr,int size,T cmp) {
  for (int bound = 0;bound < size;++bound) {
    for (int cur = size - 1;cur > bound;--cur) {
      if (cmp(arr[cur - 1],arr[cur] == 0)) {
        Swap(&arr[cur - 1],&arr[cur]);
      }
    }
  }
}
#endif 

struct Test {
  int Num;
  char* pcName;
  short sDate;
  char cha[2];
  char sBa[4];
} *p;

int main() {
  int a = 10;
  int* p = &a;
  printf("%d\n",p);
  printf("%d\n",(char*)p);
#if 0
  char* c[] = {"ENTER","NEW","POINT","FIRST"};
  //char* c[] = {p1,p2,p3,p4};数组保存的是四个字符串首元素的地址p1,p2,p3,p4              
  
  char** cp[] = {c + 3,c + 2,c + 1,c};
  //char** cp[] = {&p4,&p3,&p2,&p1};数组保存的是p1,p2,p3,p4的地址
  
  char*** cpp;
  //char*** 指向的类型是 char** (如即&p4)
  
  cpp = cp;//cpp 保存的是 cp 数组的首元素地址(即&p4)
  //运算顺序是 * ++ *
  printf("%s\n",**++cpp);
  
  printf("%s\n",*--*++cpp + 3);
  
  //运算顺序是 [] * +
  //注意：经过前两步，此时 cpp = &&p2;
  printf("%s\n",*cpp[-2] + 3);

  //对指针变量 cpp 执行 cpp[-2] 操作时,这样的减不会影响到 cpp 的指向,其功能就是单纯的
  //找到 cpp - 2 的位置(然后进行解引用)  

  //[i] 这个运算符包括两个操作1 -> 取地址.2 -> 对地址解引用
  //cpp[-2] -> &p4
  //对 &p4 解引用得 p4
  //对 (p4 + 3) 执行%s -> ST
  
  printf("%s\n",cpp[-1][-1] + 1);
  //cpp = &&p2;
  //同上，cpp[-1] -> &p3 
  //现在可以自己定义一个 char** 类型得指针变量 p：char** p = &p3 
  
  //对指针变量 p 执行 p[-2] 操作时,这样的减不会影响到 p 的指向,其功能就是单纯的
  //找到 p - 2 的位置(然后进行解引用)

  //接着执行 p[-1],同样分两步1.取地址得 &p2 
  //                         2.解引用得 p2 
  //对 (p2 + 1) 执行%s -> EW      
#endif 

#if 0
  char* a[] = {"Just","do","what","you","should","do!"};
  //用一个(指针)数组来保存 6 个字符串的首地址(  p1    p2    p3    p4    p5    p6
  //                  假设六个地址分别为      0x100,0x200,0x300,0x400,0x500,0x600)
  //       要占用内存     也要占用内存(具体占内存的大小由各个字符串的大小决定)
  //       所有指针在 64 位系统下都占 8 个字节(包括char*,int*.......)
  //       0x1000 -> 其内保存 0x100
  //       0x1008 -> 其内保存 0x200
  //       0x1016 -> 其内保存 0x300
  //       ......(以此类推)
  
  char** p;
  //char** 指向的类型是char*
  
  p = a;
  //p 中保存的是数组的首地址(即 0x1000);// p 指向了 0x1000
  
  ++p;
  //p 指向了 0x1008
  //下面是我尝试打印出整句话,结果吐核了
  printf("%s\n",*p);
  for (p = a;p <= p + 5;++p) {
    printf("%s ",*p);
  }
  printf("\n");
#endif 

#if 0
  int aa[2][5] = {1,2,3,4,5,6,7,8,9,10};
  int* p1 = (int*)(&aa + 1);
  int* p2 = (int*)(*(aa + 1));
  printf("%d,%d\n",*(p1 - 1),*(p2 - 1));
#endif 

#if 0
  int a[5][5];
  int(*p)[4];
  p = a;
  printf("%p,%p,%d\n",&a[4][0],&p[4][0],&a[4][0] - &p[4][0]);//打印的是跳过的元素个数
  //见截屏图片
#endif 

#if 0
  // 假设 a 对应的地址是 0x ff ff ff ff 00 00 00 01
  // 0x 00 00 00 01
  // 0x 00 00 00 02
  // 0x 00 00 00 00 00 00 00 02
  int a[4] = {1,2,3,4};
  int* ptr1 = (int*)(&a + 1);
  //对应上面的解释 -> int 占四个字节int* ptr2 = (int*)((int)a + 1);
  //改进
  int* ptr2 = (int*)((long)a + 1);
  //long 占 8 个字节
  // 假设 a 对应的地址是 0xff ff ff ff 00 00 00 01
  // 强转 long       ->  0xff ff ff ff 00 00 00 01
  // long + 1        ->  0xff ff ff ff 00 00 00 02
  // 将上者转化为int*->  0xff ff ff ff 00 00 00 02
  printf("%x,%x",ptr1[-1],*ptr2);
#endif 

  // p = NULL;
  // printf("%p\n",p + 1);
  // printf("%p\n",(unsigned long)p + 1);//0x1,就是单纯的 0 + 1
  // printf("%p\n",(int*)p + 1);//0x4,指针加减整数
  // printf("%p\n",(char*)p + 1);//0x1,指针加减整数
  // int a[5] = {1,2,3,4,5};
  // int* ptr = (int*)(&a + 1);
  // printf("%d,%d\n",*(a + 1),*(ptr - 1));

  //函数指针数组的应用:转移表
#if 0
  int choice = Menu();
  // 这是一个通常的写法，其圈复杂度较高
  // if (choice == 1) {
  //   Add(10,20);
  // } else if (choice == 2) {
  //   Sub(10,20);
  // } else if (choice == 3) {
  //   Mul(10,20);
  // } else if (choice == 4) {
  //   Div(10,20);
  // }
  

  // 可以使用表驱动(转移表)的方式来解决圈复杂度高的问题
  // 函数指针数组最重要的应用场景
  typedef int(*T)(int, int);
  T arr[] = {
    Add,
    Sub,
    Mul,
    Div
  };
  arr[choice - 1](10,20);
  

  // 函数指针数组
  // int (*parr1[10])();
  // typedef int(*T)();
  // T parr2[10];
#endif 

#if 0
  函数指针
  /* 对于函数指针来说,最重要的操作是 () -> 函数调用 */ 
  // printf("%p\n",Func);//   -> 0x4005af 打印这个函数在内存中的地址,这里的 Func 就是函数指针
  // printf("%p\n",&Func);//  -> 0x4005af   

  /* 下面这俩操作是完全等价的,都是函数的调用,只是第二种方式看起来很别扭 */
  // printf("%d\n",Func()); () 是函数调用操作符
  // printf("%d\n",(*Func)());
  
  int (*p)() = Func;// -> 此时定义了一个指针变量 p 的类型是 int(*)()
  typedef int(*T)();// 此时定义了一个类型的别名 T = int(*)()
  p();// 如果定义了某种函数指针类型的指针变量,它的用处其实说白了也是函数调用
  
  int (*p2)(int,int) = Add;
  typedef int(*H)(int,int);// 此时定义了一个类型的别名 H= int(*)(int,int)
  p = p2;
  int ret = p();
  printf("ret = %d\n",ret);
#endif 
  
#if 0
  int* arr[20];
  Test3(arr);
  Test4(arr);

  // int arr[3][5];
  // Test(arr);
  // int arr2[5];
  // Test2(arr2);

  // int* arr[5];       //指针数组
  // const char* arr[] = {//这个数组的三个元素分别是指向三个字符字符串首元素的指针
  //   "hehe",
  //   "haha",
  //   "aaaa"
  // };

  //int (*arr)[5];      // arr 是一个数组指针，这个指针的类型是 int(*)[5];
  //int (*arr[10])[5];  //数组指针数组
  //typedef int (*t)[5];// t ，这里的 t 不是数组指针，它是一种特殊的指针类型，t -> int(*)[5]
  //t arr2[10];
#endif 

#if 0
  char ch = 'w';
  char* p = &ch;
  // p 指针指向了单个字符
  // p 指向的不是字符串，就不能使用 strlen 函数 
  // 强行使用 strlen 就会内存访问越界，此时就是未定义行为了
  printf("%d\n",strlen(p));

  char str[] = "hehe";
  char* p2 = str;// p2 指针指向了一个字符串
  int len = strlen(p2);
  printf("%d\n",len);
#endif
  return 0;
}

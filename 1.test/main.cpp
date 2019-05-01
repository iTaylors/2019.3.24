#include <iostream>
using namespace std;

//一: C语言不支持重载, C++支持.是因为 C++ 在编译链接期间具有独有的函数名修饰规则
//在 C++ 能不能构成重载的问题上
//1.下面这个不构成

#if 0
int Add(int a,int b) {
  return a + b;
}

int Add(const int a,const int b) {
  return a + b;
}
#endif 

//2.而这个会构成
void Func(int *p) {//_Z4FuncPi

}

void Func(const int* p) {//_Z4FuncPKi

}

//二:
//1.C++模块能调用C语言写的代码
//extern "C":有时候c++工程中需要将某些函数按照 C 的风格来编译,在函数前加extern "C",
//意思是告诉编译器,将该函数按照 C 语言规则来进行编译

//extern "C" int Add(int left,int right) {
//  return left + right;
//}

//2.C程序能调用C++语言写的模块(如: C 要去调由 C++ 写的库)

void Swap(int& left,int& right) {//注意:这里不是 left 和 right 的定义,而仅仅只是它们的声明
  int temp = left;
  left = right;
  right = temp;
}

#if 0
int Add(char a,char b) {//返回的是寄存器常量,其类型就是 int 
                        //          临时变量
                        // c 在销毁前将其值传送到了寄存器里面
                        // 在调用这个函数的时候实际上直接去访问这个寄存器就可以了
  int c = a + b;
  return c;
}

int* Add(int a,char b) {//返回的是一个垂悬指针(野指针)
  int c = a + b;
  return &c;
}
#endif 

int& Add(int a,char b) {//返回的是寄存器常量(其中值 == c),其类型是 int&-----在这里就是int& c;
                        //          临时变量
                        // c 在销毁前给自己起了一个别名并将自己的值赋给了这个别名
                        // 函数跳出前 别名(int& c) 将自己的值传送到了寄存器里面
                        // 同上
  int c = a + b;
  return c;
}

#if 0
int ArrayFunc(int pos) {
  static int a[10] = {1,2,3};
  return a[pos];//返回的只是 a[pos] 的拷贝,此时要想在 ArrayFunc外部去改动 a[pos] 是做不到的
  
}
#endif 

int& ArrayFunc(int pos) {
  static int a[10] = {1,2,3};
  return a[pos];
}

#define MAX(a,b)(a) > (b) ? (a) : (b)
#define ADD(a,b)((a) + (b)) 
#define SWAP(a,b)   \
do {                \
  int c = a;        \
  a = b;            \
  b = c;            \
} while(0)

int main() {
  //二:内联函数举例---可调试,易控制,没有函数压栈的开销
  inline int Add(int a,int b) {
    int c = a + b;
    return c;
  }

  //概念2:内联函数
  //以 inline 修饰的函数叫做内联函数,编译时C++编译器会在调用内联函数的地方展开,
  //没有函数压栈的开销,从而提升程序运行的效率
  
  //一:宏函数/宏常量的缺点------1.不能调试
  //                            2.可读性变差,不容易控制
  //   宏的优点:没有函数调用栈针的开销                         

  /*
  ++char*;//每次加1
  ++int*;//每次加4
  */ 

#if 0
  int a = 10;
  int* p = &a;//语法上:p 开辟了 4/8 字节的空间去存储 a 的地址
  int& r = a; //语法上:r 是 a 的别名,没有开辟空间
              //但!!!-----实际上,在汇编的时候,底层还是给别名 r 开辟了空间的
              //即指针变量和别名在物理实现上是完全一样的
#endif 

  //以下是引用的场景
  
  //综上:如果函数返回时,离开函数作用域后,其栈上空间已经还给系统,因此就不能用栈上空间作为
  //     引用类型返回.如果以引用类型返回,返回值的生命周期必须不受函数的限制(即即即即即即
  //     比函数生命周期长)
  
  //三:引用做返回值----前提是"返回对象出了作用域后,这个返回对象还在"
  //                          就像此代码中的 static 
  //ArrayFunc(0) = 10;//expression is not assignable //会报错,具体原因见函数内部的解释
                    //报错,咋整呢?!!!
                    
  
  ArrayFunc(0) = 10;//答:将函数类型由 int型 改为 int&型
  ArrayFunc(1) = 11;
  ArrayFunc(2) = 12;
  ArrayFunc(3) = 13;

  cout << ArrayFunc(0) << endl;
  cout << ArrayFunc(1) << endl;


  //二:引用去做返回值
  //以下多个调用的都是 int& Add() 函数
#if 0
  int& ret = Add(1,2);// ret 是给那么寄存器起的别名
                      //      寄存器(在物理上称为 空间)
  cout << "Add(1,2) is :" << ret << endl;//-----  3
  
  int& ret = Add(1,2);//同上
  Add(3,4);
  cout << "ADD(1,2) is :" << ret << endl;//-----  7

  int& ret = Add(1,2);//同上
  cout << "hello world" << ret << endl;//------   随机值
#endif 

#if 0
  //一:引用去传参数
  int a = 10;
  int b = 20;
  Swap(a,b);//这里是对 left 和 right 进行定义
  cout << a << endl;
  cout << b << endl;
#endif 

#if 0
  int i = 10;
  double d = i;//隐士类型转换
               //1.将 i 赋值给一个临时变量,这个过程中会对 i 就行类型提升/截断
               //2.实际上是把这个临时变量赋值给 d
  double& d = i;//这就不行------因为临时变量具有常性(可理解为它是由const 修饰的)
                //权限扩充,当然不行了
  const double& d = i;//const 修饰的临时变量赋值给 const 修饰的 d
                    //权限没变,就可以

  //const int& c = 10;// 10 是一个常量,这句代码的意思是给常量 10 起一个别名就叫 c
  //const int c = 10;//这是将 10 的值拷贝给 c
#endif 

#if 0
  //概念1:引用
  int a = 10;
  int& b = a;//引用在定义时必须进行初始化
  int& c = a;
  int& d = c;//一个变量可以有多个别名
  
  //下面这个代码编译不过
  //因为 a 的类型是 const int 
  //而   b 的类型是 int 
  const int a = 0;
  int& b = a;(//这句代码有两层含义:1. b 是 a 的别名)
              //                   2. b 的类型是 int 

#endif 

#if 0
  这里没听懂
  int a1 = 10;
  const int a2 = 20;
  a1 = a2;-------这里能不能用权限的思想来考虑
  a2 = a1;
#endif 

#if 0
  int* p1;//可读可写
  const int* p2;//只读
  实际上是 P 指向的内容的修改权限的扩大和缩小
  //p1 = p2;//错:因为权限不能扩大
  p2 = p1;//可以:因为权限能够缩小
#endif 
  return 0;
}




















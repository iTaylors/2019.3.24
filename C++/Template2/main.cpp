#include <iostream>
#include <string.h>
using namespace std;

//#include <iostream>的含义:将"iostream"这个文件展开

#if 0
1.模版参数
template <class T,typename T2>
//用这两个定义的都叫模版参数

template <class T,size_t N>
//T叫模版参数,N叫非类型模版参数,可以把 N 当作一个常量去使用它
//如:见下
//浮点数,对象,字符串常量不能作为非类型模版参数-----这是规定!别问为什么!!!!!
//只能用整型去充当非类型模版参数(如int,char,short)

template <class T,size_t N>
class Array {
private:
  T arr[N];
};

void test() {
  Array<int,20> arr;  //这个数组的容量是20;
  Array<int,200> arr2;//这个数组的容量时200;
}
#endif 

#if 0
2.模版的特化(模版的专用化):解决通用模版所不能处理的数据类型
template <class T>
bool cmp(T& a,T& b) {
  return a > b;
}

/*特化的条件:
 * 1.必须有一个基础的类模版
 * 2.template <>
 * 3.格式要与基础模版的格式一样*/
template <>
bool cmp<char*>(char*& a,char*& b) {
  if (strcmp(a,b) > 0) {//对于两个字符串str1,str2.当str1 > str2是,int ret = strcmp(str1,str2) = 1
    return true;
  }
  return false;
}

void test0() {
  int a = 10;
  int b = 20;
  cmp(a,b);   //这里是隐式实例化
}

/*
 * 以下比较的并不是字符串本身,而是char* 类型的地址--相当于这里谁的地址大就返回谁的地址
void test() {
  char* s1 = "ab";       //s1在上面,它的地址小
  char* s2 = "cde";
  bool ret = cmp(s1,s2);
  cout << ret << endl;
}

void test1() {
  char* s2 = "cde";
  char* s1 = "ab";       //s1在下面,它的地址大
  bool ret = cmp(s1,s2);
  cout << ret << endl;
}
*/ 

template <class T>
bool cmp(const T& a,const T& b) {
  return a > b;
}

template <>
bool cmp<char*>(char* const & a,char* const & b) {
//bool cmp<char*>(const char*& a,const char*& b)这样写是错的
  if (strcmp(a,b) > 0) {
    return true;
  }
  return false;
}
//很多情况下,我们为了代码的可读性更高,就不去进行模版的特化了,而是写一个重载函数
bool cmp(const char* a,const char* b) {
  if (strcmp(a,b) > 0) {
    return true;
  }
  return false;
}
#endif 

/*类特化分类
 * 1.全特化:
 * 2.偏特化:部分特化 + 限制特化*/

template <class T1,class T2>
class A {
public:
  A() {
    cout << "A(T1,T2)" << endl;
  }
private:
  T1 _a;
  T2 _b;
};


template <>
class A<int,int> {//全特化:将多个类型T1,T2都特化完了
public:
  A() {
    cout << "A(int,int)" << endl;
  }
private:
  int _a;
  int _b;
};


template <class T1>
class A<T1,int> {
public:
  A() {
    cout << "A(T1,int)" <<endl;
  }
private:
  T1 _a;
  int _b;
};

//限制特化
template <class T1,class T2>
class A<T1*,T2*> {
public:
  A() {
    cout << "A(T1*,T2*)" << endl;
  }
private:
  T1 _a;
  T2 _b;
};

void test2() {
  A<char,char> a0;//基础类模版
  A<char,int> a1; //T1 int 
  A<int,int> a2;  //int int
  A<int*,int*> a3;

}

template <class T>
void Copy(T* dest,T* src,size_t sz) {
  //对内置类型(POD:plain old Data)就进行浅拷贝
  memcpy(dest,src,sizeof(T) * sz);//浅拷贝---字节拷贝
}

template <class T>
void Copy2(T* dest,T* src,size_t sz) {//深拷贝
  //对自定义类型就进行深拷贝
  size_t i = 0;
  for (;i < sz;++i) {
    dest[i] = src[i];
  }
}

//下面是类模版特化的一个应用:将两个函数和二为一
template <class T>
void Copy3(T* dest,T* src,size_t sz,bool PODType) {
  //第四个参数:                     true/false
  //如果是内置类型就走浅拷贝
  if (PODType) {
    memcpy(dest,src,sizeof(T) * sz);
  }

  //否则,就走深拷贝
  size_t i = 0;
  for (;i < sz;++i) {
    dest[i] = src[i];
  }
}

struct FalseType {
  static bool get() {
    return false;
  }
};

struct TrueType {
  static bool get() {
    return true;
  }
};

template <class T>
struct TypeTraits {
  typedef FalseType IsPodType;
};

template <>
struct TypeTraits<int> {
  typedef TrueType IsPodType;
};



template <class T>
void Copy4(T* dest,T* src,size_t sz) {
  if (TypeTraits<T>::IsPodType::get()) {//这句代码的优点/*编译时确定类型:O(1)*/
    /*模版特化:
     * 1.定义两个类型:TrueType,FalseType-----作用是:用来分流的
     * 2.TypeTraits:通用的类模版----它里面的IsPodType本质上就是FalseType
     *              内置类型特化----  此时的IsPodType本质上就是TrueType
     * 3.(编译时的)实例化:内置类型---->走特化
     *                  自定义类型---->走通用的类模版实例化*/
    memcpy(dest,src,sizeof(T) * sz);
  }

  size_t i = 0;
  for (;i < sz;++i) {
    dest[i] = src[i];
  }
}


/*下面这个是一个可有可无的函数
bool IsPODType(const char* typeN) {
  static const char* arr[] = {"int","double","float","char","short"};
  size_t i = 0;
  for (;i < sizeof(arr) / sizeof(arr[0]);++i) {
    if (!strcmp(typeN,arr[i])) {
      return true;
    }
  }

  return false;
}
*/


void test3() {
  int src[] = {1,2,3,4,5,6};
  int dest[100];
  Copy4(dest,src,sizeof(src) / sizeof(src[0]));

  string srcstr[] = {"12","34"};
  string deststr[100];
  Copy4(deststr,srcstr,sizeof(srcstr) / sizeof(srcstr[0]));
}

/*编译的过程:
 * 1.预处理:头文件展开,宏替换,去注释,条件编译
 * 2.编译  :语法检查,(若语法没有问题就)将源代码转为汇编代码
 * 3.汇编  :汇编代码转成机器码(即可执行代码)-----a.生成好多目标文件(其中一个目标文件就包含了入口指令)
 *                                               b.导出符号表:
 *                                               c.为解决符号表:
 * 4.链接  :(把所有指令的地址全都找到)生成可执行文件*/

//以下是编译的问题:内联和模版不支持分离编译(大白话:声明和定义要放在一起)
//1.内联函数的声明和定义必须放在一起,若分开的话,编译器在编译的时候,就可能找不到这个内联函数
//2.对与模版写的函数,其声明和定义也最好写在一个头文件里面(2019.6.14----02:30:00---02:40:00)
//  库文件就是这样做的:将声明和定义在一起的函数都放在.hpp文件中



int main() {
  //test();
  //test1();
  test3();
  return 0;
}





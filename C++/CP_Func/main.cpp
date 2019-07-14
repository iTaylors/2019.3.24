#include <iostream>
using namespace std;

//仿函数类:重载"()"运算符的类
//这个类------对应"仿函数对象"(每个类都有其对应的对象)
/*1.仿函数的作用:定义(定制)元素之间的比较规则
 * 2.仿函数的使用:对象(参数)
 * 3.仿函数的调用:对象.operator()(参数)
 * 4.仿函数类型:重载"括号运算符"函数的类型*/

template <class T>
class Less {
public:
  bool operator()(const T& a,const T& b) {
    return a < b;
  }
};

template <class T>
class Greater {
public:
  bool operator()(const T& a,const T& b) {
    return a > b;
  }
};

int main() {

  return 0;
}

#include <iostream>
using namespace std;

#if 0
未实现多态
class Person {
public:
  void BuyTicket() {
    cout << "买票-全价" << endl;
  }
};
class Student : public Person {
public:
  void BuyTicket() {
    cout << "买票-半价" << endl;
  }
};
#endif 

/*多态实现的3个条件:缺一不可
 * 1.先实现继承
 * 2.函数要声明为虚函数
 * 3.被调用函数的类型必须为指针或引用(引用在底层实现上还是指针)*/
class Person {
public:
  virtual void BuyTicket() {
    cout << "买票--全价" << endl;
  }
};
class Student : public Person {
public:
  virtual void BuyTicket() {//这里不仅是父类函数的隐藏,亦是子类函数对父类函数的覆写
    cout << "买票--半价" << endl;
  }
};

/*虚函数的覆写
 * 1.函数为虚函数
 * 2.子类用相同的函数(接口形式完全相同)---和父类的函数名相同;参数完全相同,返回值也要相同
 *                                     ---例外:协变(其返回值类型是继承关系)
 * */


//下边是对协变的介绍
class A {};
class B : public A {};

class Person1 {
public:
  virtual A* BuyTicket() {
    cout << "买票--全价" << endl;
    return new A;
  }
};
class Student1 : public Person1 {
public:
  virtual B* BuyTicket() {
    cout << "买票--半价" << endl;
    return new B;
  }
};

/*和函数相关的三个概念
 * 1.函数重载(前提是这些函数在同一个作用域):函数名相同,参数不同
 * 2.函数隐藏(也叫函数重定义):在继承体系中,子类和父类的函数名相同
 * 3.函数覆写(也叫函数覆盖)  :在继承体系中,子类和父类的虚函数接口完全相同*/

void Func(Person& p) {
  p.BuyTicket();
}

void Func2(Person1& p) {
  p.BuyTicket();
}

void test() {
  Person p;
  Student s;
  Func(p);
  Func(s);
}

void test1() {
  Person p;
  Student s;
  Func(p);
  Func(s);
}

void test2() {//验证协变
  Person1 p;
  Student1 s;
  Func2(p);
  Func2(s);
}

int main() {
  //test1();
  test2();
  return 0;
}

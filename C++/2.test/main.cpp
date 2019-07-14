#include <iostream>
#include <cstring>
using namespace std;

//一:
//初始化列表:是成员的定义
//类中包含以下成员,必须放在初始化列表位置进行初始化
//1.引用成员变量
//2.const 成员变量
//3.(没有合适的构造函数可以用的)自定义类型的成员变量----见class B{}中对私有成员 _obj的初始化
//4.尽量使用初始化列表初始化,因为不管你是否使用初始化列表,对于自定义类型的成员变量,一定会先使用
//  初始化列表进行初始化



//5.不是说有了初始化列表之后构造函数就可以完全抛弃了,因为初始化列表也不是万能的:见下面这个例子
#if 0
4
class string{
public:
  /*
  string(char* str)
    :_str(str)
  {}*/

  string(char* str):_str(new char[strlen(str) + 1])
  //这个初始化列表只是把空间开了出来,但是还没有拷贝数据呢                  
  {
    strcpy(_str,str);//拷贝数据必须在构造函数体体内才能完成
  }
private:
  char* _str;
};
#endif 

#if 0
2
class Date{
public:
  Date(int year = 1900,int month = 1,int day = 1)
    //初始化列表:成员变量的初始化是在初始化列表中完成的
    :_year(year)   //对_year初始化为 1900
     ,_month(month)
     ,_day(day)
     ,_n(10)
  {
    cout << "Date()" << endl;
    _year = 1001;  //可以单独对某一个成员变量进行赋值:_year = 1001
  }
  void Print() {
    cout << _year << '-' << _month << '-' << _day << '-' << _n << endl;
  }

private:
  int _year;
  int _month;
  int _day;
  const int _n;
};
#endif 

#if 0
class Date{
public:
  Date(int year = 1900,int month = 1,int day = 1) {
    this->_year = year;
    this->_month = month;
    this->_day = day;
  }
private://这儿是成员变量的声明
  int _year;
  int _month;
  int _day;
  const int _n;
};
#endif 

#if 1
3
class A{
public:
  A(int a)//我写了,系统就不会自动生成构造函数了
          //但是我现在故意写的这个,既不是无参的构造函数,也不是全缺省的构造函数
          //!!!!!这是一个"不合适的构造函数-----无法完成对成员变量两的初始化"
    :_a(a)
  {}
private:
  int _a;
};

class B{
public:
  B(int a,int ref)
    :_ref(ref)  //引用类型的成员变量也可以在初始化列表中去初始化它
    ,_n(10)
  {}
private:
  A _aobj;      //A 没有默认构造函数
  int& _ref;    //引用
  const int _n; //const
};
#endif 

#if 0
5
class A{
public:
  A():_a2(_a1),_a1(88) {

  }
  /*
  A():_a2(10),_a1(_a2) {

  }*/

  void Print() {
    cout << _a1 << ' ' << _a2 << endl;
  }
private:
  //初始化列表在对成员变量进行初始化的时候,不是根据它们定义的顺序,而是它们声明的顺序
  int _a1;
  int _a2;
};
#endif 

#if 0
6 C++98仅具有单参数构造函数的类
class A{
public:
  //explicit A(int a)加上这个之后,C++就不会支持隐式类型转换了
  A(int a):_a(a) {
    cout << "A(int a)" << endl;
  }

  A(const A& aa):_a(aa._a) {
    cout << "A(coust A& aa)" << endl;
  }
private:
  int _a;
};
#endif 

#if 0
class A{
public:
  A(int a1,int a2):_a1(a1),_a2(a2) {

  }
private:
  int _a1;
  int _a2;
};
#endif 

//二:static成员
//1.静态成员为所有类对象所共享,不属于某个具体的实例
//2.静态成员变量必须在类外定义,且定义式不加static关键字
//3.对类的静态成员的访问方式:Date::_n(类名::静态成员)
//                           d._n    (对象.静态成员)
//4.静态成员函数没有隐藏的this指针,所以不能用静态函数去访问任何非静态成员
//5.静态成员和类的普通成员一样,也有public,protected,private 3种访问级别,也可以具有返回值
#if 0
class A{
public:
  A(int a):_a(a) {
    cout << "A(int a)" << endl;
    ++_n;
  } 
  A(const A& a):_a(a._a) {
    cout << "A(const A& a)" << endl;
    ++_n;
  }

  static int GetN() {//静态函数,要访问必须加上访问符号(即你是在那个类中的你要告诉我)
    return _n;
  }

private:
  int _a;
  static int _n;// _n 的大小不会算在类(对象)的总大小里面
};

//特性:
int A::_n = 0//静态的成员变量一定要在类外进行初始化

A f(A a) {  //传参的时候拷贝构造一次
  return a; //传返回值的时候再拷贝构造一次
}
#endif 

class A{
public:
  A(int a):_a2(10),_a1(_a2) {

  }
  void Print() {
    cout << _a1 << ' ' << _a2 << endl;
  }
private: 
  int _a1;    //没有对内置类型进行缺省
  int _a2 = 2;//对内置类型的缺省为2
};

int main() {
  A aa;
  aa.Print();//_a1 = 2
             //_a2 = 10
  
#if 0
  A aa1(1);
  A aa2 = 10;
  f(aa1);
  cout << A::GetN() << endl;
#endif 

#if 0
  A aa1(1,2);
  A aa2{1,2};//这个编译报错是因为此编译器不支持 C++11
#endif 

#if 
  A aa1(10);   //构造------运用构造函数进行初始化
  //A aa5 = int 20//不能把20的类型显式的显示出来,为什么?
  //没有为什么????!!!!C/C++不允许将常量作为变量名
  int b = 3;
  A aa5 = b;
  //int 2 = 3;
  
  A aa2 = 20;  //伪构造1.A tmp(20)     //构造
               //      2.A aa2 = tmp   //+拷贝构造
               //      3.优化:将这两步合起来"认为"是构造
               //      这就是C++里面的隐式类型转换
  A aa3(aa1);  //拷贝构造
  A aa4 = aa1; //拷贝构造
#endif 

#if 0
  //A a;
  //a.Print();
  //cout << a._a1 << ' ' << a._a2 << endl;
#endif 

  //Date d;//这儿是对对象的定义
  //d.Print();

  //这儿是对成员变量整体的定义(注意:编译器是不会对某一个成员变量单独去进行定义的)
#if 0
  1
  const int x = 9;//const 对象只能在声明的时候去初始化它
  const int x;
  x = 9;          //错!!!!错因在上一行
  int i = 0;
  int& a = i;
  cout << i << ' ' << a << endl;
  cout << &i << ' ' << &a << endl;
#endif 
  return 0;
}

#include <iostream>
using namespace std;

//终端是一个进程,./a.out就是把a.out用exec去替换然后开始一个子进程

#if 0
class Date{
public:
  //友元函数可以直接访问类的私有成员,它是定义在类外部的普通函数,怒属于任何类,但需要在类的内部
  //声明,声明时需要加上 friend 关键字
  //friend void operator<<(ostream& _cout,const Date& d);/*3(2--3)*/
  friend ostream& operator<<(ostream& _cout,const Date& d);/*4,5的声明*/
  friend istream& operator>>(istream& _cin,Date& d);
  Date(int year = 1900,int month = 1,int day = 1)
    :_year(year),_month(month),_day(day) {

    }
  /*
   * 1
  void operator<<(ostream& _cout) {//this指针是左操作数,_cout(表现为值,实质为址,输出为值)是右操作数
    _cout << _year << '-' << _month << '-' << _day << endl;
  }*/
  
  void SetTimeOfDate(int hour,int minute,int second) {
    _t._hour = hour;
    _t.minute = minute;
    _t.second = second;
  }
private:
  int _year;
  int _month;
  int _day;
  Time _t;
};
/*4,5*/

ostream& operator<<(ostream& _cout,const Date& d) {
  _cout << d._year << '-' << d._month << '-' << d._day << endl;
  return _cout;
}

/*2
void operator<<(ostream& _cout,const Date& d) {
  _cout << d._year << '-' << d._month << '-' << d._day << endl;
}*/ 

//从控制台输入数据放到对象里面去
istream& operator>>(istream& _cin,Date& d) {
  _cin >> d._year;
  _cin >> d._month;
  _cin >> d._day;
  return _cin;
}

//友元函数提供了一种突破封装的方式,有时提供了便利.但是友元会增加耦合度,破坏了封装,
//所以友元不宜多用

class Time{
public:
  friend class Date;//Date 是 Time 的友元类,所以我在 类Date 里面可以直接去访问 Time 的私有的成员变量
  Time(int hour,int minute,int second):
    _hour(hour),_minute(minute),_second(second) {
    
    }
private:
  int _hour;
  int _minute;
  int _second;
};
#endif 



int main() {
#if 0
  Date d1(2019,5,21);
  cout << d1;  //operator(cout,d1)-------友元函数的调用
  //d1 << cout;
  Date d2(1,1,1);
  cin >> d1 >> d2;
  cout << d1 << d2;
#endif 
  return 0;
}


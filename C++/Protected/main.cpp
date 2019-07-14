#include <iostream>
#include <string>
using namespace std;

//指针的类型-->决定了这个指针可以开多大的空间
//通过代码复用的手段，解决代码冗余-------继承

class Person1 {
public:
  void Print() {
    cout << "name:" << _name << endl;
    cout << "age:" << _age << endl;
  }
protected://保护成员
  string _name = "peter";
  int _age = 18;
private:  //私有成员
  int _a = 10;
};

#if 0 
公有继承
class Student : public Person {
//继承不仅会继承基类的成员变量，而且会继承基类的函数成员
  void fun() {
    cout << _name << endl << _age << endl;
    //cout << _a << endl;//注意:基类的private成员,不论是哪种继承方式所产生的派生类
                         //基类的private成员在这些派生类中都是不可见的
                         //大白话:就算在派生类体内都是不能去访问基类的private成员的
  }
};

void test() {
  Student s;
  s.Print();//s对Print()的继承方式是公有的
  //cout << s._name << endl;//s对成员变量的继承方式是仍是受保护的(protected),
                            //对私有成员的继承只能在类内部进行使用,不能在类外部去访问
}
#endif 

#if 0
class Student : protected Person {保护继承

};

void test() {
  Student s;
  //s.Print();//以保护方式继承的基类公有函数,在派生类中是受保护的----即即使在类外面也是访问不到的
}

class Student : private Person {私有继承

};
#endif 

//一般是(子类进行)公有的继承 + (父类进行对成员变量)保护的声明

#if 0
class A {
public:
  A(int a):_a(a) {

  }
private:
  int _a;
};

void test1() {
  A a = 10;//当构造函数只有一个参数的话,此时就会进行一个单参类型的隐式类型转换
           //首先,用10构造一个匿名对象
           //接着,用这个匿名对象去拷贝构造生成对象 a
  int b = 10;
  int* p = (int*)b;
}
#endif 

#if 0
class Student : public Person {

};
 
//切片:不是将子类对象黄色以上部分切过去给父类
//     是用黄色以上部分的内容调用拷贝构造去生成一个父类对象

void test2() {
  Student s;
  Person p = s;//将子类对象赋给父类对象----这个不是隐式类型转换,而是切片
}

void test3() {
  Person* p;
  Student s;
  p = &s;//父类类型的指针可以指向子类对象的地址
}

void test4() {
  Student s;
  Person& p = s;//子类的引用可以赋给父类对象
}
//综上:子类的对象\地址\引用都可以相应的赋给父类,这些都是切片的操作都是天然支持的
//因为你(父类)要的我(子类)都有----我能够满足你

//相反就不行----你只能给我一小部分东西,但你无法给我我想要的全部东西----你不能满足我-SORRY
void test5() {
  Person p;
  //Student s = p;-----父类对象不能赋值给子类对象
  //Student* s_ptr = &p;
  Student* s_ptr = (Student*)&p;//这个强制类型转换存在安全问题:
                                //&p这一父类指针指向的空间大小
                                //要小于 s_ptr 指向的空间的大小
                                //这样赋值很容易产生内存访问越界的问题
  //Student& S_bind = p;//bind:引用
}
#endif 

#if 0
class Person {
public:
  void Print() {
    cout << "Person:Print()" << endl;
    cout << "name:" << _name << endl;
    cout << "age:" << _age << endl;
  }
protected:
  string _name = "peter";
  int _age = 18;
};

class Student : public Person {
public:
  void fun() {
    cout << _name << _age << endl;
  }

  //函数隐藏:子类成员和父类成员同名,子类中隐藏父类成员
  void Print() {
    cout << "name:" << _name << endl;
    cout << "age:"<< _age << endl;
    cout << "id:" << _id << endl;
    //Person::Print();
  }
private:
  string _name = "Taylor";
  int _age = 29;
  int _id = 118;
};

void test6() {
  Student s;
  s.Print();         //当子类,父类中有同名的函数成员时,优先调用子类的函数成员
  
  s.Person::Print();
}
#endif 

#if 1
class Person {
public:
  Person(const char* name = "peter"):_name(name) {//给了name一个缺省值"Peter"
    cout << "Person()" << endl;
  }

  Person(const Person& p):_name(p._name) {
    cout << "Person(const Person& p)" << endl;
  }

  Person& operator=(const Person& p) {
    cout << "Person operator=(const Person& p)" << endl;
    if (this != &p) {
      _name = p._name;
    }
    return *this;
  }

  ~Person() {
    cout << "~Person()" << endl;
  }
protected:
  string _name;//注意:string是一个自定义类型,这个对象资源的释放是在~Person()函数体内通
               //过调用delete来实现的
               //_name 的析构编译器自动调用的,在哪里调用呢,在这个基类Person的析构函数中完成这一过程
};
#endif 

#if 0
构造函数
class Student : public Person {
public:
  /*
  Student(const char* name = "Taylor"):_name(name) {
  //这样写编译器是不支持的
  //因为编译器认为_name不是子类的非静态数据成员(not-static data member)/基类(base class)
  }*/

  //只能像下面这样去调用父类的构造
  Student(const char* name = "Taylor"):Person(name) {
    
  }
  //就算不写初始化列表,编译器也会去调用父类的构造函数
  Student(const char* name = "Taylor") {}
   1.子类构造(不论什么时候)都是会去调用父类的构造的
   2.从父类中继承的成员必须通过父类的构造才能进行子类的初始化
   3.不是从父类继承而来的成员的初始化就与一般的类(如Date类)完全一样了
  Student(const char* name = "Taylor"):Person(name),_id(8) {

  }
private:
  int _id;
};
#endif 

#if 0
拷贝构造
class Student : public Person {
public:
  Student(const char* name = "Taylor"):Person(name),_id(8) {

  }

  // 1.不写时,编译器默认生成的拷贝构造函数去自动去调用父类的拷贝构造函数
  // 2.显式得写出子类的拷贝构造函数的话,编译器默认调用父类的构造函数
  Student(const Student& s) {

  }

private:
  int _id;
};

class Student : public Person {
public:
  Student(const char* name = "Taylor"):Person(name),_id(8) {

  } 

  Student(const Student& s) //Student(Student* const this,const Student& s)
    :Person(s) {            //Person(Person* const this,const Person& p)
    //3.在这里,可以显式调用父类的拷贝构造
    //这里发生了两次切片的操作,第一次
    //首先:s是一个子类的对象
    //然后:这个子类对象(s)去调父类的拷贝构造---因为父类的拷贝构造在定义时接收的是一个父类对象的引用
    //所以:这里进行了一个切片的操作---把子类进行了转换,将子类"切"成了父类的引用
    
    //第二次,拷贝构造函数的左操作数是this指针
    //首先:Student(const Student& s)这里的左操作数是 (Student*型的) this指针
    //然后:Preson(s)---Person(const Person& p)父类的构造函数的左操作数是 (Person*型的) this指针
    //     走到这里,就理所当然的发生了指针的切片
  }
private:
  int _id;
};

void test7() {
  //对应----1
  //调父类的拷贝构造
  Student src;
  Student dest(src);
}

void test8() {
  //对应----2
  //调父类的构造
  Student src;
  Student dest(src);
}

void test9() {
  //对应----3
  //这样一来,调用的不再是父类的构造,而是父类的拷贝构造
  Student src;
  Student dest(src);
}
#endif 

#if 0
class Student : public Person {
public:
  Student(const char* name = "Taylor"):Person(name),_id(8) {

  }

  Student(const Student& s):Person(s) {

  }

  // 1.我们不写,默认生成的赋值运算符会自动调用父类的赋值运算符重载函数
  // 2.我们写(显式定义子类的赋值运算符重载函数):这是编译器调用的就不再是父类的=函数,而是子类的=函数 
  Student& operator=(const Student& s) {
    if (this != &s) {
      _name = s._name;
      //Person:operator=(s)
      _id = s._id;
    }

    cout << "Student& operator=(const Student& s)" << endl;
    return *this;
  }
private:
  int _id = 18;
};

void test10() {
  //对应-----1.我们不写
  Student s1;
  Student s2("MJ");
  s1 = s2;//改变已存在的对象的内容,会默认调用父类的赋值运算符重载函数
} 

void test11() {
  //对应-----2
  Student s1;
  Student s2("MJ");
  s1 = s2;
}
#endif 

#if 1
//析构函数
class Student : public Person {
public:
  Student() {
    cout << "Student()" << endl;
  }

  // 0.不显式的写子类的构造函数时,编译器就不会自动去生成子类的析构函数

  // 1.父类析构函数和子类析构函数构成同名隐藏---编译器在底层修改了析构函数的名字,目的是为了支持多态
  //~Student() {
  //  ~Person();//自己调子集,栈溢出----注意:这里~Student 和 ~Person是同名的
  //  //那我就想在这里去调用父类的析构函数怎么办呢?见下
  //  Person::~Person();
  //}
  
  // 2.父类析构在任何情况下编译器都会自动调用----不需要显式调用
  ~Student() {
     cout << "~Student()" << endl;
  }
};

void test12() {
  //对应----0
  Student s;
}

void test13() {
  Student s;
}
#endif 

//如何实现一个不能被继承的类
#if 0
//C98:构造函数私有化
class Date {
private:
  Date() {

  }
};

//C11:将基类标识成一个 final 类----语法规定:这种类是不能被继承的
class Time final {

};
class Time1 : public Time {

};
#endif 

/*两个概念:
 * 1.继承与友元----语法规定:父类的友元函数不能被子类继承
 * 2.继承与静态成员----*/

class A {
public:
  static int _a;
};
int A::_a = 0;//静态成员不在类里面,是存放在数据段的

class B : public A{};
class C : public B{};
class D : public C{};
//这三个类都可以继承到这个基类的静态成员使用权
//即:整个继承体系中只存在这么一个静态成员,不是每个类都独有的
void test14() {
  A a;
  a._a = 100;
  B b;
  C c;
  D d;
  cout << &a._a << endl;
  cout << &b._a << endl;
  cout << &c._a << endl;
  cout << &d._a << endl;
}

#if 0
class Person {
public:
  int _name;
  //string _name;       //姓名
};
class Student : public Person {//成员有:_name,_num
protected:
  int _num;           //学号
};
class Teacher : public Person {//成员有:_name,_id
protected:
  int _id;            //职工编号
};
class Assistant : public Student,public Teacher {//成员有:Student::_name,Person::_name 
                                                 //       Student::_mum,Person::_id
                                                 //       _majorCourse 
                                                 //       都是 int 类型
protected:
  int _majorCourse;
  //string _majorCourse;//学生主修课程
};

void test15() {
  Assistant a;
  cout << sizeof(a) << endl;

  //菱形继承导致数据冗余和数据的二义性
  a.Student::_name = 666;
  a.Teacher::_name = 999;
  a._num = 000;
  a._id = 111;
  a._majorCourse = 111000;
}
#endif 

#if 0
class Person {
public:
  int _name;
};
class Student : virtual public Person {
protected:
  int _num;
};
class Teacher : virtual public Person {
protected:
  int _id;
};
class Assistant : public Student,public Teacher {
protected:
  int _majorCourse;
};

void test16() {
  Assistant a;
  cout << sizeof(a) << endl;
  a._name = 10;
}
#endif 

int main() {
  /*
  test7();
  cout << endl;
  test8();
  cout << endl;
  */

  //test10();
  //test11();
  //test12();
  //test13();
  
  //test15();
  //test16();
  return 0;
}


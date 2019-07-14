#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

/* 动态绑定与静态绑定
 * 1.静态绑定:又称前期绑定,在程序编译期间确定程序的行为,也称为静态多态-----如函数重载就是编译时多态
 *            点睛之笔:就没有 call 寄存器这样的汇编代码
 * 2.动态绑定:又称后期绑定,是在程序运行期间,根据具体拿到的类型确定程序的具体行为,调用
 *            具体的函数,也称为动态多态
 * */

/*函数复写:
 * 1.子类先把父类的虚表继承下来
 * 2.修改对应的函数地址完成覆盖*/

//多态:体现是接口继承---我继承你,并不是要去使用你的函数,而是只继承这个函数的外观,然后我自己去实现
//     这个函数的功能

#if 0
class Person {
public:
  //建议:将析构函数尽量写成虚函数,与子类构成多态
  virtual ~Person() {
    cout << "~Person()" << endl;
  }

  virtual void Buyticket() {
    cout << "全票" << endl;
  }
};
class Student : public Person {
public:
  Student(const char* name = "hello"):_name(new char[strlen(name) + 1]) {
    strcpy(_name,name);
  }

  virtual void Buyticket() {
    cout << "半票" << endl;
  }

  virtual ~Student() {
    if (_name) {
      delete[] _name; //先将子类在堆上占用的资源给释放掉(----这样一来编译器在下一步自动调用父类的
                      //析构函数时就不会造成内存泄露了----内存泄露:一份空间释放两次)
      _name = NULL;
    }
    cout << "~Student()" << endl;
  }
private:
  char* _name;
};

void test() {//你指向的是哪个对象,调用的就是这个对象的析构函数
  //在堆上创建对象
  Person* a = new Person;  // a指针指向的是一个在堆上创建的Person实例化的一个对象
  Student* b = new Student;
  Person* c = new Student; // c指针指向的是一个在堆上创建的Student实例化的一个对象
                           // 虽然c的类型是父类指针,但是这里已经不关心c的类型了,只关心c指向的
                           // 类型对象是什么


  //用户在堆上创建的对象需要自己去管理它
  delete a;// p指向的是一个父类对象,所以这里去调用的是父类的析构函数
  delete b;
  delete c;
}

void test1() {
  Person* a = new Person;
  Person* b = new Student;
  //a.Buyticket();member reference type 'Person*' is a pointer;did you mean to use '->' 
  //a本身是指针(这个指针指向的内容是类所实例化出的对象),所以要是想要用a去访问对象的成员,就得使用'->'
  //当a本身就是类所实例化出的一个对象时,此时对a中成员的访问就得使用'.'
  a->Buyticket();
  b->Buyticket();
}
#endif 

#if 0 
/*下面引入纯虚函数的概念:
 * 1.纯虚函数都是写在基类中的(此时这个基类叫做抽象类)
 * 2.抽象类不能实例化
 * 3.一个纯粹的抽象类里面是没有任何函数的实现的,它都是一些函数的声明
 * 4.纯虚函数后面必须加上 = 0----它告诉编译器这就是一个抽象类;
 * 5.C++11提供override和final来修饰虚函数
 *   override(用在子类中):这个函数必须重写一个父类函数
 *   final(用在父类中)   :这个函数不能被任何子类重写*/
class Person {
public:
  virtual ~Person() {
    cout << "~Person()" << endl;
  }

  virtual void Buyticket() = 0;//----纯虚函数
};

class Student : public Person {
public:
  Student(const char* name = "Taylor"):_name(new char[strlen(name + 1)]) {
    strcpy(_name,name);
  }

  virtual void Buyticket() {
    cout << "半票" << endl;
  }

  virtual ~Student() {
    if (_name) {
      delete[] _name;
      _name = NULL;
    }
    cout << "~Student()" << endl;
  }
private:
  char* _name;
};
#endif 

class Person {
public:
  virtual ~Person() {
    cout << "~Person()" << endl;
  }

  virtual void Buyticket() {
    cout << "全票" << endl;
  }

  virtual void SellTicket() {

  }

  void fun() {

  }
};
class Student : public Person {
public:
  Student(const char* name = "Taylor"):_name(new char[strlen(name + 1)]) {
    strcpy(_name,name);
  }

  virtual void Buyticket() {
    cout << "半票" << endl;
  }

  virtual ~Student() {
    if (_name) {
      delete[] _name;
      _name = NULL;
    }
    cout << "~Student" << endl;
  }
private:
  char* _name;
};

/*下面介绍多态的底层实现原理
 * 1.vfptr(虚表指针):是一个指向虚函数指针的指针-----虚函数**---a**
 *    说白了就是指向虚表的首地址0x00a71217(存放虚函数的地址)---p = &a = a*
 *                           p是虚函数指针       指向的内容是a
 *    的一个二级指针0x00a7dc74(0x00a71217---p)              ---q = &p = a**
 *                          q虚函数指针指针       指向的内容是p
 *
 *   vfptr存放在对象模型的头部,一般占用8/4个字节
 * 2.虚表(就是一个指针数组):这个数组用来存放所有的虚函数指针
 *                          只存放虚函数指针,普通函数是不存放的
 *                          虚表的最后一个元素是NULL,以NULL作为结束标志
 *                          虚表中各个元素的顺序是与类中虚虚函数的声明,定义是一致的
 * */
void test2() {//对象模型的大小只跟成员变量有关系(且只跟非静态成员变量有关系)
  Person p; 
  Student s;
  cout << sizeof(p) << endl;
  //结果是 8 :因为p中有一个_vfptr指针成员
  cout << sizeof(s) << endl;
  //结果是 16:因为s继承了来自父类的_vfptr指针成员,且s自己又有一个指针成员 _name
}

void test4() {
  Person p; //p中只存放虚表指针
  Student s;//s存放虚表指针和私有成员_name
}

void test3() {
  int a = 2019;
  int* p = &a;
  int** q = &p;
  cout << q << endl;
}

//////////验证虚表究竟存放在哪里
typedef void (*VFPTR) ();
void test5() {
  Person p;
  static int a = 10;  //静态变量存放在数据段
  int b = 1;          //局部变量存放在栈上
  int* c = new int;   //在堆上
  char* str = "hello";//在代码段

  cout << "ststic:\t" << &a << endl;
  cout << "stack:\t" << &b << endl;
  cout << "heap:\t" << c << endl;
  printf("code:\t%p\n",str);

  cout << "virtual table:\t" << (VFPTR*)*(long long*)&p << endl;
  //经验证知虚表是存放在代码段的
}

//多态
void fun(Person& p) {//注意:实质上,函数的参数 Person& 在这里已经没有多大的意义了
                     //你指向的是哪个对象,相应的就去调用这个对象的成员/成员函数
                     //因为:引用的底层实现就是指针-----参见第47行注释
  p.Buyticket();
  /* 汇编底层
   * p.Buyticket();
   * 1.003E5CFE mov   eax,dword ptr[p]    ---把p对象的地址(即this指针----&p)存放到eax寄存器中
   * 2.003E5D01 mov   edx,dword ptr[eax]  ---将eax中的前8个字节的数据取出并存放到edx寄存器之中
   *   (&p这一数据的前8个字节:就是虚表的首地址)--->(大白话:将虚表的首地址存放在edx寄存器中)
   *   在此类族中,虚表首地址这以数据本身还有另一个身份:~Person()*这一虚函数指针
   * 3.003E5D03 mov   esi,esp 
   * 4.003E5D05 mov   ecx,dword ptr[p]
   * 5.003E5D08 mov   eax,dword ptr[edx + 8]-将edx寄存器的的内容向后偏移8个字节得到下一个虚函数指针
   *                                         (此时eax中存放的就是:Buyticket()*这一虚函数指针)
   * 6.003E5D0B call  eax                 ---执行eax寄存器中的内容:实现多态的点睛之笔
   * */
  
  /*底层实现原理:
   * p是一个父类对象
   * 1.走父类对象的虚表指针vfptr,通过vfptr拿到父类对象的虚表
   * 2.编译器会先通过这个对象的头8个(或4个)字节拿到此对象的虚表的首地址
   * 3.在这个虚表中通过函数指针找到买票的函数
   * 4.通过函数指针?拿到当前函数(买票函数)的指令的首地址
   * 5.执行指令----从call 函数首地址开始,依次执行此函数的所有汇编代码*/

  /*当 p 是一个子类对象的时候
   * 1.走子类对象的虚表指针vfptr,通过vfptr拿到子类对象的虚表
   * 2.同上
   * 3.同上
   * 4.同上
   * 5.同上
   * */
}

void test6() {
  Person p;
  Student s;
  fun(p);
  fun(s);
}

//三:被调用的函数类型必须是指针/引用
//非多态(之一:被调用的函数类型不是指针,而是值)
void fun(Person p) {
  p.Buyticket();
  /*父类汇编底层:
  013C5D74  lea       ecx,[p]---取一个this指针:把p(对象)的地址(即this指针 this = &p)放在exc寄存器中 
  013C5D77  call      Person::BuyTicket (013C108Ch)---调用成员函数
  */
}

#if 1
//以下是单继承
class Base {
public:
  virtual void func1() {cout << "Base::func1" << endl;}
  virtual void func2() {cout << "Base::func2" << endl;}
private:
  int _a;
};

class Derive1 : public Base {
public:
  virtual void func1() {cout << "Derive::func1" << endl;}//此函数重写了父类的func1()函数
  virtual void func3() {cout << "Derive::func3" << endl;}
  virtual void func4() {cout << "Derive::func4" << endl;}
private:
  int _b;
};

typedef void(*VFPTR) ();

void PrintVFun(VFPTR* VTable) {
  cout << "虚表地址:\t" << VTable << endl;
  int i = 1;
  VFPTR  vfun = VTable[0];
  for (;vfun != NULL;) {
    cout << "第 " << i << " 个虚函数的地址:" << vfun << endl;
    vfun();
    ++VTable;      //走到下一个元素的位置
    vfun = *VTable;//拿到下一个元素的值,它是一个函数指针
    i++;
  }
}

void test7() {
  Base b;
  Derive1 d;
  cout << "Base virtual table:" << endl;
  PrintVFun((VFPTR*) (*(int*)&b));
  // &b                 :获取对象首地址,即得到对象指针
  // (int*)&b           :将这个数据由对象指针 -->(转化为) 整型指针
  // *(int*)&b          :获取对象前8个字节的内容,即得到虚表的首地址(以整型形式存放的虚表首地址)
  // (VFPTR*)(*(int*)&b):将整型形式的虚表首地址 强转为 虚函数**形式的指针
  //
  cout << "Derive virtual table:" << endl;
  PrintVFun((VFPTR*) (*(int*)&d));
}
#endif 

/*以下是多继承
 * 1.虚表的个数 = 直接父类的个数
 * 2.子类新增的虚函数存放在第一个直接父类的虚表末尾(按声明顺序存放)
 * 3.可以在子类中新定义一个虚函数func4()来验证上面这句话*/

class Base1 {
public:
  virtual void func1() {cout << "Base1::func1" << endl;}
  virtual void func2() {cout << "Base1::func2" << endl;}
private:
  int _b1;
};

class Base2 {
public:
  virtual void func1() {cout << "Base2::func1" << endl;}
  virtual void func2() {cout << "Base2::func2" << endl;}
private:
  int _b2;
};

class Derive : public Base1,public Base2 {
public:
  virtual void func1() {cout << "Derive::func1" << endl;}//复写父类的func1()函数
  virtual void func3() {cout << "Derive::func3" << endl;}
  virtual void func4() {cout << "Derive::func4" << endl;}
  //子类自己定义的虚函数放在第一个直接父类的虚表当中
private:
  int _d;
};

void test8() {
  Base1 b1;//只有一个虚表
  Base2 b2;//只有一个虚表
  Derive d;//有两个虚表
  
  cout << "Base1:" << endl;
  PrintVFun((VFPTR*) (*(int*)&b1));
  cout << endl;

  cout << "Base2:" << endl;
  PrintVFun((VFPTR*) (*(int*)&b2));
  cout << endl;
  //PrintVFun((VFPTR*) (*(int*)&d));
  
  cout << "Derive:" << endl;
  cout << "Derive:Base2" << endl;
  Base2* p = &d;//指针偏移法一:
  PrintVFun((VFPTR*) (*(int*)p));
  //指针偏移法二:PrintVFun((VFPTR*) (*(int*) ((char*)&d + sizeof(Base1))));
  cout << "Derive:Base1" << endl;
  PrintVFun((VFPTR*) (*(int*)&d));
}

int main() {
  //test();
  //test1();
  //test5();
  //test6();
  //test7();
  test8();
  return 0;
}

















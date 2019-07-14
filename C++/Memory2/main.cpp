#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


//静态变量(/全局变量)的销毁时间:是在整个程序结束之后(说白了就是main函数结束之后)
//设计模式:(Design Pattern)是一套被反复使用\多数人直销的\经过分类的\代码设计经验的总结

class Test{
public:
  Test():_data(0) {
    cout << "Test():" << this << endl;
  }

  ~Test() {
    cout << "~Test():" << this << endl;
  }
private:
  int _data;
};

//请设计一个类,该类只能在堆上创建对象
//方法一:构造函数私有化
//      第1步.将类的构造函数私有,拷贝构造声明成私有
//      第2步.提供一个静态的成员函数,在这个函数中完成堆对象的创建


//请设计一个类,该类只能在栈上创建对象

#if 0
1
class HeapOnly{
private:
};
#endif 

#if 0
2  4
class HeapOnly {
public:
  static HeapOnly* GetHeapObj() {//通过类域就能访问到这个函数,从而才能去调用这个类的构造函数
    return new HeapOnly;         //这就是在堆上直接创建对象(因为用到的是 new 这个操作符)
  }
private:
  HeapOnly(const HeapOnly&);//优化:将拷贝构造函数也封死-----这就是防拷贝
  HeapOnly() {//这就是将构造函数私有化(外界不能访问,但是我这个类本身还是能够访问的)

  }
};
#endif 

#if 0
3  4
class StackOnly{
public:
  static StackOnly GetStackObj() {
    return StackOnly();          //直接创建再返回这一过程就是在栈上完成的(没有那么多为什么!!)
  }
private:
  StackOnly(const StackOnly&);//优化:将拷贝构造函数也封死------防拷贝
  StackOnly() {

  }
};
#endif 

//以下是单例模式:
//单例模式:一个类只能创建一个对象,即单例模式,该模式可以保证系统中该类只有一个实例,并提供一个访问\
//         它的全局访问点,该实例被所有程序模块共享

//单例模式有两种实现模式
//1.饿汉模式:就是说不管你将来用不用,程序启动时就创建一个唯一的实例对象
//2.懒汉模式:



/*
饿汉模式:这个对象是在 main 函数创建之前就已经创建好了
缺陷是:1.成也萧何,败也萧何(所有的线程必须在 main 主进程之后,但是单例模式却不是这样,它反其道而行)
       2.不能控制多个单利的初始化顺序
       3.当有多个单例需要初始化的时候, main 函数的启动会特别慢
*/

#if 0
5
class Singleton{
public:
  //步骤二:提供公有的静态方法来获取实例:通过一个函数返回创建好的对象
  static Singleton* GetInstance() {
    return &_singleton;
                           
                          //在类里面创建一个对象(_singleton),出了作用域这个对象(_singleton)还在
                          //返回一个已经创建好的对象-----这个对象在哪里创建的?答:程序启动之前
                          //那么那些变量是在程序启动之前就已经创建好了呢?答:静态变量,全局变量
                          //这个静态成员(变量见步骤三:)
  }
private:
  //步骤一:构造函数私有化
  Singleton() {

  }

  //步骤五:防拷贝
  //法1:只声明不实现
  //Singleton(const Singleton& s);
  //法2:声明为delete函数L:删除函数就是不能被使用的函数
  Singleton(const Singleton& s) = delete;

  //步骤三:声明这个静态成员
  //Singleton _singleton;错,递归调用
  static Singleton _singleton;
};

//步骤四:在类外定义这个静态成员(只不过这个对象特殊在:它是Singleton类中的一个静态成员)
Singleton Singleton::_singleton;//(这里其实已经调用了构造函数了)

//    Singleto | Singleton::_singleton 
//  这是一个类 | 这是这个类所对应的一个对象

#endif 

//懒汉:就是在需要的时候才创建
//优点:1.延迟加载----结果就是启动快,
//     2.可以去控制多个单例的实例化顺序
//缺陷:因为单例模式的创建不是原子操作,所以多线程时很可能会出错(就是`程序运行的结果不符合预期`)
class Singleton{//单例类
public:
  //步骤二:提供公有的静态方法
  static Singleton* GetInstance() {
    if (_ps == NULL) {
      mtx.lock();//保证线程安全
      if (_ps == NULL) {
        _ps = new Singleton;   //_ps的生命周期是直到整个程序终止就会终结,
                               //在 main 函数就是之后 _ps 所占的资源就会自动返还给系统
        mtx.unlock();
      }
      return _ps;

    }
    //mtx.lock();
    //if (_ps == NULL) {
    //  _ps = new Singleton;
    //  mtx.unlock();
    //  return _ps;
    //}
  }

  //下面这个是加分项
  class GC{
  ipublic:
    ~GC() {
      delete _ps;//释放 new 的单例对象
      _ps = NULL;
    }
  };

private:
  //步骤一:构造函数私有化
  Singleton() {

  }
  //步骤三:声明这个静态成员
  static Singleton* _ps;

  //步骤五:防拷贝
  Singleton(const Singleton&);
  
  //步骤六:声明锁
  static mutex mtx;//静态成员的声明

  static GC _gc;//这是一个内部类(就是在类里面再定义一个类)
};

//步骤四:队静态成员进行初始化
Singleton* Singleton::_ps = NULL;  

//步骤七:定义锁
mutex Singleton::mtx;

//内部类并不从属于外部类
Singleton::GC Singleton::_gc;
//GC类  |  所对应的一个对象_gc(在本例中,1---这个对象是一个静态的,2---这个对象是外部类的私有成员)



int gi = 0;
void Func(int num) {
  int i = 0;
  for (;i < num;++i) {
    ++gi;
  }
}

int main() {
  thread t1(Singleton::GetInstance);
  thread t2(Singleton::GetInstance);
  t1.join();
  t2.join();

#if 0
  先回顾一下线程
  int num = 10;
  thread t1(Func,num);
  thread t2(Func,num);

  t1.join();
  t2.join();
  cout << gi << endl;
#endif 

#if 0
  Singleton* ps = Singleton::GetInstance();
  cout << ps << endl;
  ps = Singleton::GetInstance();
  cout << ps << endl;
#endif 
  
#if 0
  //对应 5
  cout << Singleton::GetInstance() << endl;
  cout << Singleton::GetInstance() << endl;
#endif 

#if 0
  对应 4
  //但是真的就只能在堆(/栈)上创建而不会出错吗?----1 和 2有一个致命缺陷
  //优化前下面这段代码能够跑过
  HeapOnly* p = HeapOnly::GetHeapObj();   //p创建在堆上
  HeapOnly copy(*p);                      //但是copy创建在栈上

  StackOnly so = StackOnly::GetStackObj();//so创建在栈上
  StackOnly* copyso = new StackOnly(so);  //但是copyso创建在堆上
  
  //优化之后下面这段代码就跑不过了
  //再想要跑过,有一种方法如下:
  //栈如下
  //private:
  //  void* operator new(size_t n);
  //  StackOnly() {
  //
  //  }
  //HeapOnly 与 StackOnly类似
#endif 


#if 0
  对应 3
  StackOnly so = StackOnly::GetStackObj();//so 这个对象就是在栈上
#endif 
#if 0
  对应 2
  HeapOnly* p = HeapOnly::GetHeapObj();
  HeapOnly* &a = p;//给指针变量起一个别名
  cout << p << endl;
  cout << a << endl;
  cout << &p << endl;
  cout << &a << endl;
  delete p;
#endif 

#if 0
  对应 1
  HeapOnly ho;               //这是在栈上创建对象
  HeapOnly* p = new HeapOnly;//这是在堆上创建对象
#endif 

#if 0
  //有时候申请空间不想从堆上走,因为堆的效率太低了------所以出现了内存池
  Test* p1 = (Test*)operator new(sizeof(Test));
  new(p1)Test();//对已由空间显示调用构造函数的方式

  p1->~Test();
  operator delete(p1);
#endif 
  return 0;
}

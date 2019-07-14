#include <iostream>
using namespace std;

template<class T>//T是模版参数,它不代表一个具体的类型-----模版是一个与类型无关的参数
                 //就像类和对象一样:类实际上是不占空间的,实例出来的这个对象才占空间
                 
//这不是一个具体能执行的函数,只有类型真正确认的函数才能执行-----本质上:这也是一个实例化的过程
//根据这个T去推演参数的类型,这个过程就叫做模版的实例化
//模版的作用:程序员写的代码减少了,但是实际在底层上代码量是没有减少的
void Swap(T& left,T& right) {
  T temp = left;
  left = right;
  right = temp;
}

template<class T1,class T2>//函数1
bool Fun(const T1& a,const T2& b) {
  cout << "template<class T1,class T2>" << endl;
  return a > b;
}

template<class T>          //函数2
bool Fun(const T& a,const T& b) {
  cout << "template<class T>" << endl;
  return a > b;
}

bool Fun(const int& a,const int& b) {//函数3
  cout << "Fun(const int& a,const int& b)" << endl;
  return a > b;
}

#if 0
typedef int DataType;
struct seqlist {
  DataType* _data;//这个顺序表只能存放int类型的数据
};
#endif  

//于是引出了类模版
template<class T> //类模版(接下来看一下5.18的seqlist模版)
struct seqlistT{ 
  seqlistT(int capacity = 10):_data(new T[capacity]) {

  }

  void push_back(const T& val) {
    _data[++_size] = val;
  }

  void pop_back() {
    --_size;
  }

  T operator[](size_t pos) {
    return _data[pos];
  }

  void print() {
    int i = 0;
    for (;i < _size;++i) {
      cout << _data[i] << ' ';
    }
    cout << endl;
  }

  T* _data;       //这个顺序表能够存放各种类型的数据
  size_t _size;
};

int main() {
  seqlistT<int> st;
  st.push_back(1);
  st.push_back(2);
  st.print();
#if 0
  类模版必须显式实例化
  seqlistT<int> st; //存放int类型数据的顺序表
  seqlistT<char> sc;//存放char类型数据的顺序表
#endif 

#if 0
  实例化匹配规则
  int a = 1;
  int b = 0;
  double c = 7.7;

  //如果非模版函数的参数与输入类型完全匹配,则编译器会去优先调用非模版函数(即函数3)
  Fun(a,b);

  //如果非模版函数的参数与输入参数类型只是部分匹配,则编译器会去优先调用合适的模版函数----走实例化
  Fun(a,c);//即函数1

  //如果指定显式实例化,不管有没有合适的非模版函数,都必须进行模版的实例化(即函数2)
  Fun<int>(a,b);
  Fun<double>(a,c);
#endif 

#if 0
  //参数不一致时:推演的过程称为'模版的显式实例化'(这里用Fun(比较大小)函数较为合适)
  int a = 10;
  double b = 2.2;
  Fun((double)a,b);//强制类型转换
  Fun<double>(a,b);//显式实例化
#endif 

#if 0
  参数类型一致时:推演的过程称为'模版的隐式实例化'(这里用Swap函数较为合适)
  int a = 10;
  int b = 20;
  Swap(a,b); 
  cout << a << " " << b << endl;

  double d = 2.2;
  double f = 1.1;
  cout << d << " " << f << endl;
#endif 
  return 0;
}

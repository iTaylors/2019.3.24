#include <iostream>
#include <queue> //-------deque是包含在"queue"这个头文件之中的
#include <vector>
#include <list>
using namespace std;

/*stack:只能实现尾插尾删;其他所有能够实现尾插尾删的容器都可以用来实现栈
 * queue:只能实现尾插头删;其他所有能够实现尾插头删的容器都可以用来实现队列
 * priority_queue:*/

/*为什么将stack,queue和priority_queue称作为容器适配器(***适配器是一种设计模式***)
 *                     优先级队列              适配器:把一种存在的容器转化成新的容器
 * 虽然三者都可以存放元素,但在STL中并没有将其划分在容器的行列,而是将其称为容量适配器.
 * 这是因为每个容器在底层都有自己的实现方式,而stack,queue,priority_queue只是
 * 在底层将其他容器进行了封装------最大限度的利用别的容器来实现自己的功能
 * 也就是说:STL中的上述三者在实现时没有自己独有得实现方式,都是通过封装其他容器来实现的!!!!
 * */

//stack的底层实现默认是deque:
//因为deque增容代价小(相对于vector来说),不会造成内存碎片(相对于list来说)

/*std::stack 
 * template <class T,class Constainer = deque<T>>
 * 通过封装deque来实现stack
 * Constainer:容器
 * 第一个范型表示你存储的数据类型;第二个范型表示stack是由双端队列作为底层来实现的
 *class stack {

 };*/

/*std::queue
 * template <class T,class Constainer = deque<T>>
 * 通过封装deque来实现queue
 * class queue {
 *
 * };*/

#if 0
void test0() {
  stack<int,vector<int>> s1;//vector作为stack的底层实现方式
  stack<int,list<int>> s2;  //list作为stack的底层实现方式
  stack<int,deque<int>> s3; //deque作为stack的底层实现方式
  s1.push(1);
  s2.push(2);
  s3.push(3);
}
#endif 

//要想让我们手写的Stack和库里面的stack一模一样,就可以这样做:
//template <class T,class Container = deque<T>>---这样一来,对它的使用就和调用库函数一样方便了,如
//void test() {
//  Stack<int> s;  ----此时,只需要给一个参数就可以了
//}
template <class T,class Container>
class Stack {
public:
  void push(const T& x) {
    _con.push_back(x);
  }

  void pop() {
    _con.pop_back();
  }

  T& top() {
    return _con.back();
  }

  size_t size() {
    return _con.size();
  }

  bool empty() {//判断栈是否为空
    return _con.empty();//是--true;否--false
  }
private:
  Container _con;
};

void test() {
  Stack<int,deque<int>> s1;
  Stack<int,list<int>> s2;
  Stack<int,vector<int>> s3;
  /*以 s 泛指 上述3者
   * Stack<,> s  栈的构造
   * s.empty()   栈的探空
   * s.size()    栈的大小
   * s.top()     栈顶元素的引用
   * s.push(x)   将元素x压入栈顶
   *             依次调用deque,list,vector的pushback()函数
   * s.pop()     删除栈顶元素
   *             依次调用deque,list,vector的popback()函数*/ 
}

//队列也一样
template <class T,class Container>
class Queue{
public:
  
  Container _con;
};

int main() {
  test();
  return 0;
}
















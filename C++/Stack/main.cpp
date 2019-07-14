#include <iostream>
#include <stack>//LIFO
using namespace std;

void test0() {
  //stack()栈的构造
  //empty()检测栈是否为空
  //size() 返回栈中元素的个数
  //top()  返回栈顶元素的引用
  //push() 将元素val压入栈顶
  //pop()  将栈顶的元素弹出
}

void test1() {
  stack<int> s;  //构造一个栈s
  s.push(0);
  s.push(1);
  s.push(2);
  s.push(3);

  //下面这种访问是不太恰当的
  //for (int i = 0;i < s.size();++i) {
  //  cout << s.top() << endl;
  //  s.pop();
  //}
  while (!s.empty()) {
    cout << s.top() << endl;
    s.pop();
  }
}

void test() {
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  while (!s.empty()) {
    int& ret = s.top();
    ret = 6;
    cout << s.top();
    s.pop();
  }
  cout << endl;
}

int main() {
  test();
  test1();

  return 0;
}

#include <iostream>
using namespace std;

int fun(int a,int b) {
  if (b == 0) {
    throw "devide by zero";
  }
  return a / b;
}

void test() {
  int a;
  int b;
  cin >> a >> b;
  fun(a,b);
}

void test1() {
  int a;
  int b;
  cin >> a >> b;
  try {
    fun(a,b);
  }
  catch(const int a) {
    cout << a << endl;
  }
  catch(const char* str) {
    cout << str << endl;
  }
}

int main() {
  //test();
  test1();
  return 0;
}

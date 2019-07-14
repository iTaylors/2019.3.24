#include <iostream>
using namespace std;

class A {
  public:
    A() {
      _a = 0;
      _b = 0;
      cout << "A()" << endl;
      cout << "_a = " << _a << "_b = " << _b << endl;
    }

    A(int i,int j) {
      _a = i;
      _b = j;
      cout << "A(int i,int j)" << endl;
      cout << "_a = " << _a << "_b = " << _b << endl;
    }

    ~A() {
      cout << "~A()" << endl;
    }
  private:
    int _a;
    int _b;
};

void test() {
  A obj1;
  A obj2(5,8);
}

int main() {
  test();
  return 0;
}

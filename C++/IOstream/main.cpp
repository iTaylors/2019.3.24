#include <iostream>
#include <fstream> //展开文件流头文件
                   //提供两种文件的输入/输出的方式:
                   //1.文本文件(对二进制文件进行编码之后形成的可读性更高的文件,这种文件的名字就)
                   //2.二进制文件                                                   叫做文本文件
using namespace std;

void test() {
  cout << 2 << endl;
  //本质上:cout是一个对象,这就代码是在调用此对象的成员函数->cout.operator<<(2);
  clog << 2 << endl;
  cerr << 2 << endl;
  //这三个都是标准输出
}

void test2() {
  ifstream fin;
  fin.open("text.txt");
  fin.read();
  fin.close();

  ofstream fout;
  fout.open();
  fout.write();
  fout.close();
}

int main() {
  test();
  return 0;
}

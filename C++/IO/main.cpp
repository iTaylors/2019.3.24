#include <fstream> //文件流头文件
#include <iostream>
#include <string.h>
using namespace std;

/* C++IO流:--------这就是标准IO
 * 1.C++系统实现了一个庞大的类库,其中ios为基类,其他类都是直接或间接派生自ios类
 * 2.cin,cout,cerr,clog都是ios这个类所实例化出的一个个对象
 * 3.<<是ios这个类中的运算符重载函数----成员函数
 *   所有的内置类型都把 << 这个运算符重载了
 * 4.>>同<<
 * 5.*/

/* IO
 * 1.标准IO
 * 2.文件IO
 * */

//下面是文件IO
/* C++的文件IO就用fstream文件流
 * 1.ifstream:输入文件流(也叫文件输入流)
 * 2.ofstream:输出文件流(也叫文件输出流)*/

/*文本写:
 * 1.ifstream fin; 定义一个对象
 * 2.int i;        比如说你要将四个字节的内容写入磁盘
 * 3.fin >> i;     这样就写入了----这里的对象重载了 >> 运算符*/

/*文本读:
 * 1.ofstream fout;定义一个对象
 * 2.fout << i     这样就读出了----这里的对象重载了 << 运算符*/      

//二进制读写--以最小格式读写(最小格式:不考虑字符的编码种类,一律每次只读写一个字节的内容
//                           最小格式 = 一个字节)
//二进制读写:数据在内存当中是以字节形式存储的,则它在磁盘上也是以字节形式存储的,并不关心某个字符
//           是什么样子的----因为这个字符本质上是一种编码:有的字符(如英文)是按一个字节进行编码;
//                                                        有的字符(如汉字)是按两个字节进行编码
//                                                        有的字符是按三个字节进行编码
//           对二进制读写来说:它并不关心当前字符是用几个字节来进行编码的----
//                            它只是一个字节一个字节的输进去
//                            or一个字节一个字节的输出来

//文本读写:也叫字符流读写----按空格/按行来读写的


//1.这是一个配置文件:每次去读这个配置文件,都可以读到所有服务器的网址和端口号信息
struct ServerInfo {
  char _ip[50];//IP地址
  int _port;   //IP地址端口号
};

//2.下面是一个配置类:去设置和读取前面的配置文件
//先介绍可读性比较高的文本读写
class Cfg {
public:
  Cfg(const char* filename = "test.cfg"):_filename(filename) {
    //用"test.cfg去初始化一个string对象"
  }

  //写不是写:是将配置文件作为参数传进来,然后在类域中对此文件进行设计------设计(v) == 写(v)
  void WriteText(const ServerInfo& info) {
    ofstream fout(_filename.c_str());
    //所谓的设计,大白话就是当前文件还是一个空文件
    fout << info._ip << endl;   //设计a:将_ip数据作为文件第一行的内容
    fout << info._port << endl; //设计b:将_port数据作为文件第二行的内容
  }

  //读不是读:
  //这个函数需要修改结构体当中的内容
  void ReadText(ServerInfo& info) {//函数功能:将配置信息全部读进来
                                   //怎么读呢?
    ifstream fin(_filename.c_str());
    fin >> info._ip;
    fin >> info._port;

  }

private:
  string _filename;
};

void test() {
  ServerInfo s;     //定义一个(配置文件类型的)对象
  strcpy(s._ip,"www.bitekeji.com");
  s._port = 3030;

  Cfg cfg;          //定义一个配置类对应的对象
  cfg.WriteText(s);  //先把配置文件进行设计

  //一般都是在程序启动之前,先将配置文件设计好了----大白话:文件中存在有效数据

  ServerInfo sIn;
  cfg.ReadText(sIn);



}

int main() {
  test();
  return 0;
}

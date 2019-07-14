#include <string>//要使用String这个类(具体这个类的实现即解释见下方),就得包含这个头文件
#include <iostream>
using namespace std;

//这节介绍了一些常用的 string类的接口

/*
 * 2 ^ n
 * n = 8:256
 * n = 16:65535
 * n = 24:16777216
 * n = 32:42亿9千万*/

/*
 * 2 ^ n
 * n = 10:1K----1024
 * n = 20:1M----1048576        (~1百万)
 * n = 30:1G----1073741824     (~10亿)
 * n = 40:1T----1099511627776  (1024个10亿)*/

//std::String -------见下面的解释
//typedef basic_string<char> string:用类模版实例化了一个类出来,这个类中存放的数据类型就是char
//string是一个范型的别名

//string的4种遍历方式:operator[];迭代器;范围for;at 
//std::String::at 
//      char& at(size_t pos);
//const char& at(size_t pos)const;
//其中---std::String::operator[]最常用

//4G = 4294967294
//4G * 4G = 18446744073709551614

#if 0
1
//std::String::string
//Sring类:它是一个顺序表类的容器(专门去管理字符的(顺序表)容器)
//default---string():无参构造(即默认构造)----它创建的是一个空的顺序表
//copy   ---string(const string& str):拷贝构造
//substring---string(const string& str,size_t pos,size_t len = npos):
//fill   ---string(size_t n,char c);
#endif 

#if 0
2
//std::String::operator=
//string(1)    string& operator=(const string& str);//可以赋值一个string对象
//c-string(2)  string& operator=(const char* s);    //可以赋值一个C风格的字符串
//                                                  //把被赋值的s的内容给变了,被为这个"C风格字符串"
//character(3) string& operator=(char c);           //可以赋值一个字符
#endif 

#if 0
3
//std::String::operator[]
//      char& operator[](size_t pos);     //可读可写的接口
//const char& operator[](size_t pos)const;//只读的接口
#endif 

#if 0
4
//std::string::iterator                            正向迭代器---普通(可读可写)
//string::const_iterator()const         const 正向迭代器---只读(一般适用于你只想去遍历这个容器的内容) 
//std::string::reverse_iterator                    反向迭代器
//std::string::const_reverse_iterator()const;const 反向迭代器---只读(同上)
#endif 

/*一下是和容量(Capacity)相关的接口*/
#if 0
5
std::string::resize 
  void resize(size_t n)        重新设置顺序表的容量
  void resize(size_t n,char c) 重新设置顺序表的容量并将新开辟的位置填充为你想要的字符
#endif 

#if 0
6
//该看reverse接口了
//增容:开新的空间,拷贝原有空间的内容,释放原有空间
/*
 * reserve:只增容,不改变size
 * n > capacity:增容
 * n <= capacity:不做任何操作*/
#endif 
  
//std::String::assign()------字符串赋值函数族

//std::String::insert()------字符串插入函数族

//std::String::erase() ------字符串删除函数族

//std::String::swap(函数1)
//void swap(string& str);
//
//注意还有一个swap函数(函数2)
//void swap(string& x,string& y)
//两个函数实现的功能是完全一样的

#if 0
std::String::c_str 
const char* c_str()const;
#endif 

/*Non-member function overloads-----string类的非成员函数
 * 1.operator+
 * 2.relational operators
 * 3.swap 
 * 4.operator>>
 * 5.operator<<
 * 6.getline*/

#if 0
std::getline(string)--获取一行的内容,然后存到string对象里面去
  (1) istream& getline(istream& is,string& str,char delim)
                    is:输入流   str:这一行的内容应该存到哪个string对象里面去   delim:分隔符
  (2) istream& getline(istream& is,string& str)
#endif 

int main() {
#if 0
  string s;
  //常规(常见的方式)
  getline(cin,s);      aaaaa
  cout << s << endl;   aaaaa
  
  //以空格' '做为分隔符
  getline(cin,s,' ');
  cout << s << endl;

  //以都好,作为分割符
  getline(cin,s,',');
  cout << s << endl;
#endif 
  
#if 0
  当 .比较多是,就要用rfind这个函数接口从后往前找
  string s = "test.tar.gz.exe.txt";
  size_t pos = s.rfind('.');
  string subs = s.substr(pos);
  cout << subs << endl;
#endif 

#if 1
  //string substr(size_t pos = 0,size_t len = npos) const
  //npos:Maximum value for size_t(size_t的最大值)
  //std::String::npos
  //**** static const size_t npos = -1 ****
  //因为size_t代表无符号的整型,所以这里的值实际上等于 npos = 2^32(42亿9千万)
  string str = "test.txt";
  size_t pos = str.find('.');  //一般情况下是从后向前找
  string sub = str.substr(pos);//用sub去接收文件名的后缀
  cout << sub << endl;
#endif 

#if 0
  string s("12345");
  int a = atoi(s.c_str());//将字符串转化为整型
  cout << a << endl;
#endif 

#if 0
  在g++下打印的是...,在VS下打印的是"陕科大"
  char chineseStr[7];
  chineseStr[0] = -55;
  chineseStr[1] = -62;
  //chineseStr[1] = -89;骚科大!!!!哈哈哈哈哈哈哈~~
  chineseStr[2] = -65;
  chineseStr[3] = -58;
  chineseStr[4] = -76;
  chineseStr[5] = -13;
  chineseStr[6] = 0;
  cout << chineseStr << endl;
#endif 

#if 0
  char c = 1;
  cout << c << endl;
  //printf("%x\n",c);
  
  char chineseStr[] = {"陕科大"};
  cout << chineseStr << endl;
  cout << sizeof(chineseStr) << endl;
#endif 

#if 0
  string s1("123");
  string s2("aaa");
  cout << s1 << endl;
  s1.swap(s2);----函数1
  cout << s1 << endl;

  swap(s1,s2);----函数2
  cout << s1 << endl;
#endif 
#if 0
  string s("abcdefghijklmnopqrstuvwxyz");
  s.erase(s.begin());
  cout << s << endl;

  //删除区间:法1
  s.erase(0,4);     
  cout << s << endl;
  //法2:迭代器
  s.erase(s.begin(),s.end());
  cout << endl;
#endif 

#if 0
  插入insert
  string s("12345");
  s.insert(0,"MMM");//头插
  //s.insert(3,"MMM");//在指定的位置插入
  cout << s << endl;
#endif 

#if 0
  string s2("12335");
  s2 += "@";
  string s("KKKKKKKKKKK");
  cout << s << endl;
  s.assign(s2.begin(),s2.end());//assign(赋值)之后,s原有的内容就被覆盖了
  cout << s << endl;
  cout << s2 << endl;
#endif 

#if 0
  string s("12345");
  s.append("tang");
  s.append(1,'@');//插入几个字符要标明----没有+=方便
  s.append("yun");
  cout << s << endl;
#endif 

#if 0
  //std::String::operator+=();string的+=运算符重载-----注意:是尾插
  string s("20131");
  s += "4";
  //s += '6';//二者完全等同,没有区别
  cout << s << endl;
  cout << s.size() << endl;
  cout << s.capacity() << endl;
  s += "shu";
  cout << s << endl;
#endif 

#if 0
  string s("12345");
  cout << s.size() << endl;
  cout << s.capacity() << endl;
  cout << "-----我-----是-----分-----隔-----线-----" << endl;
  
  s.empty();
  cout << s.size() << endl;
  cout << s.capacity() << endl;
#endif 

#if 0
  对应 6 
  string s;
  s.reserve(200);//为了提高效率:可以再定义对象的时候就给它指定容量的大小
                 //提前开好空间,可以提高效率,减少增容的操作
  size_t Capacity = s.capacity();
  cout << "--------capacity:" << Capacity << "--------" << endl;

  int i = 0;
  for (;i < 200;++i) {
    s.push_back(i);//----------++size();
    if (Capacity != s.capacity()) {
      Capacity = s.capacity();
      cout << Capacity << endl;
    }
  }
#endif 
  /*
   * resize(size_t n,char c):
   * n < size: size = n
   * n > size: size = n
   *     1.n < capacity:0 ~ size - 1之间的值不变,size ~ n - 1之间的值初始化为程序员指定的字符
   *     2.n > capacity:先扩容---开一个至少大于等于 n 的空间,拷贝原有空间的内容
   *                    0 ~ size - 1之间的值不变,size ~ n - 1之间的值初始化为程序员指定的字符*/

#if 0
  对应 5
  resize()的基础用法
  string s("12345");
  cout << s.size() << endl;
  cout << s.capacity() << endl;

  s.resize(10,'a');
  cout << s.size() << endl;
  int j = 0;
  for (;j < s.size();++j) {
    cout << s[j] << " ";
  }
  cout << endl;

  j = 0;
  s.resize(2,'b');
  cout << s.size() << endl;
  for (;j < s.size();++j) {
    cout << s[j] << " ";
  }
  cout << endl;
#endif 

#if 0
  范围 for 
  const string s("qdcuiheuhye");
  for (const char& e:s) {
    cout << e << " ";
  }
  cout << endl;

  for (const auto& e:s) {
    cout << e << " ";
  }
  cout << endl;
#endif 

#if 0
  对应 4
  //迭代器:其内容是可读可写的
  //实现原理:char* (大多数底层实现都是char*型的原始指针)
  //作用  :访问元素---类似于指针,可以解引用,可以移动
  //范围  :[begin,end)
  //      :[rend,rbegin)

  //反向迭代器
  //++:反向的++是向前走
  //--:反向的--是向后走
  //rbegin():返回指向最后一个元素的上一个位置的迭代器
  //rend():  返回指向第一个元素位置的迭代器
  string s;
  s = "12345";
  string::reverse_iterator it = s.rbegin();
  for (;it != s.rend();++it) {
    cout << *it << " ";
  }
  cout << endl;

  it = s.rbegin();
  for (;it != s.rend();++it) {
    *it = 'a';    //------说明迭代器是可读可写的
    cout << *it << " ";
  }
  cout << endl;
  

  //正向迭代器
  //++:正向的++是向后走
  //--:正向的--是向前走
  //begin():返回指向第一个元素位置的迭代器
  //end() : 返回指向最后一个元素的下一个位置的迭代器
  string s;
  s = "122345";
  string::iterator it = s.begin();
  for (;it != s.end();++it) {
    cout << *it << " ";
  }
  cout << endl;

  it = s.begin();//迭代器起始的位置其实是可以++的,但是只能 it += 1,不能 it += 2;
  ++it;          
  for (;it != s.end();++it) {
    cout << *it << " ";
  }
  cout << endl;
#endif 

#if 0
  对应 3 
  string s;
  s = "12345";
  int i = 0;
  for (;i < s.size();++i) {
    cout << s[i] << " ";    //用到了迭代器里面的重载运算符[]
  }
  cout << endl;
#endif 

#if 0
  对应 2
  string s;
  s = "ggggg";       //(1)
  cout << s << endl; 
  s = '0';           //(3):不论s之前的内容是什么,现在s中就只包含一个"0"
  cout << s << endl;
#endif 

#if 0
  对应 1
  string s;//无参构造       //空的,里面啥都没有

  char strarr[] = {"12345"};
  string s2(strarr);        //用上面这个数组去拷贝构造s2这个顺序表

  string s3(strarr,2);      //"12"

  string s4(5,'a');         //"aaaaa"

  string s5(s2,1,3);        //"234"
  cout << s << endl;
  cout << s2 << endl;
  cout << s3 << endl;
  cout << s4 << endl;
  cout << s5 << endl;
#endif 
  return 0;
}

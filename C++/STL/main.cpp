#include <iostream>
using std::cout;
using std::endl;
#include <string>

//比特学习STL:是围绕六大组件之一的 "容器" 来展开讲解的
//容器中包括:string,vector,list,deque,map,set,multimap,mullset这么多的类
//遍历方式:1.operator[];2.iterator;3.范围for
class string {
  char* _str;
  size_t _size;
  size_t _capacity;
};
/*一:以下是String类中的普通函数*/

void test_string() {
  //第1:构造一个空对象s1,字符串里面只有一个字符->'\0'
  std::string s1;
  cout << s1.c_str() << endl;

  //第2:用一个已经存在的字符串去初始化对象s2
  std::string s2("hello");
  cout << s2 << endl;
}

void test_string1() {
  //string& append (const string& str);
  //string& append (const char* s);
  std::string s1("hello");
  s1.push_back(' ');
  s1.append("world");
  cout << s1 << endl;
  //实际上很少用到这两个,而是用 +=
  
  std::string s("hello");
  std::string w("world");
  s += ' ';
  cout << s << endl;
  s += w;
  cout << s << endl;

}

void test_string2() {
  std::string s("hello");
  cout << s.size() << endl;
  cout << s.length() << endl;
  cout << s.capacity() << endl;

  s.clear();
  cout << s << endl;
  cout << s.size() << endl;
  cout << s.capacity() << endl;
}

void test_string3() {
  std::string s("hello");
#if 0
  s.resize(3);
  cout << s << endl;
  cout << s.size() << endl;
  cout << s.capacity() << endl;
#endif

#if 0
  s.resize(13);
  //"hello'\0''\0''\0''\0''\0''\0''\0''\0'
  cout << s << endl;
  cout << s.size() << endl;
  cout << s.capacity() << endl;
#endif 

  s.resize(13);
  //"hello'\0''\0''\0''\0''\0''\0''\0''\0'"
  s.resize(20,'a');
  //"hello'\0''\0''\0''\0''\0''\0''\0''\0''a''a''a''a''a''a''a'" ------对
  //在底层数据的存储就是这样的,只不过这种形式在输出的时候就不会在显示终端打印出'\0'
  //"hello'a''a''a''a''a''a''a''\0''\0''\0''\0''\0''\0''\0''\0'" ------错
  //不要被显示终端迷惑了!!!!
  cout << s << endl;
  cout << s.size() << endl;
  cout << s.capacity() << endl;
}

void test_string4() {//两种扩容方式
  std::string s("hello");
  s.reserve(20);
  //reserve这个函数只会把容量扩容,并不会改变size
  cout << s.size() << endl;
  cout << s.capacity() << endl;
  s.resize(20);
  cout << s.size() << endl;
  cout << s.capacity() << endl;

  ///////////////////////////////////////////////////////////////////////////// 
  //reserve是跟插入,+=去配合         reserve(保留)  reverse(逆置)
  //resize 是跟operator[]去配合
}

void test_string5() {//测试每此增容的大小
  std::string s;
  size_t sz = s.capacity();//用sz来保存扩容前的容量
  cout << "making s grow:" << endl;
  int i = 0;
  for (;i < 1000;++i) {
    s += 'c';
    if (sz != s.capacity()) {
      sz = s.capacity();
      cout << "capacity changed: " << sz << endl;
    }
  }
}
/*二:以下是String中的iterator(迭代器)
 * std::string::iterator*/

void test_string6() {
  std::string s1("hello");
  std::string s2 = s1;    //拷贝构造
  cout << s2 << endl;
  std::string s4("world");
  s1 = s4;                //赋值(重载)运算
  cout << s1 << endl;

  size_t i = 0;
  for (;i < s1.size();++i) {
    cout << s1[i] << ' '; //operator[]:Get character of string 
                          //[]重载
  }
  cout << endl;
  i = 0;
  s1[4] = 'x';
  for (;i < s1.size();++i) {
    cout << s1[i] << " ";
  }
  cout << endl;

  //正向迭代器:[         )-----------可读可写
  //          begin     end
  //            |        |
  //        第一个数据  不是最后一个数据(是最后一个数据的下一个数据 -> 即'\0')
  std::string::iterator it1 = s1.begin();
  while (it1 != s1.end()) {
    cout << *it1 << " ";
    ++it1;
  }
  cout << endl;

  //反向迭代器:[             )--------可读可写
  //         rbegin         rend 
  //           |             |
  //        最后一个数据    不是第一个数据(是第一个数据的前一个数据)
  std::string::reverse_iterator rit1 = s1.rbegin();
  while (rit1 != s1.rend()) {
    cout << *rit1 << " ";
    ++rit1;
  }
  cout << endl;

  //const迭代器(也分为正向和反向)---------值可读
  const std::string s5("122333");
  std::string::const_iterator it5 = s5.begin();
  while (it5 != s5.end()) {
    //(*it5)++;5错因:只可读,不可写!!!!!!!
    cout << *it5 << " ";
    it5++;
  }
  cout << endl;

} 

void test_string7() {
  //字符串插入函数
  std::string s1("world");
  //string& insert(size_t pos,const char* s)
  s1.insert(s1.begin(),' ');//在第一个元素前加上一个空格字符
  cout << s1 << endl;

  //string& insert(size_t pos,const string& str)
  s1.insert(0,"hello");     //从新的 0 号位置开始加上一个字符串
  cout << s1 << endl;


  //以下是字符串删除函数
  //1.sequence:string& erase(size_t pos = 0,size_t len = npos);
  //2.character:iterator erase(iterator p);     删去每一个确定的字符
  //3.range   :iterator erase(iterator first,iterator last); 删去一个区间
  
  //现在我要删掉空格
  std::string::iterator it1 = s1.begin();
  //auto it1 = s1.begin();
  while (it1 != s1.end()) {
    if (*it1 == ' ') {
      s1.erase(it1);
    }
    ++it1;
  }
  cout << s1 << endl;
}


int main() {
  test_string7();
  return 0;
}

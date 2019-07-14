#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*STL
 * 1.PJ-------VS
 * 2.SGI------g++*/

void testVec3() {
  vector<int> v;
  //cout << v.size() << endl;     
  //cout << v.capacity() << endl;

  //v.resize(10);
  //cout << v.size() << endl;
  //cout << v.capacity() << endl;

  size_t capa = v.capacity();
  cout << "capacity: " << capa << endl;

  int i = 0;
  for (;i < 200;++i) {
    v.push_back(i);
    if (capa != v.capacity()) {
      capa = v.capacity();
      cout << capa << endl;
    }
 
  }

}

template <class T>
void PrintVec(const vector<T>& v) {
  int i = 0;
  for (;i < v.size();++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}

void testVec4() {
  vector<int> v;
  v.insert(v.begin(),1);//头插
  v.insert(v.end(),10,5);//从v.end()开始插入10个元素
  int arr[] = {1,2,3,4,5,6,7};
  v.insert(v.begin(),arr,arr + sizeof(arr) / sizeof(arr[0]));//头插入一个区间的元素

  vector<int>::iterator it = v.begin();
  cout << *it << endl;
  v.insert(it,-1);//插入会引起迭代器失效:增容导致迭代器失效
  it = v.begin();//改进方法:插入之后重新获取迭代器----说的这么神秘,其实就是指针

  cout << *it << endl;
  PrintVec(v);

  v.erase(it);//删除也会导致迭代器失效:访问越界
  //it = v.erase(it);//改进方法:获取erase接口的返回值----指向原有空间的下一个元素
  it = v.begin();
  cout << *it << endl;

  vector<int> v2;
  swap(v,v2);
  v.swap(v2);
}

void testVec5() {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  //v.push_back(5);
  PrintVec(v);
  vector<int>::iterator it = v.begin();
  while (it != v.end()) {
    if (*it % 2 == 0) {
      v.erase(it);
    }
    ++it;
  }
  PrintVec(v);
}

class Date{
public:
  friend ostream& operator<<(ostream& _cout,const Date& d);
  Date(int year,int month,int day):_year(year),_month(month),_day(day) {
    cout << "Date(int, int, int)" << endl;
  }
private:
  int _year;
  int _month;
  int _day;
};

ostream& operator<<(ostream& _cout,const Date& d) {
  cout << d._year << "-" << d._month << "-" << d._day << endl;
  return _cout;
}

void testVec6() {
  vector<Date> v;
  Date d1(2019,5,25);
  Date d2(2019,6,25);
  Date d3(2019,7,25);
  v.push_back(d1);        //把d1插入v
  //v.emplace_back(d2);     //把d2尾插入v
  v.insert(v.begin(),d1); //再次将d1头插入v
  //v.emplace(v.begin(),d2);//再次将d2头插入v

  PrintVec(v);
}

int main() {
  testVec6();
  return 0;
}

















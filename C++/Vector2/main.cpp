#include <iostream>
#include <assert.h>
#include <string>
using namespace std;
//vector的底层实现
/*vector:
 * T* _start,T* _finish,T* _endOfStorage;
 * size:_finish - _start;
 * capacity:_endOfStorage - +start;
 * insert(iterator pos):vector的插入是通过给一个迭代器,既然是插入就有可能增容
 *            增容就可能导致迭代器失效,所以在insert后,最好再重新获取一下这个迭代器
 * erase(iterator pos):(这个接口是有返回值的,返回值是执行下一个元素的位置)
 *            同时erase也可能导致迭代器失效,保险的(建议!)的方法是:
 *            在erase后获取返回值,此时这个返回值就是指向"被删除的元素的下一个元素"
 * 迭代器:T*(是一个左闭右开的区间)--begin(){return _start},end(){return _finish}
 * vector的实现表面上看是T*,本质上还是原始指针-因为原始指针本身就可以实现"访问当前位置指向的元素"
 * 即范围永远是从第一个位置到指向左后一个元素的下一个位置
 * */


//上次看到了2019.6.1----01:12:00

template <class T>
class Vector{
public:
  typedef T* iterator;
  typedef const T* const_iterator;
  //friend ostream& operator<<(ostream& _cout << int*);
  void PushBack(const T& val) {   //插入数据
    if (_finish == _endOfStorage) {//扩容
      size_t newC = Capacity() == 0 ? 1 : 2 * Capacity();//如果容量是0,就只开存放一个T的空间
                                                         //此后容量依次递增
      Reserve(newC);//扩容函数
    }

    *_finish = val; //将数据插入末尾
    ++_finish;//原始指针要向后挪动一个(T*大小的)位置
  }

  //void PushBack2(const T& val) {
  //  Insert(end(),val);
  //}

  void Reserve(size_t n) {//我要将容量变为 n
    size_t num = Size();//用num记录有效的数据个数
    if (n > Capacity()) {
      T* tmp = new T[n];//1.在堆上开空间
      //浅拷贝
      //if (_start) {
      //  memcpy(tmp,_start,sizeof(T) * num);//2.拷贝---将旧空间的有效数据拷贝到新空间
      //}

      //深拷贝
      if (_start) {
        int i = 0;
        for (;i < Size();++i) {
          tmp[i] = _start[i];
        }
      }

      delete[] _start;//3.再释放将原始指针释放-----这个写在里面,外面都没关系

      //更新原始指针
      _start = tmp;
      _finish = _start + num;
      _endOfStorage = _start + n;
    }
  }

  size_t Capacity() {
    return _endOfStorage - _start;
  }

  size_t Size() {
    return _finish - _start;
  }


  iterator begin() {
    return _start;
  }

  const iterator begin() const {
    return _start;
  }

  iterator end(){
    return _finish;
  }

  const iterator end() const {
    return _finish;
  }

  void Resize(size_t n){}

  T& operator[](size_t pos) {
    assert(pos <= Size());
    return _start[pos];
    //int arr[4] = {a,b,c,d};
    //int* p = arr;
    //arr[3] = d;
    //p[3] = d;
  }

  const T& operator[](size_t pos) const {
    assert(pos <= Size());
    return _start[pos];
  }
  void PopBack() {}

  //挪动:插入式,将元素从后向前移动
  void Insert(iterator pos,const T& val) {
    size_t len = pos - _start;
    if (_finish == _endOfStorage) {
      size_t newC = Capacity() == 0 ? 1 : 2 * Capacity();
      Reserve(newC);
    }

    //这里一定要更新迭代器,因为增容会导致迭代器失效(迭代器(指针)此时是一个垂悬指针-----野指针)
    pos = _start + len;

    iterator end = _finish;
    while (end > pos) {
      *end = *(end - 1);
      --end;
    }
    *pos = val;
    ++_finish;
  }
  void Erase(iterator pos) {
    assert(pos < _finish && pos >= _start);
    iterator begin = pos + 1;
    while (begin < _finish) {
      *(begin - 1) = *begin;
      ++begin;
    }
    --_finish;
  }


private: 
  T* _start = NULL;
  T* _finish = NULL;
  T* _endOfStorage = NULL;
};

#if 0
template <class T>
void Print(const Vector<T>& v) {
  Vector<T>::const_iterator it = v.begin();
  while (it != v.end()) {
    cout << *it << endl;
    ++it;
  }
}
#endif 

void test1() {
  
  Vector<int> v;
  v.PushBack(1);
  v.PushBack(2);
  v.PushBack(3);
  v.PushBack(4);
  v.PushBack(5);
  int i = 0;
  for (;i < v.Size();++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}

void test2() {
  Vector<string> v;
  v.PushBack("123");
  v.PushBack("456");
  v.PushBack("789");
  v.PushBack("100");
  int i = 0;
  for (;i < v.Size();++i) {
    cout << v[i] << endl;
  }
}

void test3() {
  Vector<int> v;
  v.PushBack(1);

}

#if 0
template <class T>
void    --_finish    --_finish;; Print(Vector<T>& v) {
  Vector<T>::iterator it = v.begin();
}
#endif 

int main() {
  //tesn t();
  test2();
  return 0;
}



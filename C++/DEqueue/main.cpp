#include <iostream>
using namespace std;

/*deque:
 * T** map;
 * iterator start :(T*)first,(T*)last,(T*)cur,(T**)node;
 * iterator finish:(T*)first,(T*)last,(T*)cur,(T**)node*/

//DEqueue:double-end queue(双端队列)
//既可以在头部插入/删除,也可以在尾部插入/删除,有时也可以在中间插入/删除(但这样做的效率极低)

/*DEqueue的优缺点:
 * 1.头插/头删/尾插/尾删的时间复杂度都是O(1)
 * 2.支持随机访问
 * 3.增容代价很小,比vector还小
 * 4.一般作为特殊容器的底层结构*/

/* DEqueue,vector,list的比较
 * DEqueue:支持随机访问(但随机访问的效率没有vector高),而且中间的插入/删除比较麻烦(效率低)
 * 增容的代价小,也不会造成内存碎片,头插/头删的效率最高
 * vector最大优势:随机访问,DEqueue也支持
 *       最大缺点:增容代价高
 * list  最大优势:插入/删除效率高
 *       最大缺点:小片段内存的申请和释放,有可能造成内存碎片*/

template <class T,size_t bufferLen>//非类型模版参数可以当作常量来使用
struct __Iterator {
  T& operator*() {
    return *cur;
  }

  __Iterator& operator++() {
    ++cur;
    if (cur == last) {//当前buffer已经走完了,需要去走下一个buffer
      ++node;
      *first = *node;//node是一个二级指针,解引用之后拿到的是下一个buffer的首地址
      cur = first;
      last = first + bufferLen;//在双端队列中,每个buffer都是定长的---bufferLen是一个定值
    }
  }

  __Iterator& operator--() {
    --cur;
    if (cur == first) {
      --node;
      *first = *node;
      cur = first;
      last = first + bufferLen;
    }

  }

  T* first;
  T* last;
  T* cur;
  T** node;
};

template <class T>
class Deque {
  typedef __Iterator<T> iterator;
  iterator begin() {
    return start;
  }

  iterator end() {
    return finish;
  }

  //pushback :尾插是在最后一个buffer的末尾(注意,这里不一定是最后一个位置)进行元素的插入
  //          每次尾插之后,需要更新一下迭代器
  //pushfront:头插是在第一个  buffer的最后一个位置从后先前依次进行元素的插入
  
  //增容:1.当前buffer满了,不需要拷贝数据,只需新开一个buffer即可
  //     2.中控(map)满了,也不需要拷贝数据,只需要开一个更大的空间去存放 n 个T*(node)即可
  //     综上,Deque增容的代价很小

  T** map;
  iterator start; //first指向map中的第一个buffer
  iterator finish;//finish指向map中最后一个buffer
  //这两个指针本身又是一个迭代器
};

int main() {
  return 0;
}

#include <iostream>
using namespace std;

//迭代器要实现的功能:*(接引用),->(箭头是一个指针的操作),++,!=,==----实际上这些功能都要重载
/*list:双向带头的循环链表:头不存元素,仅用来存放链表的头指针,里面的元素并不重要
 *     第一个元素从哪里开始存呢?:存在head->next这个结点中
 *1.迭代器:通过封装链表的结点来实现迭代器
   *  :要拿到这个元素的值,并且必须是可读可写的,所以说要返回这个元素本身T& 
       T& operator*(){return _node->_data;}
   -> :当指针是一个自定义类型或结构体的时候,就可以通过->去访问它的成员,所以返回值是T*
       T* operator->(){return &_node->_data;//返回值是结点中数据成员的地址}
       在调用的时候这样来调:本质上是这样调的-----iterator.operator->()->data成员
      但是编译器在这里做了优化,将两个->合并成一个->了:iterator->data
      也就是说,我们在代码中要想实时的显式调用->函数,就必须写成第二种方式
   ++ :迭代器的++就是迭代器本身的++,所以说返回的是迭代器本身iterator&
       iterator& operator++(){_node = _node->_next;return *this;
       就是把迭代器里面封装的结点的值变一下就可以了---让这个结点走到它的下一个位置
       然后再把这个迭代器(这个迭代器----*this)返回出来就行了}
   -- :iterator& operator--(){_node = _node->_prev;return *this}
 !=/==:两个迭代器去判断相等和不相等,是判断它们指向的位置是否一样,本质上还是去比较迭代器的成员node
       因为node本身也是一个指针,所以判断它(node)就可以了
       bool operator!=(iterator& it){return _node != it._node;}
       bool operator==(iterator& it){return _node == it._node;}
       
  2.拷贝构造/赋值:这里是深拷贝,所以不能只是把链表的头拷过去
  pushback();
  insert();
  erase():erase之后,迭代器(此时的迭代器就是一个垂悬指针)指向的结点已被删掉了,再访问此位置就是非法
  */

/*vector VS list 
 * 1.空间:                        连续/不连续
 * 2.是否支持随机访问的时间复杂度:O(1)/O(n)
 * 3.插入/删除的时间复杂度:       O(n)/O(1)
 * 4.迭代器的实现:            原始指针/封装(非原始指针)
 * 5.迭代器的失效:          插入和删除/只有删除可能导致迭代器失效
 * 6.空间的利用率:                  高/低
 *   因为vector空间申请好之后,除过增容一般是不会释放这个空间的
 *   待对于内存来说:list不管是插入还是删除你都有资源的开销,这里的开销指的是----
 *   插入都要申请新的空间
 *   删除都要释放空间
 *   而且每次都是1个结点这样的大小,所以很容易造成内存碎片,而vector每次都是一大片的去申请与释放
 *   空间,一般不会造成内存碎片
 * 7.使用场景:    当你对随机访问的效率要求比较高的时候一般首选vector
 *                当你需要频繁地插入和删除,一般首选list*/

template <class T>
struct ListNode {//结点帮助迭代器完成解引用的操作(++,--,=,==,!=)
  ListNode<T>* _prev;
  ListNode<T>* _next;
  T _data;

  ListNode(const T& val = T()):_prev(NULL),_next(NULL),_data(val) {

  }
};

//template <class T>
template <class T,class Ptr,class Sef>
struct _ListIterator {//*(解引用),->(返回数据(data成员)的地址),++(移动到下一个结点的地址),!=,==
  typedef ListNode<T> Node;
  typedef _ListIterator<T,Ptr,Sef> Self;
  Node* _node;
  _ListIterator(Node* node):_node(node) {

  }

  Sef operator*() {
  //T& operator*() {
    return _node->_data;
  }

  //T* operator->() {
  Ptr operator->() {
    return &_node->_data;
  }

  Self& operator++() {
    _node = _node->_next;
    return *this;
  }

  Self operator++(int) {
    Self tmp(*this);
    _node = _node->_next;
    return tmp;
  }

  Self& operator--() {
    _node = _node->_prev;
  }

  Self operator--(int) {
    Self tmp(*this);
    _node = _node->_prev;
    return tmp;
  }

  bool operator!=(Self& it) {
    return _node != it._node;
  }
};

#if 0
template <class T>
struct _ConstListIterator {
  typedef ListNode<T> Node;
  typedef _ConstListIterator<T> Self;
  Node* _node;
  _ConstListIterator(Node* node):_node(node) {

  }

  const T& operator*() {
    return _node->_data;
  }

  const T* operator->() {
    return &_node->_data;
  }

  Self& operator++() {
    _node = _node->_next;
    return *this;
  }

  Self operator++(int) {
    Self tmp(*this);
    _node = _node->_next;
    return tmp;
  }

  Self& operator--() {
    _node = _node->_prev;
    return *this;
  }

  Self operator--(int) {
    Self tmp(*this);
    _node = _node->_prev;
    return tmp;
  }

  bool operator!=(Self& it) {
    return _node != it._node;
  }

};
#endif 

template <class T>
class List {//双向带头的循环链表
            //拷贝构造/赋值:深拷贝(PushBack,Insert)
public:
  typedef ListNode<T> Node;
  typedef _ListIterator<T,T*,T&> iterator;     //可读可写的迭代器
  typedef _ConstListIterator<T,const T*,const T&> const_iterator;
  List():_head(new Node) {
    _head->next = _head;
    _head->prev = _head;
  }
  
  void PushBack(const T& val) {
    Node* tail = _head->_prev;
    Node* node = new Node(val);
    tail->_next = node;
    node->_prev = tail;
    node->_next = _head;
    _head->prev = node;
  }

private:
  Node* _head;
};

template <class T>
void PrintLst(List<T>& lst) {
  List<T>::iterator it = lst.begin();
  while (it != lst.end()) {
    *it = 10;
    cout << *it << " ";
  }
  cout << endl;
}

template <class T>
void PrintConstLst(const List<T>& lst) {
  List<T>::const_iterator it = lst.begin();
  while (it != lst.end()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
}

int main() {
  List<int> lst;
  lst.PushBack(1);

  //List<int>::iterator lis = lst.begin();
  return 0;
}



















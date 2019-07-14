#include <iostream>
#include <list>
#include <queue> //双端队列包含在queue这个文件中
using namespace std;

/*************优先级队列就是一个最大堆(通过封装其他容器实现一个顺序表)*******************
 * ***********这个顺序表的特殊之处:对元素的操作必须复合先进先出的原则********************
 * 先进:将元素插如到当前顺序表末尾的下一个位置(尾插)  (后进后出)的原则,思维太抽象,就按先进先出去
 * 先出:将当前顺序表中第一个元素删除  (头删)                 理解就行了,别没事找事想这些垃圾问题
 * 后进:
 * 后出:*/ 

//vector:不能作为queue的底层实现,因为vector不提供pop_front接口(本质上还是头删的效率太低了)
//list  :可以作为queue的底层实现  
//默认  :deque (因为它相对于list来说不会造成内存碎片)
#if 0
void test0() {
  queue<int> q;
  q.push(); //---就是调用相应容器的push_back()函数
  q.pop();  //---就是调用相应容器的pop_front()函数
  q.front();//---调用相应容器的front()函数来获取队头元素 
  q.back(); //---调用相应容器的back()函数来获取队尾元素
  q.empty();//---..............empty()函数判断队列是否为空
  q.size(); //---..............size()函数来求出当前队列中的元素个数
}
#endif 

template <class T,class Container>
class Queue {
public:
  //以下这些函数只有在对象去调用它的时候编译器才会去生成,不调用就不生成
  void push(const T& x) {
    _con.push_back(x);
  }

  void pop() {
    _con.pop_front();
  }

  T& front() {
    return _con.front();
  }

  T& back() {
    return _con.back();
  }

private:
  Container _con;
};

void testQueue() {
  Queue<int,list<int> > q1;
  Queue<int,deque<int> > q2;
  q1.push(3);
  q1.pop(); 
}

/*priority_queue:堆 + 顺序表
 * push:push_back() + (从叶子开始进行)向上调整
 * pop :swap(根,叶子) + pop_back() + (从根开始进行)向下调整
 * top :front()
 * empty:empty()
 * size:size()*/

#if 0
void Test_priority_queue() {
  priority_queue<int> q;
  q.push();//push_back + 最大堆调整函数
  q.pop;   //swap(根,最小元素) + pop_back(交换完成后,此时删除掉的就是原先的根了) + 最大堆调整函数
  q.top;   //调用front函数
}
#endif 

/*priority_queue的实现:
 * vector,deque 可以
 * list 不行---因为顺序表(最大堆化时)的向上调整和向下调整都要用到随机访问,但list不支持随机访问
 * 库里面的默认实现是vector:因为vector的随机访问效率更高*/

template <class T,class Container,class Compare>
class PriorityQueue {        //向上调整/向下调整的目的:都是为了在逻辑上使这个顺序表变为(成为)最大堆
public:
  void push(const T& x) {
    _con.push_back(x);
    shiftUp(_con.size() - 1);//向上调整
  }

  void shiftUp(int child) {  //向上调整的初始参数是孩子的下标
                             //孩子的下标会越来越大
    int parent = (child - 1) / 2;
    while (child > 0) {
      //if (_con[parent] < _con[child]) {
      if (_cmp(_con[parent],_con[child])) {//在任何比较的地方都不用绝对的比较,而是用一个仿函数对象
                                           //就是用我的仿函数成员,比较的规则由此成员自己去定义
        swap(_con[parent],_con[child]);
        child = parent;
        parent = (child - 1) / 2;
      } 

      break;
    }
  }

  void pop() {
    swap(_con[0],_con[_con.size() - 1]);
    _con.pop_back();
    shiftDown(0);             //向下调整----从根开始向下进行调整
  }

  // void shiftDown1(int parent) {
  //   int lchild = 2 * parent + 1;
  //   while (lchild < _con.size()) {
  //     if (lchild + 1 < _con.size()//lchild + 1 就是右孩子(rchild)了
  //         && _con[lchild] < _con[lchild + 1]) {
  //       ++lchild;                 //这句代码的思想就是为了让右孩子去与根进行比较
  // 
  //     }
  //   }
  // }

  void shiftDown(int parent) {//向下调整的初始参数是父亲的下标
                              //由它(父亲的下标)求得的孩子的下标会越来越小
    int child = 2 * parent + 1;
    while (child < _con.size()) {
      //if (child + 1 < _con.size()//如果右孩子的值大于左孩子,就用右孩子去代替左孩子
      //    && _con[child] < _con[child + 1]) {
      if (child + 1 < _con.size()
          && _cmp(_con[child],_con[child + 1])) {
        ++child;
      }

      //if (_con[parent] < _con[child]) {
      if (_cmp(_con[parent],_con.[child])) {
        swap(_con[parent],_con[child]);
        parent = child;
        child = 2 * parent + 1;//更改孩子的下标
      }

      break;
    }
    
  }

  T& top() {
    return _con.front();
  }

  bool empty() {
    return _con.empty();
  }

private:
  Compare _cmp;
  Container _con;
};

template <class T>
class Less {
public:
  bool operator()(const T& a,const T& b) {
    return a < b;
  }
};

template <class T>
class Greater {
public:
  bool operator()(const T& a,const T& b) {
    return a > b;
  }
};



void test() {
  PriorityQueue<int,vector<int>,Less<int> > q;
  //priority_queue<int,vector<int>,greater<int> > q;
  q.push(7);
  q.push(5);
  q.push(2);
  q.push(9);

  while (!q.empty()) {
    cout << q.top() << endl;
    q.pop();
  }

}

#if 0
void test00() {
  Less less;//这是一个对象
  cout << less(2,3) << endl;//使用起来感觉就像函数一样--本质上就是调它的成员函数(见下一行代码)
  cout << less.operator()(2,3) << endl;//明显上一行的可读性更高

  //less(2,3) <==> less.operator()(int a,int b);
}
#endif 

class Date {
public:
  bool operator>(const Date& d) {
    return this->_year > d._year; 
  }

  bool operator<(const Date& d) {
    return this->_year < d._year;
  }
private:
  int _year;
  int _month;
};

int main() {
  test();
  return 0;
}

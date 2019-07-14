#include <iostream>
#include <cstring>
using namespace std;

struct ListNode{
  ListNode* _next;
  ListNode* _prev;
  int _data;

  void* operator new(size_t n) {
    void* p = nullptr;
    p = allocator<ListNode>().allocate(1);
    cout << "memory pool allocate" << endl;
    return p;
  }

  void* operator delete(void* p) {
    allocator<ListNode>().deallocate((ListNode*)p,1);
    cout << "memory pool deallocate" << endl;
  }
};

int globalval = 1;             //存放在数据段的初始化段
static int staticGlobalval;    //存放在数据段的未初始化段

void Test() {//整个函数体存在于代码区

  //注意:在PCB中,谁的地址数值越小,就代表此地址越小(即越靠上)
  int a = 0;//在栈区,先定义a.先-----a的地址(如0x0000 aaa0)  实际运行结果&a = 0x7ffd760db66c
  int b = 0;//b会进行"(压栈)",b抢走了a的地址: 0x0000 aaa0-----这现在成了b的地址了
            //                     a的地址变为0x0000 aaa4)  实际运行结果&b = 0x7ffd760db668
  //若将 int 换为 对象 Date
  //则就是先调用 a 的构造函数
  //再调用的 b 构造函数
  //再调用的 c 构造函数
  /*********************/
  //析构的时候,
  //先析构c,再析构b,再析构a(这也点明了栈区栈区"栈(后进先出---)"这一名称的由来)

  static int staticVal = 1;    //存放在数据段的未初始化段
  int localVal = 1;            //存放在栈区(属于函数里面,函数建立栈帧)

  int num1[10] = {1,2,3,4};    //存放在栈区(函数建立栈帧)

  /*-------------------------------------------------------------------------------------------*/

  char char2[] = "abcd";       //函数建立栈帧:将静态缓冲区的常量静态字符串"abcd"拷贝到char2这个数组中
                               //char2是存放在栈上的
                               //*char2 的内容是拷贝过来的"拷贝数组中的"内容
                               
  char* pChar3 = "abcd";       //函数建立栈帧:这里不是将常量静态字符串拷贝过来,而是让pChar3去指向它
                               //pChar3这个(局部的)指针变量本身是存放在栈上的
                               //但是 *pChar3(它指向的内容仍旧是) 常量静态字符串
                               //即 *pChar3 存放在静态缓冲区(也叫文字常量区)
                               
                               //常量区和编译出来的指令一般都放在代码段（老师说的这句话有待商榷）
                               
  char* char4[] = {"a","b","c","d"};//函数建立栈帧:
  cout << sizeof(char2) << endl;
  cout << sizeof(pChar3) << endl;
  cout << sizeof(char4) << endl;
  cout << &a << endl;
  cout << &b << endl;
  
#if 0
  int* ptr1 = (int*)malloc(sizeof(int) * 4);      //ptr1存放在堆区?错!!!!!!
                                                  //函数建立栈帧
                                                  //ptr1这个(局部的)指针变量本身是在栈上,
                                                  //*ptr1(它指向的内容)是在堆上
  int* ptr2 = (int*)calloc(4,sizeof(int));        //同上
  //calloc:开空间并且初始化 calloc == malloc(函数) + memset(函数)
  int* ptr3 = (int*)realloc(ptr2,sizeof(int) * 4);//同上
  //如果检测到堆后边有足够大的空间,在需要扩容的情况下就能够扩容 
  free(ptr1);
  free(ptr2);
#endif
}

//new和delete是用户进行动态内存申请和释放的操作符,operator new和operator delete是系统提供的全局函
//数,new在底层调用operator new 这个全局函数来申请空间,delete在底层通过operator delete这个全局函数
//来释放空间

#if 0
也就是说
new(的实现)   :operator new + 调用构造函数
              :new失败了会抛异常(相反malloc失败了会返回NULL)

delete(的实现):调用析构函数 + operator delete 
              :delete失败了不会抛异常
/********************************************************************************************/
总结一下:new,malloc,operator new的异同
         delete,free,operator delete的异同
1.对内置类型.三者基本相似
2.对自定义类型 
  //new的原理:
  //先调用operator new函数申请空间
  //再在申请的空间上执行构造函数,完成对对象的初始化
  
  //delete的原理:
  //先在空间上执行析构函数,完成对对象中资源的清理工作
  //再调用operator delete来进行空间的释放
/********************************************************************************************/

#endif
int main() {
  //operator new不是对new这一操作符的重载,相反它是一个系统提供的全局函数
  int* p = (int*)operator new(4);

#if 0
  Test();
  char p1[] = "abcd\0";
  cout << sizeof(p1) << endl;
  cout << strlen(p1) << endl;
  char p2[] = "abcd\\0";
  cout << sizeof(p2) << endl;
#endif 
  return 0;
}
















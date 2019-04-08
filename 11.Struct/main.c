#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if 0
struct Student {
  char name[1024];
  int score;
};
#endif 

// typedef struct Student {
//   char name[1024];
//   int score;
// } Student;

typedef struct Student {
  char name[1024];
  int score;
  //struct student s;//这样不行,编译无法同过
  struct Student* s;//这样就行了,因为不管何种类型的指针,只要其类型确定,就可以知道
                    //这个指针对应 多少个 房间号
                    //结构体中要想包含自身,就得通过指针的方式
} Student;

typedef struct School {
  int a;
  Student students[];
} School;


//struct Student1 {
//  char name[1024];
//  int score;
//} student1,*p;//这是顺便定义了 ~ 类型的全局变量 student,和 struct Student1* 型的指针变量 

typedef struct Area {
  char name[1024];
} Area;

typedef struct City {
  Area areas[100];
} City;

typedef struct Province {
  City cities[100];
} Province;

typedef struct Country {
  //Province provinces[100];
  int id;
} Country;

void Func1(Country country) {//访问结构体具体的内容
  country.id = 1;           //函数形参内容的改变不会对程序实参造成任何影响
  printf("%d\n",country.id);//打印形式参数的内容
}

void Func(Country* country) {//将结构体作为函数参数的时候,优先考虑运用指针的方式传参
  country->id = 1;
  printf("%d\n",country->id);
}

/*以下是结构体的自引用*/

struct Student2 {
  char name[1024];
  int score;
  struct Student2* s;
};

/*内存对齐*/

typedef struct Test {//结构体成员占用的内存空间的相对位置 和代码中结构体变量的
                     //定义写法是密切相关的
  //int a;           //即 &Test 的值与 结构体的第一个成员的地址是相同的
  int b;
  int a;
  int c;
} Test;

typedef struct Test1 {
  double a;
  int b;
  short c;
} Test1;

typedef struct Test4 {
  char a;
  char b;
  char c;
} Test4;

// 对齐数:每个成员都拥有一个对齐数
// 编译器默认提供了一个数字,拿这个默认数字和当前的成员大小取最小值
// 该成员的相对起始位置的地址必须能够被对齐数整除,
// 如果不能整除,就需要在前面补充上若干个字节


//pragma pack(1) -> 设置对齐数为 1
//pragma pack()  -> 恢复系统默认的对齐数(在 Linux 下为 4)


typedef struct Test9 {
  int arr[1024];
  int num;
} Test9;

Test9 s = {{1,2,3,4},1000};

void Print1(Test9 s) {//结构体传参
  printf("%d\n",s.num);
}

void Print2(Test9* ps) {//结构体地址传参
  assert(ps != NULL);
  printf("%d\n",ps->num);
}

/* 一般情况下，首选Print2 函数2 */

//以下是关于位段的介绍
struct Bit {
  int _a:1;
  int _b:1;
  int _c:1;
  int _d:1;
} Bit;

int main() {
  
  printf("%lu\n",sizeof(struct Bit));// -> 4

#if 0
  Print1(s);// -> 传结构体 
  Print2(&s);// -> 传地址
#endif 

#if 0
  Test t;
  printf("%p\n",&t);
  printf("%p\n",&t.a);
  printf("%p\n",&t.b);
  printf("%p\n",&t.c);
  printf("sizeof(t) = %lu\n",sizeof(t));
  Test4 t4;
  printf("sizeof(t4) = %lu\n",sizeof(t4));
  char* p1 = (char*)&t.a;
  char* p2 = (char*)&t.c;
  printf("%d\n",p2 - p1);
#endif 

  //printf("%lu\n",sizeof(struct Student2));-> 自引用

  //char name[1024] = {"Ma Jiao"};
  //printf("%s\n",name);

#if 0
  Country America = {0};
  Func(&America);
  printf("%d\n",America.id); -> 1


  // Country China = {0};
  // Func1(China);
  // printf("%d\n",China.id); -> 0//打印实际参数的内容
#endif 

#if 0
  Student student = {"zhangsan",50,NULL};
  student.name;
  student.score;
  printf("%s,%d\n",student.name,student.score);
  //student.name = "lisi";
  strcpy(student.name,"lisi");
  printf("%s,%d\n",student.name,student.score);

  Student* p = &student;
  printf("%s,%d\n",p->name,p->score);
#endif 

  //printf("%lu\n",sizeof(Student));

  // char str[] = "呵呵";
  // printf("%lu\n",strlen(str));//size_t -> %lu
  return 0;
}


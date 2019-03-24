#include <stdio.h> //头文件里面有面条
#include <string.h>

// C# => C sharp
// 微软已经收购了 Github; 
#if 0
int Isleap1(int year) {
  if (cond) {
    return 1;
  } else {
    return 0;
  }
}

int Isleap2(int year) {
  if (cond) {
    return 1;
  }
  return 0;
  //等价于以下三行代码
  if (!cond) {
    return 0;
  }
}
int Isleap3(int year) {
  if (cond1) {
    if (cond2) {
      if (cond3) {
        if (cond4) {
          DoSomething();
        } else{

        }
      } else {

      }
    } else {

    }
  } else {

  }
}

int Isleap4(int year) {
  if (!cond1) {
    return;
  }
  if (!cond2) {
    return;
  }
  if (!cond3) {
    return;
  }
  if (!cond4) {
    return;
  }
}
#endif 
int IsOdd1(int num) {
  if (num % 2 == 1) {
    return 1;
  }
  return 0;
}

int IsOdd(int num) {//判定奇数的函数,因为函数的返回值要么是1，要么是0，
  return num % 2;   //所以这个函数
}

int main() {
  int input = 0;
  printf("请输入星期:(1-7)\n");
  scanf("%d",&input);
  switch (input) {
    case 1:{
             printf("Monday\n");
             break;
           }
    case 2:{
             printf("Tuesday\n");
             break;
           }
    default:{//每次写了 switch & case都要加上default
              printf("输入有误\n");
           }
  }

#if 0
  int count = 1;
  while (count <= 100) {
    if(IsOdd(count)) {//这里具体体现了汤神巨佬的牛逼之处
      printf("%d ",count);
    }
    count += 1;
  }
  printf("\n");
#endif  
   
  // 0 表示假，非0表示真
  /* 
  int num = -1;
  if (num) {
    printf("hehe\n");
  }
  */

  /*
  int num = 0;
  if (num == 1)
    ;    //这是一个空语句


  {
    printf("hehe\n");
  }
  */

  /*
  int n = 0;
  scanf("%d",&n);
  float ret = 10 / n;
  printf("ret = %f\n",ret);
  */
  
  /*
  int a[] = {1,2,3,4,5,6,7,8,9,10};//定义一个整形数组
  // i -> index
  int i = 0;
  while (i < 10) {
    printf("%d ",a[i]);
    i += 1;
  }
  printf("\n");
  */ 

  
  /*
  int x = 0;
  int y = 0;
  printf("请输入：\n");
  scanf("%d %d",&x,&y);
  int sum = x + y;
  printf("%d\n",sum);
  */

  /*
  //printf("c:\code\test.c\n");//    \t表示制表符
  printf("c:\\code\\test.c\n");    
  //需要打印一个字符串。my name is "TangZhong"
  printf("my name is \"TangZhong\"\n");  //双引号，单引号都需要借助斜杠 \ 来表示
  printf("%c\n",'\'');//在屏幕上打印一个单引号
  printf("%s\n","\"");//在屏幕上打印一个字符串，字符串的内容是双引号
  printf("%c\n",'\\');//在屏幕上打印单斜杠
  printf("%d\n",strlen("abcdef"));//在计算字符串的长度时，是不把 \0 包含在内的
  printf("%c\n",'\32');//ASCII 中 \32 表示的是空格
  printf("%c",'\13');//ASCII 中 \13 表示的是回车键
  printf("%c",'\10');//ASCII 中 \10 表示的是换行键
  //以上三者在屏幕上的显示很相像，要注意区分
  */
  
  /*
  printf("你会认真敲代码吗？（1 愿意，0 不愿意）\n");
  int choice = 0;
  scanf("%d",&choice);
  if (choice == 1) {
    printf("GOOD\n");
  } 
  else if (choice == 0) {
    printf("YOU ARE BAD BOY\n");
  } 
  else {
    printf("输入有误，请重新输入：\n");
  }
  */
  
  //int num = 0;
  //while (num < 10) {
  //  printf("我喜欢你\n",num);//这样就会出现死循环
  //}
  














  return 0;
}

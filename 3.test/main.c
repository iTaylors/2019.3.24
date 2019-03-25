#include <stdio.h>
#include <string.h>
#include <stdlib.h>  //这个里面包含有随机种子函数 rand();
#include <time.h>


int IsOdd(int num) {
  return num % 2;
}
//[0,10)
//[0,9]
//在整个计算机界语言中,绝大部分区间都是用前闭后开[)来表示区间

int Factor(int n) {
  int result = 1;
  int i = 1;
  for (i = 1;i <= n;++i) {
    result *= i;//result = result * i
  }
  return result;
}

int Menu() {
  printf("1.begin game\n");
  printf("0.game over\n");
  printf("please input:\n");
  int choice = 0;
  scanf("%d",&choice);
  return choice;
}
//猜数字游戏
void Game() {
  srand(time(NULL));//这个函数就是在设置随机种子函数
                 //time(0)获取到当前的时间戳
  int result = rand() % 100 + 1;
  while (1) {
    printf("请输入要猜的数字:\n");
    int num = 0;
    scanf("%d",&num);
    if (num < result) {
      printf("低了\n");
    } else if (num > result) {
      printf("高了\n");
    } else {
      printf("恭喜您猜对了!\n");
      break;
    }
  }
}

int Max(int a,int b) {
  return a > b ? a : b;//三目运算符
}

void Swap(int* x,int* y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}
typedef int* Intptr;
void Swap2(Intptr x,Intptr y) {//传址实质上就是某种意义上的传值！！！！
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

int Add(int x,int y) {
  return x + y;
}

int Divide(int x,int y,int* ok) {
  if (y == 0) {
    *ok = 0;
    return 0;
  }
  *ok = 1;
  return x / y;
}

int IsPrime(int x) {
  for (int i = 2;i < x;++i) {
    if (x % i == 0) {
      return 0;
    }
  }
  return 1;
}

//以 \0 为结尾的字符数组,叫做 C 风格字符串.
int main() {
  printf("%d\n",IsPrime(10));

#if 0
  int ok;
  int ret = Divide(10,0,&ok);
  if (ok == 1) {
    printf("调用失败！\n");
  } else {
    printf("调用成功！\n");
  }
  printf("ret = %d\n",ret);
#endif 

#if 0
  int a = 20;
  int b = 10;
  Swap2(&a,&b);
  printf("%d %d\n",a,b);
#endif 

#if 0
  Game();
  while (1) {
    int choice = Menu();
    if (choice == 1) {
    } else {
      printf("goodbye!\n");
    }   
  }
#endif 

#if 0
//在一个普通数组中，查找具体的某个数字n
  int a[] = {9,5,2,7};
  int to_find = 7;
  //求数组 a 的长度公式:sizeof(a) / sizeof(a[0])
  int i = 0;
  for (i = 0;i < sizeof(a) / sizeof(a[0]);++i) {
    if (to_find == a[i]) {
      break;
    }
  }
  if (i == sizeof(a) / sizeof(a[0])) {
    printf("meizhaodao\n");
  } else {
    printf("zhaodaole,这个数是第 %d 个数字\n",i + 1);
  }



//在一个有序数组中，用二分查找(也叫折半查找)法找到某个具体的是数字n
  double b[] = {1,2,3,4,5,6,7,8,9};
  int to_find = 7;
  int left = 0;
  int right = sizeof(b) / sizeof(b[0]) - 1;
  int mid = 0;
  //[left,right]:当前要查找的区间
  while (left <= right) {
    mid = (left + right) / 2;
    if (to_find < b[mid]) {
      right = mid - 1;
    } else if (to_find > b[mid]) {
      left = mid + 1;
    } else {//mid = to_find;
      break;
    }
  }

  if (left <= right) {
    printf("zhaodaole,yuan su xia biao shi %d\n",mid);
  } else {
    printf("mei zhao dao!\n");
  }
#endif 

#if 0
  printf("%d\n",Factor(3));//计算 n 的阶乘
  int sum = 0;
  int i = 1;
  for (i = 1;i <= 10;++i) {
    sum += Factor(i);
    printf("%d\n",sum);//计算 1！+ 2！+ 3！+......+ 10!
  }
#endif 

#if 0
  //下面是一个输入密码的程序，且只有三次输入机会

  //如果第一个参数和第二个参数相等，返回0
  //如果第一个参数小于第二个参数，返回负数
  //如果第一个参数大于第二个参数，返回正数
  char password[1024] = {0};
  int i = 0;
  for (i = 0;i < 3;++i) {
    printf("请输入密码：\n");
    scanf("%s",password);
    if (strcmp(password,"123456") == 0) {
      printf("login ok!\n");
      break;
    }
  }
  if (i == 3) {
    printf("login fault!\n");
    printf("login failed!\n");
  }
#endif

#if 0
  //自两边动态显示“welcome to bit "
  char str1[] = "welcome to bit!";//有效的字符范围是[0,14] => [0,15)
  char str2[] = "###############";
  int left = 0;
  int right = strlen(str1 - 1);
  while (left <= right) {
    str2[left] = str1[left];
    ++left;
    str2[right] = str1[right];
    --right;
    printf("%s\n",str2);
  }
#endif 
  
#if 0
  int i = 0;
  int k = 0;
  //1.下面这个循环会循环 0 次
  for (i = 0,k = 0;k = 0;++i,++k) {
    printf(".\n");
    ++k;
  }
  //循环体执行之前，先判断表达式2即k = 0,如果表达式2的结果为假，
  //  那么循环就不再继续执行了
  
  //2.下面这个循环会循环 无数 次
  //for (i = 0,k = 0;k = 1;++i,++k) {
  //  printf(".\n");
  //}
  //因为表达式2即k = 1,表达式2的结果为真，则循环就会无休止的执行下去
  
  //3.下面这个循环只会执行（即循环）一次
  for (i = 0,k = 0;k == 0;++i,++k) {
    printf("hehe\n");
    ++k;
  }
  //表达式2 'k == 0'是在判断 k 是否和0相等，因为最开始的时候 k 的初始值就是0，则第一次
  //表达式的结果为真，循环开始执行;循环执行一圈后 k 的值变成了 1，k = 0不再成立，其结果
  //为假，那么循环就不再继续执行了
#endif 

#if 0
  int i = 0;
  for (;;) {
    printf("%d\n",i);
    i += 1;
  }
#endif 

#if 0
  int ch = 0;
  while ((ch = getchar()) != EOF) {
    //if (ch >= 97 && ch <= 122)这里等价于下一行
    if (ch >= 'a' && ch <= 'z') {//推荐使用字符
      continue;
    }
    putchar(ch);
  }
#endif 

#if 0
  int i = 1;
  while (i < 101) {
    if (IsOdd(i)) {//只有当 if()条件语句的判断结果为真(即非0)时，
                  //才会执行 if {}大括号里面的语句
      printf("%d ",i);
    }
    ++i;//在写到 while 循环时，首先写出“变量的更新”
  }
  printf("\n");
  int j = 1;
  while (j < 101) {
    if (!IsOdd(j)){
      ++j;
      continue;
    }
    printf("j = %d\n",j);
    ++j;
  }
#endif 

#if 0
  int a[] = {9,5,2,7};
  int num = 2;
  int i = 0;
  while (i < 4) {
    if (a[i] == num) {
      printf("zhaodaole\n");
      break;
    }
    ++i;
  }
  if (i == 4) {
    printf("meizhaodao\n");
  }
#endif 

#if 0
  int num = 0;
  while (num < 10); {
    printf("num = %d\n",num);
    num += 1;
  }
#endif
}

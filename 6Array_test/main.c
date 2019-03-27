#include <stdio.h>
#define ROW 3
#define COL 3
char g_board[ROW][COL];//定义一个全局变量，这个全局变量是一个二维数组
                       //用这个二维数组表示棋盘
                       //期盼上的每个位置初始化成 空格 字符.' '

void Init() {
  int row,col;
  for (row = 0;row < ROW;++row) {
    for (col = 0;col < COL;++col) {
      g_board[row][col] = ' ';
    }
  }
}

void Swap(int* x,int* y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

void BubbleSort(int* arr,int size) {//冒泡排序:zhe ge shi sheng xu pai xu
  int bound = 0;
  //[0,bound]:already sorted
  //[bound,size):waiting to sort 
  for (;bound < size;++bound) {
    int cur = size - 1;
    for (;cur > bound;++bound) {
      if (arr[cur - 1] < arr[cur]) {
        Swap(&arr[cur],&arr[cur - 1]);
      }
    }
  }
}

void Print() {
  int row,col;
  for (row = 0;row < ROW;++row) {
    printf("| %c | %c |%c |\n",g_board[row][0],g_board[row][1],g_board[row][2]);
    printf("---|---|---|\n");
    
}



//三个子连成一条线，横竖斜都算获胜
//一个是玩家，一个是电脑
//轮到玩家落子，提示玩家落子
//轮到电脑落子，电脑会随机找一个空白的坐标落子

int main() {
  //约定好玩家的子 x,电脑的子 o
  //1.进行棋盘的初始化
  //2.先打印出棋盘(第一次就是一个空白的棋盘)
  //3.玩家落子，判定是否游戏结束
  //4.电脑落子，判定是否游戏结束
  //重复执行第二步操作
  int row,col;
  char winner;//winner -> x玩家胜
              //winner -> o电脑胜
              //winner -> ' '胜负未分
              //winner -> q和棋
  Print();
  Init();

  while (1) {
    Print();
    PalyerMove();//玩家落子
    winner = CheckWinner();
    if (winner != ' ') {
      break;
    }
    ComputerMove();//电脑落子
    winner = CheckWinner();
    if (winner != ' ') {
      break;
    }
  }
  if (winner == 'x') {
    printf("玩家胜！\n");
  } else if (winner == 'o') {
    printf("电脑胜！\n");
  } else {
    printf("和棋.\n");
  }
 
}

#if 0
  int arr[] = {9,5,2,7};
  int size = sizeof(arr) / sizeof(arr[0]);
  //先把数组的长度求好，然后当作参数传到函数里面去
  BubbleSort(arr,size);
  int i;
  for (i = 0;i < size;++i) {
    printf("%d\n",arr[i]);
  }
#endif 

#if 0
  int arr1[][5] = {//只能省略行，不能省略列
    {1,2},{3,4}
  };

  int arr[3][4] = {(1,2),(3,4)};//逗号表达式：将多个表达式用逗号写在一起时
                                //则整个表达式的值就是逗号的最后一个表达式
                                //下面是这个二维数组初始化后屏幕打印的结果：
                                //2 4 0 0
                                //0 0 0 0
                                //0 0 0 0

  //int arr[3][4] = {{1,2},{3,4}};
  
  //int arr[3][4] = {1,2,3,4,5};

  int arr[3][4] = {
    {1,2,3,4},{2,2,3,4},{3,2,3,4}
  };
  int row;
  for (row = 0;row < 3;++row) {
    int col;
    for (col = 0;col < 4;++col) {
      printf("%x ",&arr[row][col]);
    }
    printf("\n");
  }
#endif 

#if 0
  int a = 100;
  int arr[] = {0};
  int i;
  for (i = 0;i < 10;++i) {
    printf("%p\n",&arr[i]);
  }
  printf("%p,%d\n",&arr[12],arr[12]);//shu zu fang wen yue jie
#endif 

#if 0
  char arr1[] = "abcd";
  char arr2[] = {'a','b','c','d','\0'};
  //zuo wei zi fu shu zu shi,arr1[] yu arr2[] wan quan deng jia
  char arr3[] = {'a','b','c','d'};
#endif  

#if 0
  char arr1[] = {97,98,99};
  char arr2[] = {'a',98,'c'};
  char arr3[] = {'a','b','c'};
  int i;
  for (i = 0;i < 3;++i) {
    printf("%d\n",arr3[i]);
  } 
  for (i = 0;i < 3;++i) {
    printf("%c\n",arr3[i]);
  }
#endif 

  //const int n = 10;C语言步支持这个语法，但是C++支持
#if 0
  char arr[10] = {0,1,2,3};
  int i;
  for (i = 0;i < 10;++i) {
    printf("%p\n",&arr[i]);
  }
  for (i = 0;i < 10;++i) {
    printf("%d\n",arr[i]);
  }
#endif 

          


#include <stdio.h>

int BitOneCount(int num) {//求一个整数存储在内存中的二进制中 1 的个数
  int count = 0;
  int i;
  for (i = 0;i < 32;++i) {
    if (num & (1 << i)) {//在 C 语言里面 非0 就是真，并不一定非得用 1 才能表示真
                         //这个判断条件如果写成这样 if ([num & (1 << i)] == 1)
                         //就是错的！！！！不要用传统思维来思考，必须深刻理解
                         // 非0 就是真！！！！！！！！！
                         
      ++count;
    }
  }
  return count;
}//注意：非0 的数字才能转换成真，
 //但真转换成数字是就只能是 1 ！！！！！！
 
struct Student{
  char name[1024];
  int score;
}Student;


int main() {
  int i = 0;
  int result = (++i) + (++i) + (++i);
  printf("%d\n",result);

#if 0
  //整型提升，凡是对 char/short 进行数学运算，此时都会先隐式转换成 int 
  unsigned char a = 255;
  //unsigned char b = (a << 1);// -> 254
  unsigned char b = (a << 1) >> 1;// ->255

  printf("%u\n",b);
#endif 

#if 0
  int a = 10;
  int b = 20;
  int max;
  //由于三目运算符的优先级比较低
  max = 1 + (a > b ? a : b);//将啊a,b中的较大者与一做和之后。赋值给max
#endif  

#if 0
  //短路求值：如果是&&，左侧表达式为假的时候，右侧表达式就不会求值了
  //          如果是||，左侧表达式为真的时候，右侧表达式就不会求值了
  int i = 0,a = 0,b = 2,c = 3,d = 4;
  i = a++ && ++b && d++;//注意 a++ 做为表达式时表示的是(a == 0)，0 就是假
  
  printf("%d %d %d %d\n",a,b,c,d);//注意 这里就是对后置++理解的分水岭
                            //此时，具体理解看下方的后置++剖析(a == 1)
  int i = 0,a = 0,b = 2,c = 3,d = 4;
  i = a++ || ++b || d++;
  printf("%d %d %d %d\n",a,b,c,d);
#endif 

#if 0
  int a = 1;
  int b = 2;
  printf("%d\n",a && b);//逻辑与：表达式为真 -> 1,表达式为假 -> 0
  printf("%d\n",a & b);//按位与
  printf("%d\n",a || b);//逻辑或:表达式为真 -> 1,表达式为假 -> 0
  printf("%d\n",a | b);//按位或
#endif 

#if 0
  int num = 1;
  printf("%d\n",num++);// -> 1
  printf("%d\n",num);// -> 2
  //后置++可以理解成以下等效代码
  int tmp = num;
  num += 1;
  return tmp;

  int num = 1;
  printf("%d\n",++num);// -> 2
  printf("%d\n",num);// -> 2
  //前置++可以理解成以下等效代码
  int num0;
  num1 = num0 + 1;
  return num1;
#endif 


#if 0
  int num = 2;
  printf("%x\n",~num);//按位取反
  printf("%x\n",!num);//逻辑取反
#endif 

  //float num = -30146;
  //printf("%d\n",BitOneCount(num));

#if 0
  int a = 0;//明文
  int b = 0;//密文(加密后的数据)
  int c = 0;//密钥
  b = a ^ c;//密码学举例
#endif 

#if 0
  //将下面这个数字的第 3 位设置为 1，将数字的第 i 位设置为 1 也是如此
  unsigned int a = 0;
  printf("%x\n",a | (1 << 3));
  printf("%x\n",a | (1 << i));
  //将下面这个数字的第 3 位设置位 0，将数字的第 i 位设置为 0 也是如此
  unsigned int b = 8;
  printf("%x\n",b & ~(1 << 3));
  printf("%x\n",b & ~(1 << i));
#endif 

#if 0
  // ~ 按位取反操作：0 变 1，1 变 0
  int a = 0x3;//11 -> 0000 0000 0000 0000 0000 0000 0000 0011
  printf("%x\n",~a);//1111 1111 1111 1111 1111 1111 1111 1100
#endif 

#if 0
  // ^ (按位异或操作)：两个操作数相同的时候，结果为0，否则为1
  int a = 0x3;
  int b = 0x2;
  printf("%x\n",a ^ b);
#endif 

#if 0
  // | 按位或操作：两个操作数全为0的时候，结果才是0
  int a = 0x3;//11
  int b = 0x2;//10
  printf("%x\n",a | b);
#endif 

#if 0
  // & 按位与操作：两个操作数全为1的时候，结果才是1
  int a = 0x1;//01
  int b = 0x2;//10
  int c = 0x3;//11
  printf("%x\n",a & b);
  printf("%x\n",b & c);
#endif 

#if 0
  int a = 8;
  a = a >> 1;
  printf("%x\n",a);
  int b= -1;
  b = b >> 1;
  printf("%x\n",b);
  int c = -8;
  //1000 0000 0000 0000 0000 0000 0000 1000 -> -8的原码
  //1111 1111 1111 1111 1111 1111 1111 0111 -> -8的反码
  //1111 1111 1111 1111 1111 1111 1111 1111 -> -8的补码ff ff fff ff 
  //1111 1111 1111 1111 1111 1111 1111 1111 1-> -8右移一位
  //右移规则(算术右移)：左边用原该值的符号位填充，末尾被移出去的 bit 位抛弃掉就行了
  printf("%x\n",c);
  printf("%d\n",c);
#endif 

#if 0
  int b = -7;
  //1000 0000 0000 0000 0000 0000 0000 0111 -> -7 原码
  //1111 1111 1111 1111 1111 1111 1111 1000 -> -7 反码
  //1111 1111 1111 1111 1111 1111 1111 1001 -> -7 补码
  //将 -7 左移一位
  //1111 1111 1111 1111 1111 1111 1111 0010 -> -14 的补码
  //综上可知:无论是正数还是负数，只要是左移，就将左边最高位抛弃，末尾用0填充
  //记简单一点，就是单纯的乘 2
  b = b << 1;
  printf("%x\n",b);
  printf("%d\n",b);

  int a = 1;
  a = a << 1;//左移 1 位相当于乘以 2^1 
             //左移 i 位相当于乘以 2^i
  printf("%d\n",a);
#endif 

  //printf("%d\n",1 / (int)2);
  //printf("%f\n",1.0 / (int)2);

}

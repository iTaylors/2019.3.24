#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h> // 用来使用 int64_t
#include <errno.h>  // -> errno(错误码)


// 空字符串:"" -> char s[1] = {'\0'};
// strlen 结果为 0 的字符串就是空字符串
// 空指针:特指 NULL

//size_t -> unsigned long (就读作无符号的长整型) 
//在 32 位系统下 为 4 个字节
//在 64 位系统下 为 8 个字节

size_t Strlen(const char* str) {
  //if (str == NULL) {
  //  return 0;
  //}
  assert(str != NULL);//一重检验
  //断言:如果表达式为真,断言通过,无事发生
  //如果表达式为假,断言失败,程序直接退出
  size_t count = 0;
  while (str[count] != '\0') {
    ++count;
  }
  return count;
}

char* Strcpy(char* dest,const char* src) {
  assert(dest != NULL);
  assert(src != NULL);
  //int i;// i 的取值范围是 -21亿 - +21亿
  int64_t i = 0;
  for (;src[i] != '\0';++i) {
    dest[i] = src[i];
  }
  dest[i] = '\0';//记得将 '\0' 也拷贝过去
  return dest;
}

char* Strcat(char* dest,const char* src) {//字符串拼接函数
  assert(dest != NULL);
  assert(src != NULL);
  //1.找到 dest 的末尾
  int i = 0;
  for (;dest[i] != '\0';++i);//借助 空循环体 来找到 dest[] 中'\0'的位置

  //2.拷贝
  int j = 0;
  for (;src[j] != '\0';++j) {
    dest[i] = src[j];
    ++i;
  }
  dest[i] = '\0';

  return dest;
}

int Strcmp(const char* dest,const char* src) {//字符串"内容"比较函数
  assert(dest != NULL);
  assert(src != NULL);
  while (*dest != '\0' && *src != '\0') {
    if (*dest < *src) {
      return -1;
    } else if (*dest > *src) {
      return 1;
    } else {
      //对应字符相等,继续进行下一轮比较
      ++dest;
      ++src;
    }
  }
  //循环结束的情况:1.分出胜负
  //               2.未分胜负,有一者或两者遇到了 '\0'

  /*下面是对情况 2 的具体考虑*/
  // dest 遇到了 '\0',src 没遇到 -> dest < src 
  // src 遇到了 '\0',dest 没遇到 -> dest > src 
  // dest 和 src 同时遇到 '\0' -> dest == src 
  // if (*dest == '\0' && *src != '\0') {
  //   return -1;
  // } else if (*dest != '\0' && *src == '\0') {
  //   return 1;
  // } else {//*dest == '\0' && *src == '\0'
  //   return 0;
  // }
  if (*dest < *src) {//此时一定是 dest 遇到了 '\0',src没遇到
                     //因为 '\0' 的ASCII值为0, 0 小于 其他任何的 ASCII 值
                     //姑且先这样理解: src 肯定没遇到 '\0'
                     //在此程序中说明数组 dest[] 的长度比数组 src[] 的长度小
                     //
    return -1;
  } else if (*dest > *src) {//同上: dest 肯定没遇到 '\0';
                            //即数组 dest[] 的长度更长
    return 1;
  } else {//两者同时遇到 '\0' -> *dest == '\0' && *src == '\0'
    return 0;
  }
}

char* Strncpy(char* dest,const char* src,size_t num) {
  assert(dest != NULL);
  assert(src != NULL);
}

//strstr:判断 后字符串str2[] 是否为 前字符串str1[] 的子字符串的函数,其返回值是........
const char* Strstr(const char* str1,const char* str2) {//返回值是指向 str1[] 内部的指针
  assert(str1 != NULL);
  assert(str2 != NULL);
  if (*str2 == '\0') {//判断 str2[] 是否是空字符串,时间复杂度为O(1);
    return NULL;
  }
  //if (strlen(str2) == 0) {//功能同上,时间复杂度为O(N);
  //  return NULL;   
  //}
  if (*str1 == '\0') {
    return NULL;
  }
  const char* black_str = str1;
  while (*black_str != '\0') {
    const char* red_str = black_str;
    const char* child_str = str2;
    while (*red_str != '\0' && *child_str != '\0' && (*red_str == *child_str)) {
              // 情况1              情况2                    情况3 
      ++red_str;
      ++child_str;
    }
    if (*child_str == '\0') {//情况2 表示在此次内循环中证明了 str2[] 是 str1[] 的子字符串
      return black_str;
    }
    
    //情况1 和 情况3 都说明在此次内循环中没有 str2[] 是 str1[] 的子字符串
    //则 black_str 自增 1 ,开始下一次内循环
    ++black_str;
  }

  //外循环跳出时, black_str 指向了 str1[] 中的 '\0',说明字符串str1[] 中不包含 字符串str2[]
  return NULL;
}

//字符串分割函数
int Split(char* input,const char* split_char,char* output[]) {
  int output_index = 0;
  char* p = strtok(input,split_char);
  while (p != NULL) {
    output[output_index] = p;
    ++output_index;
    p = strtok(NULL,split_char);
  }
  return output_index;//切分出来的块数

}

//char* Strtok(char* str,const char* ) {
//  assert(str != NULL);
//}


/*以下函数都是字符分类函数 */ 

int Tolower(int c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

/*以下是内存处理函数*/
void* Memcpy(void* dest,const void* src,size_t num) {//将 地址2 中的数据拷贝到 地址1 里面去
                                      //返回值是 (void*)dest -> 即目标区域的首地址
  assert(dest != NULL);
  assert(src != NULL);

  size_t i = 0;
  char* pdest = (char*)dest;
  const char* psrc = (const char*)src;
  for (;i < num;++i) {
    //dest[i] = src[i]//错!!!!,因为对 void* 不能进行解引用操作,所以上面用到了强制类型转换
    pdest[i] = psrc[i];
  }
  //这里不需要设置 '\0'
  return dest;
}

//标准库认为的缓冲区重合
void* Memmove(void* dest,const void* src,size_t num) {
  assert(dest != NULL);
  assert(src != NULL);
  char* pdest = (char*)dest;
  const char* psrc = (const char*)src;
  if (pdest >= psrc && pdest < psrc + num) {
    //这是标准库认为的缓冲区重合
    int64_t i = num - 1;
    for(;i >= 0;--i) {
      pdest[i] = psrc[i];
    }
  }
  Memcpy(dest,src,num);
  return dest;//返回目标区域 的首地址
}

int main() {
  int arr1[4] = {1,2,3,4};
  int arr2[4] = {0};
  //memcpy(arr2,arr1,sizeof(arr1));//第三个参数的单位是字节
  Memcpy(arr2,arr1,sizeof(arr1));
  int i = 0;
  for (;i < 4;++i) {
    printf("%d\n",arr2[i]);
  }


#if 0
  char str[] = "ls -l /";
  char* output[10] = {0};
  int n = Split(str," ",output);
  int i = 0;
  for (;i < n;++i) {
    printf("%s\n",output[i]);
  }

  // char* p = strtok(str," ");
  // while (p != NULL) {
  //   printf("%s\n",p);
  //   p = strtok(NULL," ");
  // }
#endif 

#if 0
  char str1[] = "abcdef";
  char str2[] = "cde";//str2[] 是 str1[] 的子字符串
  const char* p = Strstr(str1,str2);
  const char* p1 = strstr(str1,str2);
  printf("%p\n",str1);
  printf("%p\n",p);
  printf("%p\n",p1);
#endif 

#if 0
  int num = 10;
  const int* p = &num;//说明我定义 p 这个指针变量时,是希望其指向的内容不能被修改
  int* p2 = p;//不能把 const 类型的指针变量复值给 非const 类型的指针变量
  const int* p3 = p;//这样就可以

  int a = 20;
  int* ptr = &a;
  const int* ptr2 = ptr;//可以将 非const 类型的指针变量复值给 const 类型的指针变量
#endif 

#if 0
  char str1[] = "zzz";
  char str2[] = "zzz";

  // if (strcmp(str1,str2) == 0) {
  //   printf("same\n");
  // } else if (strcmp(str1,str2) < 0) {
  //   printf("小于\n");
  // } else if (strcmp(str1,str2) > 0) { 
  //   printf("大于\n");
  // } else {
  //   printf("呵呵呵\n");
  // }这样写,函数调用 3 次,浪费内存
  
  int ret = Strcmp(str1,str2);
  if (ret == 0) {
    printf("相等\n");
  } else if (ret < 0) {
    printf("小于\n");
  } else if (ret > 0) {
    printf("大于\n");
  } else {
    printf("呵呵呵\n");
  }
#endif   

#if 0
  char str1[1024] = "hehe";
  char str2[] = "haha";
  Strcat(str1,str2);
  Strcat(str1,"bbb");
  Strcat(str1,"ddd");
  printf("%s\n",str1);
  // strcat(str1,str2);
  // strcat(str1,"aaa");
  // strcat(str1,"bbb");
  // printf("%s\n",str1);
#endif 

#if 0
  char str[] = "hehe";
  Strcpy(str,"hahaha");
  printf("%s\n",str);
#endif 

#if 0
  char str[] = "hehe";
  char* p = str;
  if (p != NULL) {    //双重检验
    printf("%lu\n",Strlen(p));
  }
  // char str[] = "hehe";
  // printf("%lu",strlen(str));
  // strlen 和 sizeof 的返回值类型都是 size_t
#endif 
  return 0;
}

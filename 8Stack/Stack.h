#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SDataType;

#define MAX_LEN (100)

typedef struct Stack {
  SDataType array[MAX_LEN];
  int       top;//top 就是 size 的功能

} Stack;

void StackInit(Stack* stack) {
  stack->top = 0;

}

void StackDestroy(Stack* stack) {
  stack->top = 0;

}

//只能从栈顶插入
void StackPush(Stack* stack, SDataType val) {
  assert(stack);
  assert(stack->top < MAX_LEN);

  stack->array[stack->top] = val;
  stack->top++;

}

//只能从栈顶删除
void StackPop(Stack* stack) {
  assert(stack);
  ssert(stack->top > 0);
  stack->top--;

}

//返回栈顶元素
SDataType StackTop(Stack* stack) {
  assert(stack);
  assert(stack->top > 0);
  return stack->array[stack->top - 1];

}

//判断栈内元素是否为空
int StackEmpty(const Stack* stack) {
  return stack->top == 0 ? 1 : 0;

}

//返回栈内数据个数
int StackSize(const Stack* stack) {
  return stack->top;
  }
}







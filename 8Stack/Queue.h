#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int QDataType;

//用单链表来实现队列
////队列的结点实际上就是单链表的结点
typedef struct QNode {
  QDataType val;
  struct QNode* next;

} QNode;

//队列
typedef struct Queue {
  QNode* front;//指向链表的第一个结点，如果链表为空， == NULL
  QNode* rear;//指向链表的最后一个结点，如果链表为空， == NULL
  int size;   //表示队列中数据个数

} Queue;

void QueueInit(Queue* queue) {
  queue->front = queue->rear =  NULL;
  queue->size = 0;

}

void QueueDestroy(Queue* queue) {
  QNode* next;
  for (QNode* cur = queue->front; cur != NULL; cur = next) {
    next = cur->next;
    free(cur);
                
  }
  queue->front = queue->rear = NULL;
  queue->size = 0;

}

//只能从队尾去插入
void QueuePush(Queue* queue,QDataType val) {
  QNode* node = (QNode*)malloc(sizeof(QNode));
  assert(node);
  node->val = val;
  node->next = NULL;
  queue->size++;
  if (queue->rear == NULL) {
    queue->front = node;
    queue->rear = node;
    return;//若是触发 if 语句中的 return 则程序将在这一步停止，并且跳出当前函数
  }

  //原先队列的最后一个结点(即queue->rear) 的 next 指向新插入的结点 node 
  queue->rear->next = node;

  //新的队列的最后一个结点(即queue->rear)就是新插入的这个结点 node 
  queue->rear = node;

}

//只能从队头去删除
void QueuePop(Queue* queue) {
  assert(queue->size > 0);
  queue->size--;
  QNode* old_front = queue->front;//old_front用来标记原先的队首结点

  //更新对首的结点
  queue->front = old_front->next;
  free(old_front);

  if (queue->front == NULL) {
    queue->rear = NULL;
                  
  }

}

//返回队首的元素
QDataType QueueFront(const Queue* queue) {
  assert(queue->size > 0);
  return queue->front->val;

}

int QueueEmpty(const Queue* queue) {
  return queue->size == 0 ? 1 : 0;

}

int QueueSize(const Queue* queue) {
  return queue->size;

}









#include "SqList.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


//1.初始化
void InitList(LinkList* L) {
  assert(L != NULL);
  L->first = NULL;
}

//2.销毁
void DestroyList(LinkList* L) {
  assert(L != NULL);
  LNode* next = NULL;
  for(LNode* cur = L->first;cur != NULL;cur = next) {
    next = cur->next;
    free(cur);
  }
  L->first = NULL;
}

//3.下面是一个购买结点的函数
LNode* BuySListNode(ElemType data) {
  LNode* node = (LNode*)malloc(sizeof(LNode));
  assert(node != NULL);
  node->data = data;
  node->next = NULL;
  return node;
}

//4.头插
void PushFrontList(LinkList* L,ElemType data) {
  assert(L != NULL);
  LNode* node = (LNode*)malloc(sizeof(LNode));
  assert(node != NULL);
  node->data = data;
  //以上四步是对（LNode*）Buy 这一封装函数的再现
  node->next = L->first;
  L->first = node;

}

//5.尾插
void PushBackList(LinkList* L,ElemType data) {
  assert(L != NULL);
  if(L->first == NULL) {
    PushFrontList(L, data);
    return;
  }
  LNode* lastone = L->first;
  for (; lastone->next != NULL; lastone = lastone->next) {

  }
  LNode* node = BuySListNode(data);
  lastone->next = node;
  node->next = NULL;
}

//6.头删
void PopFrontList(LinkList* L) {
  assert(L != NULL);
  assert(L->first != NULL);// 有链表，但是链表是空的
  LNode* old_first = L->first;
  L->first = L->first->next;
  free(old_first);
}

//7.尾删
void PopBackList(LinkList* L,ElemType data) {
  assert(L != NULL);
  assert(L->first != NULL);//链表只有0个元素
  if (L->first->next == NULL) {
    LNode* p = L->first;            //free（L->first);
    L->first = L->first->next;
    free(p);
    return;
   }
  LNode* cur = L->first;
  LNode* lastone;
  for (; cur->next->next != NULL; cur = cur->next) {
    
  }
  lastone = cur->next;
  cur->next != NULL;
  free(lastone);
}

//8.打印
void PrintList(LinkList* L) {
  for(LNode* cur = L->first;cur != NULL;cur = cur->next) {
    printf("%d --> ",cur->data);
  }
  printf("NULL\n");
}

//9.在两个结点之前插入新的结点（头插和尾插除外->时两种特殊情况）
void InsertAfterList(LNode* pos,ElemType data) {
  LNode* node = BuySListNode(data);
  node->next = pos->next;
  pos->next = node;
}

//10.删除链表中的某个结点（头删和尾删除外->是两种特殊情况）
void EraseAfterList(LNode* pos) {
  LNode* del = pos->next;
  pos->next = pos->next->next;
  free(del);
}

//11.删除第一个遇到的data结点，重点是找到 data 这个结点的前一个结点
void RemoveList(LinkList* L,ElemType data) {
  LNode* prev = NULL;
  LNode* cur = L->first;
  while(cur != NULL && cur->data != data) {
    prev = cur;
    cur = cur->next;
  }
  if(cur == NULL) {
    return;
  }
  if(prev == NULL) {
    LNode* p = L->first;
    L->first = L->first->next;
    free(p);
    return;
  }

  prev->next = cur->next;
  free(cur);
}

//12.查找
LNode* FindList(LinkList* L,ElemType data) {
  for(LNode* cur = L->first;cur != NULL;cur = cur->next) {
    if(cur->data = data) {
      return cur;
    }
  }
  return NULL;
}



void SListRemove(LinkList* L,ElemType data) {
  assert(L != NULL);
  if(L->first->data) {
    LNode* second = L->first->next;
    free(L->first);
    L->first = second;
  }
  LNode* cur = NULL;
  while(cur->next != NULL){
    if(cur->next->data == data) {
      LNode* next = cur->next;
      cur->next = cur ->next -> next;
      free(next);
      return;
    }
    cur = cur->next;
  }
}





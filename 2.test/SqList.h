#pragma once

typedef int ElemType;

typedef struct LNode{//定义结点：表示链表中的每一个结点
  ElemType data;   //ElemType是数据元素类型
  struct LNode* next;
} LNode;

typedef struct LinkList{//定义链表，它里头有一个指针 first ,其指向链表的第一个结点的地址
  struct LNode* first;
} LinkList;

void InitList(LinkList* L);
void DestroyList(LinkList* L);

void PushFrontList(LinkList* L);

void PushBackList(LinkList* L, ElemType data);
void PopFrontFront(LinkList* L);
void PopbackList(LinkList* L);
void PrintList(LinkList* L);
void InsertAfterList(LNode* pos, ElemType data);//因为么有下标可以用，所以只能用指针来表示结点的位置

void EraseAfterList(LNode* pos);//删除 pos 指向的结点的后面一个结点

void RemoveList(LinkList* L);//删除第一个遇到的 data 结点，重点是找到 data 这个结点的前一个结点

LNode* FindList(LinkList* L, ElemType data);
LNode* BuySListNode(ElemType data);
void ListInsert_L(LNode* pos, ElemType data);
















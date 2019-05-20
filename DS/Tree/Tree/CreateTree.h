#include "Tree.h" 

typedef struct Result {
  Node* node;
  int used;
} Result;

Result CreateTree(char preorder[],int size) {
  if (size <= 0) {                         //这一部分是对  
    Result result;                         //  特
    result.node = NULL;                    //  殊
    result.used = 0;                       //  情
    return result;                         //  况
  }                                        //  的
                                           //  处
  if (preorder[0] == '#') {                //  理
    Result result;                         //  
    result.node = NULL;                    //  
    result.used = 1;                       //  
    return result;                         //  
  }

  //以下是递归的情况
  Node* root = (Node*)malloc(sizeof(Node));
  root->value = preorder[0];

  Result left = CreateTree(preorder + 1,size - 1);

  Result right = CreateTree(preorder + 1 + left.used,size - 1 - left.used);

  

  Result result;
  result.node = root;
  result.used = 1 + left.used + right.used;
}

Node* CreateTree2(char preorder[],int size,int* pUsed) {
  //终止条件1
  if (size == 0) {
    *pUsed = 0;
    return NULL;
  }

  //终止条件2
  if (preorder[0] == '#') {
    *pUsed = 1;
    return NULL;
  }

  //根
  Node* root = (Node*)malloc(sizeof(Node));
  root->value = preorder[0];

  //左子树
  int leftUsed;
  root->left = CreateTree2(preorder + 1,size - 1,&leftUsed);

  //右子树
  int rightUsed;
  root->right = CreateTree2(preorder + 1 + leftUsed,size - 1 - leftUsed,&rightUsed);

  *pUsed = 1 + leftUsed + rightUsed;
  return root;
}













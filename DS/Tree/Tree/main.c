#include "Tree.h"

#if 0
//先序遍历函数原始原型(别纠结我的病句......)
void preorderTraversal(Node* root) {
  if (root == NULL) {
    return;
  }

  if (root->left == NULL && root->right == NULL) {
    printf("%d ",root->value);
    return;
  }

  if (root->right == NULL) {
    printf("%d",root->value);
    preorderTraversal(root->left);
    return;
  }

  if (root->left == NULL) {
    printf("%d ",root->value);
    preorderTraversal(root->right);
    return;
  }

  printf("%d ",root->value);
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

//第一次简化:除过 root == NULL ,剩下的每一种情况都要打印根结点中的数据
//所以就把这个语句提到函数的最前面
void preorderTraversal(Node* root) {
  if (root == NULL) {
    return;
  }
  printf("%d ",root->value);

  if (root->left == NULL && root->right ==NULL) {
    return;
  }

  if (root->right == NULL) {
    preorderTraversal(root->left);
    return;
  }

  if (root->left == NULL) {
    preorderTraversal(root->right);
    return;
  }

  preorderTraversal(root->left);
  preorderTraversal(root->right);

}

//经观察发现,还可以进一步化简
void preorderTraversal(Node* root) {
  if (root == NULL) {
    return;
  }
  printf("%d ",root->value);

  if (root->left != NULL) {
    preorderTraversal(root->left);
  }

  if (root->right != NULL) {
    preorderTraversal(root->right);
  }

}

//当 root->left == NULL 时,我递归一个 preorderTraversal(NULL)进去也没有多大影响
// root->right == NULL 时同理
void preorderTraversal(Node* root) {
  if (root == NULL) {
    return;
  }
  printf("%d ",root->value);

  if (root->left != NULL) {
    preorderTraversal(root->left);
  } else {
    preorderTraversal(NULL);
  }

  if (root->right != NULL) {
    preorderTraversal(root->right);
  } else {
    preorderTraversal(NULL);
  }
}
#endif 

//最后这一步化简最关键:当 preorderTraversal(NULL),对程序没有影响时,就可以
//得到先序遍历函数的最终形式了.
void preorderTraversal(Node* root) {
  if (root == NULL) {
    return;
  }
  printf("%d ",root->value);

  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

void inorderTraversal(Node* root) {
  if (root == NULL) {
    return;
  }
  inorderTraversal(root->left);
  printf("%d ",root->value);
  inorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
  if (root == NULL) {
    return;
  }
  postorderTraversal(root->left);
  postorderTraversal(root->right);
  printf("%d ",root->value);

}


int Size(Node* root) {
  if (root == NULL) {
    return 0;
  }
  return Size(root->left) + Size(root->right) + 1;
}

typedef struct Node{
  struct Node* left;
  struct Node* right;
  char value;
} Node;

void InOrder(Node* root) {
  if (root != NULL) {
    InOrder(root->left);
    printf("%c ",root->value);
    InOrder(root->right);
  }
}

int main() {
  char line[1024];
  while (gets(line)) {

    int size = strlen(line);
    Node* root = CreateTree2(line,size,&used);
    InOrder(root);
    printf("\n");
  }

  return 0;
}









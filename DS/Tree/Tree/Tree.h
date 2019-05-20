#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node* left;
  struct Node* right;
} Node;

#if 0
void Preorder(Node* root) {
  if (root == NULL) {
    return;
  } else if (root->left == NULL && root->right == NULL) {
    printf("%d ",root->value);
    return;
  } else if (root->left != NULL && root->right == NULL) {
    printf("%d ",root->value);
    Preorder(root->left);
    return;
  } else if (root->left == NULL && root->right != NULL) {
    printf("%d ",root->value);
    Preorder(root->right);
    return;
  } else {
    printf("%d ",root->value);
    Preorder(root->left);
    Preorder(root->right);
    return;
  }

}
#endif 

void PreorderTraversal(Node* root) {//根-左子树-右子树
  if (root == NULL) {
    return;
  }
  printf("%d ",root->value);
  PreorderTraversal(root->left);
  PreorderTraversal(root->right);
}

void InorderTraversal(Node* root) {//左子树-根-右子树
  if (root == NULL) {
    return;
  }
  InorderTraversal(root->left);
  printf("%d ",root->value);
  InorderTraversal(root->right);
}

void PostorderTraversal(Node* root) {//左子树-右子树-根
  if (root == NULL) {
    return;
  }
  PostorderTraversal(root->left);
  PostorderTraversal(root->right);
  printf("%d ",root->value);
}



















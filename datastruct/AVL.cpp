#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

typedef struct AVLNode {
	ElementType Data;
	struct AVLNode *left;
	struct AVLNode *right;
	int height;
}AVLtree;

int Getheight(AVLtree* T) {
	if (T == NULL)
		return -1;
	else
		return T->height;
}

int max(int a,int b) {
	return a > b ? a : b;
}

AVLtree* LL_Rotation(AVLtree *A) {
	AVLtree* B = A->left;
	A->left = B->right;
	B->right = A;
	A->height = max(Getheight(A->left), Getheight(A->right))+1;
	B->height = max(Getheight(B->left),A->height)+1;
	return B;
}

AVLtree* RR_Rotation(AVLtree* A) {
	AVLtree* B = A->right;
	A->right = B->left;
	B->left = A;
	A->height = max(Getheight(A->left), Getheight(A->right)) + 1;
	B->height = max(Getheight(B->left), A->height) + 1;
	return B;
}

AVLtree* LR_Rotation(AVLtree* A) {
	A->left = RR_Rotation(A->left);
	return LL_Rotation(A);
}

AVLtree* RL_Rotation(AVLtree* A) {
	A->right = RR_Rotation(A->right);
	return LL_Rotation(A);
}

AVLtree *Insert(AVLtree* T, ElementType x) {
	if (!T) {	//若插入空树，则新建包含一个结点的树
		T = (AVLtree*)malloc(sizeof(struct AVLNode));
		T->Data = x;
		T->height = 0;
		T->left = T->right = NULL;
	}

	else if (x < T->Data) {
		/* 插入T的左子树 */
		T->left = Insert(T->left, x);
		if (Getheight(T->left) - Getheight(T->right) == 2) {
			if (x < T->left->Data)
				T = LL_Rotation(T);
			else
				T = LR_Rotation(T);
		}
	}

		else if (x > T->Data) {
			/* 插入T的右子树 */
			T->right = Insert(T->right, x);
			if (Getheight(T->left) - Getheight(T->right) == -2) {
				if (x > T->left->Data)
					T = RR_Rotation(T);
				else
					T = RL_Rotation(T);
			}
		}
	T->height= max(Getheight(T->left), Getheight(T->right)) + 1;
	return T;
}

void PreOrderTree(AVLtree* t) {	//先序遍历二叉树
	if (!t)
		return;
	printf("%d ", t->Data);
	PreOrderTree(t->left);
	PreOrderTree(t->right);
}

int main(){
	AVLtree* root = NULL;
	root =Insert(root, 9);
	root =Insert(root, 5);
	root =Insert(root, 10);
	root =Insert(root, 0);
	root =Insert(root, 6);
	root =Insert(root, 11);
	root =Insert(root, -1);
	root =Insert(root, 1);
	root =Insert(root, 2);
	printf("前序遍历：\n");
	PreOrderTree(root);
	/* The constructed AVL Tree would be
				   9
				  /  \
				 1    10
			   /  \     \
			  0    5     11
			 /    /  \
			-1   2    6
  */
	return 0; 
	}
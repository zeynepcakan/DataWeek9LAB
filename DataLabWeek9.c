#include <stdio.h>
#include <stdlib.h>


struct node{
	int data;
	struct node *left;
	struct node *right;
};

typedef struct node *BTREE;

BTREE insert(BTREE root , int x){
	if(root==NULL){
		BTREE new =(BTREE)malloc(sizeof(BTREE));
		new->left=new->right=NULL;
		new->data=x;
		return new;
	}
	else if(root->data<x){
		root->right=insert(root->right,x);
		return root;
	}
	else{
		root->left=insert(root->left,x);
		return root;
	}
	
}
int traverse(BTREE root){
	if(root==NULL)
		return NULL;
	//inorder
	traverse(root->left);
	printf("%d\t",root->data);
	traverse(root->right);	

}
int size(BTREE root){
	if(root==NULL)
		return NULL;
	return size(root->left)+1+size(root->right);	
}
int countParents(BTREE root){
	int parent_say=0;
	if(root==NULL)
		return NULL;
	if(root->left!=NULL||root->right!=NULL)
		parent_say++;
	parent_say+=countParents(root->left);
	parent_say+=countParents(root->right);
	return parent_say;
		
}
int ara(BTREE root,int x){
	if(root==NULL)
		return NULL;
	if(root->data==x)
		return 1;
	if(ara(root->left,x)==1)
		return 1;
	if(ara(root->right,x)==1)
		return 1;
	return -1;			
}
//Aðacýn derinliðini bulma;
int treeDepth(BTREE root){
	if(root==NULL)
		return 0;
	else{
		int leftDepth=treeDepth(root->left);
		int rightDepth=treeDepth(root->right);
		return (leftDepth>rightDepth ? leftDepth : rightDepth)+1;
	}	
}

//Aðacýn yüksekliðini bulma;
int height(BTREE root){
	if(root==NULL)
		return -1;
	else{
		int left_h,right_h;
		left_h=height(root->left);
		right_h=height(root->right);
		if(right_h>left_h)
			return right_h+1;
		else
			return left_h+1;	
	}	
}
BTREE delete_node(BTREE root,int x){
	BTREE p,q;
	if(root==NULL)
		return NULL;
	if(root->data==x){
		if(root->left==root->right){
			free(root);
			return NULL;
		}
		else{
			if(root->left==NULL){
				p=root->right;
				free(root);
				return p;
			}
			else if(root->right==NULL){
				p=root->left;
				free(root);
				return p;
			}
			else{
				p=q=root->right;
				while(p->left!=NULL)
					p=p->left;
				p->left=root->left;
				free(root);
				return q;	
			}
		}
	}	
	else if(root->data<x)
		root->right=delete_node(root->right,x);
	else
		root->left=delete_node(root->left,x);	
	return root;	
}
int main() {
	
	BTREE myroot=NULL;
	myroot=insert(myroot,25);
	myroot=insert(myroot,18);
	myroot=insert(myroot,11);
	myroot=insert(myroot,19);
	myroot=insert(myroot,33);
	myroot=insert(myroot,32);
	myroot=insert(myroot,42);
	traverse(myroot);
	printf("\ndugumlerin sayisi:%d",size(myroot));
	
	int parent=countParents(myroot);
	printf("\nparents sayisi:%d",parent);
	
	printf("\nfonksiyondan dönen deðer: %d\n",ara(myroot,11));
	int h = height(myroot);
	printf("\nAgacin yuksekligi: %d",h);
	int d=treeDepth(myroot);
	printf("\nAgacin derinliði: %d",d);
	
	myroot=delete_node(myroot,11);
	myroot=delete_node(myroot,18);
	myroot=delete_node(myroot,33);
	printf("\nagactan dugum silindikten sonra: %d\n",size(myroot));
	traverse(myroot);

	
	
	return 0;
}

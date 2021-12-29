#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

struct node
{
	int item;
	node *left, *right;
};

bool is_leaf_node(node*);
bool insert_node(node*&, int);
void print_inorder(node*);
void print_preorder(node*);
void print_postorder(node*);
int tree_size(node*);
int tree_height(node*);

int main()
{
	node * root=NULL, *parent=NULL, *del=NULL;
	int i;
	
	srand(time(NULL));
	
	for(i = 0; i <10; i++)
	{
		insert_node(root, rand()%100);
	}

	cout<<"\nPreorder:  ";
	print_preorder(root);
	cout<<endl;

	cout<<"\nInorder:   ";
	print_inorder(root);
	cout<<endl;

	cout<<"\nPostorder: ";
	print_postorder(root);
	cout<<endl;
	cout<<"\nHeight is: "<<tree_height(root)<<endl;

	cout<<"\nThere are from tree_size: "<<tree_size(root)<<" Nodes"<<endl<<endl;
	
	return 0;
}

bool insert_node(node* &root, int n)
{
	node* temp = new node;
	temp->item = n;
	temp->left = NULL;
	temp->right = NULL;

	if( root == NULL)
	{
		root = temp;
		return true;
	}
	else{
		if( root->item <= temp->item)
		{
			insert_node( root->right, n);
		}
		else
			insert_node( root->left, n);
	}
}

void print_inorder(node *root)
{
	if(root != NULL)
	{
		print_inorder(root->left);
		cout <<root->item<< " ";
		print_inorder(root->right);
	}  
}
		
void print_preorder(node* root)
{
	if(root != NULL)
	{
		cout <<root->item<< " ";
		print_preorder(root->left);
		print_preorder(root->right);
	}

}

void print_postorder(node* root)
{
	if(root != NULL)
	{
		print_postorder(root->left);
		print_postorder(root->right);
		cout <<root->item<< " ";

	}

}
int tree_size(node* root)
{
	if ( root == NULL)
		return 0;
	else
		return 1+tree_size(root->left)+tree_size(root->right);
}

int max(int a, int b)
{
	return a>b?a:b;
}

int tree_height(node* root)
{
	return max(tree_size(root->left), tree_size(root->right));
}

bool is_leaf_node(node* target)
{
	return (target->left == NULL && target->right == NULL);
}
	



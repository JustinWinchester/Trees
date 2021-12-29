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
bool delete_node(node**, int);
bool insert_node(node**, int);
bool search_node(node*, int, node**, node**);
void print_inorder(node*);
void print_preorder(node*);
void print_postorder(node*);
int tree_size(node*);
int tree_size_2(node*);
int tree_height(node*);

int main()
{
	node * root=NULL, *parent=NULL, *del=NULL;
	int i;
	
	srand(time(NULL));
	
	for(i = 0; i <10; i++)
	{
		if(i == 5)
			insert_node(&root, 6);
		else
			insert_node(&root, rand()%100);

	}

	cout<<"\nInorder:   ";
	print_inorder(root);
	cout<<endl;

	if(delete_node(&root, 6))
		cout<<"\nFound and deleted\n";
	else
		cout<<"\nNOT find.\n";

	
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
	cout<<"\nThere are: from tree_size_2 "<<tree_size_2(root)<<" Nodes"<<endl<<endl;
	
	return 0;
}

bool insert_node(node **root, int n)
{
	node* temp = new node;
	temp->item = n;
	temp->left = NULL;
	temp->right = NULL;

	if( *root == NULL)
	{
		*root = temp;
		return true;
	}
	else{
		if( (*root)->item <= temp->item)
		{
			insert_node( &((*root)->right), n);
		}
		else
			insert_node( &((*root)->left), n);
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
		
bool search_node(node* root, int key, node** parent, node** del)
{


	if(root == NULL)
	{
		*parent = *del = NULL;
		return false;
	}

	else if(root->item == key)
	{
		*del = root;
		return true;
	}	
	else if( root->left != NULL && root->left->item == key)
	{
		*parent = root;
		*del = root->left;
		return true;
	}
	else if( root->right != NULL &&root->right->item == key)
	{
		*parent = root;
		*del = root->right;
		return true;
	}

	else if(root->item > key && root->left != NULL)
			search_node(root->left, key, parent, del);
	else if(root->item <= key && root->right != NULL)
			search_node(root->right, key, parent, del);
	else
		return false;
	
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
int tree_size_2(node* root)
{
	int cnt = 0;
	if(root->left != NULL)
		cnt += tree_size_2(root->left);
	if(root->right != NULL)
		cnt += tree_size_2(root->right);
	return 1 + cnt;
}

int max(int a, int b)
{
	return a>b?a:b;
}

int tree_height(node* root)
{
	return max(tree_size(root->left), tree_size(root->right));
}

bool delete_node(node**root, int key)
{
	node *parent=NULL, *del=NULL;
	bool result = search_node(*root, key, &parent, &del);

	cout<<result<<endl;

	if(result && del != NULL)
	{
		if(is_leaf_node(del))
		{
			if(parent->item > del->item)
				parent->left = NULL; //delete left node
			else
				parent->right = NULL;
			return true;
		}
		else if(del->right != NULL)
		{ 	node* temp = del->right; //go to right
			parent = del; //temp's parent node

			if(temp->left == NULL)
			{
				del->item = temp->item;
				parent->right = temp->right;
				return true;
			}
			else{	
			
			while(temp->left != NULL) //go to left AFAP
			{
				parent = temp;
				temp = temp->left;
			}
			del->item = temp->item;//copy temp's data into del
			parent->left = NULL; //delete temp
			return true;
			}
		}
		else //if(del->left != NULL && del->right == NULL)
		{ 	node* temp = del->left; //go to left
			parent = del; //temp's parent node
			if(temp->left == NULL)
			{
				del->item = temp->item;
				parent->left = temp->left;//remove del
				return true;
			}
			else{	
			
			while(temp->right != NULL) //go to right AFAP
			{
				parent = temp;
				temp = temp->right;
			}
			del->item = temp->item;//copy temp's data into del
			parent->right = NULL; //delete temp
			return true;
			}
		}
			
	}
	else{
		cout<<"\nNo such node\n";
		return false;
	}
		
}

bool is_leaf_node(node* target)
{
	return (target->left == NULL && target->right == NULL);
}
	



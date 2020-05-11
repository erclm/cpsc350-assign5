#include "TreeNode.h"
#include <cstddef>
#include <iostream>
#include <fstream>
template <typename T>
class BST{
	public:
		BST();
		virtual ~BST();
		void insert(T value);
		bool contains(T value);
		bool deleteNode(T value);
		bool deleteRec(T k);
		bool isEmpty();
		T search(T value);
		void printTree();
		void recPrint(TreeNode<T> *node);
		TreeNode<T>* getSucc(TreeNode<T> *d);
		void treeToFile(ofstream& file);
		void treeToFile(TreeNode<T>* root, ofstream& file);

	private:
		TreeNode<T> *root;
};

template <typename T>
BST<T>::BST()
{
	root = NULL;
}

template <typename T>
BST<T>::~BST()
{
	while (root !=NULL)
	{
		deleteRec(root->key);
	}
}

template <typename T>
void BST<T>::printTree()
{
	recPrint(root);
}

template <typename T>
bool BST<T>::isEmpty()
{
	return (root == NULL);
}

template <typename T>
void BST<T>::recPrint(TreeNode<T> *node)
{
	if (node == NULL)
		return;
	recPrint(node->left);
	cout << node->key <<endl;

	recPrint(node->right);
	//cout << node->key <<endl;
}

template <typename T>
void BST<T>::insert(T value)
{
	//check for dup
	TreeNode<T> *node = new TreeNode<T>(value);

	if(isEmpty())
	{
		root=node;
	}
	else
	{
		TreeNode<T>* current = root;
		TreeNode<T>* parent;
		while (true)
		{
			parent = current;

			if (value < current->key)
			{
				current = current->left;
				if (current ==NULL)
				{
					parent->left=node;
					break;
				}
			}
			else
			{
				current = current->right;
				if (current ==NULL)
				{
					parent->right=node;
					break;
				}
			}
		}
	}
}

template <typename T>
bool BST<T>::contains(T value)
{
	if (root == NULL)
		return false;
	else
	{
		TreeNode<T> *current = root;
		while(current->key != value)
		{
			if (current == NULL)
				return false;
			if (value < current->key)
				current = current->left;
			else
				current = current->right;
		}
		return true;
	}
}

template <typename T>
T BST<T>::search(T value)
{
	TreeNode<T> *current = root;
	while(current->key != value)
	{
		if (value < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return current->key;
}

template <typename T>
bool BST<T>::deleteRec(T k)
{
	if (!contains(k))
	 	return false;

	TreeNode<T>* current = root;
	TreeNode<T>* parent = root;
	bool isLeft = true;

	while(current->key!=k)
	{
		parent = current;
		if (k < current->key)
		{
			isLeft = true;
			current = current->left;
		}
		else
		{
			isLeft = false;
			current = current->right;
		}
	}
	if (current->left ==NULL && current->right==NULL)
	{
		if (current ==root)
			root = NULL;
		else if (isLeft)
			parent->left =NULL;
		else
			parent->right =NULL;
	}
	else if (current->right==NULL)
	{
		if (current ==root)
			root = current->left;
		else if(isLeft)
			parent->left = current->left;
		else
			parent->right = current->right;
	}
	else if (current->left==NULL)
	{
		if (current ==root)
			root = current->right;
		else if(isLeft)
			parent->right = current->right;
		else
			parent->left = current->left;
	}
	else
	{
		TreeNode<T>* succ = getSucc(current);

		if (current ==root)
			root = succ;
		else if(isLeft)
			parent->left = succ;
		else
			parent->right = succ;

		succ->left = current->left;
		return true;
	}
}

template <typename T>
TreeNode<T>* BST<T>::getSucc(TreeNode<T>* d)
{
	TreeNode<T>* sp = d;
	TreeNode<T>* succ = d;
	TreeNode<T>* current = d->right;

	while(current!=NULL)
	{
		sp = succ;
		succ = current;
		current = current->left;
	}

	if (succ!=d->right)
	{
		sp->left = succ->right;
		succ->right = d->right;
	}

	return succ;
}

template <typename T>
void BST<T>::treeToFile(ofstream& file)
{
    return treeToFile(root, file);
}

template <typename T>
void BST<T>::treeToFile(TreeNode<T>* root, ofstream& file)
{
    if (root == NULL) {
        file << "#" << endl;
        return;
    }
    file << root->key << endl;
    treeToFile(root->left, file);
    treeToFile(root->right, file);
}

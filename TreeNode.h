#include <cstddef>
using namespace std;

template <typename T>
class TreeNode
{
	public:
		TreeNode();
		TreeNode(T k);
		virtual ~TreeNode();

		T key;
		TreeNode *left;
		TreeNode *right;
};

template <typename T>
TreeNode<T>::TreeNode()
{
	left = NULL;
	right = NULL;
}


template <typename T>
TreeNode<T>::~TreeNode()
{
	delete left;
	delete right;
}


template <typename T>
TreeNode<T>::TreeNode(T k)
{
	key = k;
	left = NULL;
	right = NULL;
}

#include "pch.h"
#include "AVL.h"
#include "BinaryNode.h"
#include <iostream>
#include <string>

#define max(x,y) ((x > y)? x : y)

using namespace std;

AVL::AVL()
{
	root = NULL;
}


AVL::~AVL()
{
}

// search an item in the binary search tree
BinaryNode* AVL::search(ItemType target)
{
	return search(root, target);
}

BinaryNode* AVL::search(BinaryNode* t, ItemType target)
{
	if (t == NULL)	// item not found
		return NULL;
	else
	{
		if (t->item == target)		// item found
			return t;
		else
			if (target < t->item)	// search in left subtree
				return search(t->left, target);
			else					// search in right subtree
				return search(t->right, target);
	}
}

// insert an item to the binary search tree
void AVL::insert(ItemType item)
{
	insert(root, item);
}

void AVL::insert(BinaryNode* &t, ItemType item)
{
	if (t == NULL)
	{
		BinaryNode *newNode = new BinaryNode;
		newNode->item = item;
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else if (item < t->item)
		insert(t->left, item);  // insert in left subtree
	else
		insert(t->right, item); // insert in right subtree	
	selfBalance(t);
}


// traverse the binary search tree in inorder
void AVL::inorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorder(root);
}

void AVL::inorder(BinaryNode* t)
{
	if (t != NULL)
	{
		inorder(t->left);
		cout << t->item << endl;
		inorder(t->right);
	}
}
// traverse the binary search tree in preorder
void AVL::preorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preorder(root);
}

void AVL::preorder(BinaryNode* t)
{
	if (t != NULL)
	{
		cout << t->item << endl;
		preorder(t->left);
		preorder(t->right);
	}
}

// traverse the binary search tree in postorder
void AVL::postorder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postorder(root);
}

void AVL::postorder(BinaryNode* t)
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		cout << t->item << endl;
	}
}

//Get words function based on in order traversing
void AVL::getWordsInOrder(char c)
{
	if (isEmpty())
		cout << "";
	else
		getWordsInOrder(root, c);
}
void AVL::getWordsInOrder(BinaryNode* t, char c)
{
	if (t != NULL)
	{
		getWordsInOrder(t->left, c);
		if (t->item[0] == c)
		{
			cout << t->item << endl;
		}
		getWordsInOrder(t->right, c);
	}
}


// check if the binary search tree is empty
bool AVL::isEmpty()
{
	return (root == NULL);
}

// count the number of nodes in the binary search tree
int AVL::countNodes()
{
	return countNodes(root);
}

int AVL::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// compute the height of the binary search tree
int AVL::getHeight()
{
	return getHeight(root);
}

int AVL::getHeight(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + max(getHeight(t->left), getHeight(t->right));
}

// check if the binary search tree is balanced
bool AVL::isBalanced()
{
	return isBalanced(root);
}

bool AVL::isBalanced(BinaryNode *t)
{
	if (t != NULL)
	{
		bool isBalancedNode = (abs(getHeight(t->left) - getHeight(t->right)) <= 1);
		return (isBalancedNode && isBalanced(t->left) && isBalanced(t->right));
	}
	else
		return true;
}

// delete an item from the binary search tree
void AVL::remove(ItemType target)
{
	remove(root, target);
}

void AVL::remove(BinaryNode* &t, ItemType item)
{
	if (t != NULL)
	{
		if (item < t->item)			// search in left subtree
			remove(t->left, item);
		else if (item > t->item)	// search in right subtree
			remove(t->right, item);
		else						// item == t->item (found) - base case
		{
			if (t->left == NULL && t->right == NULL) // case 1 : node has 0 child
			{
				BinaryNode* temp = t;	// to be deleted
				t = NULL;
				delete temp;			// delete the node
			}
			else if (t->left == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->right;
				else
					t = t->right;

				delete temp;			// delete the node
			}
			else if (t->right == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->left;
				else
					t = t->left;

				delete temp;			// delete the node
			}
			else // case 3 : node has 2 children
			{
				BinaryNode* successor = t->left;
				while (successor->right != NULL)	// search for right most node in left sub-tree
					successor = successor->right;

				ItemType item = successor->item;
				remove(t->left, item);				// delete the successor (either case 1 or case 2)
				t->item = item;						// replace the node�s item with that of the successor
			}
		}
		selfBalance(t);
	}
}

BinaryNode* AVL::rotateLeft(BinaryNode* t)
{
	BinaryNode* nodeC = t->right;
	t->right = nodeC->left;
	nodeC->left = t;
	return nodeC;
}

BinaryNode* AVL::rotateRight(BinaryNode* t)
{
	BinaryNode* nodeC = t->left;
	t->left = nodeC->right;
	nodeC->right = t;
	return nodeC;
}

BinaryNode* AVL::rotateLeftRight(BinaryNode* t)
{
	BinaryNode* nodeC = t->left;
	t->left = rotateLeft(nodeC);
	return rotateRight(t);
}

BinaryNode* AVL::rotateRightLeft(BinaryNode *t)
{
	BinaryNode* nodeC = t->right;
	t->right = rotateRight(nodeC);
	return rotateLeft(t);
}

void AVL::selfBalance(BinaryNode* &t)
{
	if (getHeight(t->left) - getHeight(t->right) >= 2) //If the tree is left heavy
	{
		if (getHeight(t->left->right) - getHeight(t->left->left) < 2) //If the tree's left subtree is NOT right heavy
			t = rotateRight(t);
		else // The tree's left subtree is right heavy
			t = rotateLeftRight(t);
	}
	if (getHeight(t->right) - getHeight(t->left) >= 2) //If the tree is right heavy
	{
		if (getHeight(t->right->left) - getHeight(t->right->left) < 2) //If the tree's right subtree is NOT left heavy
			t = rotateLeft(t); //Perform Left rotation
		else //The tree's right subtree is left heavy
			t = rotateRightLeft(t);
	}
}

void AVL::checkSubstitutionError(ItemType target)
{
	if (isEmpty())
		cout << "The dictionary is empty." << endl;
	else
		checkSubstitutionError(root, target);
}

void AVL::checkSubstitutionError(BinaryNode* t, ItemType target)
{
	if (t != NULL)
	{
		checkSubstitutionError(t->left, target);
		if (t->item.size() == target.size())
			if (isSubstitutionError(t->item, target))
			{
				cout << "\nThe entered word has a substitution error." << endl <<"Did you meant to find '"<< t->item <<"'?"<< endl << endl;
			}
		checkSubstitutionError(t->right, target);
	}
}

bool AVL::isSubstitutionError(string possibleWord, string userWord)
{
	int i;
	for (i = 0; i < possibleWord.size(); i++)
	{
		if (possibleWord[i] != userWord[i])
		{
			break;
		}
	}
	if (possibleWord.substr(i + 1) == userWord.substr(i + 1))
		return true;
	else
		return false;
}




//Dominic Ng Jun Yao, S10177858H
//Kevin Toh Zheng Ying, S10179142B

#include "pch.h"
#include "AVL.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define max(x,y) ((x > y)? x : y);

// constructor
AVL::AVL()
{
	root = NULL;
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
		if (t->item == target)	// item found
			return t;
		else if (target < t->item)	// search in left subtree
			return search(t->left, target);
		else // search in right subtree
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
	else
		if (item < t->item)
			insert(t->left, item);  // insert in left subtree
		else
			insert(t->right, item); // insert in right subtree
	t = balance(t);
}

// check if the binary search tree is empty
bool AVL::isEmpty()
{
	return (root == NULL); //theres no root in the first place. no root, no tree
}

int AVL::getHeight() {
	return getHeight(root);
}

int AVL::getHeight(BinaryNode* t) {
	if (t == NULL)
		return 0;
	else
	{
		int leftHeight = getHeight(t->left);
		int rightHeight = getHeight(t->right);
		return 1 + max(leftHeight, rightHeight);
	}
}

//Get words function based on in order traversing
void AVL::getWordsInOrder(string s, bool &found)
{
	if (isEmpty())
		cout << "";
	else
		getWordsInOrder(root, s, found);
}

void AVL::getWordsInOrder(BinaryNode* t, string s, bool &found)
{
	if (t != NULL)
	{
		getWordsInOrder(t->left, s, found);
		if (t->item.substr(0,s.length()) == s)
		{
			cout << t->item << endl;
			found = true;
		}
		getWordsInOrder(t->right, s, found);
	}
}

void AVL::saveFile(ofstream& dict)
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		saveFile(root, dict);
}

void AVL::saveFile(BinaryNode* t, ofstream& dict)
{
	if (t != NULL)
	{
		saveFile(t->left, dict);
		dict << t->item << endl;
		saveFile(t->right, dict);
	}
}

void AVL::checkSubstitutionError(ItemType target, bool &found, bool &subError)
{
	if (isEmpty())
		cout << "The dictionary is empty." << endl;
	else
		checkSubstitutionError(root, target, found, subError);
}

void AVL::checkSubstitutionError(BinaryNode* t, ItemType target, bool &found, bool &subError)
{
	if (t != NULL)
	{
		if (target == t->item)
		{
			found = true;
		}
		else
		{
			checkSubstitutionError(t->left, target, found, subError);
			if (t->item.size() == target.size())
				if (isSubstitutionError(t->item, target) && !found)
				{
					subError = true;
				}
			checkSubstitutionError(t->right, target, found, subError);
		}
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


int AVL::compareHeight(BinaryNode *t)
{
	int left = getHeight(t->left);
	int right = getHeight(t->right);
	return left - right;
}

BinaryNode *AVL::rotateLeft(BinaryNode *t)
{
	BinaryNode *nodeC = t->right;
	t->right = nodeC->left;
	nodeC->left = t;
	return nodeC;
}

BinaryNode *AVL::rotateRight(BinaryNode *t)
{
	BinaryNode *nodeC = t->left;
	t->left = nodeC->right;
	nodeC->right = t;
	return nodeC;
}

BinaryNode *AVL::rotateLeftRight(BinaryNode *t)
{
	BinaryNode *nodeC = t->left;
	t->left = rotateLeft(nodeC);
	return rotateRight(t);
}

BinaryNode *AVL::rotateRightLeft(BinaryNode *t)
{
	BinaryNode *nodeC = t->right;
	t->right = rotateRight(nodeC);
	return rotateLeft(t);
}

BinaryNode *AVL::balance(BinaryNode *t)
{
	int subtractresult = compareHeight(t);
	if (subtractresult > 1) 
	{
		if (compareHeight(t->left) > 0) 
			t = rotateRight(t);
		else
			t = rotateLeftRight(t);
	}
	else if (subtractresult < -1) 
	{
		if (compareHeight(t->right) > 0)
			t = rotateRightLeft(t);
		else
			t = rotateLeft(t); 
	}
	return t;
}
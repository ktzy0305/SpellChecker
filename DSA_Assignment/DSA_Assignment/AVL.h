#pragma once
#include "BinaryNode.h"

class AVL
{
private:
	BinaryNode* root;		// root of the BST

public:
	AVL();
	~AVL();

	// search an item in the binary search tree
	BinaryNode* search(ItemType target);
	BinaryNode* search(BinaryNode* root, ItemType target);

	// insert an item to the binary search tree
	void insert(ItemType item);
	void insert(BinaryNode* &root, ItemType item);

	// delete an item from the binary search tree
	void remove(ItemType target);
	void remove(BinaryNode* &root, ItemType target);

	// traverse the binary search tree in inorder
	void inorder();
	void inorder(BinaryNode* t);

	// traverse the binary search tree in preorder
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the binary search tree in postorder
	void postorder();
	void postorder(BinaryNode* t);

	// check if the binary search tree is empty
	bool isEmpty();

	// count the number of nodes in the binary search tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// compute the height of the binary search tree
	int getHeight();
	int getHeight(BinaryNode* t);

	// check if the binary search tree is balanced
	bool isBalanced();
	bool isBalanced(BinaryNode *t);

	// single rotations
	BinaryNode* rotateLeft(BinaryNode* t);
	BinaryNode* rotateRight(BinaryNode* t);

	// double rotations
	BinaryNode* rotateLeftRight(BinaryNode* t);
	BinaryNode* rotateRightLeft(BinaryNode* t);

	// auto balancing
	void selfBalance(BinaryNode* &t);

	// get words in order
	void getWordsInOrder(char c);
	void getWordsInOrder(BinaryNode* t, char c);

	// check substitution error
	void checkSubstitutionError(ItemType target, bool &found, bool &subError);
	void checkSubstitutionError(BinaryNode* t, ItemType target, bool &found, bool &subError);
	bool isSubstitutionError(string possibleWord, string userWord);

};






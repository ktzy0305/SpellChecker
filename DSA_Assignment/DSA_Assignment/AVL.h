//Dominic Ng Jun Yao, S10177858H
//Kevin Toh Zheng Ying, S10179142B
#pragma once
#include "BinaryNode.h"

class AVL
{
private:
	BinaryNode * root;		// root of the BST
public:

	// constructor
	AVL();

	// search an item in the binary search tree
	BinaryNode* search(ItemType target);
	BinaryNode* search(BinaryNode* root, ItemType target);

	// insert an item to the binary search tree
	void insert(ItemType item);
	void insert(BinaryNode* &root, ItemType item);

	// check if the binary search tree is empty
	bool isEmpty();

	// compute the height of the binary search tree
	int getHeight();
	int getHeight(BinaryNode* t);

	int compareHeight(BinaryNode *t);
	BinaryNode *rotateLeft(BinaryNode *t);
	BinaryNode *rotateRight(BinaryNode *t);
	BinaryNode *rotateLeftRight(BinaryNode *t);
	BinaryNode *rotateRightLeft(BinaryNode *t);
	BinaryNode* balance(BinaryNode *t);

	// get words in order
	void getWordsInOrder(string s, bool& found);
	void getWordsInOrder(BinaryNode* t, string s, bool &found);

	void saveFile(ofstream& dict);
	void saveFile(BinaryNode* t, ofstream& dict);

	// check substitution error
	void checkSubstitutionError(ItemType target, bool &found, bool &subError);
	void checkSubstitutionError(BinaryNode* t, ItemType target, bool &found, bool &subError);
	bool isSubstitutionError(string possibleWord, string userWord);
};
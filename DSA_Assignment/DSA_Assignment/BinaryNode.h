//Dominic Ng Jun Yao, S10177858H
//Kevin Toh Zheng Ying, S10179142B

#pragma once
#include <string>

using namespace std;

typedef string ItemType;

struct BinaryNode
{
	ItemType   item;	// data item
	BinaryNode *left;	// pointer pointing to left subtree
	BinaryNode *right;	// pointer pointing to right subtree
};

#ifndef BSTNODE_H_
#define BSTNODE_H_

#include <iostream>

/**
 * 
 * @author Amir
 * @version 2013
 * 
 */

using namespace std;

class BSTNode
{
public:
	BSTNode *right;
	BSTNode *left;
	string value;

	BSTNode(string str)
	{
		right = NULL;
		left = NULL;
		value = str;
	}
};
#endif
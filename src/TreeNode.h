#ifndef TREENODE_H_
#define TREENODE_H_

#include <iostream>

/**
 * 
 * @author Amir
 * @version 2013
 * 
 */

using namespace std;

class TreeNode
{

public:
	TreeNode *right;
	TreeNode *left;
	TreeNode *up;
	TreeNode *down;
	TreeNode *father;
	TreeNode *QLink;
	string value;
	int distance;

	TreeNode(string str)
	{
		right = NULL;
		left = NULL;
		up = NULL;
		down = NULL;
		father = NULL;
		QLink = NULL;
		value = str;
		distance = 0;
	}
};
#endif
#ifndef BST_H_
#define BST_H_

#include <iostream>
#include "BSTNode.h"

/**
 * 
 * @author Amir
 * @version 2013
 * 
 */

using namespace std;

class BST
{
public:
	BSTNode *Root;

	BST(BSTNode *root)
	{
		Root = root;
	}

	bool AddToTree(string str)
	{
		BSTNode *p = Root;
		BSTNode *q = NULL;
		while (p)
		{
			q = p;
			if (str == p->value)
				return false;
			if (atoi(str.c_str()) < atoi(p->value.c_str()))
				p = p->left;
			else
				p = p->right;
		}
		p = new BSTNode(" ");
		p->value = str;
		if (!Root)
			Root = p;
		else
		{
			if (atoi(q->value.c_str()) < atoi(p->value.c_str()))
				q->right = p;
			else
				q->left = p;
		}
		return true;
	}

	int noLevel(BSTNode *p)
	{
		if (!p)
			return 0;
		int noRight = noLevel(p->right);
		int noLeft = noLevel(p->left);
		return (1 + max(noRight, noLeft));
	}
};
#endif
#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include "TreeNode.h"

/**
 * 
 * @author Amir
 * @version 2013
 * 
 */

class Queue
{
public:
	int max;
	TreeNode *front;
	TreeNode *rear;

	Queue()
	{
		// max = 150000;
		rear = NULL;
		front = rear;
	}

	void push(TreeNode *p)
	{
		if (rear)
		{
			rear->QLink = p;
			rear = rear->QLink;
		}
		else
		{
			front = p;
			rear = p;
		}
	}

	TreeNode *pick()
	{
		// TreeNode *q = front;
		if (front)
		{
			TreeNode *p = front;
			front = front->QLink;
			return p;
		}
		// delete p;
		return NULL;
	}
};
#endif
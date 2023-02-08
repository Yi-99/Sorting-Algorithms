/***********************************************************************
* Component:
*    Assignment 09, Binary Search Tree (BST)
*    Brother Kirby, CS 235
* Author:
*   Yirang Lim, Yeju Sthapit, Shih Chen Lee
* Summary:
*    Create a ADT type Binary Search Tree
************************************************************************/

#ifndef BST_H
#define BST_H

namespace custom
{
/**************************************************
* Binary Search Tree
* An ADT
***************************************************/
template <class T>
class BST
{
public:
	BST();               // default constructor
	BST(const BST<T>& rhs); // copy constructor
	~BST();              // destructor

	// nested classes
	class iterator;
	iterator find(const T& t);
	iterator begin() const;
	iterator end() const;
	iterator rbegin();
	iterator rend();

	class BNode;

	// standard ADT interfaces
	BST<T> & operator = (const BST<T>& rhs); // assignment operator
	int size() const;
	bool empty() const;
	void clear();

	void insert(const T& t);
	void erase(iterator& it);

	// helpful functions for insert
	void rotateRight(BNode* pNode, int num);
	void rotateLeft(BNode* pNode, int num);

	// getter
	BNode* getRoot() const { return root; }
	BNode* getSibling(BNode* pNode);

private:
	BNode* root;
	int numEle;

	void deleteNode(BNode* pDelete, bool right);
	void deleteBinaryTree(BNode*& pDelete);
	void copyBinaryTree(BNode* pSrc, BNode*& pDestination);
};

/**************************************************************************
* BST()
* Default Constructor
**************************************************************************/
template <class T>
BST<T>::BST()
{
	root = NULL;
	numEle = 0;
}

/**************************************************************************
* BST()
* Copy Constructor
**************************************************************************/
template <class T>
BST<T>::BST(const BST<T>& rhs)
{
	root = rhs.root;
	numEle = rhs.numEle;

	copyBinaryTree(rhs.root, this->root);
}

/**************************************************************************
* ~BST()
* Destructor
**************************************************************************/
template <class T>
BST<T>::~BST()
{
	clear();
}

/**************************************************************************
* Assignment Operator =
**************************************************************************/
template <class T>
BST<T>& BST<T>::operator = (const BST<T>& rhs)
{
	clear();

	//for (BST<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
	//{
	//	insert(*it);
	//}

	numEle = rhs.numEle;

	copyBinaryTree(rhs.root, this->root);

	return *this;
}

/**************************************************************************
* EMPTY()
* Informs the client if the BST is empty
**************************************************************************/
template <class T>
bool BST<T>::empty() const
{
	if (root == NULL)
		return true;
	else
		return false;
}

/**************************************************************************
* SIZE()
* Returns the size of the BST
**************************************************************************/
template <class T>
int BST<T>::size() const
{
	if (root == NULL)
		return 0;
	else
		return numEle;
}

/**************************************************************************
* CLEAR()
* Removes the values within the BST
**************************************************************************/
template<class T>
void BST<T>::clear()
{
	numEle = 0;

	BNode* pTemp = root;
	deleteBinaryTree(pTemp);
	pTemp = NULL;

	root = pTemp;
}

/**************************************************************************
* INSERT()
* Insert a new Binary Node with the value t
**************************************************************************/
template <class T>
void BST<T>::insert(const T& t)
{
	BNode* pNew = new BNode(t);
	BNode* pNode = root;

	if (pNode == NULL)
	{
		root = pNew;
		root->isRed = false; // set the root to black
	}
	else
	{
		while (pNode->pRight != NULL || pNode->pLeft != NULL) // search
		{
			if (t < pNode->data)
			{
				if (pNode->pLeft == NULL)
					break;
				pNode = pNode->pLeft;
			}
			else
			{
				if (pNode->pRight == NULL)
					break;
				pNode = pNode->pRight;
			}
		}
		// set pNew to the proper location to insert BNode
		pNew->pParent = pNode;

		if (pNew->data <= pNode->data)
		{
			pNode->pLeft = pNew;
		}
		else
		{
			pNode->pRight = pNew;
		}

		pNew->pLeft = NULL;
		pNew->pRight = NULL;

		// Recolor
		if (root != NULL)
		{
			BNode* pAunt = pNew->getAunt(pNew);

			if (root->isRed == true) // case 1: check if the root is black
			{
				root->isRed = false;
			}
			else if (pNew->pParent != NULL && pNew->pParent->isRed == false) // case 2: check if the parents are black
			{
				// could insert case 3 and 4 in this if statement
			}
			// case 3: Parent and aunt are red (triangle on the right side of the root)
			else if (pNew->pParent->isRed == true && pAunt != NULL && pAunt->isRed == true && pNew->data > pNew->pParent->data)
			{
				BNode* pGrand = pNew->pParent->pParent; // pGrandParent
				pGrand->isRed = true;
				pNew->pParent->isRed = false; // turn parent to black
				pAunt->isRed = false; // turn aunt to black
				if (root->isRed == true)
					root->isRed = false;
			}
			// case 3: Parent and aunt are red (line and triangle on the left side of the root)
			else if (pNew->pParent->isRed == true && pAunt != NULL && pAunt->isRed == true && pNew->data <= pNew->pParent->data)
			{
				BNode* pGrand = pNew->pParent->pParent; // pGrandParent
				pGrand->isRed = true;
				pNew->pParent->isRed = false; // turn parent to black
				pAunt->isRed = false; // turn aunt to black
				if (root->isRed == true)
					root->isRed = false;
			}
			else if (pAunt == NULL) // case 4: parent is red and aunt is black or null
			{
				// line case
				if (pNew->pParent->pRight == pNew && pNew->pParent->pParent->pRight == pNew->pParent) // check if pNew is on the right side and pNew's parent is on the right side of pGrand
					rotateLeft(pNew, 1);
				else if (pNew->pParent->pLeft == pNew && pNew->pParent->pParent->pLeft == pNew->pParent) // check if pNew is on the left side
					rotateRight(pNew, 1);

				else if (pNew->pParent->pLeft == pNew && pNew->data < pNew->pParent->data) // check if pNew is under directly underneath pGrand connected from the right side of pGrand
					rotateLeft(pNew, 2);
				else if (pNew->pParent->pRight == pNew && pNew->data > pNew->pParent->data) // check if pNew is directly under from the left side of pGrand
					rotateRight(pNew, 2);
			}
			else if (pAunt->isRed == false) // case 4 (textbook)
			{
				// line case
				if (pNew->pParent->pRight == pNew && pNew->pParent->pParent->pRight == pNew->pParent) // check if pNew is on the right side and pNew's parent is on the right side of pGrand
					rotateLeft(pNew, 1);
				else if (pNew->pParent->pLeft == pNew && pNew->pParent->pParent->pLeft == pNew->pParent) // check if pNew is on the left side
					rotateRight(pNew, 1);

				else if (pNew->pParent->pLeft == pNew && pNew->data < pNew->pParent->data) // check if pNew is under directly underneath pGrand connected from the right side of pGrand
					rotateLeft(pNew, 2);
				else if (pNew->pParent->pRight == pNew && pNew->data > pNew->pParent->data) // check if pNew is directly under from the left side of pGrand
					rotateRight(pNew, 2);
			}
		}
	}
	numEle++;
}

/**************************************************************************
* ROTATERIGHT()
* rotate the tree to the right
**************************************************************************/
template <class T>
void BST<T>::rotateRight(BNode* pNode, int num)
{
	BNode* pParent = NULL;
	BNode* pGrand = NULL;

	if (pNode->pParent != NULL)
	{
		pParent = pNode->pParent;
		pGrand = pNode->pParent->pParent;
	}

	switch (num)
	{
	case 1: // case4.a&b
		if (pGrand != NULL) // check if pGrand has a parent node
		{
			pParent->pParent = pGrand->pParent;
			pGrand->pParent = pParent;

			if (pParent->pRight != NULL)
			{
				pGrand->pLeft = pParent->pRight;
				pGrand->pLeft->pParent = pGrand;
			}
			else
				pGrand->pLeft = NULL;
		}

		pParent->pRight = pGrand;
		pParent->isRed = false;
		pGrand->isRed = true;

		if (pParent->pParent == NULL)
			root = pParent;
		else // connect pGrand's parent node to new parent node
		{
			if (pParent->pParent->pRight == pParent)
				pParent->pParent->pRight = pParent;
			else
				pParent->pParent->pLeft = pParent;
		}
		break;
	case 2: // case 4.c&d when pNode has no children nodes
		// move pNode to the top
		if (pGrand->pParent != NULL) // check if pGrand's parent exists
			pNode->pParent = pGrand->pParent;
		else
			pNode->pParent = NULL;
		
		// clear up connection of parent and grand node to its child node
		pParent->pRight = NULL;
		pGrand->pLeft = NULL;

		pNode->pLeft = pParent;
		pNode->pRight = pGrand;
		pGrand->pParent = pNode;
		pParent->pParent = pNode;
		pNode->pParent->pRight = pNode;
		//change color of the moved nodes
		pNode->isRed = false;
		pGrand->isRed = true;
		break;
	}
}

/**************************************************************************
* ROTATELEFT()
* rotate the tree to the left
**************************************************************************/
template <class T>
void BST<T>::rotateLeft(BNode* pNode, int num)
{
	BNode* pParent = NULL;
	BNode* pGrand = NULL;

	if (pNode->pParent != NULL)
	{
		pParent = pNode->pParent;
		pGrand = pNode->pParent->pParent;
	}

	switch (num)
	{
	case 1:
		if (pGrand != NULL)
		{
			pParent->pParent = pGrand->pParent;
			if (pParent->pParent == NULL)
				root = pParent;
			else // connect pGrand's parent node to new parent node
			{
				if (pParent->pParent->pRight == pGrand)
					pParent->pParent->pRight = pParent;
				else
					pParent->pParent->pLeft = pParent;
			}
			pGrand->pParent = pParent;
			if (pParent->pLeft != NULL)
			{
				pGrand->pRight = pParent->pLeft;
				pGrand->pRight->pParent = pGrand;
			}
			else
				pGrand->pRight = NULL;

			pParent->pLeft = pGrand;
			pParent->isRed = false;
			pGrand->isRed = true;

			break;
		}
	case 2:
		if (pGrand != NULL) // check if pGrand's parent exists
			pNode->pParent = pGrand->pParent;
		else
			pNode->pParent = NULL;

		// clear up connection of parent and grand node to its child node
		pParent->pLeft = NULL;
		pGrand->pRight = NULL;

		pNode->pLeft = pGrand;
		pNode->pRight = pParent;
		pGrand->pParent = pNode;
		pParent->pParent = pNode;
		pNode->pParent->pLeft = pNode;
		//change color
		pNode->isRed = false;
		pGrand->isRed = true;
		break;
	}
}

/**************************************************************************
* ERASE()
* remove a specific node from the binary search tree
**************************************************************************/
template<class T>
void BST<T>::erase(iterator& it)
{

}

/************************************************************
* BNODE
* A class in a data structure
*************************************************************/
template <class T>
class BST<T>::BNode
{
public:
	BNode();
	BNode(const T& t);

	BNode* getAunt(BNode* pNode);

	T data;
	BNode* pLeft;
	BNode* pRight;
	BNode* pParent;
	bool isRed;
private:
	BNode* verifyRB();
	BNode* verifyBST();
	BNode* balance();
};

/************************************************************
* BNODE()
* Default Constructor
*************************************************************/
template <class T>
BST<T>::BNode::BNode()
{
	pLeft = NULL;
	pRight = NULL;
	pParent = NULL;
	data = NULL;
	isRed = true;
}

/************************************************************
* BNODE()
* Non-default Constructor
*************************************************************/
template <class T>
BST<T>::BNode::BNode(const T& t)
{
	pLeft = NULL;
	pRight = NULL;
	pParent = NULL;
	data = t;
	isRed = true;
}

template <class T>
typename BST<T>::BNode* BST<T>::BNode::getAunt(BNode* pNode)
{
	BNode* pAunt = NULL;

	if (pNode->pParent->pParent == NULL)
	{
		return pAunt;
	}
	else
	{
		if (pNode->pParent->pParent->pLeft == pNode->pParent)
		{
			BNode* pAunt(pNode->pParent->pParent->pRight);
			return pAunt;
		}
		else if (pNode->pParent->pParent->pRight == pNode->pParent)
		{
			BNode* pAunt(pNode->pParent->pParent->pLeft);
			return pAunt;
		}

		return pAunt;
	}
}

/************************************************************
* DELETENODE()
* Delete a node in the binary search tree
*************************************************************/
template<class T>
void BST<T>::deleteNode(BNode* pDelete, bool right)
{

}

/************************************************************
* DELETEBINARYTREE()
* Delete the entire Binary Search Tree
*************************************************************/
template<class T>
void BST<T>::deleteBinaryTree(BNode*& pDelete)
{
	if (pDelete != NULL)
	{
		if (pDelete->pLeft == NULL && pDelete->pRight == NULL)
		{
			delete pDelete;
			pDelete = NULL;
		}
		else
		{
			deleteBinaryTree(pDelete->pLeft);
			deleteBinaryTree(pDelete->pRight);
		}
	}

	//if (pDelete == NULL)
	//	return;

	//deleteBinaryTree(pDelete->pLeft);
	//deleteBinaryTree(pDelete->pRight);
	//delete pDelete;

	//pDelete = NULL;
}

/************************************************************
* COPYBINARYTREE()
* Copy the entire Binary Search Tree
*************************************************************/
template<class T>
void BST<T>::copyBinaryTree(BNode* pSrc, BNode*& pDestination)
{
	if (pSrc == NULL)
		return;

	if (pDestination != NULL)
		pDestination->data = pSrc->data;
	else
		pDestination = new BST<T>::BNode(pSrc->data);

	// copy the color
	pDestination->isRed = pSrc->isRed;

	copyBinaryTree(pSrc->pLeft, pDestination->pLeft);
	if (pDestination->pLeft != NULL)
	{
		pDestination->pLeft->pParent = pDestination;
	}

	copyBinaryTree(pSrc->pRight, pDestination->pRight);
	if (pDestination->pRight != NULL)
	{
		pDestination->pRight->pParent = pDestination;
	}
}

/**************************************************
* BST ITERATOR
* An iterator through array
*************************************************/
template <class T>
class BST<T>::iterator
{
public:
	// constructors, destructors, and assignment operator
	iterator() : pNode(NULL) {              }
	iterator(BNode* pNode) : pNode(pNode) {              }
	iterator(const iterator& rhs) { *this = rhs; }
	iterator& operator = (const iterator& rhs)
	{
		this->pNode = rhs.pNode;
		return *this;
	}

	// equals, not equals operator
	bool operator != (const iterator& rhs) const { return rhs.pNode != this->pNode; }
	bool operator == (const iterator& rhs) const { return rhs.pNode == this->pNode; }

	// dereference operator
	T& operator * () { return pNode->data; }
	const T& operator * () const { return pNode->data; }

	// advance
	BST<T>::iterator& operator ++ ();

	// retreat
	BST<T>::iterator& operator--();

	// postfix increment
	iterator operator ++ (int postfix);

	// postfix decrement
	iterator operator -- (int postifix);
private:
	BNode* pNode;
};

template <class T>
typename BST<T>::iterator BST<T>::begin() const
{
	BNode* pNode = root;

	if (pNode != NULL)
	{
		while (pNode->pLeft != NULL)
		{
			pNode = pNode->pLeft;
		}
		return iterator(pNode);
	}
	else
		return iterator(NULL);
}

template <class T>
typename BST<T>::iterator BST<T>::end() const
{
	return iterator(NULL);
}

/**************************************************
* BST ITERATOR :: INCREMENT PREFIX
*     advance by one.
*************************************************/
template <class T>
typename BST<T>::iterator& BST<T>::iterator :: operator ++()
{
	// do nothing if we have nothing
	if (pNode == NULL)
		return *this;

	// if there is a right child node
	if (pNode->pRight != NULL)
	{
		pNode = pNode->pRight;
		while (pNode->pLeft != NULL)
		{
			pNode = pNode->pLeft;
		}

		return *this;
	}

	// if the parent is the root
	if (pNode->pParent == NULL)
	{
		pNode = pNode->pParent;
		return *this;
	}

	// if there is no right child node and parent's left child
	if (pNode->pRight == NULL && pNode->pParent->pLeft == pNode)
	{
		pNode = pNode->pParent;
		return *this;
	}

	// if there is no right child node and parent's right child
	if (pNode->pRight == NULL && pNode->pParent->pRight == pNode)
	{
		while (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
		{
			pNode = pNode->pParent;
		}

		pNode = pNode->pParent;
		return *this;
	}

	return *this;
}

/**************************************************
	* BST ITERATOR :: DECREMENT PREFIX
	*     advance by one.
	* Author:      Br. Helfrich
	* Performance: O(log n) though O(1) in the common case
	*************************************************/
template <class T>
typename BST <T> ::iterator& BST <T> ::iterator :: operator -- ()
{
	// do nothing if we have nothing
	if (NULL == pNode)
		return *this;

	// if there is a left node, take it
	if (NULL != pNode->pLeft)
	{
		// go left
		pNode = pNode->pLeft;

		// jig right - there might be more right-most children
		while (pNode->pRight)
			pNode = pNode->pRight;
		return *this;
	}

	// there are no left children, the right are done
	assert(NULL == pNode->pLeft);
	BNode* pSave = pNode;

	// go up
	pNode = pNode->pParent;

	// if the parent is the NULL, we are done!
	if (NULL == pNode)
		return *this;

	// if we are the right-child, go to the parent.
	if (pSave == pNode->pRight)
		return *this;

	// we are the left-child, go up as long as we are the left child!
	while (NULL != pNode && pSave == pNode->pLeft)
	{
		pSave = pNode;
		pNode = pNode->pParent;
	}

	return *this;
}

/**************************************************
* BST ITERATOR :: FIND
*************************************************/
template <class T>
typename BST<T>::iterator BST<T>::find(const T& t)
{
	for (BST<T>::iterator it = begin(); it != end(); ++it)
	{
		if (*it == t)
		{
			return it;
		}
	}

	return end();
}

template <class T>
typename BST<T>::iterator BST<T>::rbegin()
{
	BNode* pNode = root;
	while (pNode->pRight != NULL)
	{
		pNode = pNode->pRight;
	}
	return iterator(pNode);
}

template <class T>
typename BST<T>::iterator BST<T>::rend()
{
	return iterator(NULL);
}

/**************************************************
* BST ITERATOR :: INCREMENT POSTFIX
*************************************************/
template <class T>
typename BST<T>::iterator BST<T>::iterator::operator ++ (int postfix)
{
	// do nothing if we have nothing
	if (pNode == NULL)
		return *this;

	// if there is a right child node
	if (pNode->pRight != NULL)
	{
		pNode = pNode->pRight;
		while (pNode->pLeft != NULL)
		{
			pNode = pNode->pLeft;
		}

		return *this;
	}

	// if the parent is the root
	if (pNode->pParent == NULL)
	{
		pNode = pNode->pParent;
		return *this;
	}

	// if there is no right child node and parent's left child
	if (pNode->pRight == NULL && pNode->pParent->pLeft == pNode)
	{
		pNode = pNode->pParent;
		return *this;
	}

	// if there is no right child node and parent's right child
	if (pNode->pRight == NULL && pNode->pParent->pRight == pNode)
	{
		while (pNode->pParent != NULL && pNode->pParent->pRight == pNode)
		{
			pNode = pNode->pParent;
		}

		pNode = pNode->pParent;
		return *this;
	}

	return *this;
}

/**************************************************
* BST ITERATOR :: DECREMENT POSTFIX
*************************************************/
template <class T>
typename BST<T>::iterator BST<T>::iterator::operator -- (int postfix)
{
	// do nothing if we have nothing
	if (NULL == pNode)
		return *this;

	// if there is a left node, take it
	if (NULL != pNode->pLeft)
	{
		// go left
		pNode = pNode->pLeft;

		// jig right - there might be more right-most children
		while (pNode->pRight)
			pNode = pNode->pRight;
		return *this;
	}

	// there are no left children, the right are done
	assert(NULL == pNode->pLeft);
	BNode* pSave = pNode;

	// go up
	pNode = pNode->pParent;

	// if the parent is the NULL, we are done!
	if (NULL == pNode)
		return *this;

	// if we are the right-child, go to the parent.
	if (pSave == pNode->pRight)
		return *this;

	// we are the left-child, go up as long as we are the left child!
	while (NULL != pNode && pSave == pNode->pLeft)
	{
		pSave = pNode;
		pNode = pNode->pParent;
	}

	return *this;
}

} // namespace custom

#endif // BST_H
/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
	//Default constructor makes an empty node
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while (!IsEmpty())
	{
		//Deletes the root (Which will assign the root to something else) until the tree is empty.
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger ones are placed to the right.
void BinaryTree::Insert(int a_nValue)
{
	//If there's no elements then the root node is changed
	if (IsEmpty()) { m_pRoot = new TreeNode(a_nValue); return; }
	//Temp node for cycling through
	TreeNode* tmpNode = m_pRoot;
	//Looping through the binary tree to find a place for the insert
	while (tmpNode != nullptr)
	{
		//Checks if inserted value is smaller than current element
		if (a_nValue < tmpNode->GetData())
		{
			//If the next left node is empty, insert a new node for the inserted value
			if (tmpNode->GetLeft() == nullptr) { tmpNode->SetLeft(new TreeNode{ a_nValue }); break; }
			tmpNode = tmpNode->GetLeft();
		}
		else if (a_nValue > tmpNode->GetData())
		{
			//If the next right node is empty, insert a new node for the inserted value
			if (tmpNode->GetRight() == nullptr) { tmpNode->SetRight(new TreeNode{ a_nValue }); break; }
			tmpNode = tmpNode->GetRight();
		}
		else if (a_nValue == tmpNode->GetData())
		{
			break;
		}
	}
	tmpNode = nullptr;
}

//Used to just find a singular node
TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

//Finds a node & it's parent based on the search value
bool BinaryTree::FindNode(int a_nSearchValue, TreeNode* &ppOutNode, TreeNode* &ppOutParent)
{
	if (IsEmpty()) {return false; }
	TreeNode* tmpNode = m_pRoot;
	TreeNode* tmpNodeParent = nullptr;
	int count = 0;
	while (tmpNode != NULL)
	{
		if (a_nSearchValue == tmpNode->GetData())
		{
			ppOutNode = tmpNode;
			ppOutParent = tmpNodeParent;
			return true;
		}
		else
		{
			tmpNodeParent = tmpNode;
			if (a_nSearchValue < tmpNode->GetData())
			{
				tmpNode = tmpNode->GetLeft();
			}
			else
			{
				tmpNode = tmpNode->GetRight();
			}
		}
	}

	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	// If the tree is empty just return
	if (IsEmpty()) { return; } 

	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	// Find the node to remove and its parent.
	FindNode(a_nValue, pCurrent, pParent); 
	if (pCurrent->HasRight())
	{
		// If the node has a right node, replace with next smallest node.
		TreeNode* pSuccessor = pCurrent->GetRight();
		TreeNode* pParentSuccessor = pCurrent;

		while (pSuccessor->HasLeft())
		{
			pParentSuccessor = pSuccessor;
			// Find the in-order successor.
			pSuccessor = pSuccessor->GetLeft(); 
		}

		// Copy data from successor to current node.
		pCurrent->SetData(pSuccessor->GetData()); 

		if (pParentSuccessor->GetLeft() == pSuccessor)
		{
			// Updates parent's left child.
			pParentSuccessor->SetLeft(pSuccessor->GetRight()); 
		}
		else
		{
			// Updates parent's right child.
			pParentSuccessor->SetRight(pSuccessor->GetRight()); 
		}

		delete pSuccessor;
		pSuccessor = nullptr;
	}
	else
	{
		// Node to remove doesn't have a right node.
		if (pCurrent == m_pRoot)
		{
			// Update root if necessary.
			m_pRoot = pCurrent->GetLeft(); 
		}
		else if (pCurrent->GetData() < pParent->GetData())
		{
			// Update parent's left child.
			pParent->SetLeft(pCurrent->GetLeft()); 
		}
		else
		{
			// Update parent's right child.
			pParent->SetRight(pCurrent->GetLeft()); 
		}

		delete pCurrent;
	}
	pCurrent = nullptr;
	pParent = nullptr;
}


void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
    PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;
	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		pNode->Draw(x, y, (selected == pNode));
	}
}
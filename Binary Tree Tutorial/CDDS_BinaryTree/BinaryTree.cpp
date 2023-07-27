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

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

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
	if (IsEmpty()) { return; }
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	FindNode(a_nValue, pCurrent, pParent);

	if (pCurrent->HasRight())
	{
		TreeNode* TempNode = pCurrent->GetRight();
		TreeNode* ParentTempNode = pCurrent;
		int tmpcount = 0;
		while (TempNode != NULL)
		{
			if (TempNode->GetLeft() != NULL)
			{
				TempNode = TempNode->GetLeft();
				if (tmpcount == 0)
				{
					ParentTempNode = ParentTempNode->GetRight();
				}
				else { ParentTempNode = ParentTempNode->GetLeft(); }
			}
			else
			{
				pCurrent->SetData(TempNode->GetData());
				if (TempNode->GetData() < ParentTempNode->GetData())
				{
					ParentTempNode->SetLeft(TempNode->GetRight());
				}
				else 
				{ 
					ParentTempNode->SetRight(TempNode->GetRight()); 
				}
				delete TempNode;
				TempNode = NULL;
				ParentTempNode = NULL;
			}
		}
	}
	else
	{
		if (pCurrent == m_pRoot)
		{
			m_pRoot->SetLeft(pCurrent->GetLeft());
		}
		else if (pCurrent->GetData() < pParent->GetData())
		{
			pParent->SetLeft(pCurrent->GetLeft());
		}
		else if (pCurrent->GetData() > pParent->GetData())
		{
			pParent->SetRight(pCurrent->GetLeft());
		}
		delete pCurrent;
		pCurrent = NULL;
		pParent = NULL;
	}
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
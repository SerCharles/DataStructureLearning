/*
    filename: BBinaryTree.hpp
    description: a binary tree
    date: 10/23/2018
*/


#ifndef BBINARYTREE_HPP
#define BBINARYTREE_HPP

#include <iostream>

#include "BBinaryNode.hpp"

template <class Data>
class BBinaryTree
{
//pointer
public:
    BBinaryNode<Data>* m_Root{NULL};
    BBinaryTree* m_LeftSon{NULL};
    BBinaryTree* m_RightSon{NULL};
    BBinaryTree* m_Father{NULL};
    int m_Height{1};

//function of changing
public:
    //construct an empty tree
    //variable:data
    BBinaryTree(Data x)
    {
        m_Root = new BBinaryNode<Data>(x);
    }

    //destruction
    ~BBinaryTree()
    {
        if(m_LeftSon != NULL)
        {
            delete(m_LeftSon);
        }
        if(m_RightSon != NULL)
        {
            delete(m_RightSon);
        }
    }

    //function:merge trees
    //variable:the pointer of another tree, mode(0:left, 1:right)
    void m_MergeTree(BBinaryTree* new_son, const bool mode)
    {
        if(mode == 0)
        {
            new_son -> m_Father = this;
            m_LeftSon = new_son;
        }
        else
        {
            new_son -> m_Father = this;
            m_RightSon = new_son;
        }
    }


    //function: finding an element in the tree's son trees
    //return: the pointer of its subtree, no element:NULL
    BBinaryTree* m_FindNode(const BBinaryNode<Data>* target)
    {
        BBinaryTree* return_pointer = NULL;
        if(m_Root -> m_Compare(target) == 0)
        {
            return this;
        }
        if(m_LeftSon != NULL)
        {
            return_pointer = m_LeftSon -> m_FindNode(target);
            if(return_pointer != NULL)
            {
                return return_pointer;
            }
        }
        if(m_RightSon != NULL)
        {
            return_pointer = m_RightSon -> m_FindNode(target);
            if(return_pointer != NULL)
            {
                return return_pointer;
            }
        }
        return NULL;
    }

    //function:get height
    void m_GetHeight()
    {
        int h_left = 0, h_right = 0;
        if(m_LeftSon != NULL)
        {
            m_LeftSon -> m_GetHeight();
            h_left = m_LeftSon -> m_Height;
        }
        if(m_RightSon != NULL)
        {
            m_RightSon -> m_GetHeight();
            h_right = m_RightSon -> m_Height;
        }
        if(h_left > h_right)
        {
            m_Height = h_left + 1;
        }
        else
        {
            m_Height = h_right + 1;
        }
    }
};




#endif
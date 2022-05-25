/*
    filename: CCommon.hpp
    description: a common tree
    date: 10/23/2018
*/


#ifndef CCOMMONTREE_HPP
#define CCOMMONTREE_HPP

#include <iostream>
#include <vector>

#include "CCommonNode.hpp"

template <class Data>
class CCommonTree
{
//pointer
public:
    CCommonNode<Data>* m_Root{NULL};
    std::vector<CCommonTree<Data>*> m_Sons;
    int m_SonsNumber{0};
    int m_SequenceAsSon{0};
    CCommonTree<Data>* m_Father{NULL};
    int m_Height{1};

//function of changing
public:
    //construct an empty tree
    //variable:data
    CCommonTree(Data x)
    {
        m_Root = new CCommonNode<Data>(x);
    }

    //destruction
    ~CCommonTree()
    {
        for(int i = 0; i < m_SonsNumber; i ++)
        {
            delete(m_Sons[i]);
        }
    }

    //function: add a tree son
    //variable: new tree son
    void m_AddSon(CCommonTree<Data>* new_tree)
    {
        m_SonsNumber ++;
        m_Sons.push_back(new_tree);
        new_tree -> m_Father = this;
        new_tree -> m_SequenceAsSon = m_SonsNumber;
    }

};



#endif
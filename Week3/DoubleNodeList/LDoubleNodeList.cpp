/*
    filename: LDoubleNodeList.cpp
    date:09/30/2018
    function: the description of a double-end nodelist
*/


#include <iostream>
#include "LNode.hpp"
#include "LDoubleNodeList.h"
using namespace std;

LDoubleNodeList::LDoubleNodeList()
{
    m_Head = new LNode();
    m_This = m_Head;
    m_Tail = m_Head;
    m_Head -> m_Next = m_Head;
    m_Head -> m_Previous = m_Head;
    m_Length = 0;
}

LDoubleNodeList::~LDoubleNodeList()
{
    m_Tail -> m_Next = NULL;
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        LNode* previous = m_This;
        m_This = m_This -> m_Next;
        delete(previous);
    }
}

void LDoubleNodeList::m_Append(LNode* flag_node, LNode* new_node)
{
    LNode* old_next = flag_node -> m_Next;
    flag_node -> m_Next = new_node;
    new_node -> m_Next = old_next;
    new_node -> m_Previous = flag_node;
    if(old_next != m_Head)
    {
        old_next -> m_Previous = new_node;
    }
    else
    {
        m_Tail = new_node;
        new_node -> m_Next = m_Head;
        m_Head -> m_Previous = new_node;
    }
    m_Length ++;
}


LNode* LDoubleNodeList::m_FindFirst(LNode* comparison_node)
{
    m_This = m_Head -> m_Next;
    while(m_This != m_Head)
    {

        if(f_Comparison(*m_This, * comparison_node) == 0)
        {
            if(m_This != m_Head)
            {
                return m_This;
            }
        }
            m_This = m_This -> m_Next;
    }
    return NULL;
}


void LDoubleNodeList::m_ReverseOutPut()
{
    if(m_Head == m_Tail)
    {
        cout << "\n";
        return;
    }
    m_This = m_Tail;
    while(m_This -> m_Previous != m_Head)
    {
        if(m_This != m_Head)
        {
            m_This -> m_OutPut();
        }
        m_This = m_This -> m_Previous;
    }
    m_This -> m_OutPut();
    cout << "\n";
}

void LDoubleNodeList::m_ChangeFirst(LNode* new_first_node)
{
    if(new_first_node == m_Head || new_first_node == m_Head -> m_Next)
    {
        return;
    }
    LNode* previous = new_first_node -> m_Previous;
    LNode* old_tail = m_Tail;
    LNode* old_first = m_Head -> m_Next;

    old_tail -> m_Next = old_first;
    old_first -> m_Previous = old_tail;
    m_Head -> m_Next = new_first_node;
    new_first_node -> m_Previous = m_Head;
    previous -> m_Next = m_Head;
    m_Head -> m_Previous = previous;
    m_Tail = previous;
}
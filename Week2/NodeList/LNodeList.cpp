/*
    filename: LNodeList.cpp
    date:09/25/2018
    function: the description of a nodelist
*/


#include<iostream>
#include "LNode.hpp"
#include "LNodeList.h"
using namespace std;

LNodeList::LNodeList()
{
    m_Head = new LNode();
    m_This = m_Head;
    m_Tail = m_Head;
    m_Length = 0;
}

LNodeList::~LNodeList()
{
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        LNode* previous = m_This;
        m_This = m_This -> m_Next;
        delete(previous);
    }
}

void LNodeList::m_Append(LNode* flag_node, LNode* new_node)
{
    LNode* old_next = flag_node -> m_Next;
    flag_node -> m_Next = new_node;
    new_node -> m_Next = old_next;
    new_node -> m_Previous = flag_node;
    if(old_next != NULL)
    {
        old_next -> m_Previous = new_node;
    }
    else
    {
        m_Tail = new_node;
    }
    m_Length ++;
}

void LNodeList::m_Delete(LNode* flag_node)
{
    LNode* old_next = flag_node -> m_Next;
    LNode* old_previous = flag_node -> m_Previous;
    if(old_next != NULL)
    {
        old_next -> m_Previous = old_previous;
    }
    else
    {
        m_Tail = old_previous;
    }
    if(old_previous != NULL)
    {
        old_previous -> m_Next = old_next;
    }
    delete(flag_node);
    m_Length --;
}

void LNodeList::m_Reverse()
{
    if(m_Head == m_Tail)
    {
        return;
    }
    m_This = m_Tail;
    LNode* previous = m_Head;
    while(m_This -> m_Previous != m_Head)
    {
        LNode* new_this = m_This -> m_Previous;
        LNode* new_previous = m_This;
        m_This -> m_Previous = previous;
        previous -> m_Next = m_This;
        m_This = new_this;
        previous = new_previous;
    }
    previous -> m_Next = m_This;
    m_This -> m_Previous = previous;
    m_This -> m_Next = NULL;
    m_Tail = m_This;
}

void LNodeList::m_LeftShift(int distance)
{
    if(m_Length == 0)
    {
        return;
    }
    distance = distance % m_Length;
    if(distance == 0)
    {
        return;
    }
    m_This = m_Head;
    int place = 0;
    while(1)
    {
        if(place == distance + 1)
        {
            break;
        }
        else 
        {
            m_This = m_This -> m_Next;
            place ++;
        }
    }

    LNode* previous = m_This -> m_Previous;
    LNode* old_first = m_Head -> m_Next;

    m_Head -> m_Next = m_This;
    m_This -> m_Previous = m_Head;
    m_Tail -> m_Next = old_first;
    old_first -> m_Previous = m_Tail;
    previous -> m_Next = NULL;
    m_Tail = previous;   
}

LNode* LNodeList::m_FindAtPlace(int place)
{
    int place_now = 0;
    if(place < 0 || place > m_Length)
    {
        return NULL;
    }
    m_This = m_Head;
    while(place_now < place)
    {
        m_This = m_This -> m_Next;
        place_now ++;
    }
    return m_This;
}

LNode* LNodeList::m_FindFirst(LNode* comparison_node)
{
    m_This = m_Head;
    while(m_This != NULL)
    {

        if(f_Comparison(*m_This, * comparison_node) == 0)
        {
            if(m_This != m_Head)
            {
                return m_This;
            }
        }
        if(m_This -> m_Next != NULL)
        {
            m_This = m_This -> m_Next;
        }
        else
        {
            m_This = NULL;
        }
    }
    return NULL;
}

int LNodeList::m_FindFirst(LNode* comparison_node, int a)
{
    m_This = m_Head;
    int place = 0;
    while(m_This != NULL)
    {
        
        if(f_Comparison(*m_This, *comparison_node) == 0)
        {
            if(m_This != m_Head)
            {
                return place;
            }
        }
        if(m_This -> m_Next != NULL)
        {
            m_This = m_This -> m_Next;
            place ++;
        }
        else
        {
            m_This = NULL;
        }
    }
    return -1;
}

int LNodeList::m_GetLength()
{
    return m_Length;
}

void LNodeList::m_OutPut()
{
    if(m_Head == m_Tail)
    {
        cout << "\n";
        return;
    }
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        if(m_This != m_Head)
        {
            m_This -> m_OutPut();
        }
        m_This = m_This -> m_Next;
    }
    m_This -> m_OutPut();
    cout << "\n";
}

LNodeList* f_GetIntersection(LNodeList& a, LNodeList& b)
{
    if(a.m_Head == a.m_Tail || b.m_Head == b.m_Tail)
    {
        return NULL;
    }

    LNodeList* answer = new LNodeList();
    LNode* flag_a = a.m_Head -> m_Next;
    LNode* flag_b = b.m_Head -> m_Next;
    while(flag_a != NULL && flag_b != NULL)
    {
        if(f_Comparison(*flag_a, *flag_b) == -1)
        {
            flag_a = flag_a -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 0)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
            flag_b = flag_b -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 1)
        {
            flag_b = flag_b -> m_Next;
        }
    }

    return answer;
}

LNodeList* f_GetUnion(LNodeList& a, LNodeList& b)
{
    if(a.m_Head == a.m_Tail && b.m_Head == b.m_Tail)
    {
        return NULL;
    }
    else if(a.m_Head == a.m_Tail)
    {
        return &b;
    }
    else if(b.m_Head == b.m_Tail)
    {
        return &a;
    }

    LNodeList* answer = new LNodeList();
    LNode* flag_a = a.m_Head -> m_Next;
    LNode* flag_b = b.m_Head -> m_Next;
    while(flag_a != NULL || flag_b != NULL)
    {
        if(flag_a == NULL)
        {
            LNode* new_node = new LNode(*flag_b);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_b = flag_b -> m_Next;
            continue;
        }
        else if(flag_b == NULL)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
            continue;
        }


        if(f_Comparison(*flag_a, *flag_b) == -1)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 0)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
            flag_b = flag_b -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 1)
        {
            LNode* new_node = new LNode(*flag_b);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_b = flag_b -> m_Next;
        }

    }

    return answer;
}

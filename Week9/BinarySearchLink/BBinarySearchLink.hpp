/*
    filename:BBinarySearchLink.hpp
    description: used for binary search in a chainlink
    date:11/16/2018
*/
#include <cstdio>
#include <iostream>
#include "NChainLink.hpp"

#ifndef BBINARYSEARCHLINK_HPP
#define BBINARYSEARCHLINK_HPP


/*
    function: search a node in a chainlink
    variable: the chainlink, the data you want
    return: the place
    if not, return NULL
*/
template <class Data>
int g_BBinarySearchLink(NChainLink<Data>* link, Data wanted)
{
    NChainNode<Data>* head = link ->m_Head->m_Next;
    NChainNode<Data>* tail = link ->m_Head->m_Next;
    int num = 1;
    while(1)
    {
        if(tail == NULL)
        {
            return 0;
        }

        if(wanted == tail -> m_DataReal)
        {
            return num;
        }
        else if(wanted > tail -> m_DataReal)
        {
            tail = tail->m_Next;
            num ++;
        }
        else
        {
            return 0;
        }
    }

}

/*
    function: search a node in a doublechainlink
    variable: the chainlink, the data you want
    return: the place
    if not, return NULL
*/
template <class Data>
void g_BBinarySearchDoubleLink(NChainLink<Data>* link, Data wanted, bool& whether_success, int& answer)
{
    static NChainNode<Data>* flag = link ->m_Head->m_Next;
    link->m_Tail->m_Next = link->m_Head ->m_Next;
    int num = 0;
    int whether_always_bigger = -1;//initial
    while(1)
    {
        num ++;
        if(wanted == flag -> m_DataReal)
        {
            answer = num;
            whether_success = 1;
            return;
        }
        else if(wanted > flag -> m_DataReal)
        {
            if(whether_always_bigger == 0)
            {
                answer = num;
                whether_success = 0;
                return;
            }
            else if(flag == link -> m_Tail)
            {
                answer = num + 1;
                whether_success = 0;
                flag = link->m_Head->m_Next;
                return;
            }
            whether_always_bigger = 1;
            flag = flag->m_Next;
        }
        else
        {
            if(whether_always_bigger == 1)
            {
                answer = num;
                whether_success = 0;
                return;
            }
            if(flag == link -> m_Head ->m_Next)
            {
                answer = num + 1;
                whether_success = 0;
                flag = link->m_Tail;
                return;
            }
            whether_always_bigger = 0;
            flag = flag->m_Previous;
        }
    }

}

#endif
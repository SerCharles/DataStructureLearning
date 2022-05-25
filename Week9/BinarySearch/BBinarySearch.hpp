/*
    filename:BBinarySearch.hpp
    description: used for binary search
    date:11/16/2018
*/

#ifndef BBINARYSEARCH_HPP
#define BBINARYSEARCH_HPP

#include <iostream>


template <class Data>
class BBinarySearch
{
public:
    Data m_SearchNode;
    Data* m_SearchList;
    int m_Length;
public:
    BBinarySearch(Data list[], int length):m_SearchList(list),m_Length(length){}

    //function: binary search an increasing list
    //variable: the node you want to search
    //return : if <=1:return 0, if >=n return n, if = i, return i
    int m_Search(Data node)
    {
        m_SearchNode = node;
        if(m_SearchNode < m_SearchList[1])
        {
            return 0;
        }
        if(m_SearchNode >= m_SearchList[m_Length])
        {
            return m_Length;
        }
        int start = 1, end = m_Length;
        while(start <= end)
        {
            int mid = (start + end)/2;
            if(m_SearchNode == m_SearchList[mid])
            {
                return mid;
            }
            else if (m_SearchNode > m_SearchList[mid])
            {
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
        return end;
    }
};




#endif
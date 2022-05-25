/*
    filename: PPolynomial.cpp
    date:09/30/2018
    function: the description of a polynomial
*/


#include <iostream>
#include "PNode.hpp"
#include "PPolynomial.h"
using namespace std;

PPolynomial::PPolynomial()
{
    m_Head = new PNode();
    m_This = m_Head;
    m_Tail = m_Head;
    m_Length = 0;
}

PPolynomial::~PPolynomial()
{
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        PNode* previous = m_This;
        m_This = m_This -> m_Next;
        delete(previous);
    }
}

void PPolynomial::m_Append(PNode* flag_node, PNode* new_node)
{
    PNode* old_next = flag_node -> m_Next;
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



void PPolynomial::m_OutPut()
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
            cout << "+";
        }      
        m_This = m_This -> m_Next;
    }
    m_This -> m_OutPut();
    cout << "\n";
}

void PPolynomial::m_FindOddAndEven(PPolynomial*& odd_polynomial, PPolynomial*& even_polynomial)
{
    if(odd_polynomial != NULL)
    {
        delete odd_polynomial;
    }
    odd_polynomial = new PPolynomial();

    if(even_polynomial != NULL)
    {
        delete even_polynomial;
    }
    even_polynomial = new PPolynomial();

    if(m_Head == m_Tail)
    {
        return;
    }
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        if(m_This != m_Head)
        {
            if(m_This -> m_JudgeOddAndEven() == 1)
            {
                PNode* new_node = new PNode(*m_This);
                odd_polynomial -> m_Append(odd_polynomial -> m_Tail, new_node);
            }
            else
            {
                PNode* new_node = new PNode(*m_This);
                even_polynomial -> m_Append(even_polynomial -> m_Tail, new_node);
            }
        }
        m_This = m_This -> m_Next;
    }

    if(m_This -> m_JudgeOddAndEven() == 1)
    {
        PNode* new_node = new PNode(*m_This);
        odd_polynomial -> m_Append(odd_polynomial -> m_Tail, new_node);
    }
    else
    {
        PNode* new_node = new PNode(*m_This);
        even_polynomial -> m_Append(even_polynomial -> m_Tail, new_node);
    }

}

long long int PPolynomial::m_CalculateValue(int number)
{
    long long int ans = 0;
    if(m_Head == m_Tail)
    {
        return ans;
    }
     m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        if(m_This != m_Head)
        {
            ans += m_This -> m_CalculateValue(number);
        }
        m_This = m_This -> m_Next;
    }
    ans += m_This -> m_CalculateValue(number);
    return ans;
}
/*
    filename:BStack.hpp
    description:a stack using vector
    date: 10/9/2018
*/

#ifndef BSTACK_HPP
#define BSTACK_HPP

#include <vector>


template <class Data>
class BStack
{
//data
private:
    std::vector <Data> m_Stack;
public:
    int m_length;


//functions
public:
    //empty construction and destruction
    BStack():m_length(0){}
    ~BStack()
    {
        m_Stack.clear();
        m_length = 0;
    }

    //function: get the top place of the stack
    //return: the char of the top place, if empty, return NULL

    Data m_GetTop()
    {
        return m_Stack[m_length - 1];
    }

    //function: add a char to the top place of the stack
    //variable: new_element
    void m_AddTop(Data new_element)
    {
        m_Stack.push_back(new_element);
        m_length ++;
    }

    //function: delete the top element
    void m_DeleteTop()
    {
        if(m_length == 0)
        {
            return;
        }

        else
        {
            m_Stack.pop_back();
            m_length --;
        }
    }
    
};

#endif
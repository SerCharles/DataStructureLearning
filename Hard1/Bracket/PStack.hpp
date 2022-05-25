/*
    filename:PStack.hpp
    description:a stack using vector
    date: 10/9/2018
*/

#ifndef PSTACK_HPP
#define PSTACK_HPP

#include <vector>



class PStack
{
//data
private:
    std::vector <char> m_Stack;
public:
    int m_Length;


//functions
public:
    //empty construction and destruction
    PStack():m_Length(0){}
    ~PStack()
    {
        m_Stack.clear();
        m_Length = 0;
    }

    //function: get the top place of the stack
    //return: the char of the top place, if empty, return -1

    char m_GetTop()
    {
        if(m_Length == 0)
        {
            return -1;
        }
        return m_Stack[m_Length - 1];
    }

    //function: add a char to the top place of the stack
    //variable: new_element
    void m_AddTop(char new_element)
    {
        m_Stack.push_back(new_element);
        m_Length ++;
    }

    //function: delete the top element
    void m_DeleteTop()
    {
        if(m_Length == 0)
        {
            return;
        }

        else
        {
            m_Stack.pop_back();
            m_Length --;
        }
    }
    
    //function: clear the stack
    void m_Clear()
    {
        m_Stack.clear();
        m_Length = 0;
    }
};

#endif

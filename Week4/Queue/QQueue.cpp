/*
    filename:QQueue.cpp
    description:a queue
    date: 10/9/2018
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;


#include "QPhone.hpp"
#include "QQueue.h"


void QQueue::m_AddToBack(string new_number, int type)
{
    QPhone new_node(new_number, type);
    if(type == 0)
    {
        m_UnansweredCall.push_back(new_node);
        m_UnansweredLength ++;
    }
    if(type == 1)
    {
        m_AnsweredCall.push_back(new_node);
        m_AnsweredLength ++;
    }
    if(type == 2)
    {
        m_CalledCall.push_back(new_node);
        m_CalledLength ++;
    }
}

void QQueue::m_DeleteBack(int type)
{
    if(type == 0)
    {
        if(m_UnansweredLength <= 0)
        {
            return;
        }
        m_UnansweredCall.pop_back();
        m_UnansweredLength --;
    }
    if(type == 1)
    {
        if(m_AnsweredLength <= 0)
        {
            return;
        }
        m_AnsweredCall.pop_back();
        m_AnsweredLength --;
    }
    if(type == 2)
    {
        if(m_CalledLength <= 0)
        {
            return;
        }
        m_CalledCall.pop_back();
        m_CalledLength --;
    }
}

string QQueue::m_ReturnBack(int type)
{
    if(type == 0)
    {
        return m_UnansweredCall[m_UnansweredLength - 1].m_Number;
    }
    if(type == 1)
    {
        return m_AnsweredCall[m_AnsweredLength - 1].m_Number;
    }
    if(type == 2)
    {
        return m_CalledCall[m_CalledLength - 1].m_Number;
    }
}

void QQueue::m_OutPut()
{
    for(int i = 0; i < 10; i ++)
    {
        if(m_UnansweredLength == 0)
        {
            cout << "0 ";
        }
        else
        {
            string out_string = m_ReturnBack(0);
            cout << out_string << " ";
            m_DeleteBack(0);
        }

        if(m_AnsweredLength == 0)
        {
            cout << "0 ";
        }
        else
        {
            string out_string = m_ReturnBack(1);
            cout << out_string << " ";
            m_DeleteBack(1);
        }

        if(m_CalledLength == 0)
        {
            cout << "0" << endl;
        }
        else
        {
            string out_string = m_ReturnBack(2);
            cout << out_string << endl;
            m_DeleteBack(2);
        }
    }

}
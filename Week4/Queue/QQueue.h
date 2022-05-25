/*
    filename:QQueue.h
    description:a queue
    date: 10/9/2018
*/

#ifndef QQUEUE_H
#define QQUEUE_H

#include <string>
#include <vector>

#include "QPhone.hpp"


class QQueue
{
    //data
    public:
        std::vector<QPhone> m_UnansweredCall;
        std::vector<QPhone> m_AnsweredCall;
        std::vector<QPhone> m_CalledCall;
        int m_UnansweredLength, m_AnsweredLength, m_CalledLength;


    //function
    public:
        QQueue():m_UnansweredLength(0), m_AnsweredLength(0), m_CalledLength(0){}
        ~QQueue()
        {
            m_UnansweredLength = 0;
            m_AnsweredLength = 0;
            m_CalledLength = 0;
            m_UnansweredCall.clear();
            m_AnsweredCall.clear();
            m_CalledCall.clear();
        }

        //function: add a new phone call to the back
        //variable: new number and its type
        void m_AddToBack(std::string new_number, int type);


        //function: return the last element at the back of the queue
        //variable: type of the queue
        //return: the string of the element
        std::string m_ReturnBack(int type);

        //function: delete the last element at the back of the queue
        //variable: type of the queue
        void m_DeleteBack(int type);


        //function: output the queues
        void m_OutPut();
};













#endif
/*
    filename: LDoubleNodeList.h
    date:09/30/2018
    function: the description of a double-end nodelist
*/



#ifndef LDOUBLENODELIST_H
#define LDOUBLENODELIST_H


#include "LNode.hpp"



class LDoubleNodeList
{
    //data
    private:
        
        int m_Length;
        LNode* m_This;
    public:
        LNode* m_Head;
        LNode* m_Tail;

    //operation functions
    public:

        //construction
        //add the head node of the list
        LDoubleNodeList();

        //destruction
        ~LDoubleNodeList();

        //function:add one after the pointer
        //variable: flag_node:the flag, which cannot be the head; new_node:the one that will be appended after flag_node
        void m_Append(LNode* flag_node, LNode* new_node);



        //function: change the first element of the nodelist
        //variable: the pointer of the nodelist
        void m_ChangeFirst(LNode* new_first_node);
        
    //find functions
    public:

        //function:find the first one that is the same with the node
        //variable: the node you want to check
        //return: the pointer of the first node identical; no such place:NULL
        LNode* m_FindFirst(LNode* comparison_node);



        //function: reverse output the nodelist
        void m_ReverseOutPut();
};

#endif
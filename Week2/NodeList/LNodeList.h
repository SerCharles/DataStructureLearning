/*
    filename: LNodeList.h
    date:09/25/2018
    function: the description of a nodelist
*/



#ifndef LNODELIST_H
#define LNODELIST_H


#include "LNode.hpp"



class LNodeList
{
    //data
    private:
        LNode* m_Head;
        int m_Length;
        LNode* m_This;
    public:
        LNode* m_Tail;

    //operation functions
    public:

        //construction
        //add the head node of the list
        LNodeList();

        //destruction
        ~LNodeList();

        //function:add one after the pointer
        //variable: flag_node:the flag, which cannot be the head; new_node:the one that will be appended after flag_node
        void m_Append(LNode* flag_node, LNode* new_node);

        //function:delete one at the pointer
        //variable: the node that will be deleted
        void m_Delete(LNode* flag_node);

        //function:reverse the list
        void m_Reverse();

        //function:left shift the list
        //variable:the distance of the shift
        void m_LeftShift(int distance);


    //find functions
    public:
        //function:find the xth element of the nodelist
        //variable: the number x
        //return: the pointer of the node
        LNode* m_FindAtPlace(int place);

        //function:find the first one that is the same with the node
        //variable: the node you want to check
        //return: the pointer of the first node identical; no such place:NULL
        LNode* m_FindFirst(LNode* comparison_node);

        //function:find the first one that is the same with the node
        //variable: the node you want to check
        //return: the place of the first node identical; no such place: -1
        int m_FindFirst(LNode* comparison_node, int a);



        //function:return the length
        //return:length
        int m_GetLength();

        //function:output
        void m_OutPut();



    //friend functions
        //function: get the union of two ordered nodelists
        //return:new nodelist of the union, empty:null
        //variable: the two you want to calculate
        friend LNodeList* f_GetUnion(LNodeList& a, LNodeList& b);

        //function: get the union of two ordered nodelists
        //return:new nodelist of the union, empty:null
        //variable: the two you want to calculate
        friend LNodeList* f_GetIntersection(LNodeList& a, LNodeList& b);
};

extern LNodeList* f_GetUnion(LNodeList& a, LNodeList& b);
extern LNodeList* f_GetIntersection(LNodeList& a, LNodeList& b);

#endif
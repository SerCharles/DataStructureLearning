/*
    filename: LNode.hpp
    date:09/25/2018
    function: the description of a node in a nodelist, whose element is a char
*/
#ifndef LNODE_HPP
#define LNODE_HPP

#include <iostream>


class LNode
{
    //data
    private:
        int m_Element; 

    //pointer
    public:
        LNode* m_Next;
        LNode* m_Previous;

    //function
    public:

        //empty construction
        LNode():m_Element(0),m_Next(NULL), m_Previous(NULL){}

        //construct with a char
        LNode(int c):m_Element(c),m_Next(NULL), m_Previous(NULL){}

        //destruction
        ~LNode(){}

        //set element value
        //variable: new char
        void m_SetValue(const int new_value){m_Element = new_value;}

        //get element value
        //return: the element of the node
        int m_GetValue(){return m_Element;}

        //function: output the value of the node
        void m_OutPut()
        {
            std::cout << m_Element <<" ";
        }

        /*
        friend function
        function:compare the value of two nodes in ASCII
        variable:two nodes
        return: -1:first<last 0:first=last 1:first>last
        */
        friend int f_Comparison(const LNode& node_first, const LNode& node_last)
        {
            if(node_first.m_Element < node_last.m_Element)
            {
                return -1;
            }
            else if(node_first.m_Element == node_last.m_Element)
            {
                return 0;
            }
            else if(node_first.m_Element > node_last.m_Element)
            {
                return 1;
            }
        }


};

extern int f_Comparison(const LNode& node_first, const LNode& node_last);






#endif
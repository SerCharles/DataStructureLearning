/*
    filename: BBinaryNode.hpp
    description: the node of a binary tree
    date: 10/23/2018
*/
#ifndef BBINARYNODE_HPP
#define BBINARYNODE_HPP

#include <iostream>


template<class Data>
class BBinaryNode
{
//data
private:
    Data m_Data;

//function
public:
    //construction and destruction
    BBinaryNode(Data d):m_Data(d){}
    ~BBinaryNode(){}
    
    //function: compare two nodes
    //variable: new node
    //return: -1:this<new 0:this=new 1:this>new
    int m_Compare(const BBinaryNode* new_node)
    {
        if(m_Data < new_node -> m_Data)
        {
            return -1;
        }
        if(m_Data == new_node -> m_Data)
        {
            return 0;
        }
        if(m_Data > new_node -> m_Data)
        {
            return 1;
        }
    }
    
    //function: print node
    //warning: must has cout
    void m_Print()
    {
        std::cout << m_Data;
    }

};









#endif
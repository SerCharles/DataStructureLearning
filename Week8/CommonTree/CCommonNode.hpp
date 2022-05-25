/*
    filename: CCommonNode.hpp
    description: the node of a normal tree
    date: 11/6/2018
*/
#ifndef CCOMMONNODE_HPP
#define CCOMMONNODE_HPP

#include <iostream>


template<class Data>
class CCommonNode
{
//data
private:
    Data m_Data;

//function
public:
    //construction and destruction
    CCommonNode(Data d):m_Data(d){}
    ~CCommonNode(){}
    
    //function: compare two nodes
    //variable: new node
    //return: -1:this<new 0:this=new 1:this>new
    int m_Compare(const CCommonNode* new_node)
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

    //get data
    Data m_GetData()
    {
        return m_Data;
    }

};









#endif
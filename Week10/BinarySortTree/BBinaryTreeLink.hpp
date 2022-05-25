
/*
    filename: BBinaryTreeLink.hpp
    description: a binary tree in the form of a link
    date: 11/20/2018
*/


#ifndef BBINARYTREELINK_HPP
#define BBINARYTREELINK_HPP

#include <iostream>

#include "BStack.hpp"



template<class Data>
class BBinaryNode
{
//data
protected:
    Data m_Data;    //used for int, char, string, etc
    Data* m_DataPointer{NULL}; //used for self-design things, such as char
public:
    BBinaryNode<Data>* m_LeftSon{NULL};
    BBinaryNode<Data>* m_RightSon{NULL};
    BBinaryNode<Data>* m_Father{NULL};
    bool m_Mode{0};//0:left, 1:right

//function
public:
    //construction and destruction
    BBinaryNode(Data d):m_Data(d){}
    BBinaryNode(Data* d):m_DataPointer(d){}

    
    //function: compare two nodes, in real data
    //variable: new node
    //return: -1:this<new 0:this=new 1:this>new
    int m_Compare(BBinaryNode<Data>* new_node)
    {
        if(m_DataPointer != NULL)
        {
            //return m_DataPointer -> m_Compare(new_node -> m_DataPointer);
        }
        else
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
    }

    //return the data
    Data m_GetData()
    {
        return m_Data;
    }

    //copy the data from another node
    void m_CopyData(BBinaryNode<Data>* new_node)
    {
        if(m_DataPointer != NULL)
        {
            m_DataPointer = new_node -> m_DataPointer;
        }
        else
        {
            m_Data = new_node -> m_Data;
        }
    }

    void m_OutPut()
    {
        if(m_DataPointer != NULL)
        {
           // m_DataPointer -> m_OutPut();
        }
        else
        {
            std::cout << m_Data;
        }
    }
    //todo: used in pointer, compare two and return

};


template <class Data>
class BBinaryTreeLink
{
//pointer
public:
    BBinaryNode<Data>* m_Root{NULL};
    int m_Height{0};

//function of changing
public:

    //destruction
    void m_DeleteTree(BBinaryNode<Data>* current_place)
    {
        if(current_place == NULL)
        {
            return;
        }
        if(current_place -> m_LeftSon != NULL)
        {
            m_DeleteTree(current_place -> m_LeftSon);
        }
        if(current_place -> m_RightSon != NULL)
        {
            m_DeleteTree(current_place -> m_RightSon);
        }
        delete(current_place);
    }    
    ~BBinaryTreeLink()
    {
        if(m_Root != NULL)
        {
            m_DeleteTree(m_Root);
        }
    }

    

    //function:add one new node to the tree
    //variable:the new node, the place you want to insert, mode(0:left, 1:right)
    void m_AddNode(BBinaryNode<Data>* new_son, BBinaryNode<Data>* add_place, bool mode)
    {
        if(mode == 0)
        {
            new_son -> m_Father = add_place;
            add_place -> m_LeftSon = new_son;     
            new_son -> m_Mode = 0;                 
        }
        else
        {
            new_son -> m_Father = add_place;
            add_place -> m_RightSon = new_son;      
            new_son -> m_Mode = 1;                 
                 
        }
    }

    //function: find the Left_down place of the subtree
    BBinaryNode<Data>* m_FindLeftEnd(BBinaryNode<Data>* start_place)
    {
        BBinaryNode<Data>* current = start_place;
        while(current -> m_LeftSon != NULL)
        {
            current = current->m_LeftSon;
        }
        return current;
    }

    //function: print the link
    void m_OutPut(BBinaryNode<Data>* current)
    {
        if(current == NULL)
        {
            return;
        }
        else
        {
            current -> m_OutPut();
            if(current -> m_LeftSon == NULL && current -> m_RightSon == NULL)
            {
                return;
            }
            else
            {
                std::cout <<"(";
                if(current -> m_LeftSon == NULL)
                {
                    std::cout <<"-";
                }
                else
                {
                    m_OutPut(current -> m_LeftSon);
                }
                std::cout <<",";
                if(current -> m_RightSon == NULL)
                {
                    std::cout <<"-";
                }
                else
                {
                    m_OutPut(current -> m_RightSon);
                }
                std::cout << ")";
            }
        }
    }

    //todo: get height
};




#endif

/*
    filename: BBinarySortTree.hpp
    description: a binary tree in the form of a link
    date: 11/20/2018
*/


#ifndef BBINARYSORTTREE_HPP
#define BBINARYSORTTREE_HPP

#include <iostream>

#include "BBinaryTreeLink.hpp"
#include "BStack.hpp"


template <class Data>
class BBinarySortTree : public BBinaryTreeLink<Data>
{

//function of changing
public:

    //function: finding an element in the tree
    //return: the pointer of the node, no element:the last place you have searched
    BBinaryNode<Data>* m_FindNode(BBinaryNode<Data>* target)
    {
       if(this -> m_Root == NULL)
       {
           //emtpty tree
           return NULL;
       } 
       BBinaryNode<Data>* current = this -> m_Root;
       while(1)
       {
           int a = target -> m_Compare(current);
           if(a == -1)
           {
               if(current -> m_LeftSon != NULL)
               {
                   current = current -> m_LeftSon;
               }
               else
               {
                   return current;
               }
           }
           else if (a == 1)
           {
               if(current -> m_RightSon != NULL)
               {
                   current = current -> m_RightSon;
               }
               else
               {
                   return current;
               }
           }
           else
           {
               return current;
           }
       }
    }

    //function: delete an chosen element in the tree
    //variable:the node you want to delete
    void m_DeleteNode(BBinaryNode<Data>* ready_to_delete)
    {
        if(ready_to_delete == NULL)
        {
            return;
        }
        if(ready_to_delete -> m_LeftSon == NULL && ready_to_delete -> m_RightSon == NULL)
        {
            if(ready_to_delete == this -> m_Root)
            {
                this -> m_Root = NULL;
            }
            else
            {
                if(ready_to_delete -> m_Mode == 0)
                {
                    ready_to_delete -> m_Father -> m_LeftSon = NULL;
                }
                else
                {
                    ready_to_delete -> m_Father -> m_RightSon = NULL;
                }
            }
                delete(ready_to_delete);

        }
        else if (ready_to_delete -> m_LeftSon == NULL)
        {
            if(ready_to_delete == this -> m_Root)
            {
                this -> m_Root = ready_to_delete -> m_RightSon;
            }
            else
            {
                if(ready_to_delete -> m_Mode == 0)
                {
                    ready_to_delete -> m_Father -> m_LeftSon = ready_to_delete -> m_RightSon;
                    ready_to_delete -> m_RightSon -> m_Mode = 0;
                }
                else
                {
                    ready_to_delete -> m_Father -> m_RightSon = ready_to_delete -> m_RightSon;

                }
            }
            ready_to_delete -> m_RightSon -> m_Father = ready_to_delete -> m_Father;
            delete(ready_to_delete);
        }
        else if (ready_to_delete -> m_RightSon == NULL)
        {
            if(ready_to_delete == this -> m_Root)
            {
                this -> m_Root = ready_to_delete -> m_LeftSon;
            }
            else
            {
                if(ready_to_delete -> m_Mode == 0)
                {
                    ready_to_delete -> m_Father -> m_LeftSon = ready_to_delete -> m_LeftSon;
                }
                else
                {
                    ready_to_delete -> m_Father -> m_RightSon = ready_to_delete -> m_LeftSon;
                    ready_to_delete -> m_LeftSon -> m_Mode = 1;

                }
            }
            ready_to_delete -> m_LeftSon -> m_Father = ready_to_delete -> m_Father;
            delete(ready_to_delete);
        }
        else
        {
            BBinaryNode<Data>* new_current = this -> m_FindLeftEnd(ready_to_delete -> m_RightSon);
            bool previous_mode = ready_to_delete -> m_Mode;
            ready_to_delete -> m_CopyData(new_current);
            ready_to_delete -> m_Mode = previous_mode;
            m_DeleteNode(new_current);
        }
    }
    

    //delete all nodes not smaller than the given point, recursion
    //variable:given point, the recurring current place 
    void m_DeleteAllBigger(BBinaryNode<Data>* given_node, BBinaryNode<Data>* given_place)
    {
        if(given_place == NULL)
        {
            return;
        }
        if(given_node -> m_Compare(given_place) <= 0)
        {
            this -> m_DeleteTree(given_place->m_RightSon);
            given_place -> m_RightSon = NULL;
            BBinaryNode<Data>* new_place = given_place -> m_LeftSon;
            m_DeleteNode(given_place);
            m_DeleteAllBigger(given_node, new_place);
        }
        else
        {
            m_DeleteAllBigger(given_node, given_place -> m_RightSon);
        }
    }

    //insert a new node
    void m_InsertNewNode(BBinaryNode<Data>* given_node)
    {
        if(this->m_Root == NULL)
        {
            this->m_Root = given_node;
            return;
        }
        
        BBinaryNode<Data>* certain_place = m_FindNode(given_node);
        if(given_node -> m_Compare(certain_place) == -1)
        {
            given_node -> m_Father = certain_place;
            certain_place -> m_LeftSon = given_node;
            given_node -> m_Mode = 0;
        }
        else if(given_node -> m_Compare(certain_place) == 1)
        {
            given_node -> m_Father = certain_place;
            certain_place -> m_RightSon = given_node;
            given_node -> m_Mode = 1;
        }
    }

};

#endif
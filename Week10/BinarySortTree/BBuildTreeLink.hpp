/*
    filename: BBuildTreeLink.hpp
    description: build a binary tree linkthrough a link
    date: 11/22/2018
*/

#ifndef BBUILDTREELINK_HPP
#define BBUILDTREELINK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "BBinaryTreeLink.hpp"
#include "BBinarySortTree.hpp"
#include "BStack.hpp"


int g_SwitchCharToInt(char list[], int length)
{
    int ans = 0;
    int multiply = 1;
    for(int i = length - 1; i >= 0 ;i --)
    {
        ans += (list[i] - '0')* multiply;
        multiply *= 10;
    }
    return ans;
}
//function: build a binary tree through a link
//return BBinaryTree
BBinarySortTree<int>* g_BuildTree()
{
    BBinarySortTree<int>* the_tree = new BBinarySortTree<int>();
    BStack<BBinaryNode<int>*> the_stack;
    char main_char[10000];
    if(!(std::cin.getline(main_char,10000)))
    {
        return NULL;
    }
    if(main_char[0] == 0)
    {
        return NULL;
    }
    int length = strlen(main_char);
    int flag_previous = -1;
    for(int i = 0; i < length; i ++)
    {
        if(main_char[i] >='0'&& main_char[i] <='9')
        {
            if(flag_previous == -1)
            {
                flag_previous = i;
            }
        }
        else
        {
            if(flag_previous != -1)
            {
                int new_num = g_SwitchCharToInt(&main_char[flag_previous],i - flag_previous);
                BBinaryNode<int>* new_node = new BBinaryNode<int>(new_num);
                if(the_stack.m_Length == 0)
                {
                    the_tree->m_Root = new_node;
                    if(main_char[i] == '(')
                    {
                        the_stack.m_AddTop(new_node);
                    }
                }
                else
                {
                    BBinaryNode<int>* add_place = the_stack.m_GetTop();
                    if(main_char[flag_previous - 1] =='(')
                    {
                        add_place -> m_LeftSon = new_node;
                        new_node -> m_Mode = 0;
                        new_node -> m_Father = add_place;
                    }
                    else
                    {
                        add_place -> m_RightSon = new_node;
                        new_node -> m_Mode = 1;
                        new_node -> m_Father = add_place;
                    }
                    if(main_char[i] == '(')
                    {
                        the_stack.m_AddTop(new_node);
                    }
                    if(main_char[i] == ')')
                    {
                        the_stack.m_DeleteTop();
                    }
                }

                flag_previous = -1;

            }
        }
    }
    if(flag_previous != -1)
    {
        int new_num = g_SwitchCharToInt(main_char,length);
        BBinaryNode<int>* new_node = new BBinaryNode<int>(new_num);
        the_tree -> m_Root = new_node;
    }
    return the_tree;
        
}



extern BBinarySortTree<int>* g_BuildTree();


#endif
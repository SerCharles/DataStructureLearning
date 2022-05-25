/*
    filename: BBuildTree.hpp
    description: build a binary tree through a link
    date: 10/23/2018
*/

#ifndef BBUILDTREE_HPP
#define BBUILDTREE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "BBinaryNode.hpp"
#include "BBinaryTree.hpp"
#include "BStack.hpp"

//function: build a binary tree through a link
//return BBinaryTree
BBinaryTree<std::string>* g_BuildTree()
{
    std::string main_char;
    std::cin >> main_char;
    BStack<BBinaryTree<std::string>*> the_stack;
    BBinaryTree<std::string>* final_tree = NULL;
    int length = main_char.length();
    int flag_char = -1;
    for(int i = 0; i < length; i ++)
    {
        if(main_char[i] >= 'A' && main_char[i] <= 'Z')
        {
            if(flag_char == -1)
            {
                flag_char = i;
            }
        }
        else
        {
           
            if(flag_char != -1)
            {
                
                std::string previous_node = main_char.substr(flag_char, i - flag_char);
                flag_char = -1;
                BBinaryTree<std::string>* new_subtree = new BBinaryTree<std::string>(previous_node);
                if(final_tree == NULL)
                {
                    final_tree = new_subtree;
                }
                else
                {
                    BBinaryTree<std::string>* stack_top = the_stack.m_GetTop();
                    if(stack_top -> m_LeftSon == NULL)
                    {
                        stack_top -> m_MergeTree(new_subtree, 0);
                    }
                    else
                    {
                        stack_top -> m_MergeTree(new_subtree, 1);
                    }
                }
                if(main_char[i] == '(')
                {
                    the_stack.m_AddTop(new_subtree);
                }
            }
            if(main_char[i] == ')')
            {
                the_stack.m_DeleteTop();
            }

        }
    }
    if(flag_char != -1)
    {
        std::string previous_node = main_char.substr(flag_char, length);
        flag_char = -1;
        final_tree = new BBinaryTree<std::string>(previous_node);
    }
    final_tree -> m_GetHeight();
    return final_tree;
}

//function: build a total binary tree
//return: binary tree, if empty:return 0
BBinaryTree<char>* g_BuildTotalBinaryTree()
{
    std::vector<BBinaryTree<char>*> node_list;
    while(1)
    {
        char c;
        std::cin >> c;
        if(c == '$')
        {
            break;
        }
        BBinaryTree<char>* new_node = new BBinaryTree<char>(c);
        node_list.push_back(new_node);
    }
    for(int i = 0; i < node_list.size(); i ++)
    {
        if(2 * i + 1 < node_list.size())
        {
            node_list[i] -> m_LeftSon = node_list[2 * i + 1];
            node_list[2 * i + 1] -> m_Father = node_list[i];
        }
        if(2 * i + 2 < node_list.size())
        {
            node_list[i] -> m_RightSon = node_list[2 * i + 2];
            node_list[2 * i + 2] -> m_Father = node_list[i];
        }
    }
    if(node_list.size() == 0)
    {
        return NULL;
    }
    else
    {
        return node_list[0];
    }
}



extern BBinaryTree<std::string>* g_BuildTree();
extern BBinaryTree<char>* g_BuildTotalBinaryTree();

#endif
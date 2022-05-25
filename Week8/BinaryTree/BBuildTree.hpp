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
#include <cstring>

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

BBinaryTree<char>* g_BuildBinaryTreeByRank()
{
    BBinaryTree<char>* point_queue[10000] = {NULL};
    int head = -1, tail = -1;
    while(1)
    {
        char c[10] = {0};
        std::cin >> c;
        if(c[1] == '^')
        {
            break;
        }
           BBinaryTree<char>* new_node = new BBinaryTree<char>(c[1]);
           tail ++;
           point_queue[tail] = new_node;
           if(c[0] == '^')
           {
               head = 0;
               tail = 0;
               point_queue[0] = new_node;
           }
           else
           {
               while(head <= tail)
               {
                    BBinaryNode<char>* head_node = (point_queue[head]->m_Root);
                    BBinaryNode<char>* new_father = new BBinaryNode<char>(c[0]);
                    if(head_node->m_Compare(new_father) == 0)
                    {
                        if(c[2] == 'L')
                        {
                            new_node -> m_Father = point_queue[head];
                            point_queue[head]->m_LeftSon = new_node;
                        }
                        else
                        {
                            new_node -> m_Father = point_queue[head];
                            point_queue[head]->m_RightSon = new_node;
                        }
                        break;
                    }
                    else
                    {
                        head ++;
                    }
                    delete(new_father);
               }
           } 
    }
    BBinaryTree<char>* the_tree = point_queue[0];
    return the_tree;
}



//recursion sub void
//used in building binary tree by traverse
//variable: current root, current handle list(pre order and post order), current length;
void AddTreeByTraverse(BBinaryTree<char>* the_root, char pre_order_list[], char middle_order_list[], int handle_length)
{
    char c = the_root -> m_Root -> m_GetData();
    int length_left = 0, length_right = 0, middle_place = 0;
    int start_left_pre = 0, start_right_pre = 0, start_left_middle = 0, start_right_middle = 0;
    for(int i = 0; i < handle_length; i ++)
    {
        if(middle_order_list[i] == c)
        {
            middle_place = i;
            break;
        }
        
    }
    length_left = middle_place;
    length_right = handle_length - middle_place - 1;
    start_left_pre = 1;
    start_right_pre = middle_place + 1;
    start_left_middle = 0;
    start_right_middle = middle_place + 1;
    BBinaryTree<char>* left_root = NULL;
    BBinaryTree<char>* right_root = NULL;
    if(length_left != 0)
    {
        left_root = new BBinaryTree<char>(pre_order_list[start_left_pre]);
        the_root -> m_LeftSon = left_root;
        left_root -> m_Father = the_root;
        AddTreeByTraverse(left_root, &pre_order_list[start_left_pre], &middle_order_list[start_left_middle], length_left);
    }
    if(length_right != 0)
    {
        right_root = new BBinaryTree<char>(pre_order_list[start_right_pre]);
        the_root -> m_RightSon = right_root;
        right_root -> m_Father = the_root;
        AddTreeByTraverse(right_root, &pre_order_list[start_right_pre], &middle_order_list[start_right_middle], length_right);
    }
}

//build tree by pre-order and middle-order traverse
BBinaryTree<char>* g_BuildBinaryTreeByTraverse()
{
    char pre_order[70] = {0};
    char middle_order[70] = {0};
    int length = 0;
    std::cin >> pre_order;
    std::cin >> middle_order;
    length = strlen(pre_order);
    if(length == 0)
    {
        return NULL;
    }
    BBinaryTree<char>* the_tree = new BBinaryTree<char>(pre_order[0]);
    AddTreeByTraverse(the_tree, &pre_order[0], &middle_order[0], length);
    return the_tree;
}


extern BBinaryTree<char>* g_BuildBinaryTreeByTraverse();
extern BBinaryTree<std::string>* g_BuildTree();
extern BBinaryTree<char>* g_BuildTotalBinaryTree();
extern BBinaryTree<char>* g_BuildBinaryTreeByRank();


#endif
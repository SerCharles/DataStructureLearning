#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

};






template <class Data>
class BBinaryTree
{
//pointer
public:
    BBinaryNode<Data>* m_Root{NULL};
    BBinaryTree* m_LeftSon{NULL};
    BBinaryTree* m_RightSon{NULL};
    BBinaryTree* m_Father{NULL};
    int m_Height{1};

//function of changing
public:
    //construct an empty tree
    //variable:data
    BBinaryTree(Data x)
    {
        m_Root = new BBinaryNode<Data>(x);
    }

    //destruction
    ~BBinaryTree()
    {
        if(m_LeftSon != NULL)
        {
            delete(m_LeftSon);
        }
        if(m_RightSon != NULL)
        {
            delete(m_RightSon);
        }
    }

    //function:merge trees
    //variable:the pointer of another tree, mode(0:left, 1:right)
    void m_MergeTree(BBinaryTree* new_son, const bool mode)
    {
        if(mode == 0)
        {
            new_son -> m_Father = this;
            m_LeftSon = new_son;
        }
        else
        {
            new_son -> m_Father = this;
            m_RightSon = new_son;
        }
    }


    //function: finding an element in the tree's son trees
    //return: the pointer of its subtree, no element:NULL
    BBinaryTree* m_FindNode(const BBinaryNode<Data>* target)
    {
        BBinaryTree* return_pointer = NULL;
        if(m_Root -> m_Compare(target) == 0)
        {
            return this;
        }
        if(m_LeftSon != NULL)
        {
            return_pointer = m_LeftSon -> m_FindNode(target);
            if(return_pointer != NULL)
            {
                return return_pointer;
            }
        }
        if(m_RightSon != NULL)
        {
            return_pointer = m_RightSon -> m_FindNode(target);
            if(return_pointer != NULL)
            {
                return return_pointer;
            }
        }
        return NULL;
    }

    //function:get height
    void m_GetHeight()
    {
        int h_left = 0, h_right = 0;
        if(m_LeftSon != NULL)
        {
            m_LeftSon -> m_GetHeight();
            h_left = m_LeftSon -> m_Height;
        }
        if(m_RightSon != NULL)
        {
            m_RightSon -> m_GetHeight();
            h_right = m_RightSon -> m_Height;
        }
        if(h_left > h_right)
        {
            m_Height = h_left + 1;
        }
        else
        {
            m_Height = h_right + 1;
        }
    }
};



template <class Data>
class BStack
{
//data
private:
    std::vector <Data> m_Stack;
public:
    int m_length;


//functions
public:
    //empty construction and destruction
    BStack():m_length(0){}
    ~BStack()
    {
        m_Stack.clear();
        m_length = 0;
    }

    //function: get the top place of the stack
    //return: the char of the top place, if empty, return NULL

    Data m_GetTop()
    {
        return m_Stack[m_length - 1];
    }

    //function: add a char to the top place of the stack
    //variable: new_element
    void m_AddTop(Data new_element)
    {
        m_Stack.push_back(new_element);
        m_length ++;
    }

    //function: delete the top element
    void m_DeleteTop()
    {
        if(m_length == 0)
        {
            return;
        }

        else
        {
            m_Stack.pop_back();
            m_length --;
        }
    }
    
};

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
    final_tree -> m_GetHeight();
    return final_tree;
}



int height_list[1100]={0};

//function: calculate all the subtree numbers;
//variable: used for dfs, current tree
void g_GetTreeHeight(const BBinaryTree<string>* the_tree)
{
    int c = the_tree -> m_Height;
    height_list[c] ++;
    if(the_tree -> m_LeftSon != NULL)
    {
        g_GetTreeHeight(the_tree -> m_LeftSon);
    }
    if(the_tree -> m_RightSon != NULL)
    {
        g_GetTreeHeight(the_tree -> m_RightSon);
    }
}



int main()
{
    BBinaryTree<string>* the_tree = g_BuildTree();
    int max_height = the_tree -> m_Height;
    g_GetTreeHeight(the_tree);
    cout << max_height <<endl;
    for(int i = 1; i <= max_height; i ++)
    {
        cout << height_list[i] <<endl;
    }
    delete(the_tree);
    return 0;
}


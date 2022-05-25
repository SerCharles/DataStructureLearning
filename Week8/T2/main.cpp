#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

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

    //get data
    Data m_GetData()
    {
        return m_Data;
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

    //function:cout the tree in the form of a link
    void m_PrintTree()
    {
        m_Root -> m_Print();
        if(m_LeftSon != NULL || m_RightSon != NULL)
        {
                std::cout << "(";
            if(m_LeftSon != NULL)
            {
                m_LeftSon -> m_PrintTree();
            }
            if(m_RightSon != NULL)
            {
                std::cout << ",";
            }
            if(m_RightSon != NULL)
            {
                m_RightSon -> m_PrintTree();
            }
                std::cout << ")";
        }
    }

    //function: print the tree by level
    void m_TraverseByLevel()
    {
        int head = 0, tail = 0;
        std::vector<BBinaryTree<Data>*> queue;
        queue.push_back(this);
        while(head <= tail)
        {
            queue[head] -> m_Root -> m_Print();
            std::cout << " ";
            if(queue[head] -> m_LeftSon != NULL)
            {
                tail ++;
                queue.push_back(queue[head] -> m_LeftSon);
            }
            if(queue[head] -> m_RightSon != NULL)
            {
                tail ++;
                queue.push_back(queue[head] -> m_RightSon);
            }
            head ++;
        }
    }



    //traverse
    void m_Traverse_Pre()
    {
        //root -> left -> right
        m_Root -> m_Print();
        if(m_LeftSon != NULL)
        {
            m_LeftSon -> m_Traverse_Pre();
        }
        if(m_RightSon != NULL)
        {
            m_RightSon -> m_Traverse_Pre();
        }

    }

    void m_Traverse_Middle()
    {
        //left -> root ->right
        if(m_LeftSon != NULL)
        {
            m_LeftSon -> m_Traverse_Middle();
        }
        m_Root -> m_Print();
        
        if(m_RightSon != NULL)
        {
            m_RightSon -> m_Traverse_Middle();
        }
    }


    void m_Traverse_Back()
    {
        //left->right->middle
        if(m_LeftSon != NULL)
        {
            m_LeftSon -> m_Traverse_Back();
        }
        if(m_RightSon != NULL)
        {
            m_RightSon -> m_Traverse_Back();
        }
        m_Root -> m_Print();

    }

    void m_Fake_Traverse_Back()
    {
        //right->left->middle
        if(m_RightSon != NULL)
        {
            m_RightSon -> m_Fake_Traverse_Back();
        }
        if(m_LeftSon != NULL)
        {
            m_LeftSon -> m_Fake_Traverse_Back();
        }
        m_Root -> m_Print();
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

int main()
{
    BBinaryTree<char>* the_tree = NULL;
    the_tree = g_BuildBinaryTreeByTraverse();
    if(the_tree != NULL)
    {
        the_tree -> m_Traverse_Back();
        cout << "\n";
        the_tree -> m_Fake_Traverse_Back();
        delete(the_tree);
    }
    return 0;
}
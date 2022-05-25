#include <iostream>
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
            m_Height += new_son -> m_Height;
        }
        else
        {
            new_son -> m_Father = this;
            m_RightSon = new_son;
            m_Height += new_son -> m_Height;
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
};

int num_quantity = 0;
int left_son[10010] = {0};
int right_son[10010] = {0};
int son = 0; 
int father = 0;
BBinaryTree<int>* tree_list[10010] = {NULL};

int main()
{
    cin >> num_quantity;
    for(int i = 0; i <= num_quantity; i ++)
    {
        cin >> left_son[i];
    }
    for(int i = 0; i <= num_quantity; i ++)
    {
        cin >> right_son[i];
    }
    cin >> son >> father;
    for(int i = 1; i <= num_quantity; i ++)
    {
        tree_list[i] = new BBinaryTree<int>(i);
    }
    for(int i = 1; i <= num_quantity; i ++)
    {
        if(left_son[i] != 0)
        {
            tree_list[i] -> m_MergeTree(tree_list[left_son[i]], 0);
        }
        if(right_son[i] != 0)
        {
            tree_list[i] -> m_MergeTree(tree_list[right_son[i]], 1);
        }
    }
    BBinaryNode<int>* son_node = new BBinaryNode<int>(son);
    if(tree_list[father] -> m_FindNode(son_node) == NULL)
    {
        cout << "false";
    }
    else
    {
        cout << "true";
    }
    delete(son_node);
    return 0;

}
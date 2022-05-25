#include <iostream>
#include <vector>
using namespace std;

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


template <class Data>
class CCommonTree
{
//pointer
public:
    CCommonNode<Data>* m_Root{NULL};
    std::vector<CCommonTree<Data>*> m_Sons;
    int m_SonsNumber{0};
    int m_SequenceAsSon{0};
    CCommonTree<Data>* m_Father{NULL};
    int m_Height{1};

//function of changing
public:
    //construct an empty tree
    //variable:data
    CCommonTree(Data x)
    {
        m_Root = new CCommonNode<Data>(x);
    }

    //destruction
    ~CCommonTree()
    {
        for(int i = 0; i < m_SonsNumber; i ++)
        {
            delete(m_Sons[i]);
        }
    }

    //function: add a tree son
    //variable: new tree son
    void m_AddSon(CCommonTree<Data>* new_tree)
    {
        m_SonsNumber ++;
        m_Sons.push_back(new_tree);
        new_tree -> m_Father = this;
        new_tree -> m_SequenceAsSon = m_SonsNumber;
    }

};


int main()
{
    int n;
    CCommonTree<int>* the_trees[10003] = {NULL};
    cin >> n;
    for(int i = 1; i <= n ; i ++)
    {
        the_trees[i] = new CCommonTree<int>(i);
    }
    for(int i = 1; i <= n; i ++)
    {
        int father;
        cin >> father;
        if(father != 0)
        {
            the_trees[father] -> m_AddSon(the_trees[i]);
        }
    }
    for(int i = 1; i <= n; i ++)
    {
        if(the_trees[i] -> m_SonsNumber == 0)
        {
            cout << 0 << ' ';
        }
        else
        {
            int c = the_trees[i] -> m_Sons[0] -> m_Root -> m_GetData();
            cout << c <<' ';
        }
        if(the_trees[i] -> m_Father == NULL || the_trees[i] -> m_SequenceAsSon == the_trees[i] -> m_Father -> m_SonsNumber)
        {
            cout << 0 << endl;
        }
        else
        {
            int c = the_trees[i] -> m_Father -> m_Sons[the_trees[i] -> m_SequenceAsSon] -> m_Root -> m_GetData();
            cout << c << endl;
        }
    }
    return 0;
}
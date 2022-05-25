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
    int m_Length;


//functions
public:
    //empty construction and destruction
    BStack():m_Length(0){}
    ~BStack()
    {
        m_Stack.clear();
        m_Length = 0;
    }

    //function: get the top place of the stack
    //return: the char of the top place, if empty, return NULL

    Data m_GetTop()
    {

        return m_Stack[m_Length - 1];
    }

    //function: add a char to the top place of the stack
    //variable: new_element
    void m_AddTop(Data new_element)
    {
        m_Stack.push_back(new_element);
        m_Length ++;
    }

    //function: delete the top element
    void m_DeleteTop()
    {
        if(m_Length == 0)
        {
            return;
        }

        else
        {
            m_Stack.pop_back();
            m_Length --;
        }
    }
    
};

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


};

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



int main()
{
    BBinarySortTree<int>* the_tree = g_BuildTree();
    if(the_tree == NULL)
    {
        return 0;
    }
    int min;
    cin >> min;
    BBinaryNode<int>* given_node = new BBinaryNode<int>(min);
    the_tree -> m_DeleteAllBigger(given_node, the_tree -> m_Root);
    the_tree -> m_OutPut(the_tree -> m_Root);
    //delete(the_tree);
    return 0;
}
#include <iostream>
using namespace std;


class LNode
{
    //data
    private:
        int m_Element; 

    //pointer
    public:
        LNode* m_Next;
        LNode* m_Previous;

    //function
    public:

        //empty construction
        LNode():m_Element(0),m_Next(NULL), m_Previous(NULL){}

        //construct with a char
        LNode(int c):m_Element(c),m_Next(NULL), m_Previous(NULL){}

        //destruction
        ~LNode(){}

        //set element value
        //variable: new char
        void m_SetValue(const int new_value){m_Element = new_value;}

        //get element value
        //return: the element of the node
        int m_GetValue(){return m_Element;}

        //function: output the value of the node
        void m_OutPut()
        {
            std::cout << m_Element <<" ";
        }

        /*
        friend function
        function:compare the value of two nodes in ASCII
        variable:two nodes
        return: -1:first<last 0:first=last 1:first>last
        */
        friend int f_Comparison(const LNode& node_first, const LNode& node_last)
        {
            if(node_first.m_Element < node_last.m_Element)
            {
                return -1;
            }
            else if(node_first.m_Element == node_last.m_Element)
            {
                return 0;
            }
            else if(node_first.m_Element > node_last.m_Element)
            {
                return 1;
            }
        }


};


class LDoubleNodeList
{
    //data
    private:
        
        int m_Length;
        LNode* m_This;
    public:
        LNode* m_Head;
        LNode* m_Tail;

    //operation functions
    public:

        //construction
        //add the head node of the list
        LDoubleNodeList();

        //destruction
        ~LDoubleNodeList();

        //function:add one after the pointer
        //variable: flag_node:the flag, which cannot be the head; new_node:the one that will be appended after flag_node
        void m_Append(LNode* flag_node, LNode* new_node);



        //function: change the first element of the nodelist
        //variable: the pointer of the nodelist
        void m_ChangeFirst(LNode* new_first_node);
        
    //find functions
    public:

        //function:find the first one that is the same with the node
        //variable: the node you want to check
        //return: the pointer of the first node identical; no such place:NULL
        LNode* m_FindFirst(LNode* comparison_node);



        //function: reverse output the nodelist
        void m_ReverseOutPut();
};

LDoubleNodeList::LDoubleNodeList()
{
    m_Head = new LNode();
    m_This = m_Head;
    m_Tail = m_Head;
    m_Head -> m_Next = m_Head;
    m_Head -> m_Previous = m_Head;
    m_Length = 0;
}

LDoubleNodeList::~LDoubleNodeList()
{
    m_Tail -> m_Next = NULL;
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        LNode* previous = m_This;
        m_This = m_This -> m_Next;
        delete(previous);
    }
}

void LDoubleNodeList::m_Append(LNode* flag_node, LNode* new_node)
{
    LNode* old_next = flag_node -> m_Next;
    flag_node -> m_Next = new_node;
    new_node -> m_Next = old_next;
    new_node -> m_Previous = flag_node;
    if(old_next != m_Head)
    {
        old_next -> m_Previous = new_node;
    }
    else
    {
        m_Tail = new_node;
        new_node -> m_Next = m_Head;
        m_Head -> m_Previous = new_node;
    }
    m_Length ++;
}


LNode* LDoubleNodeList::m_FindFirst(LNode* comparison_node)
{
    m_This = m_Head -> m_Next;
    while(m_This != m_Head)
    {

        if(f_Comparison(*m_This, * comparison_node) == 0)
        {
            if(m_This != m_Head)
            {
                return m_This;
            }
        }
            m_This = m_This -> m_Next;
    }
    return NULL;
}


void LDoubleNodeList::m_ReverseOutPut()
{
    if(m_Head == m_Tail)
    {
        cout << "\n";
        return;
    }
    m_This = m_Tail;
    while(m_This -> m_Previous != m_Head)
    {
        if(m_This != m_Head)
        {
            m_This -> m_OutPut();
        }
        m_This = m_This -> m_Previous;
    }
    m_This -> m_OutPut();
    cout << "\n";
}

void LDoubleNodeList::m_ChangeFirst(LNode* new_first_node)
{
    if(new_first_node == m_Head || new_first_node == m_Head -> m_Next)
    {
        return;
    }
    LNode* previous = new_first_node -> m_Previous;
    LNode* old_tail = m_Tail;
    LNode* old_first = m_Head -> m_Next;

    old_tail -> m_Next = old_first;
    old_first -> m_Previous = old_tail;
    m_Head -> m_Next = new_first_node;
    new_first_node -> m_Previous = m_Head;
    previous -> m_Next = m_Head;
    m_Head -> m_Previous = previous;
    m_Tail = previous;
}


int main()
{
    LDoubleNodeList* main_list = new LDoubleNodeList();
    int length;
    cin >> length;
    for(int i = 1; i <= length; i ++)
    {
        int temp_num;
        cin >> temp_num;
        LNode* new_node = new LNode(temp_num);
        main_list -> m_Append(main_list -> m_Tail, new_node);
    }
    int want;
    cin >> want;
    LNode node_want(want);

    LNode* new_first = main_list -> m_FindFirst(&node_want);
    main_list -> m_ChangeFirst(new_first -> m_Next);
    main_list -> m_ReverseOutPut();
    delete(main_list);
    return 0;
}
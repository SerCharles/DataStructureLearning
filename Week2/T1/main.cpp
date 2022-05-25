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


class LNodeList
{
    //data
    private:
        LNode* m_Head;
        int m_Length;
        LNode* m_This;
    public:
        LNode* m_Tail;

    //operation functions
    public:

        //construction
        //add the head node of the list
        LNodeList();

        //destruction
        ~LNodeList();

        //function:add one after the pointer
        //variable: flag_node:the flag, which cannot be the head; new_node:the one that will be appended after flag_node
        void m_Append(LNode* flag_node, LNode* new_node);

        //function:delete one at the pointer
        //variable: the node that will be deleted
        void m_Delete(LNode* flag_node);

        //function:reverse the list
        void m_Reverse();

        //function:left shift the list
        //variable:the distance of the shift
        void m_LeftShift(int distance);


    //find functions
    public:
        //function:find the xth element of the nodelist
        //variable: the number x
        //return: the pointer of the node
        LNode* m_FindAtPlace(int place);

        //function:find the first one that is the same with the node
        //variable: the node you want to check
        //return: the pointer of the first node identical; no such place:NULL
        LNode* m_FindFirst(LNode* comparison_node);

        //function:find the first one that is the same with the node
        //variable: the node you want to check
        //return: the place of the first node identical; no such place: -1
        int m_FindFirst(LNode* comparison_node, int a);



        //function:return the length
        //return:length
        int m_GetLength();

        //function:output
        void m_OutPut();



    //friend functions
        //function: get the union of two ordered nodelists
        //return:new nodelist of the union, empty:null
        //variable: the two you want to calculate
        friend LNodeList* f_GetUnion(LNodeList& a, LNodeList& b);

        //function: get the union of two ordered nodelists
        //return:new nodelist of the union, empty:null
        //variable: the two you want to calculate
        friend LNodeList* f_GetIntersection(LNodeList& a, LNodeList& b);
};


LNodeList::LNodeList()
{
    m_Head = new LNode();
    m_This = m_Head;
    m_Tail = m_Head;
    m_Length = 0;
}

LNodeList::~LNodeList()
{
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        LNode* previous = m_This;
        m_This = m_This -> m_Next;
        delete(previous);
    }
}

void LNodeList::m_Append(LNode* flag_node, LNode* new_node)
{
    LNode* old_next = flag_node -> m_Next;
    flag_node -> m_Next = new_node;
    new_node -> m_Next = old_next;
    new_node -> m_Previous = flag_node;
    if(old_next != NULL)
    {
        old_next -> m_Previous = new_node;
    }
    else
    {
        m_Tail = new_node;
    }
    m_Length ++;
}

void LNodeList::m_Delete(LNode* flag_node)
{
    LNode* old_next = flag_node -> m_Next;
    LNode* old_previous = flag_node -> m_Previous;
    if(old_next != NULL)
    {
        old_next -> m_Previous = old_previous;
    }
    else
    {
        m_Tail = old_previous;
    }
    if(old_previous != NULL)
    {
        old_previous -> m_Next = old_next;
    }
    delete(flag_node);
    m_Length --;
}

void LNodeList::m_Reverse()
{
    if(m_Head == m_Tail)
    {
        return;
    }
    m_This = m_Tail;
    LNode* previous = m_Head;
    while(m_This -> m_Previous != m_Head)
    {
        LNode* new_this = m_This -> m_Previous;
        LNode* new_previous = m_This;
        m_This -> m_Previous = previous;
        previous -> m_Next = m_This;
        m_This = new_this;
        previous = new_previous;
    }
    previous -> m_Next = m_This;
    m_This -> m_Previous = previous;
    m_This -> m_Next = NULL;
    m_Tail = m_This;
}

void LNodeList::m_LeftShift(int distance)
{
    if(m_Length == 0)
    {
        return;
    }
    distance = distance % m_Length;
    if(distance == 0)
    {
        return;
    }
    m_This = m_Head;
    int place = 0;
    while(1)
    {
        if(place == distance + 1)
        {
            break;
        }
        else 
        {
            m_This = m_This -> m_Next;
            place ++;
        }
    }

    LNode* previous = m_This -> m_Previous;
    LNode* old_first = m_Head -> m_Next;

    m_Head -> m_Next = m_This;
    m_This -> m_Previous = m_Head;
    m_Tail -> m_Next = old_first;
    old_first -> m_Previous = m_Tail;
    previous -> m_Next = NULL;
    m_Tail = previous;   
}

LNode* LNodeList::m_FindAtPlace(int place)
{
    int place_now = 0;
    if(place < 0 || place > m_Length)
    {
        return NULL;
    }
    m_This = m_Head;
    while(place_now < place)
    {
        m_This = m_This -> m_Next;
        place_now ++;
    }
    return m_This;
}

LNode* LNodeList::m_FindFirst(LNode* comparison_node)
{
    m_This = m_Head;
    while(m_This != NULL)
    {

        if(f_Comparison(*m_This, * comparison_node) == 0)
        {
            if(m_This != m_Head)
            {
                return m_This;
            }
        }
        if(m_This -> m_Next != NULL)
        {
            m_This = m_This -> m_Next;
        }
        else
        {
            m_This = NULL;
        }
    }
    return NULL;
}

int LNodeList::m_FindFirst(LNode* comparison_node, int a)
{
    m_This = m_Head;
    int place = 0;
    while(m_This != NULL)
    {
        
        if(f_Comparison(*m_This, *comparison_node) == 0)
        {
            if(m_This != m_Head)
            {
                return place;
            }
        }
        if(m_This -> m_Next != NULL)
        {
            m_This = m_This -> m_Next;
            place ++;
        }
        else
        {
            m_This = NULL;
        }
    }
    return -1;
}

int LNodeList::m_GetLength()
{
    return m_Length;
}

void LNodeList::m_OutPut()
{
    if(m_Head == m_Tail)
    {
        cout << "\n";
        return;
    }
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        if(m_This != m_Head)
        {
            m_This -> m_OutPut();
        }
        m_This = m_This -> m_Next;
    }
    m_This -> m_OutPut();
    cout << "\n";
}

LNodeList* f_GetIntersection(LNodeList& a, LNodeList& b)
{
    if(a.m_Head == a.m_Tail || b.m_Head == b.m_Tail)
    {
        return NULL;
    }

    LNodeList* answer = new LNodeList();
    LNode* flag_a = a.m_Head -> m_Next;
    LNode* flag_b = b.m_Head -> m_Next;
    while(flag_a != NULL && flag_b != NULL)
    {
        if(f_Comparison(*flag_a, *flag_b) == -1)
        {
            flag_a = flag_a -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 0)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
            flag_b = flag_b -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 1)
        {
            flag_b = flag_b -> m_Next;
        }
    }

    return answer;
}

LNodeList* f_GetUnion(LNodeList& a, LNodeList& b)
{
    if(a.m_Head == a.m_Tail && b.m_Head == b.m_Tail)
    {
        return NULL;
    }
    else if(a.m_Head == a.m_Tail)
    {
        return &b;
    }
    else if(b.m_Head == b.m_Tail)
    {
        return &a;
    }

    LNodeList* answer = new LNodeList();
    LNode* flag_a = a.m_Head -> m_Next;
    LNode* flag_b = b.m_Head -> m_Next;
    while(flag_a != NULL || flag_b != NULL)
    {
        if(flag_a == NULL)
        {
            LNode* new_node = new LNode(*flag_b);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_b = flag_b -> m_Next;
            continue;
        }
        else if(flag_b == NULL)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
            continue;
        }


        if(f_Comparison(*flag_a, *flag_b) == -1)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 0)
        {
            LNode* new_node = new LNode(*flag_a);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_a = flag_a -> m_Next;
            flag_b = flag_b -> m_Next;
        }
        else if(f_Comparison(*flag_a, *flag_b) == 1)
        {
            LNode* new_node = new LNode(*flag_b);
            answer -> m_Append(answer -> m_Tail, new_node);
            flag_b = flag_b -> m_Next;
        }

    }

    return answer;
}




int main()
{
    LNodeList* main_list = new LNodeList();
    int num_of_list, num_of_operation;
    cin >> num_of_list >> num_of_operation;
    for(int i = 1; i <= num_of_list; i ++)
    {
        int temp_num;
        cin >> temp_num;
        LNode* new_node = new LNode(temp_num);
        main_list -> m_Append(main_list -> m_Tail, new_node);
    }

    for (int i = 1; i <= num_of_operation; i ++)
    {
        int operation;
        cin >> operation;
        if(operation == 1)
        {
            int temp_place;
            int new_num;
            cin >> temp_place >> new_num;
            LNode* place = main_list -> m_FindAtPlace(temp_place);
            LNode* new_node = new LNode(new_num);
            main_list -> m_Append(place, new_node);
        }

        if(operation == 2)
        {
            int place_want;
            int num_want;
            cin >> num_want;
            LNode node_want(num_want);
            place_want = main_list -> m_FindFirst(&node_want, 0);
            cout << place_want << endl;
        }

        if(operation == 3)
        {
            int num_want;
            cin >> num_want;
            LNode node_want(num_want);
            LNode* place_want = main_list -> m_FindFirst(&node_want);
            if(place_want == NULL)
            {
                cout << "no" <<endl;
            }
            else
            {
                main_list -> m_Delete(place_want);
                cout << "yes" <<endl;
            }
        }

        if(operation == 4)
        {
            int distance;
            cin >> distance;
            main_list -> m_LeftShift(distance);
        }

        if(operation == 5)
        {
            main_list -> m_OutPut();
        }

    }
    delete(main_list);
    return 0;
}
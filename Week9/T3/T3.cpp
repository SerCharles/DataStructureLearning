#include <cstdio>
#include <iostream>
using namespace std;


template <class Data>
class NChainNode
{
	//data
public:
	Data * m_Data{ NULL };
	Data  m_DataReal;
	//pointer
public:
	NChainNode<Data>* m_Next{ NULL };
	NChainNode<Data>* m_Previous{ NULL };

	//function
public:

	//constructions and destructions
	NChainNode<Data>() {}
	NChainNode<Data>(Data* d) : m_Data(d) {}
	NChainNode<Data>(Data d) : m_DataReal(d) {}
	~NChainNode<Data>() {}

	//set the data
	void m_SetData(const Data* new_data)
	{
		m_Data = new_data;
	}

	//function:compare the node and another
	//variable: node new
	//return: -1: this<new ,0: this==new, 1: this>new
	int m_Compare(const NChainNode<Data>* new_node)
	{
		return m_Data->m_Compare(new_node->m_Data);
	}

	Data* m_GetData()
	{
		return m_Data;
	}
	Data* m_GetDataReal()
	{
		return m_DataReal;
	}
	//print the node
	/*void m_Print()
	{
	m_Data.m_Print();
	}*/
};



template <class Data>
class NChainLink
{
	//pointer
public:
	NChainNode<Data> *m_Head, *m_Tail, *m_This;
	int m_Length;


	//function of searching
public:

	//function:return the pointer of the node at certain place
	//variable:place
	//return:pointer
	//warning: if place is invalid, return NULL
	NChainNode<Data>* m_SearchAtPlace(const int place)
	{
		if (place <= 0 || place > m_Length)
		{
			return NULL;
		}
		m_This = m_Head;
		for (int i = 1; i <= place; i++)
		{
			m_This = m_This->m_Next;
		}
		return m_This;
	}

	//function:search for the first node that is identical to the given one
	//variable:given node
	//return:pointer of the first node, if no such node, return NULL
	NChainNode<Data>* m_SearchEqual(const NChainNode<Data>* required_node)
	{
		m_This = m_Head;
		while (m_This != NULL)
		{
			if (m_This != m_Head)
			{
				if (m_This->m_Compare(required_node) == 0)
				{
					return m_This;
				}
			}
			m_This = m_This->m_Next;
		}
		return NULL;
	}




	//function of changing
public:
	//empty construction
	NChainLink()
	{
		m_Head = new NChainNode<Data>();
		m_Head->m_Next = NULL;
		m_This = m_Head;
		m_Tail = m_Head;
		m_Head->m_Previous = NULL;
		m_Length = 0;
	}

	//empty destruction
	~NChainLink()
	{
		m_This = m_Head;
		NChainNode<Data>* previous = m_This;
		while (m_This->m_Next != NULL)
		{
			previous = m_This;
			m_This = m_This->m_Next;
			delete(previous);
		}
		delete(m_This);
	}

	//function: insert a node at the back of one node
	//variable: the place you want, and the pointer of the new node 
	void m_InsertAtPlace(NChainNode<Data>* wanted_node, NChainNode<Data>* new_node)
	{
		NChainNode<Data>* old_next = wanted_node->m_Next;
		wanted_node->m_Next = new_node;
		new_node->m_Previous = wanted_node;
		new_node->m_Next = old_next;
		if (old_next == NULL)
		{
			m_Tail = new_node;
		}
		else
		{
			old_next->m_Previous = new_node;
		}
		m_Length++;
	}

	//function: delete a node at a certain place
	//variable: the node being deleted
	void m_DeleteAtPlace(NChainNode<Data>* wanted_node)
	{
		if (wanted_node == m_Head)
		{
			return;
		}
		NChainNode<Data>* old_next = wanted_node->m_Next;
		NChainNode<Data>* old_previous = wanted_node->m_Previous;
		old_previous->m_Next = old_next;
		if (old_next != NULL)
		{
			old_next->m_Previous = old_previous;
		}
		else
		{
			m_Tail = old_previous;
		}
		m_Length -= 1;
	}

	//maybe useful: sort
};



/*
    function: search a node in a doublechainlink
    variable: the chainlink, the data you want
    return: the place
    if not, return NULL
*/
template <class Data>
void g_BBinarySearchDoubleLink(NChainLink<Data>* link, Data wanted, bool& whether_success, int& answer)
{
    static NChainNode<Data>* flag = link ->m_Head->m_Next;
    link->m_Tail->m_Next = link->m_Head ->m_Next;
    int num = 0;
    int whether_always_bigger = -1;//initial
    while(1)
    {
        num ++;
        if(wanted == flag -> m_DataReal)
        {
            answer = num;
            whether_success = 1;
            return;
        }
        else if(wanted > flag -> m_DataReal)
        {
            if(whether_always_bigger == 0)
            {
                answer = num;
                whether_success = 0;
                return;
            }
            else if(flag == link -> m_Tail)
            {
                answer = num + 1;
                whether_success = 0;
                flag = link->m_Head->m_Next;
                return;
            }
            whether_always_bigger = 1;
            flag = flag->m_Next;
        }
        else
        {
            if(whether_always_bigger == 1)
            {
                answer = num;
                whether_success = 0;
                return;
            }
            if(flag == link -> m_Head ->m_Next)
            {
                answer = num + 1;
                whether_success = 0;
                flag = link->m_Tail;
                return;
            }
            whether_always_bigger = 0;
            flag = flag->m_Previous;
        }
    }

}


int main()
{
    int n;
    scanf("%d",&n);

    int m;
    scanf("%d",&m);

    NChainLink<int>* the_link = new NChainLink<int>();
    for(int i = 1; i <= n; i ++)
    {
        int c;
        scanf("%d", &c);
        NChainNode<int>* new_node = new NChainNode<int>(c);
        the_link -> m_InsertAtPlace( the_link->m_Tail, new_node);
    }
    


    for(int i = 1; i <= m; i ++)
    {
        int wanted;
        scanf("%d", &wanted);
        if(n == 0)
        {
            printf("0 0\n");
        }
        else
        {
            int ans;
            bool whether;
            g_BBinarySearchDoubleLink(the_link, wanted,whether,ans);
            printf("%d %d\n",whether,ans);
        }
    }

    the_link->m_Tail->m_Next = NULL;
    delete(the_link);
    return 0;


}
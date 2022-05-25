#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class PNode
{
    //data
    private:
        int m_Coefficient;
        int m_Grade; 


    //pointer
    public:
        PNode* m_Next;
        PNode* m_Previous;

    //function
    public:

        //empty construction
        PNode():m_Coefficient(0),m_Grade(1),m_Next(NULL), m_Previous(NULL){}
        PNode(int coefficient, int grade):m_Coefficient(coefficient), m_Grade(grade), m_Next(NULL), m_Previous(NULL){}
        //destruction
        ~PNode(){}

        //get element value
        //return: the element of the node
        long long int m_CalculateValue(int number)
        {
            int i;
            long long int answer = 1;
            for(i = 1; i <= m_Grade; i ++)
            {
                answer *= number;
            }
            answer *= m_Coefficient;
            return answer;

        }

        //judge whether the grade of it is odd or even
        //return: odd 1, even 0;
        bool m_JudgeOddAndEven()
        {
            if(m_Grade == 0)
            {
                return 0;
            }
            if(m_Grade % 2 == 0)
            {
                return 0;
            }
            return 1;
        }

        //function: output the value of the node
        void m_OutPut()
        {
            if(m_Coefficient == 0)
            {
                return;
            }
            else if(m_Coefficient == 1 && m_Grade == 1)
            {
                std::cout << "x";
            }
            else if(m_Grade == 1)
            {
                std::cout << m_Coefficient << "x";
            }
            else if(m_Grade == 0)
            {
                std::cout << m_Coefficient;
            }
            else if (m_Coefficient == 1)
            {
                std::cout << "x^" << m_Grade;
            }
            else 
            {
                std::cout << m_Coefficient << "x^" << m_Grade;
            }
        }

        /*
        friend function
        function:compare the grade of two nodes 
        variable:two nodes
        return: -1:first<last 0:first=last 1:first>last
        */
        friend int f_Comparison(const PNode& node_first, const PNode& node_last)
        {
            if(node_first.m_Grade < node_last.m_Grade)
            {
                return -1;
            }
            else if(node_first.m_Grade == node_last.m_Grade)
            {
                return 0;
            }
            else if(node_first.m_Grade > node_last.m_Grade)
            {
                return 1;
            }
        }

        /*
        friend function
        function:when two node has the same grade, add their coefficient together
        variable:two nodes
        return: the new node
        */
        friend PNode* f_Merge(const PNode& node_first, const PNode& node_last)
        {
            PNode* new_node = new PNode(node_first.m_Coefficient + node_last.m_Coefficient, node_first.m_Grade);
            return new_node;
        }


};


class PPolynomial
{
    //data
    private:
        PNode* m_Head;
        int m_Length;
        PNode* m_This;
    public:
        PNode* m_Tail;

    //operation functions
    public:

        //construction
        //add the head node of the list
        PPolynomial();

        //destruction
        ~PPolynomial();

        //function:add one after the pointer
        //variable: flag_node:the flag, which cannot be the head; new_node:the one that will be appended after flag_node
        void m_Append(PNode* flag_node, PNode* new_node);


    //find functions
    public:

        //function:find all the Odd Numbers and Even Numbers and store them in a two polynomial
        //variables: new odd_polynomial and even_polynomial, best be empty
        void m_FindOddAndEven(PPolynomial*& odd_polynomial, PPolynomial*& even_polynomial);


        //function: output the Polynomial
        void m_OutPut();

        
        //function:calculate the overall value of the polynomial
        //variable: the number of x
        //return: value
        long long int m_CalculateValue(int number);
};


PPolynomial::PPolynomial()
{
    m_Head = new PNode();
    m_This = m_Head;
    m_Tail = m_Head;
    m_Length = 0;
}

PPolynomial::~PPolynomial()
{
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        PNode* previous = m_This;
        m_This = m_This -> m_Next;
        delete(previous);
    }
}

void PPolynomial::m_Append(PNode* flag_node, PNode* new_node)
{
    PNode* old_next = flag_node -> m_Next;
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



void PPolynomial::m_OutPut()
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
            cout << "+";
        }      
        m_This = m_This -> m_Next;
    }
    m_This -> m_OutPut();
    cout << "\n";
}

void PPolynomial::m_FindOddAndEven(PPolynomial*& odd_polynomial, PPolynomial*& even_polynomial)
{
    if(odd_polynomial != NULL)
    {
        delete odd_polynomial;
    }
    odd_polynomial = new PPolynomial();

    if(even_polynomial != NULL)
    {
        delete even_polynomial;
    }
    even_polynomial = new PPolynomial();

    if(m_Head == m_Tail)
    {
        return;
    }
    m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        if(m_This != m_Head)
        {
            if(m_This -> m_JudgeOddAndEven() == 1)
            {
                PNode* new_node = new PNode(*m_This);
                odd_polynomial -> m_Append(odd_polynomial -> m_Tail, new_node);
            }
            else
            {
                PNode* new_node = new PNode(*m_This);
                even_polynomial -> m_Append(even_polynomial -> m_Tail, new_node);
            }
        }
        m_This = m_This -> m_Next;
    }

    if(m_This -> m_JudgeOddAndEven() == 1)
    {
        PNode* new_node = new PNode(*m_This);
        odd_polynomial -> m_Append(odd_polynomial -> m_Tail, new_node);
    }
    else
    {
        PNode* new_node = new PNode(*m_This);
        even_polynomial -> m_Append(even_polynomial -> m_Tail, new_node);
    }

}

long long int PPolynomial::m_CalculateValue(int number)
{
    long long int ans = 0;
    if(m_Head == m_Tail)
    {
        return ans;
    }
     m_This = m_Head;
    while(m_This -> m_Next != NULL)
    {
        if(m_This != m_Head)
        {
            ans += m_This -> m_CalculateValue(number);
        }
        m_This = m_This -> m_Next;
    }
    ans += m_This -> m_CalculateValue(number);
    return ans;
}

int g_SwitchCharToInt(char c[], int start, int end)
{
    int answer = 0;
    int coefficient = 1;
    for(int i = end; i >= start; i --)
    {
        int temp_num = c[i]- '0';
        answer += temp_num * coefficient;
        coefficient *= 10;
    }
    return answer;
}


int main()
{
    PPolynomial* main_list = new PPolynomial();

    char formula[120];
    cin >> formula;
    int length = strlen(formula);
    vector<int> flag_start;
    vector<int> flag_end;
    for (int i = 0; i < length; i ++)
    {
        if(i == 0)
        {
            flag_start.push_back(i);
        }
        else if (i == length - 1)
        {
            flag_end.push_back(i);
        }
        else
        {
            if(formula[i] == '+')
            {
                flag_end.push_back(i-1);
                flag_start.push_back(i+1);
            }
        }
    }

    int node_number = flag_start.size();
    for(int i = 0; i < node_number; i ++)
    {
        bool whether_has_x = 0;
        bool whether_grade_exceeds_1 = 0;
        int coefficient;
        int grade;
        for(int j = flag_start[i]; j <= flag_end[i]; j ++)
        {
            if(formula[j] == 'x')
            {
                whether_has_x = 1;
                if(j == flag_start[i])
                {
                    coefficient = 1;
                }
                else
                {
                    coefficient = g_SwitchCharToInt(formula, flag_start[i], j-1);
                }
            }

            if(formula[j] == '^')
            {
                whether_grade_exceeds_1 = 1;
                grade  = g_SwitchCharToInt(formula, j+1, flag_end[i]);
            }
        }
        if(whether_has_x == 0)
        {
            grade = 0;
            coefficient = g_SwitchCharToInt(formula, flag_start[i], flag_end[i]);
        }
        else if(whether_grade_exceeds_1 == 0)
        {
            grade = 1;
        }
        PNode* new_node = new PNode(coefficient, grade);
        main_list -> m_Append(main_list -> m_Tail, new_node);
    }

    PPolynomial* odd_list = NULL;
    PPolynomial* even_list = NULL;
    main_list -> m_FindOddAndEven(odd_list, even_list);
    odd_list -> m_OutPut();
    even_list -> m_OutPut();
    return 0;
}
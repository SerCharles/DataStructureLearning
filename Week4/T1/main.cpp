#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class PStack
{
//data
private:
    std::vector <char> m_Stack;
public:
    int m_length;


//functions
public:
    //empty construction and destruction
    PStack():m_length(1)
    {
        m_Stack.push_back('#');
    }
    ~PStack()
    {
        m_Stack.clear();
        m_length = 0;
    }

    //function: get the top place of the stack
    //return: the char of the top place, if empty, return -1

    char m_GetTop()
    {
        if(m_length == 0)
        {
            return -1;
        }
        return m_Stack[m_length - 1];
    }

    //function: add a char to the top place of the stack
    //variable: new_element
    void m_AddTop(char new_element)
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

class NumberAndMark
{
    public:
        //0:mark 1:number
        bool m_Type;

        //if mark: 1:+, 2:-, 3:*, 4:/
        int m_Number;
    NumberAndMark(int t, int m):m_Type(t),m_Number(m){}
};


class PolandFormula
{
    //data
    private:
        int m_Answer;
        //-1:+, -2:-,  -3:*,  -4:/
        std::vector <NumberAndMark> m_Numbers;
        PStack m_MarkStack;


    //functions
    public:

        //empty construction and destruction
        PolandFormula():m_Answer(0){}
        ~PolandFormula(){}

        //build the poland formula through inputing a char
        void m_Build();

        //calculate the answer of the poland formula
        void m_Calculate();

        //return answer
        //return: answer
        int m_GetAnswer()
        {
            return m_Answer;
        }

};

//function: judge the priority of two marks
//variable: new mark and old mark(at stack top)
//return: new>old:1  new<old:0  
extern bool g_JudgePriority(char new_one, char old_one);


//function: switch a char to int
//variable: the char, start position, end position
//return : the int
extern int g_SwitchCharToInt(char c[], int start, int end);





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

//todo
bool g_JudgePriority(char new_one, char old_one)
{
    if(new_one == '+' || new_one == '-')
    {
        if( old_one == '#')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(new_one == '*' || new_one == '/')
    {
        if(old_one == '*' || old_one == '/')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if(new_one == '#')
    {
        if(old_one == '#')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }


}

void PolandFormula::m_Build()
{
    char formula_list[2300] = {0};
    cin >> formula_list;
    int length = strlen(formula_list);
    int flag_before = 0, flag_after = 0;
    formula_list[length] = '#';
    for(int i = 0; i <= length; i ++)
    {
        if(formula_list[i] > '9' || formula_list[i] < '0')
        {
            //switch char to int
            if(formula_list[i - 1] >='0' && formula_list[i - 1] <= '9')
            {
                flag_after = i - 1;
                NumberAndMark new_num(1, g_SwitchCharToInt(formula_list, flag_before, flag_after));
                m_Numbers.push_back(new_num);
            }
            if(formula_list[i + 1] >='0' && formula_list[i + 1] <= '9')
            {
                flag_before = i + 1;
                flag_after = i + 1;
            }


            while(1)
            {
                char old_top = m_MarkStack.m_GetTop();
                if(g_JudgePriority(formula_list[i], old_top) == 1)
                {
                    m_MarkStack.m_AddTop(formula_list[i]);
                    break;
                }
                else
                {
                    m_MarkStack.m_DeleteTop();
                    int mark_type = 0;
                    if(old_top == '+')
                    {
                        mark_type = 1;
                    }
                    if(old_top == '-')
                    {
                        mark_type = 2;
                    }
                    if(old_top == '*')
                    {
                        mark_type = 3;
                    }
                    if(old_top == '/')
                    {
                        mark_type = 4;
                    }
                    if(mark_type != 0)
                    {
                        NumberAndMark new_mark(0,mark_type);
                        m_Numbers.push_back(new_mark);
                    }

                }
            }

        }

    }
}


//todo
void PolandFormula::m_Calculate()
{
    for(int i = 0; i < m_Numbers.size(); i ++)
    {
        if(m_Numbers[i].m_Type == 0)
        {
            int num_prior = m_Numbers[i - 2].m_Number;
            int num_latter = m_Numbers[i - 1].m_Number;
            if(m_Numbers[i].m_Number == 1)
            {
                m_Numbers[i].m_Number = num_prior + num_latter;
            }
            else if(m_Numbers[i].m_Number == 2)
            {
                m_Numbers[i].m_Number = num_prior - num_latter;
            }
            else if(m_Numbers[i].m_Number == 3)
            {
                m_Numbers[i].m_Number = num_prior * num_latter;
            }
            else if(m_Numbers[i].m_Number == 4)
            {
                m_Numbers[i].m_Number = num_prior / num_latter;
            }
            m_Numbers[i].m_Type = 1;
            m_Numbers.erase(m_Numbers.begin() + i - 1);
            m_Numbers.erase(m_Numbers.begin() + i - 2);
            i -= 2;
        }
    }
    m_Answer = m_Numbers[0].m_Number;
}

int main()
{
    PolandFormula* the_formula = new PolandFormula();
    the_formula -> m_Build();
    the_formula -> m_Calculate();
    cout << the_formula -> m_GetAnswer();
    delete(the_formula);
    return 0;
}

/*
    filename: BBracket.cpp
    description: the class used to judge whether a bracket is available
    date: 10/12/2018
*/


#include <vector>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

#include "PStack.hpp"
#include "BBracket.h"

bool g_JudgeMatch(char front, char back)
{
    if(front == '(')
    {
        if(back == ')')
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }

    if(front == '[')
    {
        if(back == ']')
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }

    if(front == '{')
    {
        if(back == '}')
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }


}



BBracket::BBracket()
{
    m_ValidNumber = 0;
    m_UnknownNumber = 0;
    m_BracketNumberLeft[1] = 0;
    m_BracketNumberLeft[2] = 0;
    m_BracketNumberLeft[3] = 0;
    m_BracketNumberRight[1] = 0;
    m_BracketNumberRight[2] = 0;
    m_BracketNumberRight[3] = 0;

    m_Length = 0;
    cin >> m_InputList;
    m_BracketList = m_InputList;
    m_Length = m_InputList.length();
    for(int i = 0; i < m_Length; i ++)
    {
        if(m_InputList[i] == '(')
        {
            m_BracketNumberLeft[1] ++;
        }
        if(m_InputList[i] == '[')
        {
            m_BracketNumberLeft[2] ++;
        }
        if(m_InputList[i] == '{')
        {
            m_BracketNumberLeft[3] ++;
        }
        if(m_InputList[i] == ')')
        {
            m_BracketNumberRight[1] ++;
        }
        if(m_InputList[i] == ']')
        {
            m_BracketNumberRight[2] ++;
        }
        if(m_InputList[i] == '}')
        {
            m_BracketNumberRight[3] ++;
        }
        if(m_InputList[i] == '?')
        {
            m_UnknownNumber ++;
            m_UnknownPlaceList.push_back(i);
        }
    }
}

void BBracket::m_GenerateBrackets()
{
    //odd: impossible
    if(m_Length % 2 == 1)
    {
        return;
    }
    //impossible
    if(m_BracketList[0] != '?' && m_BracketList[m_BracketList.size() - 1] != '?' && g_JudgeMatch(m_BracketList[0], m_BracketList[m_BracketList.size() - 1]) == 0)
    {
        return;
    }

    m_GetVitalBracketNumber();

    m_EnumBracketNumber();

}

void BBracket::m_GetVitalBracketNumber()
{
    int gap_bracket[4];
    for(int i = 1; i <= 3; i ++)
    {
        gap_bracket[i] = m_BracketNumberLeft[i] - m_BracketNumberRight[i];
    }

    a_FreeGroup = (m_UnknownNumber - abs(gap_bracket[1]) - abs(gap_bracket[2]) - abs(gap_bracket[3])) / 2;
    
    for(int i = 1; i <= 3; i ++)
    {
        if(gap_bracket[i] >= 0)
        {
            a_RequireBracketLeft[i] = 0;
            a_RequireBracketRight[i] = gap_bracket[i];
        }
        if(gap_bracket[i] < 0)
        {
            a_RequireBracketLeft[i] = 0 - gap_bracket[i];
            a_RequireBracketRight[i] = 0;
        }
    }

}

void BBracket::m_EnumBracketNumber()
{
    if(a_FreeGroup == 0)
    {
        m_EnumBracketList();
        return;
    }

    else
    {
        for(int i = 1; i <= 3; i ++)
        {
            a_FreeGroup -= 1;
            a_RequireBracketLeft[i] ++;
            a_RequireBracketRight[i] ++;

            m_EnumBracketNumber();

            a_FreeGroup += 1;
            a_RequireBracketLeft[i] --;
            a_RequireBracketRight[i] --;
        }
    }

}

void BBracket::m_EnumBracketList()
{
    if(m_UnknownNumber == 0)
    {
        if(m_JudgeValid())
        {
            m_ValidNumber ++;
            m_AnswerList.push_back(m_BracketList);
        }
        return;
    }

    for(int i = 1; i <= 6; i ++)
    {
        if(i <= 3)
        {
            if(a_RequireBracketLeft[i] > 0)
            {
                a_RequireBracketLeft[i] --;
                m_UnknownNumber --;
                if(i == 1)
                {
                    m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = '(';
                }
                else if(i == 2)
                {
                    m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = '[';
                }
                else if(i == 3)
                {
                    m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = '{';
                }

                m_EnumBracketList();

                a_RequireBracketLeft[i] ++;
                m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = '?';
                m_UnknownNumber ++;
            }
        }

        else
        {
            if(a_RequireBracketRight[i - 3] > 0)
            {
                a_RequireBracketRight[i - 3] --;
                m_UnknownNumber --;
                if(i == 4)
                {
                    m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = ')';
                }
                else if(i == 5)
                {
                    m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = ']';
                }
                else if(i == 6)
                {
                    m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = '}';
                }

                m_EnumBracketList();


                a_RequireBracketRight[i - 3] ++;
                m_BracketList[m_UnknownPlaceList[m_UnknownNumber]] = '?';
                m_UnknownNumber ++;
            }
        }


    }




}

bool BBracket::m_JudgeValid()
{
    for(int i = 0; i < m_Length; i ++)
    {
        if(m_BracketList[i] == '(' || m_BracketList[i] == '[' || m_BracketList[i] == '{')
        {
            m_Stack.m_AddTop(m_BracketList[i]);
        }
        else
        {
            char stack_top = m_Stack.m_GetTop();

            //empty stack
            if(stack_top == -1)
            {
                m_Stack.m_Clear();
                return 0;
            }

            //match
            else if (g_JudgeMatch(stack_top, m_BracketList[i]))
            {
                m_Stack.m_DeleteTop();

            }

            //unmatch
            else
            {
                m_Stack.m_Clear();
                return 0;
            }
        }
    }

    //empty
    if(m_Stack.m_Length == 0)
    {
        return 1;
    }

    //no empty
    else
    {
        m_Stack.m_Clear();
        return 0;
    }
}


void BBracket::m_EliminateRepeat()
{
    if(m_ValidNumber == 0)
    {
        return;
    }
    for(int i = 0; i < m_AnswerList.size() - 1; i ++)
    {
        for(int j = i + 1; j < m_AnswerList.size(); j ++)
        {
            if(m_AnswerList[i] == m_AnswerList[j])
            {
                m_AnswerList.erase(m_AnswerList.begin() + j);
                j --;
            }
        }
    }
    m_ValidNumber = m_AnswerList.size();
}
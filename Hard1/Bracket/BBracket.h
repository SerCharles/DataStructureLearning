/*
    filename: BBracket.h
    description: the class used to judge whether a bracket is available
    date: 10/12/2018
*/

#ifndef BBRACKET_H
#define BBRACKET_H

#include <vector>
#include <string>

#include "PStack.hpp"


class BBracket
{
//data
private:
    std::string m_BracketList;
    std::string m_InputList;
    int m_Length;
    int m_BracketNumberLeft[4];
    int m_BracketNumberRight[4];
    int m_UnknownNumber;
    std::vector<int> m_UnknownPlaceList;
    std::vector<std::string> m_AnswerList;


    PStack m_Stack;
    int m_ValidNumber;

//auxilliary data
private:
    int a_RequireBracketLeft[4];
    int a_RequireBracketRight[4];
    int a_FreeGroup;



//function
public:
    //construct the list through input
    BBracket();

    //destrcution
    ~BBracket()
    {
        m_BracketList.clear();
        m_InputList.clear();
        m_UnknownPlaceList.clear();
        m_AnswerList.clear();
    }

    //generate all valid bracketlist

    //general function
    void m_GenerateBrackets();

    //get vital bracket numbers
    void m_GetVitalBracketNumber();

    //enum bracket number
    void m_EnumBracketNumber();

    //enum bracket list
    void m_EnumBracketList();

    //judge and elimiate repeat
    void m_EliminateRepeat();

    //judge whether it is valid
    //return: 1:valid, 0:invalid
    bool m_JudgeValid();

    //return the valid number
    int m_GetValidNumber()
    {
        return m_ValidNumber;
    }
};


extern bool g_JudgeMatch(char front, char back);



#endif
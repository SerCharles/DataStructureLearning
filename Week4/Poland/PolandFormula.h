/*
    filename:PolandFormula.h
    description:Poland Formula, used to store and calculate a formula
    date: 10/9/2018
*/

#ifndef POLANDFORMULA_H
#define POLANDFORMULA_H

#include <iostream>
#include <vector>

#include "PStack.hpp"

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






#endif
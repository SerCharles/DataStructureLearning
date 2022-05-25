/*
    filename:SString.h
    description:a String that can carcat, strcmp, reverse, and strcpy
    date: 10/9/2018
*/

#ifndef SSTRING_H
#define SSTRING_H

#include <vector>

class SString
{
//data
private:
    std::vector<char> m_String;
    std::vector<int> m_Next;
    int m_Length;

//function    
public:
    //change the string

    //empty construction
    SString():m_Length(0){}

    //construction through a char and length
    //variable: the char list and the length
    SString(const char c[], const int l);

    //construction through input
    //variable: useless
    SString(int a);

    //uses default copy construction function

    //destruction
    ~SString();

    //function: reverse the string
    void m_ReverseString(); 


    //function: find the next function of the string, which is useful in kmp
    //remind: use it once after building or changing the string
    void m_GetNextFunction();


    //function: build a new SString from a fragment of the old SString
    //variable: begin place, end place 
    //return: new SString
    SString* m_CutString(const int start, const int end);

public:
    //find in the string


    //function: compare the two strings by ASCII order
    //variable: the string being compared
    //return: 0:this = new, -1: this < new 1:this > new
    int m_CompareString(const SString& new_string);


    //function: find the identical substring in the string, using kmp
    //variable: the string being compared
    //return: -1: no, i: the begin place of the first substring is at i
    int m_FindSubString(const SString& compared_string);

    //function: get the length of the string
    //return: length
    int m_GetLength()
    {
        return m_Length;
    }

    //function: output the string
    void m_OutPut();
};

#endif
/*
    filename: PPolynomial.h
    date:09/30/2018
    function: the description of a Polynomial
*/



#ifndef PPOLYNOMIAL_H
#define PPOLYNOMIAL_H


#include "PNode.hpp"



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


#endif
/*
    filename: PNode.hpp
    date:09/30/2018
    function: the description of a node in a polynominal
*/

#ifndef PNODE_HPP
#define PNODE_HPP

#include <iostream>


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

extern int f_Comparison(const PNode& node_first, const PNode& node_last);

extern PNode* f_Merge(const PNode& node_first, const PNode& node_last);

#endif
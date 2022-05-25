/*
    filename:QPhone.hpp
    description:Phone number
    date: 10/9/2018
*/

#ifndef QPHONE_HPP
#define QPHONE_HPP
#include <string>



class QPhone
{
    public:
        std::string m_Number;
        int m_Type;
        QPhone(std::string num, int t):m_Number(num), m_Type(t){}
};













#endif

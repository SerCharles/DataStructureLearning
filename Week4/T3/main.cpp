#include <iostream>
#include <vector>
using namespace std;

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


SString::SString(int a)
{
    m_Length = 0;
    while(1)
    {
        char temp;
        cin >> temp;
        if(temp == '@')
        {
            break;
        }
        m_String.push_back(temp);
        m_Length ++;
    }
}

SString::SString(const char c[], const int l)
{
    m_Length = l;
    for(int i = 0; i < l; i ++)
    {
        m_String.push_back(c[i]);
    }
}

SString::~SString()
{
    m_Length = 0;
    m_String.clear();
    m_Next.clear();
}

SString* SString::m_CutString(const int start, const int end)
{
    if(start < 0 || end >= m_Length)
    {
        return NULL;
    }
    SString* new_string = new SString();
    for(int i = start; i <= end; i ++)
    {
        new_string -> m_String.push_back(m_String[i]);
        new_string -> m_Length ++;
    }
    return new_string;
}

void SString::m_ReverseString()
{
    for(int i = 0; i < m_Length / 2; i ++)
    {
        char temp;
        temp = m_String[i];
        m_String[i] = m_String[m_Length - 1 - i];
        m_String[m_Length - 1 - i] = temp;
    }
}

int SString::m_CompareString(const SString& new_string)
{
    int length;
    if(m_Length <= new_string.m_Length)
    {
        length = m_Length;
    }
    else
    {
        length = new_string.m_Length;
    }

    for(int i = 0; i < length; i ++)
    {
        if(m_String[i] < new_string.m_String[i])
        {
            return -1;
        }

        if(m_String[i] > new_string.m_String[i])
        {
            return 1;
        }
    }

    if(m_Length < new_string.m_Length)
    {
        return -1;
    }
    if(m_Length == new_string.m_Length)
    {
        return 0;
    }
    if(m_Length > new_string.m_Length)
    {
        return 1;
    }
}

void SString::m_OutPut()
{
    for(int i = 0; i < m_Length; i ++)
    {
        cout << m_String[i];
    }
}

int SString::m_FindSubString(const SString& compared_string)
{
    int length_father = m_Length;
    int length_son = compared_string.m_Length;

    // the place of the pointer
    int place_father = 0;
    int place_son = 0;
    
    //comparison leap
    while(1)
    {
        //stop:
        if(place_son >= length_son)
        {
            return place_father - length_son;
        }
        else if(place_father >= length_father)
        {
            return -1;
        }

        //compare
        char char_father = m_String[place_father];
        char char_son = compared_string.m_String[place_son];
        if(char_father == char_son)
        {
            place_father ++;
            place_son ++;
        }
        else
        {
            //失效函数
            place_son = compared_string.m_Next[place_son];

            if(place_son == -1)
            {
                place_son = 0;
                place_father ++;
            }
        }
    }
}

void SString::m_GetNextFunction()
{
    m_Next.clear();
    for(int i = 0; i < m_Length; i ++)
    {
        if(i == 0)
        {
            m_Next.push_back(-1);
        }
        else if(i == 1)
        {
            m_Next.push_back(0);
        }
        else
        {
            int next_i = 0;
            for(int j = i - 1; j >= 1; j -- )
            {
                SString* sub_front = m_CutString(0, j - 1);
                SString* sub_back = m_CutString(i - j, i - 1);
                if(sub_front -> m_CompareString(*sub_back) == 0)
                {
                    next_i = j;
                    break;
                }
                delete(sub_front);
                delete(sub_back);
            }
            m_Next.push_back(next_i);
        }
    }
}


int main()
{
    SString* the_string = new SString(1);
    int middle = the_string -> m_GetLength() / 2 ;
    int back = the_string -> m_GetLength() - 1;
    SString* back_string = the_string -> m_CutString(middle, back);
    back_string -> m_ReverseString();
    back_string -> m_GetNextFunction();
    int answer = the_string -> m_FindSubString(*back_string);
    if(answer == -1)
    {
        cout << "false";
    }
    else if(answer == 0)
    {
        cout << "true";
    }
    delete(the_string);
    delete(back_string);
    return 0;
}
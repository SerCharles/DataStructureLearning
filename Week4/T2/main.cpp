#include <iostream>
#include <string>
#include <vector>
using namespace std;



class QPhone
{
    public:
        std::string m_Number;
        int m_Type;
        QPhone(std::string num, int t):m_Number(num), m_Type(t){}
};




class QQueue
{
    //data
    public:
        std::vector<QPhone> m_UnansweredCall;
        std::vector<QPhone> m_AnsweredCall;
        std::vector<QPhone> m_CalledCall;
        int m_UnansweredLength, m_AnsweredLength, m_CalledLength;


    //function
    public:
        QQueue():m_UnansweredLength(0), m_AnsweredLength(0), m_CalledLength(0){}
        ~QQueue()
        {
            m_UnansweredLength = 0;
            m_AnsweredLength = 0;
            m_CalledLength = 0;
            m_UnansweredCall.clear();
            m_AnsweredCall.clear();
            m_CalledCall.clear();
        }

        //function: add a new phone call to the back
        //variable: new number and its type
        void m_AddToBack(std::string new_number, int type);


        //function: return the last element at the back of the queue
        //variable: type of the queue
        //return: the string of the element
        std::string m_ReturnBack(int type);

        //function: delete the last element at the back of the queue
        //variable: type of the queue
        void m_DeleteBack(int type);


        //function: output the queues
        void m_OutPut();
};



void QQueue::m_AddToBack(string new_number, int type)
{
    QPhone new_node(new_number, type);
    if(type == 0)
    {
        m_UnansweredCall.push_back(new_node);
        m_UnansweredLength ++;
    }
    if(type == 1)
    {
        m_AnsweredCall.push_back(new_node);
        m_AnsweredLength ++;
    }
    if(type == 2)
    {
        m_CalledCall.push_back(new_node);
        m_CalledLength ++;
    }
}

void QQueue::m_DeleteBack(int type)
{
    if(type == 0)
    {
        if(m_UnansweredLength <= 0)
        {
            return;
        }
        m_UnansweredCall.pop_back();
        m_UnansweredLength --;
    }
    if(type == 1)
    {
        if(m_AnsweredLength <= 0)
        {
            return;
        }
        m_AnsweredCall.pop_back();
        m_AnsweredLength --;
    }
    if(type == 2)
    {
        if(m_CalledLength <= 0)
        {
            return;
        }
        m_CalledCall.pop_back();
        m_CalledLength --;
    }
}

string QQueue::m_ReturnBack(int type)
{
    if(type == 0)
    {
        return m_UnansweredCall[m_UnansweredLength - 1].m_Number;
    }
    if(type == 1)
    {
        return m_AnsweredCall[m_AnsweredLength - 1].m_Number;
    }
    if(type == 2)
    {
        return m_CalledCall[m_CalledLength - 1].m_Number;
    }
}

void QQueue::m_OutPut()
{
    for(int i = 0; i < 10; i ++)
    {
        if(m_UnansweredLength == 0)
        {
            cout << "0 ";
        }
        else
        {
            string out_string = m_ReturnBack(0);
            cout << out_string << " ";
            m_DeleteBack(0);
        }

        if(m_AnsweredLength == 0)
        {
            cout << "0 ";
        }
        else
        {
            string out_string = m_ReturnBack(1);
            cout << out_string << " ";
            m_DeleteBack(1);
        }

        if(m_CalledLength == 0)
        {
            cout << "0" << endl;
        }
        else
        {
            string out_string = m_ReturnBack(2);
            cout << out_string << endl;
            m_DeleteBack(2);
        }
    }

}


int main()
{
    QQueue* this_queue = new QQueue();
    int temp_type;
    string temp_string;
    while(cin >> temp_type)
    {
        cin >> temp_string;
        this_queue -> m_AddToBack(temp_string, temp_type);
    }
    this_queue -> m_OutPut();
    delete(this_queue);
    return 0;
}
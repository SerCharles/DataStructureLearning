#include <iostream>
#include <string>
using namespace std;

class TTrieNode
{
public:
    std::string m_String;
    TTrieNode* m_NodeList[26]{NULL};
    bool m_WhetherHasSelf{0};
public:
    TTrieNode(){}
    TTrieNode(std::string new_string):m_String(new_string){}
    TTrieNode(std::string old_string, char new_char)
    {
        m_String = old_string + new_char;
    }
    ~TTrieNode()
    {
        for(int i = 0; i < 26; i ++)
        {
            if(m_NodeList[i] != NULL)
            {
                delete(m_NodeList[i]);
            }
        }
    }
};

class TTrieTree
{
public:
    TTrieNode* m_Root{NULL};
public:

    //construction and destruction
    TTrieTree()
    {
        m_Root = new TTrieNode();
    }
    ~TTrieTree()
    {
        delete(m_Root);
    }


    void m_InsertWord(std::string new_string)
    {
        TTrieNode* current = m_Root;
        int i = 0;
        while(i < new_string.length())
        {
            int letter = new_string[i] - 'A';
            if(current -> m_NodeList[letter] == NULL)
            {
                TTrieNode* new_node = new TTrieNode(new_string);
                current -> m_NodeList[letter] = new_node;
                new_node-> m_WhetherHasSelf = 1;
                return;
            }
            else if(current -> m_NodeList[letter] ->m_String.length() - i > 1)
            {
                if(current -> m_NodeList[letter] ->m_WhetherHasSelf == 1 && new_string == current->m_NodeList[letter] ->m_String)
                {
                    return;
                }
                TTrieNode* new_node = new TTrieNode(current->m_String, new_string[i]); 
                TTrieNode* old_son = current -> m_NodeList[letter];
                current -> m_NodeList[letter] = new_node;
                std::string else_string = old_son->m_String;
                delete(old_son);

                m_InsertWord(else_string);
                current = current -> m_NodeList[letter];
                i ++;
            }
            else
            {
                //judge repeatant
                if(current -> m_NodeList[letter] ->m_WhetherHasSelf == 1 && new_string == current->m_NodeList[letter] ->m_String)
                {
                    return;
                }
                current = current -> m_NodeList[letter];
                i ++;
            }
        }     
        if(current -> m_WhetherHasSelf == 0)
        {
            current -> m_WhetherHasSelf = 1;
        }
    }

    void m_OutPut(TTrieNode* current_place)
    {
        //empty or one
            int a = 0;
            for(int i = 0; i < 26; i ++)
            {
                if(current_place->m_NodeList[i] != NULL)
                {
                    a = 1;
                    break;
                }
            }
            if(a == 0)
            {
                if(current_place -> m_WhetherHasSelf == 1)
                {
                    std::cout << current_place->m_String;
                }
                return;
            }

        //others
        std::cout << '(';
        bool whether_input = 0;

        if(current_place -> m_WhetherHasSelf == 1)
        {
            whether_input = 1;
            std::cout << current_place->m_String;
        }
        for(int i = 0; i < 26; i ++)
        {
            if(current_place->m_NodeList[i] != NULL)
            {
                if(whether_input == 1)
                {
                    std::cout <<",";
                }
                else
                {
                    whether_input = 1;
                }
                m_OutPut(current_place->m_NodeList[i]);
            }
        }
        std::cout << ')';
    }
    




};


int main()
{
    TTrieTree* the_tree = new TTrieTree();
    string main_char;
    cin >> main_char;
    main_char += ',';
    int flag = 0;
    for(int i = 0; i < main_char.length(); i ++)
    {
        if(main_char[i] > 'Z' || main_char[i] < 'A')
        {
            string new_word = main_char.substr(flag, i - flag);
            the_tree->m_InsertWord(new_word);            
            flag = i + 1;
        }
    }
    for(int i = 1; i <= 3; i ++)
    {
        string new_word;
        cin >> new_word;
        the_tree->m_InsertWord(new_word);
    }
    the_tree->m_OutPut(the_tree -> m_Root);
    delete(the_tree);
    return 0;
}
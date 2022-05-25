#include <iostream>
#include <cstdio>

int numbers[200000] = {0};

template <class Data>
class BBinarySearch
{
public:
    Data m_SearchNode;
    Data* m_SearchList;
    int m_Length;
public:
    BBinarySearch(Data list[], int length):m_SearchList(list),m_Length(length){}

    //function: binary search an increasing list
    //variable: the node you want to search
    //return : if <=1:return 0, if >=n return n, if = i, return i
    int m_Search(Data node)
    {
        m_SearchNode = node;
        if(m_SearchNode < m_SearchList[1])
        {
            return 0;
        }
        if(m_SearchNode >= m_SearchList[m_Length])
        {
            return m_Length;
        }
        int start = 1, end = m_Length;
        while(start <= end)
        {
            int mid = (start + end)/2;
            if(m_SearchNode == m_SearchList[mid])
            {
                return mid;
            }
            else if (m_SearchNode > m_SearchList[mid])
            {
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
        return end;
    }
};

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d",&numbers[i]);
    }
    BBinarySearch<int>* the_list = new BBinarySearch<int>(numbers, n);
    int m;
    scanf("%d",&m);
    for(int i = 1; i <= m; i ++)
    {
        int want;
        scanf("%d", &want);
        int ans = the_list -> m_Search(want);
        printf("%d\n", ans);
    }
    delete(the_list);
    return 0;
}
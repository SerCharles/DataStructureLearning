#include <iostream>
using namespace std;

int n, m;
int heap[210000] = {0};
int length;

void insert(int new_num)
{
    length ++;
    heap[length] = new_num;
    int place = length;
    while(1)
    {
        if(place == 1)
        {
            break;
        }
        int father = place / 2;
        if(heap[father] > heap[place])
        {
            int temp = heap[father];
            heap[father] = heap[place];
            heap[place] = temp;
            place = father;
        }
        else
        {
            break;
        }
    }
}

int main()
{
    cin >> n >> m;
    length = n;
    for(int i = 1; i <= n; i ++)
    {
        cin >> heap[i];
    }
    for(int i = 1; i <= m; i ++)
    {
        int t;
        cin >> t;
        insert(t);
    }
    for(int i = 1; i <= length; i ++)
    {
        cout << heap[i] <<" ";
    }
    return 0;

}
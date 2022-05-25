#include <stdio.h>
#include <stdlib.h>
int stack_begin[2000000] = {0};
int stack_end[2000000] = {0};
int stack_middle[2000000] = {0};
int stack_top = 0;
int list[1000] = {0};
int n;

void sort(int start, int end)
{
    for(int i = start; i < end; i ++)
    {
        for(int j = i + 1; j <= end; j ++)
        {
            if(list[i] > list[j])
            {
                int temp = list[j];
                list[j] = list[i];
                list[i] = temp;
            }
        }
    }
}

void m_qsort()
{
    int head = 1, tail = n;
    while(1)
    {
        if(tail - head < 3)
        {
            sort(head, tail);
            if(stack_top <= 0)
            {
                break;
            }
            head = stack_middle[stack_top] + 1;
            tail = stack_end[stack_top];
            stack_top --;
        }
        else
        {
            int criterion = list[head];
            int low = head, high = tail;
            while(low < high)
            {
                while(list[high] >= criterion && low < high)
                {
                    high --;
                }
                if(low < high)
                {
                    list[low] = list[high];
                    low ++;
                }
                while(list[low] <= criterion && low < high)
                {
                    low ++;
                }
                if(low < high)
                {
                    list[high] = list[low];
                    high --;
                }
            }
            list[high] = criterion;
            
            stack_top ++;
            stack_begin[stack_top] = head;
            stack_end[stack_top] = tail;
            stack_middle[stack_top] = high;
            head = head;
            tail = high - 1;
        }
    }


}

int main()
{
    scanf("%d",&n);
    for(int ii = 1; ii <= n; ii ++)
    {
        scanf("%d",&list[ii]);
    }
    
    m_qsort();

    for(int ii = 1; ii <= n; ii ++)
    {
        printf("%d ",list[ii]);
    }
    return 0;




}
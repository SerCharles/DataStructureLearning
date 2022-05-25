#include <stdio.h>
#include <stdlib.h>

int n;
int list[10000000]={0};

int main()
{
    scanf("%d",&n);
    for(int ii = 1; ii <= n; ii ++)
    {
        scanf("%d",&list[ii]);
    }
    int flag_left = 1, flag_right = n;
    while(flag_left <= flag_right)
    {    
        int i = flag_left, j = flag_right;
        while( i < flag_right && j > flag_left)
        {
            if(list[i] > list[i + 1])
            {
                int temp = list[i+1];
                list[i+1] = list[i];
                list[i] = temp;
            }
            if(list[j] < list[j - 1])
            {
                int temp = list[j - 1];
                list[j - 1]=list[j];
                list[j]=temp;
            }
            i ++;
            j --;
        }
        flag_left ++;
        flag_right --;
    }

    for(int ii = 1; ii <= n; ii ++)
    {
        printf("%d ",list[ii]);
    }
    return 0;

}
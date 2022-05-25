#include<stdio.h>

int total_num[1100000] = {0};
int total_x[1100000] = {0};
int total_y[1100000] = {0};
int hash_num[1100000][10] = {0};
int hash_x[1100000][10] = {0};
int hash_y[1100000][10] = {0};
int total[1100000] = {0};

int main()
{
    int n,m;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d %d %d",&total_x[i],&total_y[i],&total_num[i]);
        int key = (total_y[i]*131+total_x[i]*131*131)%1000000;
        total[key] ++;
        hash_num[key][total[key]] = total_num[i];
        hash_x[key][total[key]] = total_x[i];
        hash_y[key][total[key]] = total_y[i];
    }

        scanf("%d", &m);

    for(int i = 1; i <= m; i ++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        int key = (y*131+x*131*131)%1000000;
        int whether_find = 0;
        for(int j = 1; j <= total[key];j++)
        {
            if(x == hash_x[key][j] && y == hash_y[key][j])
            {
                printf("%d\n",hash_num[key][j]);
                whether_find = 1;
                break;
            }
        }
        if(whether_find == 0)
        {
            printf("0\n");
        }
    }

return 0;
    




}

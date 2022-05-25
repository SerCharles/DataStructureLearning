#include <stdio.h>
int hashlist[300000] = {0};
char list[15000][120] = {0};
int num_of_list[27] ={0};
void insert(int c)
{
    int num = list[c][0]-'A' + 1;
    num_of_list[num] ++;
    hashlist[26*(num_of_list[num] - 1)+num] = c;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%s",list[i]);
        insert(i);
    }
    for(int i = 1; i <= 26; i ++)
    {
        for(int j = 1; j <= num_of_list[i]; j ++)
        {
                printf("%s\n", list[hashlist[j*26-26+i]]);
        }
    }
    return 0;
}

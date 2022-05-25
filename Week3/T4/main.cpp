#include <iostream>
using namespace std;


int map[30][30] = {0};
int visit[30][30] = {0};
bool m_WhetherSuccess = 0;
int start_x, start_y, end_x, end_y;
int width, height, max_time; 


void DFS(int step, int place_x, int place_y)
{
    if(step <= max_time && place_x == end_x && place_y == end_y)
    {
        m_WhetherSuccess = 1;
        return;
    }
    if(m_WhetherSuccess == 1)
    {
        return;
    }
    if(step > max_time)
    {
        return;
    }
    visit[place_x][place_y] = 1;
    int next_step_x[5] = {0, 1, -1, 0, 0};
    int next_step_y[5] = {0, 0, 0, 1, -1};
    for(int i = 1; i <= 4; i ++)
    {
        int new_x = place_x + next_step_x[i];
        int new_y = place_y + next_step_y[i];
        if(new_x >= 1 && new_x <= width && new_y >=1 && new_y <= height && visit[new_x][new_y] == 0 && map[new_x][new_y] == 1)
        {
            DFS(step+1, new_x, new_y);
            visit[new_x][new_y] = 0;
        }
    }
}


int main()
{
    while(1)
    {
        cin >> width >> height >> max_time;
        if(width == 0 && height == 0 && max_time == 0)
        {
            break;
        }
        m_WhetherSuccess = 0;
        for(int i = 0; i < 30; i ++)
        {
            for(int j = 0; j < 30; j ++)
            {
                map[i][j] = 0;
                visit[i][j] = 0;
            }
        }
        for (int i = 1; i <= height; i ++)
        {
            for(int j = 1; j <= width; j ++)
            {
                char c;
                cin >> c;
                if(c == '.')
                {
                    map[j][i] = 1;
                }
                else if (c == '*')
                {
                    map[j][i] = 0;
                }
                else if (c == 'S')
                {
                    map[j][i] = 1;
                    start_x = j;
                    start_y = i;
                }
                else if (c == 'P')
                {
                    map[j][i] = 1;
                    end_x = j;
                    end_y = i;
                }
            }
        }
        DFS(0, start_x, start_y);
        if(m_WhetherSuccess == 1)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}
#include<stdio.h>

#define MAXSIZ 2500
#define and &&
#define or ||

struct node
{
    int x;
    int y;
    int father;
    int step;
};

int main(void)
{
    struct node queue[MAXSIZ];
    int map[50][50] = {{0}}, book[50][50] = {{0}};
    /*坐标定义为 map[x][y]
     *    y-->
     *  0 ----------->
     *  x |
     *  | |
     *  | |
     *  V |            
     *    |
     *    V
     * */
    int next[4][2] = {{0, 1},      
                      {1, 0},      
                      {0, -1},     
                      {-1, 0}};
    int head = 0, tail = 0;
    int startx, starty, endx, endy, tx, ty, flag, row=0, col=0;
    int i, j, k;

    printf("请输入地图大小(最大为50行，50列):\n");
    scanf("%d%d", &row, &col);
    printf("请设计地图，0为可通过，1为障碍物:\n");
    for(i = 0; i < row; i++)
        for(j = 0; j < col; j++)
            scanf("%d", &map[i][j]);

    printf("请输入入口坐标(x, y):\n");
    scanf("%d%d", &startx, &starty);
    printf("请输入终点坐标(x, y):\n");
    scanf("%d%d", &endx, &endy);
    
    //初始化
    startx--;
    starty--;
    endx--;
    endy--;
    head = tail = 0;
    queue[tail].x = startx;
    queue[tail].y = starty;
    queue[tail].father = -1;
    queue[tail].step = 0;
    tail++;
    book[startx][starty] = 1;
    flag = 0;

    while(head < tail)
    {
        //枚举每个点的四个方向的可行性
        for(k = 0; k < 4; k++)
        {
            tx = queue[head].x + next[k][0];
            ty = queue[head].y + next[k][1];

            //判断是否越界
            if(tx < 0 or tx > (row-1) or ty < 0 or ty > (col-1))
                continue;

            //判断下一步是否可行,可行就入队
            if(map[tx][ty] == 0 and book[tx][ty] == 0)
            {
                book[tx][ty] = 1;
                queue[tail].x = tx;
                queue[tail].y = ty;
                queue[tail].father = head;
                queue[tail].step = queue[head].step+1;
                tail++;
            }

            if(tx == endx and ty == endy)
            {
                flag = 1;
                break;
            }
        }

        if(flag == 1)
            break;

        head++;
    }

    printf("%d\n", queue[tail-1].step);

    getchar();getchar();
    return 0;

}                                  
                                   
                                   
                                   
                                   

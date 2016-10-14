/* 用dfs算法解决走迷宫问题，其中
 * 地图用二维数组保存: map[MAXSIZ][MAXSIZ]
 * 0表示可以通过，1表示有障碍物
 * 用另外一个二维数组表示走过的路：
 * trace[MAXSIZ][MAXSIZ]
 * */

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZ 50
#define and &&
#define or ||

struct status
{
    int row;
    int column;
    int endx;
    int endy;
    int min;
};

int map[MAXSIZ][MAXSIZ], book[MAXSIZ][MAXSIZ];

void dfs(int, int, int, struct status *);

int main(void)
{
    int startx, starty, i, j;
    struct status init;

    printf("请输入地图的行和列：");
    scanf("%d%d", &init.row, &init.column);
    printf("请输入地图，用0表示空的位置，用1表示障碍物：\n");

    for(i = 0; i < init.row; i++)
    {
        for(j = 0; j < init.column; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }

    printf("请输入终点坐标(x y):");
    scanf("%d%d", &init.endx, &init.endy);
    
    printf("请输入起点坐标(x y):");
    scanf("%d%d", &startx, &starty);

    init.min = 99999;

    dfs(startx, starty, 0, &init);

    printf("最小步数是: %d\n", init.min);

    return 0;
}

void dfs(int startx, int starty, int step, struct status *save)
{
    int next[4][2] = {{0, 1},   //向右走
                      {1, 0},   //向下走
                      {0, -1},  //向左走
                      {-1, 0}}; //向上走
    int tx, ty, k; //tx，ty为下一步的坐标

    if(startx == save->endx and starty == save->endy)
    {
        if(step < save->min)
        {
            save->min = step;
        }
        return ;
    }

    for(k = 0; k < 4; k++)
    {
        tx = startx + next[k][0];
        ty = starty + next[k][1];

        if(tx < 0 or tx >= save->row or ty < 0 or ty >= save->column)
        {
            continue;
        }

        if(map[tx][ty] == 0 and book[tx][ty] == 0)
        {
            book[tx][ty] = 1;
            dfs(tx, ty, step+1, save);
            book[tx][ty] = 0;
        }
    }

    return ;
}

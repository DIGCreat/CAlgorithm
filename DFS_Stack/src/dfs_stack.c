#include<stdio.h>

/**利用栈结构来实现深度优先搜索
 * 用数组模拟栈，利用count来统计当前节点被访问了几次
 * 关键点：
 * 1、输出结果的判断条件为节点的bit位大小为排列的数的范围减一。
 * 2、出栈的条件为当前节点被访问了两次。
 * 3、循环结束的条件为栈空。
 * */

struct node
{
    int val;     //这个节点的值
    int bit;     //在结果中的第几位
    int count;   //用来标记当前节点被访问几次
};

void
dfs_stack(int range)
{
    int i, j, th = 0, len = 0;
    struct node temp[45], m;
    int book[10] = {0};
    int result[9] = {0};

    //初始化栈，把所有数放进去
    for(i = 1; i <= range; i++)
    {
        temp[len].val = i;
        temp[len].bit = 0;
        temp[len].count = 0;
        len++;
    }
    th = len - 1;

    //主循环，当栈空的时候，len为0,循环结束
    while(len)
    {
        //count增加1代表访问了一次，第一次访问，需要将值放进结果数组里，并把book置一
        temp[th].count++;
        result[temp[th].bit] = temp[th].val;
        book[temp[th].val] = 1;

        //如果count访问了2次，代表该节点已经把所有可能都尝试完毕，并回溯到自己。
        if(temp[th].count == 2){
            book[temp[th].val] = 0;
            temp[th].val = -1;
            temp[th].bit = -1;
            len--;th--;
            continue;
        }

        //如果结果长度等于数的范围，说明已经尝试完毕，可用输出结果。
        if(temp[th].bit == range-1)
        {
            for(j = 0; j < range; j++)
            {
                fprintf(stdout, "%d", result[j]);
            }
            fprintf(stdout, "\n");
            continue;
        }

        //把当前栈顶的节点保存到m里面，因为接下来栈顶会变，而起需用用到当前栈顶节点。
        m = temp[th];

        for(i = 1; i <= range; i++)
        {
            if(book[i] == 0)
            {
                temp[len].val = i;
                temp[len].bit = m.bit+1;
                temp[len].count = 0;
                len++;th++;
            }
        }
    }
}

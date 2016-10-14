#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define and &&
#define or ||
#define Int(X) (X - '0')

//用于检测输入的是否是数字，如果是就返回0,不是就返回1
int checkNum(const char *num)
{
    int i;
    for(i = 0; (size_t)i < strlen(num); i++)
    {
        if(num[i] < '0' or num[i] > '9')
        {
            return 1;
        }
    }
    return 0;
}

//返回结果result，为一片内存块，类似数组
int *multiBigInteger(const char *num1, const char *num2)
{
    int *result = NULL;                //用来保存最终结果
    int num1Len = strlen(num1);        //num1的长度
    int num2Len = strlen(num2);        //num2的长度
    int resultLen;                     //结果的最大长度
    int i, j;                          //循环计数器
    resultLen = num1Len + num2Len;     //结果长度最大为num1长度和num2长度之和
    //初始化result为0
    result = (int *)malloc((resultLen+1)*sizeof(int));
    memset(result, 0, (resultLen+1)*sizeof(int));

    result[0] = resultLen; //result的第一位是用来保存result的长度的。
    /* num1乘以num2,由于这里采用先不进位的算法，所以算法是按从左到右
     * 按顺序来乘，然后将每位的结果保存到result的每一位中，循环一次
     * reult就从下一位开始求和。如下：(左边为正常算法，右边为本程序算法)
     *
     *     54321     |     54321
     *    ×  123     |    ×  123
     *    -------    |   --------
     *    162963     |     54321
     *   108642      |     108642
     *   54321       |      162963
     *   --------    |   ---------
     *   6681483     |     6681483
     *
     * */
    for(j = 0; j < num2Len; j++)
    {
        for(i = 0; i < num1Len; i++)
        {
            /* result第一位是用来保存result长度的，而第二位是保存结果最后的进位的
             * 没有进位，则result[1]为0，所以每位相乘之和是从第三位（即result[2]）
             * 开始。这里是本程序的比较巧妙的地方，需要仔细想想。
             * */
            result[i+j+2] += Int(num1[i]) * Int(num2[j]);
        }
    }

    /* 这个循环用来处理进位的，所以要从result的最后一位一直处理到首位。
     * 要注意result的总长度是resultLen+1,有一位是保存result的长度，而
     * C语言下标是从0开始，所以result的最后一位的下标就是resultLen，而
     * 第一位就是1。*/
    for(i = resultLen; i > 1; i--)
    {
        result[i-1] += result[i]/10;
        result[i] = result[i]%10;
    }
    printf("num1Len:%d\nnum2Len:%d\n", num1Len, num2Len);
    return result;
}

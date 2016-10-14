#include<stdio.h>
#include<string.h>

#include "BigIntegerMul.h"


int main(void)
{
    char num1[100] = {'\0'}, num2[100] = {'\0'};
    printf("Please input two nunber(less than 100 digits):\n> ");
    while(scanf("%s%s", num1, num2) != EOF)
    {
        int *result = NULL;
        int i, change = 0;
        //对输入的数据进行检验
        if(strlen(num1) > 100 or strlen(num2) > 100)
        {
            printf("per number must less than 100 digits\n");
            return 1;
        }

        if(checkNum(num1) or checkNum(num2))
        {
            printf("ERROR: input must be an Integer\n");
            return 1;
        }

        printf("num1:\t%s\nnum2:\t%s\n", num1, num2);

        result = multiBigInteger(num1, num2);

        /* 输出结果result，result[0]保存着result的长度，
         * 所以下标要从1开始 */
        printf("result:\t");
        for(i = 1; i <= result[0]; i++)
        {
            if(result[i] != 0) //这一步用来去掉前导0,第一位为0跳过不输出
                change = 1;
            if(not change)
            {
                if(i > 1)        //这一步用来判断结果是否为0,
                    {                //如果结果第二位还是0,就判断为0
                        printf("0");
                        break;
                    }
                continue;
            }
            printf("%d", result[i]);
        }
        printf("\n");
        printf("\nPlease input two nunber(less than 100 digits):\n> ");
    }
    return 254;
} 

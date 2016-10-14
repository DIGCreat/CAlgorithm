#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>

#define or ||
#define and &&
#define not !
#define Int(X) (X - '0')

char *multiBigInteger(const char *, const char *);

int main(void)
{
    char num1[7] = {'\0'};
    int num2;
    while(scanf("%s%d",num1, &num2) != EOF)
    {
        unsigned int num1D = 0;
        char *result;
        int nDot = 0, i = 0, j = 0;
        char temp[103] = {'\0'};
        //对输入的数据的检验
        if(strlen(num1) > 6 or num2 < 0 or num2 > 25 )
        {
            continue;
        }

        //找出小数位，包括小数尾的0
        for(i = 0, j = 0; (size_t)i < strlen(num1); i++)
        {
            if(num1[i] == '.')
            {
                j++;
                nDot = strlen(num1)-1 - i;
                continue;
            }
            if(num1[i] == '0')
            {
                j++;
            }
            num1D = num1D*10 + Int(num1[i]);
        }

        if(num1D/pow(10, nDot) > 99.99 or num1D/pow(10, nDot) < 0)
        {
            continue;
        }

        //将小数尾的0去掉，由后向前遍历，当遇到第一个非0的数结束循环
        for(i = strlen(num1)-1; (size_t)i > strlen(num1)-(size_t)nDot; i-- )
        {
            if(num1[i] != '0')
            {
                break;
            }
            num1[i] = '\0';
        }

        //找出真正的小数位数，并将num1去掉小数点和将temp设置为num1
        for(i = 0, j = 0; (size_t)i < strlen(num1); i++)
        {
            if(num1[i] == '.')
            {
                nDot = strlen(num1)-1 - i;
                continue;
            }
            temp[j] = num1[i];
            num1[j] = num1[i];
            j++;
        }
        num1[j] = '\0';
        //处理底为0和幂为0或1的情况
        if(num1D == 0)
        {
            printf("0\n");
            continue;
        }
        else if(num2 == 0)
        {
            printf("1\n");
            continue;
        }
        else if(num2 == 1)
        {
            for(i = 0; (size_t)i < strlen(num1); i++)
            {
                if((size_t)i == strlen(num1)-(size_t)nDot)
                {
                    printf(".");
                }
                printf("%c", num1[i]);
            }
            printf("\n");
            continue;
        }

        nDot *= num2; //计算结果的小数位数

        //n次幂需要循环n-1次，调用大整数相乘，将每次的结果乘以底数
        for(i = 0; i < num2-1; i++ )
        {
            result = multiBigInteger(temp, num1);
            //先将temp清零
            memset(temp, 0, 103*sizeof(char));
            //将每次相乘的结果赋给temp，如果首位是0则不传
            if(result[0] == '0')
            {
                memcpy(temp, result+1, strlen(result));
            }
            else
            {
                memcpy(temp, result, strlen(result)+1);
            }
        }

        //输出结果，k为标志位，只有k为1时开始输出数字
        //由头开始，只有遇到第一个非0或者小数点时，k才等于1
        j = 0;
        for(i = 0; (size_t)i < strlen(result); i++)
        {
            if(result[i] != '0')
            {
                j = 1;
            }

            if((size_t)i == strlen(result)-(size_t)nDot)
            {
                j = 1;
                printf(".");
            }

            if(j)
            {
                printf("%c", result[i]);
            }
        }
        printf("\n");
        memset(num1, 0, 7 * sizeof(char));
    }
    printf("\n");
    return 0;
} 


char *multiBigInteger(const char *num1, const char *num2)
{
    char *tempRes;        //用来保存每次相乘的结果
    char *result;
    int tempResLen;                    //每次相乘结果的最大长度
    int num1Len = strlen(num1);        //num1的长度
    int num2Len = strlen(num2);        //num2的长度
    int resultLen;                     //结果的最大长度
    int i, j, k;                       //循环计数器
    int res;                           //每次一位相乘/相加的结果
    int carry = 0;                     //进位
    int offset = 0;                    //加法的偏移位
    resultLen = num1Len + num2Len - 1; //结果长度最大为num1长度和num2长度之和，由于下标从0开始，所以要减一
    tempResLen = num1Len;              //每次num1乘以num2每一位的结果最大长度是num1Len+1,由于下标从0开始，所以减一后约去1,只剩num1Len

    result = (char *)malloc((resultLen+2) * sizeof(char));
    memset(result, 0, sizeof(*result));

    tempRes = (char *)malloc((tempResLen+2) * sizeof(char));
    memset(tempRes, 0, sizeof(*tempRes));
    
    //初始化result为0
    memset(result, '0', (resultLen+1) * sizeof(char));
    for(j = num2Len - 1; j >= 0; j--)
    {
        //初始化tempRes每位为0
        memset(tempRes, '0', (tempResLen+1) * sizeof(char));
        /*计算num1与num2各位相乘的结果，保存到tempRes中
         *每一位相乘后与之前的进位相加得出res，将res的个
         *位(res%10)保存到tempRes里,然后将res的其余位数
         *(res/10)则为进位carry*/
        for(i = num1Len-1; i >= 0; i--)
        {
            res = (num1[i] - '0') * (num2[j] - '0') + carry;
            tempRes[tempResLen--] = res % 10 + '0';
            carry = res / 10;
        }
        //tempRes第一位为进位，刚刚的循环是没有算的，最后把进位算上
        tempRes[tempResLen] = carry + '0';
        tempResLen = num1Len;
        carry = 0;
        //由result的末尾开始计算和，算完一次，向左偏移一位
        for(k = resultLen-offset; k > (resultLen-offset-num1Len); k--)
        {
            res = (result[k]-'0') + (tempRes[tempResLen--]-'0') + carry;
            result[k] = res%10 + '0';
            carry = res/10;
        }
        result[k] += (tempRes[tempResLen] + carry - '0');
        carry = 0;
        tempResLen = num1Len;
        offset++;

    }
    return result;
}

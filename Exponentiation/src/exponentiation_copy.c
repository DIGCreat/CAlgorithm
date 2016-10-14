#include<stdio.h>
#include<string.h>
#include<math.h>

#define or ||
#define and &&
#define not !
#define Int(X) (X - '0')

void multiBigInteger(char num1[], char num2[], char result[]);

int main(void)
{
    char num1[7] = {'\0'};
    int num2;
    while(scanf("%s%d",num1, &num2) != EOF)
    {
        unsigned int num1D = 0;
        char result[103] = {'\0'};
        int nDot = 0, i = 0, j = 0, k = 0;
        char temp[103] = {'\0'};
        if(strlen(num1) > 6 or num2 < 0 or num2 > 25 )
        {
            continue;
        }
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

        if(num1D/pow(10, nDot) >= 99999.0 or num1D/pow(10, nDot) < 0)
        {
            continue;
        }
        for(i = strlen(num1)-1; (size_t)i > strlen(num1)-(size_t)nDot; i-- )
        {
            if(num1[i] != '0')
            {
                break;
            }
            num1[i] = '\0';
        }
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

        nDot *= num2; 

        for(i = 0; i < num2-1; i++ )
        {
            multiBigInteger(temp, num1, result);
            memset(temp, 0, 103*sizeof(char));
            if(result[0] == '0')
            {
                memcpy(temp, result+1, strlen(result));
            }
            else
            {
                memcpy(temp, result, strlen(result)+1);
            }
        }

        k = 0;
        for(i = 0; (size_t)i < strlen(result); i++)
        {
            if(result[i] != '0')
            {
                k = 1;
            }

            if((size_t)i == strlen(result)-(size_t)nDot)
            {
                k = 1;
                printf(".");
            }

            if(k)
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


void multiBigInteger(char num1[], char num2[], char result[])
{
    char tempRes[102] = {'\0'};        
    int tempResLen;                    
    int num1Len = strlen(num1);        
    int num2Len = strlen(num2);        
    int resultLen;                     
    int i, j, k;                       
    int res;                           
    int carry = 0;                     
    int offset = 0;                    
    resultLen = num1Len + num2Len - 1; 
    tempResLen = num1Len;              

    for(j = 0; (size_t)j < strlen(result); j++)
    {
        result[j] = '\0';
    }

    memset(result, '0', (resultLen+1) * sizeof(char));
    for(j = num2Len - 1; j >= 0; j--)
    {
        memset(tempRes, '0', (tempResLen+1) * sizeof(char));
        for(i = num1Len-1; i >= 0; i--)
        {
            res = (num1[i] - '0') * (num2[j] - '0') + carry;
            tempRes[tempResLen--] = res % 10 + '0';
            carry = res / 10;
        }
        tempRes[tempResLen] = carry + '0';
        tempResLen = num1Len;
        carry = 0;
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
}

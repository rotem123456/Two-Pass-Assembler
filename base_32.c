#include "base_32.h"


/*-------------------------------------------------------*/   
/* Helper function to reverse an array. */
/* Gets an array and its size and reverses it. */
void reverse(int *digits, int size)
{
    int i;
    for (i = 0; i < (size/2); i++)
    {
        int tmp = digits[i];
        digits[i] = digits[(size)-i-1];
        digits[(size)-i-1] = tmp;
    }
}
/*-------------------------------------------------------*/
/* Coverts a decimal number to any base */
/* Gets a parameter to save the size of the array and a number to convert */
/* Returns an int array of digits in said base */
char* base32(int num)
{
    int i = 0,j=0;
    const char base[] = {'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f',
                                'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
    int *digits = (int*)calloc(1, sizeof(int)); 
    char *print_base;
	if(digits == NULL)
	{
		exit(1);
	}

    while (num !=  0)
    {
        digits = (int*)realloc(digits, (sizeof(int)*(i+1)));
        if(digits==NULL)
        {
        	exit(1);
        }
        digits[i++] = num % BASE32;
        num /= BASE32;
    }
    print_base = (char*)calloc(2+i,sizeof(char));
	if(num==0)
	{
		print_base[0]='!';
		print_base[1]='!';
	}
    reverse(digits, i);
    if(i == 1)
    	print_base[1] = base[digits[j]];
    else while(j<i)
    {
    	print_base[j] = base[digits[j]];
    	++j;
    }
    free(digits);
    
    return print_base;
}






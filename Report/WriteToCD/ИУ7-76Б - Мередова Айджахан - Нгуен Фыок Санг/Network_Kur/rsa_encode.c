#include <stdio.h>
#include <stdlib.h>

#include <string.h>



#define MAXFILENAMELENGTH 255

unsigned long long int modpow(int base, int power, int mod)
{
        int i;
        unsigned long long int result = 1;
        for (i = 0; i < power; i++)
        {
                result = (result * base) % mod;
        }
        return result;
}


char* rsa(char * msg)
{
	int m, n, e;
    unsigned long long int c;

    FILE *inp = fopen("public.txt", "r");
    fscanf(inp, "%d %d", &n, &e);
    fclose(inp);
    
    char * res = (char *)malloc(255 * sizeof(char));
    char * tmp = (char *)malloc(255 * sizeof(char));
    sprintf(res, "");
	
	int i;

	
	for (i = 0; msg[i]!= '\0'; i++)
	{
        c = modpow(msg[i],e,n);
		printf("%llu ", c);
		sprintf(tmp, "%llu\n", c);
		strcat(res, tmp);
	}

    
    return res;
}

int main (int argc, char *argv[])
{

	char * res =  rsa(argv[1]);
	printf("res = [%s]\n", res);
	return 0;
}

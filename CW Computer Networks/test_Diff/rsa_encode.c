#include "stdio.h"
#include "stdlib.h"

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

char * rsa_encode(char * str, int n, int e)
{
	char * res = (char *)malloc(MAXFILENAMELENGTH * sizeof(char));
	strcpy(res, "");
	int i;
	for (i = 0; str[i]!= '\0'; i++)
	{
        c = modpow(str[i],e,n);
		printf("%llu ", c);
		//sprintf(res, "%d "
		fprintf(outp, "%llu\n", c);
	}
}

int main (int argc, char *argv[])
{
    int m, n, e;
    unsigned long long int c;

    FILE *inp = fopen("public.txt", "r");
    fscanf(inp, "%d %d", &n, &e);
    fclose(inp);

	printf("ciphertext c = ");

	int i;
	FILE *outp = fopen("ciphertext.txt", "w");

	for (i = 0; argv[1][i]!= '\0'; i++)
	{
        c = modpow(argv[1][i],e,n);
		printf("%llu ", c);
		fprintf(outp, "%llu\n", c);
	}

    printf("\n");
    fclose(outp);

        return 0;
}

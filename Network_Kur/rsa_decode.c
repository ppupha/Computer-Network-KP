#include "stdio.h"
#include "stdlib.h"
#include <string.h>


#define MAXVERSIONLENGTH 255

unsigned long long int modpow(unsigned long long int base, int power, int mod)
{
        int i;
        unsigned long long int result = 1;
        for (i = 0; i < power; i++)
        {
                result = (result * base) % mod;
        }
        return result;
}

int inverse(int a, int mod)     /*find inverse of number a in % mod*/
{                               /*inverse of a = i*/
        int aprev, iprev, i = 1, atemp, itemp;

        aprev = mod, iprev = mod;
        while (a != 1)
        {
                atemp = a;
                itemp = i;
                a = aprev - aprev / atemp * a;
                i = iprev - aprev / atemp * i;
                aprev = atemp;
                iprev = itemp;
                while (i < 0)
                        i += mod;
        }

        return i;
}


char * rsa_decode(char * input)
{
	int d, n, p, q, h, m, qInv, m1m2;
    unsigned long long int c, dP, dQ, m1, m2;
    FILE *inp;

    inp = fopen("private.txt", "r");
    fscanf(inp, "%d %d", &n, &d);
    fclose(inp);

    inp = fopen("pq.txt", "r");
    fscanf(inp, "%d %d", &p, &q);
    fclose(inp);

	char * outstr = (char *)malloc(MAXVERSIONLENGTH * sizeof(char));
	memset(outstr, 0, sizeof(MAXVERSIONLENGTH * sizeof(char)));
	
	inp = fopen("tmp.encode", "w");
	fwrite(input, strlen(input), sizeof(char), inp);
	fclose(inp); 
	inp = fopen("tmp.encode", "r");
	int count = 0;

	while (fscanf(inp, "%llu", &c) != EOF)
	{
    	dP = d % (p - 1);
    	dQ = d % (q - 1);
    	qInv = inverse(q,p);
    	m1 = modpow(c,dP,p);
    	m2 = modpow(c,dQ,q);
    	m1m2 = m1 - m2;
    	if (m1m2 < 0)
            	m1m2 += p;
   		h = (qInv * m1m2) % p;
    	m = m2 + h * q;

		outstr[count] = m;
		count++;
		
	}
	
	fclose(inp);
	return outstr;
}

int main ()
{
		char * res = rsa_decode("373248 1030301 1259712 1259712 1367631");
		printf("result is [%s]\n", res);
		return 0;
}

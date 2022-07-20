#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <sys/wait.h>

#include "rsa.h"
#include "functions.h"

int exDiff(char * workpath, char * uploadpath)
{
	pid_t pid;
	int status;
	char diffFile[255];
	diffFile[0] = 0; 
	
	if ((pid = fork()) < 0)
	{
		printf("Cant Fork\n");
		return -1;
	}
	else if (pid == 0)
	{
		printf("Enter SOn Process\n");
		sprintf(diffFile, "%s/diff.patch", uploadpath);
		freopen("./greetings-1.0/diff.txt", "w", stdout);
		/* Execute the diff command. */
		
		
		execlp("diff", "diff", "-Naur", uploadpath, workpath, NULL);
		printf("Couldnt Execute Command\n");
		return 0;
	}
	if (waitpid(pid, &status, 0) < 0)
		perror("waitpid");
	return 1;
}

int commit()
{
	pid_t pid;
	int status;
	
	if ((pid = fork()) < 0)
	{
		printf("Cant Fork\n");
		return -1;
	}
	else if (pid == 0)
	{
		printf("Enter SOn Process\n");
		
		freopen("./greetings-1.0/diff.txt", "r", stdin);

		/* Execute the diff command. */
		
		//execlp("cd", "cd", "greetings-1.0", NULL);
		execlp("patch", "patch", "-p1", "-u", NULL);
		printf("Couldnt Execute Command\n");
		return 0;
	}
	if (waitpid(pid, &status, 0) < 0)
		perror("waitpid");
	return 1;
}


int patch()
{
	pid_t pid;
	int status;
	
	if ((pid = fork()) < 0)
	{
		printf("Cant Fork\n");
		return -1;
	}
	else if (pid == 0)
	{
		printf("Enter SOn Process\n");
		freopen("./greetings-1.0/diff.txt", "r", stdin);

		execlp("patch", "-Rp1", "patch", NULL);
		printf("Couldnt Execute Command\n");
		return 0;
	}
	if (waitpid(pid, &status, 0) < 0)
		perror("waitpid");
	return 1;
}

int main(void)
{
	printf("Hello World\n");
	std::string keyfile = "key.txt";
	
	char in_file[] = "diff.txt";
	
	Rsa rsa;

    rsa.generate_keys();
    rsa.save_keys_to_file(keyfile);

    rsa.encode_file(in_file, in_file + ".encoded");

    Rsa rsa2;

    rsa2.load_keys_from_file(keyfile);
    rsa2.decode_file(in_file + ".encoded", in_file + ".decoded");

	
	int c;
	while (1)
	{
		printf("1. Diff\n");
		printf("2. Commit\n");
		printf("3. Patch\n");
		printf("0. Exit\n");
		printf("Input Choise:\n");
		scanf("%d", &c);
		printf("C = %d\n", c);
		
		switch (c)
		{
			case (1):
			{
				exDiff("./greetings-1.0-mod", "./greetings-1.0");
				break;
			}
			case (2):
			{

				commit();
				break;
			}
			case (3):
			{
				patch();
				break;
			}
			case (0):
				return 0;
		}
	}
	
	
	return 0;
}

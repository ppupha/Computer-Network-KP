#include <dirent.h> 
#include <stdio.h>
#include <string.h>

#define MAX_LEN 255
#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"
#define RED  "\x1b[31m"


int fileCompare(char * filename1, char * filename2)
{
	FILE *file1 = fopen(filename1, "r");
   	FILE *file2 = fopen(filename2, "r");
   	if (file1 == NULL && file2 == NULL)
   	{
      	return -2;
   	}
   	else if (file1 == NULL)
   		return -1;
   	else if (file2 == NULL)
   		return -2;
   	char ch1 = getc(file1);
   	char ch2 = getc(file2);
   	int error = 0, pos = 0, line = 1;
   	while (ch1 != EOF && ch2 != EOF){
      	if (ch1 != ch2)
      	{
      		return 0;
      	}
      	ch1 = getc(file1);
      	ch2 = getc(file2);
   	}
   	
   	if (ch1 == EOF && ch2 == EOF)
   		return 1;
   	return 0;
}


int main(void)
{
	char currentDir[MAX_LEN] = "./work";
	char uploadDir[MAX_LEN] = "./serverFiles/uploadedFiles";
	char commitDir[MAX_LEN] = "./serverFiles/currentFiles";
	char currentPath[MAX_LEN];
	char commparePath[MAX_LEN];
	char tmp[MAX_LEN];
	
	char res[MAX_LEN * 100];
	res[0] = 0;
	
	DIR * d = NULL;
	struct dirent * dir;
	d = opendir(currentDir);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type != DT_DIR)
			{
				tmp[0] = 0;
				sprintf(currentPath, "%s/%s", currentDir, dir->d_name);

				sprintf(commparePath, "%s/%s", commitDir, dir->d_name);
				int isCommited = fileCompare(currentPath, commparePath);
				
				sprintf(commparePath, "%s/%s", uploadDir, dir->d_name);
				int isUploaded = fileCompare(currentPath, commparePath);
				
				printf("Check = %d\n CheckUpload = %d\n", isCommited, isUploaded);
				
				if (isCommited == 1)
					sprintf(tmp, "%s%s: %s%s\n", BLUE, "Commited", dir->d_name, NORMAL_COLOR);
				else if (isCommited == 0)
				{
					if (isUploaded == 1)
						sprintf(tmp, "%s%s: %s%s\n", BLUE, "Modified", dir->d_name, NORMAL_COLOR);
					else if (isUploaded == 0)
						sprintf(tmp, "%s%s: %s%s\n", RED, "Modified", dir->d_name, NORMAL_COLOR);
				}
				else if (isCommited == -2)
				{
					if (isUploaded == 1)
						sprintf(tmp, "%s%s: %s%s\n", BLUE, "Create", dir->d_name, NORMAL_COLOR);

					else if (isUploaded == -2)
						sprintf(tmp, "%s%s: %s%s\n", RED, "Create", dir->d_name, NORMAL_COLOR);

				}
				
				strcat(res, tmp);
				
			}
		}
	}
	else
	{
		printf("Cant open Folder %s\n", currentDir);
	}
	
	printf("Result is : [%s]\n", res);
	return 0;
}

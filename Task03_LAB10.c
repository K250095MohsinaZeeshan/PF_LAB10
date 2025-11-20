#include <stdio.h>
#include <string.h>

#define MAX 40
#define LEN 200

int main() 
{
	printf("COOKING ASSISTANT DEVICE\n");
	printf("________________________\n");
	
    char recipes[MAX][LEN], temp[LEN], temp2[LEN];
    int n = 0, choice, i, j;

    FILE *fp = fopen("recipes.txt", "r");
    if (fp != NULL) {
        while (fgets(recipes[n], LEN, fp) && n < MAX) 
		{
            recipes[n][strcspn(recipes[n], "\n")] = 0;
            n++;
        }
        fclose(fp);
    }
    while (1) 
	{
        printf("\n1 Add\n2 Delete\n3 Update\n4 Search\n5 Display\n6 For Exit (Enter -1)\nChoice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == -1) 
		{

            for (i = 0; i < n - 1; i++)
                for (j = i + 1; j < n; j++)
                    if (strcmp(recipes[i], recipes[j]) > 0) 
					{
                        strcpy(temp, recipes[i]);
                        strcpy(recipes[i], recipes[j]);
                        strcpy(recipes[j], temp);
                    }

            fp = fopen("recipes.txt", "w");
            for (i = 0; i < n; i++)
                fprintf(fp, "%s\n", recipes[i]);
            fclose(fp);

            printf("\nSaved.\n");
            break;
        }
        if (choice == 1)
		 {
            if (n >= MAX) 
			{ printf("Full\n"); 
			continue; 
			}
            printf("\nEnter recipe: ");
            fgets(recipes[n], LEN, stdin);
            recipes[n][strcspn(recipes[n], "\n")] = 0;
            n++;
        }
        else if (choice == 2) 
		{
            printf("Delete: ");
            fgets(temp, LEN, stdin);
            temp[strcspn(temp, "\n")] = 0;

            for (i = 0; i < n; i++) 
			{
                if (strcmp(recipes[i], temp) == 0) 
				{
                    for (j = i; j < n - 1; j++)
                        strcpy(recipes[j], recipes[j + 1]);
                    n--;
                    break;
                }
            }
        }
        else if (choice == 3) 
		{
            printf("\nOld name: ");
            fgets(temp, LEN, stdin);
            temp[strcspn(temp, "\n")] = 0;

            for (i = 0; i < n; i++) 
			{
                if (strcmp(recipes[i], temp) == 0) 
				{
                    printf("\nNew name: ");
                    fgets(temp2, LEN, stdin);
                    temp2[strcspn(temp2, "\n")] = 0;
                    strcpy(recipes[i], temp2);
                    break;
                }
            }
        }
        else if (choice == 4) 
		{
            printf("Search: ");
            fgets(temp, LEN, stdin);
            temp[strcspn(temp, "\n")] = 0;

            for (i = 0; i < n; i++)
                if (strstr(recipes[i], temp))
                    printf("%s\n", recipes[i]);
        }
        else if (choice == 5) 
		{
            for (i = 0; i < n; i++)
                printf("%d. %s\n", i + 1, recipes[i]);
        }
    }
    return 0;
}


#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 200


int wc(char *str) 
{
    int wordCount = 0, flag = 0;
    while (*str) 
	{                                                             
        if (*str != ' ' && *str != '\t' && !flag)                      
		{ 
		wordCount++; 
		flag = 1; 
		}
        else if (*str == ' ' || *str == '\t')
		 flag = 0;
        str++;
    }
    return wordCount;
}
int main() 
{
    char levels[MAX][LEN], t1[LEN], t2[LEN];
    int n = 0, i, j, choice;
  
    printf("GAME APP\n");
    printf("________\n");
    FILE *fp = fopen("levels.txt", "r");
    if (fp) 
	{
        while (fgets(levels[n], LEN, fp) && n < MAX) 
		{
            levels[n][strcspn(levels[n], "\n")] = 0;
            n++;
        }
        fclose(fp);
    }
    while (1) 
	{
        printf("\n1 Add\n2 Delete\n3 Update\n4 Search\n5 Display\n6-For Exit(Enter -1)\nChoice:");
        scanf("%d", &choice);
        getchar();

        if (choice == -1) 
		{
            fp = fopen("levels.txt", "w");
            for (i = 0; i < n; i++) 
			fprintf(fp, "%s\n", levels[i]);
            fclose(fp);
            printf("Saved.\n");
            break;
        }
        if (choice == 1) 
		{
            if (n >= MAX) { printf("Full.\n"); continue; 
			}
            printf("\nEnter level description (max 7 words): ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            if (wc(t1) > 7) {
			 printf("\nToo many words.\n"); 
			 continue; 
			 }
            strcpy(levels[n++], t1);
        }
        else if (choice == 2) 
		{
            printf("Delete: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            for (i = 0; i < n; i++)
                if (strcmp(levels[i], t1) == 0) 
				{
                    for (j = i; j < n-1; j++)
                        strcpy(levels[j], levels[j+1]);
                    n--;
                    break;
                }
        }
        else if (choice == 3) 
		{
            printf("\nOld level: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            for (i = 0; i < n; i++)
                if (strcmp(levels[i], t1) == 0) 
				{
                    printf("\nNew level (max 7 words): ");
                    fgets(t2, LEN, stdin); 
					t2[strcspn(t2, "\n")] = 0;
                    if (wc(t2) > 7) 
					{ printf("\nToo many words.\n"); 
					break; 
					}
                    strcpy(levels[i], t2);
                    break;
                }
        }
        else if (choice == 4) 
		{
            printf("Search: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            for (i = 0; i < n; i++)
                if (strstr(levels[i], t1))
                    printf("%s\n", levels[i]);
        }

        else if (choice == 5) 
		{
            for (i = 0; i < n; i++)
                printf("\n%d. %s\n", i+1, levels[i]);
        }
    }
    return 0;
}


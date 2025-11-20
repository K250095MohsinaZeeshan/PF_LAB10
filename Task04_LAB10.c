#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 200

int wordCount(char *str) 
{
    int count = 0, flag = 0;
    while (*str) 
	{
        if (*str != ' ' && *str != '\t' && !flag) 
		{ 
		count++; 
		flag = 1; 
		}
        else if (*str == ' ' || *str == '\t') 
		flag = 0;
        str++;
    }
    return count;
}
void displayAffirmations(char aff[MAX][LEN], int n) 
{
	int i;
    for (i = 0; i < n; i++) 
	printf("%d. %s\n", i + 1, aff[i]);
}
void addAffirmation(char aff[MAX][LEN], int *n, char *line) 
{
    if (*n >= MAX) 
	{ 
	printf("\nAffirmation list full.\n"); 
	return; 
	}
    if (wordCount(line) > 7) 
	{ 
	printf("Max 7 words allowed.\n"); 
	return; 
	}
    strcpy(aff[*n], line);
    (*n)++;
}
void deleteAffirmation(char aff[MAX][LEN], int *n, char *line)
 {
 	int i,j;
    for (i = 0; i < *n; i++) 
	{
        if (strcmp(aff[i], line) == 0) 
		{
            for (j = i; j < *n - 1; j++)
                strcpy(aff[j], aff[j + 1]);
            (*n)--;
            printf("\nDeleted.\n");
            return;
        }
    }
    printf("\nNot found.\n");
}
void updateAffirmation(char aff[MAX][LEN], int n, char *oldLine, char *newLine) 
{
	int i;
    for (i = 0; i < n; i++) 
	{
        if (strcmp(aff[i], oldLine) == 0) 
		{
            if (wordCount(newLine) > 7) 
			{
			 printf("\nMax 7 words allowed.\n"); 
			 return; 
			 }
            strcpy(aff[i], newLine);
            printf("\nUpdated.\n");
            return;
        }
    }
    printf("\nNot found.\n");
}

void searchAffirmations(char aff[MAX][LEN], int n, char *key) 
{
    int found = 0;
    int i;
    for (i = 0; i < n; i++) 
	{
        if (strstr(aff[i], key)) 
		{
            printf("%s\n", aff[i]);
            found = 1;
        }
    }
    if (!found) printf("\nNo matches.\n");
}

int main() 
{
    char aff[MAX][LEN], t1[LEN], t2[LEN];
    int n = 0, choice;

    printf("WELLNESS APP\n");
    printf("____________\n");
    FILE *fp = fopen("affirmation.txt", "r");
    if (fp) 
	{
        while (fgets(aff[n], LEN, fp) && n < MAX) 
		{
            aff[n][strcspn(aff[n], "\n")] = 0;
            n++;
        }
        fclose(fp);
    }

    while (1) 
	{
		int i;
        printf("\n1 Add\n2 Delete\n3 Update\n4 Search\n5 Display\n6 For Exit (Enter -1)\nChoice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == -1) 
		{
            fp = fopen("affirmation.txt", "w");
            for (i = 0; i < n; i++) 
			fprintf(fp, "%s\n", aff[i]);
            fclose(fp);
            printf("Saved.\n");
            break;
        }
        if (choice == 1) 
		{
            printf("\nEnter new affirmation (max 7 words): ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            addAffirmation(aff, &n, t1);
        }
        else if (choice == 2) 
		{
            printf("\nEnter affirmation to delete: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            deleteAffirmation(aff, &n, t1);
        }
        else if (choice == 3) 
		{
            printf("\nOld affirmation: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            printf("\nNew affirmation (max 7 words): ");
            fgets(t2, LEN, stdin); 
			t2[strcspn(t2, "\n")] = 0;
            updateAffirmation(aff, n, t1, t2);
        }
        else if (choice == 4) 
		{
            printf("Search: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            searchAffirmations(aff, n, t1);
        }
        else if (choice == 5) 
		displayAffirmations(aff, n);
    }
    return 0;
}


#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 200

int wordCount(char *str) 
{
    int count = 0;
    int flag = 0;

    while (*str != '\0') 
    {
        if (*str != ' ' && *str != '\t') 
        {
            if (flag == 0) 
            {
                count++;
                flag = 1;
            }
        }
        else 
        {
            flag = 0;
        }
        str++;
    }
    return count;
}
void displayTags(char tags[MAX][LEN], int n) 
{
	int i;
    for (i = 0; i < n; i++)
        printf("\n%d. %s\n", i + 1, tags[i]);
}
void addTag(char tags[MAX][LEN], int *n, char *newTag) 
{
    if (*n >= MAX) 
	{ 
        printf("\nTag list full.\n"); 
        return; 
    }

    int words = wordCount(newTag);

    if (words < 5 || words > 7) 
    {
        printf("\nTag must be 5-7 words.\n");
        return;
    }

    strcpy(tags[*n], newTag);
    (*n)++;
    printf("\nTag added.\n");
}
void deleteTag(char tags[MAX][LEN], int *n, char *tag) 
{
	int i,j;
    for (i = 0; i < *n; i++) 
    {
        if (strcmp(tags[i], tag) == 0) 
        {
            for (j = i; j < *n - 1; j++)
                strcpy(tags[j], tags[j + 1]);
            (*n)--;
            printf("\nDeleted.\n");
            return;
        }
    }
    printf("\nTag not found.\n");
}
void updateTag(char tags[MAX][LEN], int n, char *oldTag, char *newTag) 
{
	int i;
    for (i = 0; i < n; i++) 
    {
        if (strcmp(tags[i], oldTag) == 0) 
        {
            int words = wordCount(newTag);

            if (words < 5 || words > 7) 
            {
                printf("\nTag must be 5-7 words.\n"); 
                return;
            }

            strcpy(tags[i], newTag);
            printf("\nUpdated.\n");
            return;
        }
    }
    printf("\nTag not found.\n");
}
void searchTags(char tags[MAX][LEN], int n, char *key) 
{
    int i, found = 0;

    for (i = 0; i < n; i++) 
    {
        if (strstr(tags[i], key)) 
        {
            printf("%s\n", tags[i]);
            found = 1;
        }
    }
    if (!found) 
        printf("\nNo matching tags.\n");
}
int main()
{
    char tags[MAX][LEN], t1[LEN], t2[LEN];
    int n = 0, choice, i;

    printf("DIGITAL CAMERA\n");
    printf("______________\n");

    FILE *fp = fopen("tags.txt", "r");
    if (fp) 
    {
        while (fgets(tags[n], LEN, fp) && n < MAX) 
        {
            tags[n][strcspn(tags[n], "\n")] = 0;
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
            fp = fopen("tags.txt", "w");
            for (i = 0; i < n; i++)
                fprintf(fp, "%s\n", tags[i]);
            fclose(fp);

            printf("\nSaved.\n");
            break;
        }
        if (choice == 1) 
        {
            printf("\nEnter new tag (5-7 words): ");
            fgets(t1, LEN, stdin);
            t1[strcspn(t1, "\n")] = 0;
            addTag(tags, &n, t1);
        }
        else if (choice == 2) 
        {
            printf("\nEnter tag to delete: ");
            fgets(t1, LEN, stdin);
            t1[strcspn(t1, "\n")] = 0;
            deleteTag(tags, &n, t1);
        }
        else if (choice == 3) 
        {
            printf("\nOld tag: ");
            fgets(t1, LEN, stdin);
            t1[strcspn(t1, "\n")] = 0;

            printf("\nNew tag (5-7 words): ");
            fgets(t2, LEN, stdin);
            t2[strcspn(t2, "\n")] = 0;

            updateTag(tags, n, t1, t2);
        }
        else if (choice == 4) 
        {
            printf("Search: ");
            fgets(t1, LEN, stdin);
            t1[strcspn(t1, "\n")] = 0;
            searchTags(tags, n, t1);
        }
        else if (choice == 5) 
        {
            displayTags(tags, n);
        }
    }
    return 0;
}

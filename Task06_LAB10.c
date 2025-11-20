#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 200

int countWords(char *str) 
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
void displayNotes(char notes[MAX][LEN], int n) 
{
	int i;
    for (i = 0; i < n; i++) 
	printf("\n%d. %s\n", i + 1, notes[i]);
}
void addNote(char notes[MAX][LEN], int *n, char *note) 
{
    if (*n >= MAX) 
	{ 
	printf("\nNotes full.\n"); 
	return; }
	
    strcpy(notes[*n], note);
    (*n)++;
}
void deleteNote(char notes[MAX][LEN], int *n, char *note) 
{
	int i,j;
    for (i = 0; i < *n; i++) 
	{
        if (strcmp(notes[i], note) == 0) 
		{
            for (j = i; j < *n - 1; j++)
                strcpy(notes[j], notes[j + 1]);
            (*n)--;
            printf("\nDeleted.\n");
            return;
        }
    }
    printf("\nNote not found.\n");
}
void updateNote(char notes[MAX][LEN], int n, char *oldNote, char *newNote) 
{
	int i;
    for (i = 0; i < n; i++) 
	{
        if (strcmp(notes[i], oldNote) == 0) 
		{
            strcpy(notes[i], newNote);
            printf("\nUpdated.\n");
            return;
        }
    }
    printf("\nNote not found.\n");
}
void searchNotes(char notes[MAX][LEN], int n, char *key) 
{
    int i,found = 0;
    for (i = 0; i < n; i++)
	 {
        if (strstr(notes[i], key)) 
		{
            printf("%s\n", notes[i]);
            found = 1;
        }
    }
    if (!found) printf("\nNo matching notes.\n");
}
int countWord(char notes[MAX][LEN], int n, char *word) 
{
    int i, total = 0;
    for (i = 0; i < n; i++) 
	{
        char *p = notes[i];
        while ((p = strstr(p, word))) 
		{
            total++;
            p += strlen(word);
        }
    }
    return total;
}

int main() 
{
    char notes[MAX][LEN], t1[LEN], t2[LEN];
    int i,n = 0, choice;

    printf("PODCAST RECORDNG TOOL\n");
    printf("_____________________\n");
    
    FILE *fp = fopen("episodes.txt", "r");
    if (fp) 
	{
        while (fgets(notes[n], LEN, fp) && n < MAX) 
		{
            notes[n][strcspn(notes[n], "\n")] = 0;
            n++;
        }
        fclose(fp);
    }
    while (1) 
	{
        printf("\n1 Add\n2 Delete\n3 Update\n4 Search\n5 Display\n6 Count Word\n7 For Exit (Enter -1)\nChoice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == -1)
		 {
            fp = fopen("episodes.txt", "w");
            for (i = 0; i < n; i++) 
			fprintf(fp, "%s\n", notes[i]);
            fclose(fp);
            printf("\nSaved.\n");
            break;
        }
        if (choice == 1) 
		{
            printf("\nEnter new note: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            addNote(notes, &n, t1);
        }
        else if (choice == 2) 
		{
            printf("\nEnter note to delete: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            deleteNote(notes, &n, t1);
        }
        else if (choice == 3) 
		{
            printf("\nOld note: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            printf("\nNew note: ");
            fgets(t2, LEN, stdin); 
			t2[strcspn(t2, "\n")] = 0;
            updateNote(notes, n, t1, t2);
        }
        else if (choice == 4) 
		{
            printf("Search: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            searchNotes(notes, n, t1);
        }
        else if (choice == 5) 
		    displayNotes(notes, n);

        else if (choice == 6) 
		{
            printf("\nWord to count: ");
            fgets(t1, LEN, stdin); 
			t1[strcspn(t1, "\n")] = 0;
            int c = countWord(notes, n, t1);
            printf("\nTotal occurrences: %d\n", c);
        }
    }
    return 0;
}

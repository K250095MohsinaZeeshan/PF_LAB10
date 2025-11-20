#include <stdio.h>
#include <string.h>

#define MAX 10
#define LEN 200

void sort(char a[][LEN], int n)
{
    char t[LEN];
    int i,j;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(strcmp(a[i],a[j])>0)
            {
                strcpy(t,a[i]); 
                strcpy(a[i],a[j]); 
                strcpy(a[j],t);
            }
}
int find(char a[][LEN], int n, char *key)
{
    int i;
    for(i=0;i<n;i++)
        if(strcmp(a[i], key)==0) 
            return i;
    return -1;
}
int main()
{
    printf("MUSIC STREAMING DEVICE\n");
    printf("______________________\n");
    
    char list[MAX][LEN], buf[LEN];
    int n=0, ch;
    int i,j;

    FILE *fp=fopen("playlist.txt","r");
    if(fp)
    {
        while(n<MAX && fgets(list[n], LEN, fp))
        {
            list[n][strcspn(list[n], "\n")] = 0;
            n++;
        }
        fclose(fp);
    }
    while(1)
    {
        printf("\n1-Add\n2-Delete\n3-Update\n4-Search\n(Enter -1 to Exit)\n");
        scanf("%d", &ch); 
        getchar();

        if(ch==-1) break;

        if(ch==1 && n<MAX)
        {
            printf("\nEnter title: ");
            fgets(list[n], LEN, stdin);
            list[n][strcspn(list[n], "\n")] = 0;
            n++;
        }
        else if(ch==2)
        {
            printf("Delete: ");
            fgets(buf, LEN, stdin);
            buf[strcspn(buf,"\n")] = 0;
            int i = find(list, n, buf);
            if(i>=0)
            {
                for(j=i;j<n-1;j++) 
                    strcpy(list[j], list[j+1]);
                n--;
            }
        }
        else if(ch==3)
        {
            printf("Update: ");
            fgets(buf, LEN, stdin);
            buf[strcspn(buf,"\n")] = 0;
            int i = find(list, n, buf);
            if(i>=0)
            {
                printf("\nNew title: ");
                fgets(list[i], LEN, stdin);
                list[i][strcspn(list[i],"\n")] = 0;
            }
        }
        else if(ch==4)
        {
            printf("Search: ");
            fgets(buf, LEN, stdin);
            buf[strcspn(buf,"\n")] = 0;
            int i = find(list, n, buf);
            printf(i>=0 ? "\nFound at position %d\n" : "\nNot found\n", i+1);
        }
    }

    printf("\nSorting playlist alphabetically before exit...\n");
    sort(list, n);

    fp = fopen("playlist.txt","w");
    for(i=0;i<n;i++) 
        fprintf(fp,"%s\n",list[i]);
    fclose(fp);

    printf("\nFinal Playlist (Alphabetical Order):\n");
    for(i=0;i<n;i++)
        printf("%d. %s\n", i+1, list[i]);

    return 0;
}


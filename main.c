#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item
{
    int id;
    char name[50];
    char category[50];
    char location[50];
    char status[20];
};

void addLostItem();
void addFoundItem();
void displayItems();
void searchItem();

int main()
{
    int choice;

    while (1)
    {
        printf("\n===== LOST AND FOUND MANAGEMENT SYSTEM =====\n");
        printf("1. Add Lost Item\n");
        printf("2. Add Found Item\n");
        printf("3. Display All Items\n");
        printf("4. Search Item\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addLostItem();
            break;

        case 2:
            addFoundItem();
            break;

        case 3:
            displayItems();
            break;

        case 4:
            searchItem();
            break;

        case 5:
            printf("Exiting Program...\n");
            exit(0);

        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

void addLostItem()
{
    FILE *fp;
    struct Item item;

    fp = fopen("records.txt", "a");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Item ID: ");
    scanf("%d", &item.id);

    getchar();

    printf("Enter Item Name: ");
    fgets(item.name, sizeof(item.name), stdin);
    item.name[strcspn(item.name, "\n")] = '\0';

    printf("Enter Category: ");
    fgets(item.category, sizeof(item.category), stdin);
    item.category[strcspn(item.category, "\n")] = '\0';

    printf("Enter Lost Location: ");
    fgets(item.location, sizeof(item.location), stdin);
    item.location[strcspn(item.location, "\n")] = '\0';

    strcpy(item.status, "Lost");

    fprintf(fp, "%d|%s|%s|%s|%s\n",
            item.id,
            item.name,
            item.category,
            item.location,
            item.status);

    fclose(fp);

    printf("Lost Item Added Successfully!\n");
}

void addFoundItem()
{
    FILE *fp;
    struct Item item;

    fp = fopen("records.txt", "a");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Item ID: ");
    scanf("%d", &item.id);

    getchar();

    printf("Enter Item Name: ");
    fgets(item.name, sizeof(item.name), stdin);
    item.name[strcspn(item.name, "\n")] = '\0';

    printf("Enter Category: ");
    fgets(item.category, sizeof(item.category), stdin);
    item.category[strcspn(item.category, "\n")] = '\0';

    printf("Enter Found Location: ");
    fgets(item.location, sizeof(item.location), stdin);
    item.location[strcspn(item.location, "\n")] = '\0';

    strcpy(item.status, "Found");

    fprintf(fp, "%d|%s|%s|%s|%s\n",
            item.id,
            item.name,
            item.category,
            item.location,
            item.status);

    fclose(fp);

    printf("Found Item Added Successfully!\n");
}

void displayItems()
{
    FILE *fp;
    struct Item item;

    fp = fopen("records.txt", "r");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\n===== ITEM RECORDS =====\n");

    while (fscanf(fp,
                  "%d|%49[^|]|%49[^|]|%49[^|]|%19[^\n]\n",
                  &item.id,
                  item.name,
                  item.category,
                  item.location,
                  item.status) == 5)
    {
        printf("\nID: %d\n", item.id);
        printf("Name: %s\n", item.name);
        printf("Category: %s\n", item.category);
        printf("Location: %s\n", item.location);
        printf("Status: %s\n", item.status);
    }

    fclose(fp);
}

void searchItem()
{
    FILE *fp;
    struct Item item;
    char searchName[50];
    int found = 0;

    fp = fopen("records.txt", "r");

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    getchar();

    printf("\nEnter Item Name to Search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    while (fscanf(fp,
                  "%d|%49[^|]|%49[^|]|%49[^|]|%19[^\n]\n",
                  &item.id,
                  item.name,
                  item.category,
                  item.location,
                  item.status) == 5)
    {
        if (strcmp(item.name, searchName) == 0)
        {
            printf("\n===== ITEM FOUND =====\n");
            printf("ID: %d\n", item.id);
            printf("Name: %s\n", item.name);
            printf("Category: %s\n", item.category);
            printf("Location: %s\n", item.location);
            printf("Status: %s\n", item.status);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Item Not Found!\n");
    }

    fclose(fp);
}
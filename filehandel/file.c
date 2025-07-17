#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct accounts
{
    int n;
    char account_number[3][10]; // 3 accounts, each up to 9 chars + null
    int pass[3];
    int money[3];
};

struct user
{
    char name[20];
    char phone_number[10];
    struct accounts b[3];
    int type;
};

void menu();
int choice(struct user *a[20], char number[10]);
int create_account(struct user *a[20]);
int login(struct user *a[20], char number[10]);
int check(struct user *a[20], char number[10]);
int working(struct user *a[20], int index1, int index2);
int check_length(char *str, int max_length);

int main()
{
    struct user *u[20] = {NULL};
    char input_number[10];

    for (int i = 0; i < 20; i++)
    {
        u[i] = (struct user *)malloc(sizeof(struct user));
        if (u[i] == NULL)
        {
            perror("Memory allocation failed");
            return 1;
        }
        memset(u[i], 0, sizeof(struct user));
    }

    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("\033[1;31mError opening file.\033[0m\n");
        return 1;
    }

    for (int i = 0; i < 20; i++)
    {
        if (fread(u[i], sizeof(struct user), 1, fp) != 1)
        {
            break;
        }
    }
    fclose(fp);

    printf("\n\033[1;36m========================================\n");
    printf(" Welcome to the Bank Management System\n");
    printf("========================================\033[0m\n");

    while ((choice(u, input_number) != 1))
        ;

    fp = fopen("data.txt", "w");
    if (fp == NULL)
    {
        perror("Error opening file for writing");
    }

    for (int i = 0; i < 20; i++)
    {
        if (u[i]->phone_number[0] != '\0')
        {
            fwrite(u[i], sizeof(struct user), 1, fp);
        }
    }

    fclose(fp);
    for (int i = 0; i < 20; i++)
    {
        free(u[i]);
    }

    printf("\n\033[1;32mThank you for using the Bank Management System!\033[0m\n");
    return 0;
}

void menu()
{
    printf("\n\033[1;34m----------------------------------------\n");
    printf(" Main Menu\n");
    printf("----------------------------------------\033[0m\n");
    printf(" 1. \033[1;32mCreate an account\033[0m\n");
    printf(" 2. \033[1;34mLogin\033[0m\n");
    printf(" 3. \033[1;33mOpen menu\033[0m\n");
    printf(" 4. \033[1;31mExit\033[0m\n");
    printf("----------------------------------------\n");
    printf("Enter your choice: ");
}

int choice(struct user *a[20], char number[10])
{
    int c;
    menu();
    scanf("%d", &c);
    printf("\n");
    switch (c)
    {
    case 1:
        create_account(a);
        break;
    case 2:
        login(a, number);
        break;
    case 3:
        menu();
        break;
    default:
        printf("\033[1;31mExiting program...\033[0m\n");
        return 1;
    }
    return 0;
}

int check(struct user *a[20], char number[10])
{
    printf("\n\033[1;36m--- Account Check ---\033[0m\n");
    printf("Enter your phone number: ");
    scanf("%s", number);
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(a[i]->phone_number, number) == 0)
        {
            printf("\033[1;33mYour number is already registered.\033[0m\n");
            return 1;
        }
    }
    create_account(a);
    return 0;
}

int login(struct user *a[20], char number[10])
{
    int index1;
    int index2;
    char account[10];
    int pass;
    int ischeck = check(a, number);
    if (ischeck == 1)
    {
        printf("\n\033[1;36m--- Login ---\033[0m\n");
        printf("Enter your account number: ");
        scanf("%10s", account);
        printf("Enter your password: ");
        scanf("%4d", &pass);
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (strcmp(a[i]->b[j].account_number[j], account) == 0 && a[i]->b[j].pass[j] == pass)
                {
                    printf("\033[1;32mAccount found.\033[0m\n");
                    index1 = i;
                    index2 = j;
                    printf("You are logged in from the \033[1;36m%s\033[0m account.\n", a[index1]->b[index2].account_number[index2]);
                    working(a, index1, index2);
                    return 1;
                }
            }
        }
    }

    printf("\033[1;31mAccount not found.\033[0m\n");
    return 0;
}

int create_account(struct user *a[20])
{
    for (int i = 0; i < 20; i++)
    {
        if (a[i]->phone_number[0] == '\0')
        {
            printf("\n\033[1;36m--- Account Creation ---\033[0m\n");
            printf("Enter your name: ");
            scanf("%s", a[i]->name);
            printf("Enter your phone number: ");
            scanf("%10s",a[i]->phone_number);
            printf("How many accounts do you want to create (max 3)? ");
            scanf("%d", &a[i]->b[i].n);
            printf("Enter your account number and password for each account:\n");
            for (int j = 0; j < a[i]->b[i].n; j++)
            {
                printf("  Account %d number: ", j + 1);
                scanf("%10s", a[i]->b[j].account_number[j]);
                printf("  Password: ");
                scanf("%4d", &a[i]->b[j].pass[j]);
                printf("  Account type: ");
                scanf("%d", &a[i]->type);
                printf("  Initial balance: ");
                scanf("%d", &a[i]->b[j].money[j]);
                printf("\033[1;32mAccount number: %s, Password: %d created.\033[0m\n", a[i]->b[j].account_number[j], a[i]->b[j].pass[j]);
            }
            printf("\033[1;32mAccount(s) created successfully!\033[0m\n");
            return 1;
        }
    }
    printf("\033[1;31mNo space available to create a new account.\033[0m\n");
    return 0;
}

int working(struct user *a[20], int index1, int index2)
{
    int c, input_pass, input_money;
    while (1)
    {
        printf("\n\033[1;34m========= Account Menu =========\033[0m\n");
        printf(" 1. Withdraw money\n 2. Change password\n 3. Check balance\n 4. Logout\n 5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &c);

        if (c == 1)
        {
            printf("Enter your password: ");
            scanf("%d", &input_pass);
            if (input_pass == a[index1]->b[index2].pass[index2])
            {
                printf("\033[1;32mCorrect password.\033[0m\n");
                printf("Currently you have \033[1;33m%d\033[0m in your account.\n", a[index1]->b[index2].money[index2]);
                printf("Enter the amount to withdraw: ");
                scanf("%d", &input_money);
                if (input_money > 0 && input_money <= a[index1]->b[index2].money[index2])
                {
                    a[index1]->b[index2].money[index2] -= input_money;
                    printf("\033[1;32mWithdrawal successful.\033[0m Remaining balance: \033[1;33m%d\033[0m\n", a[index1]->b[index2].money[index2]);
                }
                else
                {
                    printf("\033[1;31mInvalid amount or insufficient balance.\033[0m\n");
                }
            }
            else
            {
                printf("\033[1;31mIncorrect password.\033[0m\n");
            }
        }
        else if (c == 2)
        {
            printf("Enter your current password: ");
            scanf("%d", &input_pass);
            if (input_pass == a[index1]->b[index2].pass[index2])
            {
                printf("Enter your new password: ");
                scanf("%d", &input_pass);
                a[index1]->b[index2].pass[index2] = input_pass;
                printf("\033[1;32mYour new password is set.\033[0m\n");
            }
            else
            {
                printf("\033[1;31mIncorrect current password.\033[0m\n");
            }
        }
        else if (c == 3)
        {
            printf("You have \033[1;33m%d\033[0m money in your account.\n", a[index1]->b[index2].money[index2]);
        }
        else if (c == 4)
        {
            printf("\033[1;35mYou are logged out from the %s account.\033[0m\n", a[index1]->b[index2].account_number[index2]);
            return 0;
        }
        else if (c == 5)
        {
            printf("\033[1;31mExiting...\033[0m\n");
            return 0;
        }
        else
        {
            printf("\033[1;31mInvalid option. Please try again.\033[0m\n");
        }
    }
    return 0;
}
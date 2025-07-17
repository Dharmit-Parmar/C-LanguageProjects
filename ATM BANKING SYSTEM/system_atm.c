#include <stdio.h>
#include <math.h>
#include <conio.h>

struct user 
{
    double account_number;
    char user_name[20];
    double balance;
    int pin; 
    int account_type; // 1 for Savings, 2 for Current
};
void menu();
int options(int *option);
int account(struct user *u);
int check_user(struct user users[], int *l, int total_users);
int check_pin(struct user *u);
int widrawl(struct user *u);
int change_pin(struct user *u);

int main()
{
    int n;
    int l;
    int ispin;

    struct user users[2] = {
        {1234567890,"dharmit", 100000.0, 112233, 1},
        {9876543210,"krish", 200000.0, 445566, 2}
    };

    int total_users = 2;

    do
    {
    int Isuser = check_user(users, &l, total_users);
    if (Isuser == 1)
    {
        printf("Welcome, User with Account Number: %.0lf\n", users[l].account_number);
        printf("Welcome, User with Account holder: %s\n\n\n\n\n", users[l].user_name);
        account(&users[l]);
        do 
        {
           
        
        options(&n);
        if (n == 3 )
        {
            account(&users[l]);
            break;
        }
        
        switch (n)
        {
        case 0:
            ispin = check_pin(&users[l]);
            if (ispin == 1)
            {
                widrawl(&users[l]);
            }
            break;

        case 1:
            change_pin(&users[l]);
            break;
        
        case 2 :
        options(&n);
        break;
        }
    }while(1);
    }
}while (1);

   
    return 0;
}
void menu(){
    printf("Choose one option:\n");
    printf("0 - Withdraw\n");
    printf("1 - Change PIN\n");
    printf("2 - open menu\n");
    printf("3 - Exit\n");
}
int options(int *option)
{
   
    menu();
    scanf("%d", option);

    if (*option < 0 || *option > 3)
    {
        printf("Invalid option selected. Please choose between 0, 1, or 2.\n");
    }
    else
    {
        printf("You selected option: %d\n", *option);
    }
    return 0;
}

int check_user(struct user users[], int *l, int total_users)
{
    double input_account_number;
    printf("Input the account number of the user: ");
    scanf("%lf", &input_account_number);

    for (int i = 0; i < total_users; i++)
    {
        if (users[i].account_number == input_account_number)
        {
            *l = i;
            printf("Account found\n");
            return 1;
        }
    }
    printf("Invalid account number\n");
    return 0;
}

int account(struct user *u)
{
    printf("---------account information-----------\n");
    printf("Account Number is : \t %.0lf\n", u->account_number);
    printf("Account holder is : \t %s\n", u->user_name);
    printf("Account Balance is : \t %.2lf\n", u->balance);
    printf("Account Type is : \t %s\n", u->account_type == 1 ? "Savings" : "Current");
    printf("--------------------------------------\n\n");
    return 0;
}

int check_pin(struct user *u)
{
    int input_pin;
    printf("Enter the pin here: ");
    scanf("%d", &input_pin);

    if (input_pin == u->pin)
    {
        return 1;
    }
    else
    {
        printf("Invalid pin\n");
    }
    return 0;
}

int widrawl(struct user *u)
{
    double amount;
    printf("Your current balance is: %.2lf\n", u->balance);
    printf("Enter the amount to withdraw: ");
    scanf("%lf", &amount);

    if (amount > u->balance)
    {
        printf("Insufficient balance!\n");
    }
    else
    {
        u->balance -= amount;
        printf("Withdrawal successful! Your new balance is: %.2lf\n", u->balance);
    }
    return 0;
}

int change_pin(struct user *u)
{
    int new_pin, old_pin;
    printf("Enter the old pin: ");
    scanf("%d", &old_pin);

    if (old_pin == u->pin)
    {
        printf("Enter the new pin here: ");
        scanf("%d", &new_pin);
        u->pin = new_pin;
        printf("Your new pin is: %d\n", u->pin);
    }
    else
    {
        printf("Invalid pin\n");
    }
    return 0;
}








//1 person holding more then one account
//after exit all the transiction can be seen like passbook(optianal)

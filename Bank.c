#include <stdio.h>
#include <string.h>

int a; // flag to indicate the account type
int bal1 = 548734; // balance for account type 1
int bal2 = 243532; // balance for account type 2

void deposit(int i); // function to deposit amount
void withdraw(int i); // function to withdraw amount

int main()
{
    int pin;
    char usn[10]; // username
    printf("         =====Welcome To Bank!!=====\n");
    printf("=============================================\n");
    printf("Please sign in to your account to continue\n");
    printf("PIN code: ");
    scanf("%d", &pin);
    switch (pin)
    {
    case 2316:
    {
        strcpy(usn, "Pranav");
        a = 1; // set account type to 1
        acc:
        while(1)
        {
            printf("=============================================\n");
            printf("         =====Account:%s=====\n", usn);
            printf("Options:\n1)Check account balance\n2)Deposit\n3)Withdraw\n4)Exit\n");
            printf("Enter your choice:");
            int ch;
            scanf("%d", &ch);
            switch (ch)
            {
            case 1:
            {
                printf("Balance is: Rs.%d\n", bal1);
            }
            break;
            case 2:
            {
                printf("Enter amount to deposit: Rs.");
                int dep;
                scanf("%d", &dep);
                deposit(dep);
                printf("Rs.%d has been sucessfully deposited in your account!\n", dep);
            }
            break;
            case 3:
            {
                printf("Enter amount to withdraw: Rs.");
                int w;
                scanf("%d", &w);
                if (w >= bal1)
                {
                    printf("You don't have Rs.%d in your account\n", w);
                }
                else
                {
                    withdraw(w);
                    printf("Rs.%d has been withdrawn from your account\n", w);
                }
            }
            break;
            case 4:
            {
                printf("            =====Exiting=====\n");
                return 0;
            }
            break;
            default:
            {
                printf("         =====Unknown Option Entered=====\n\n");
            }
            }
            goto acc;
        }
    }
    case 1099:
    {
        strcpy(usn, "Null");
        acc1:
        while(1)
        {
            printf("=============================================\n");
            printf("         =====Account:%s=====\n", usn);
            printf("Options:\n1)Check account balance\n2)Deposit\n3)Withdraw\n4)Exit\n");
            printf("Enter your choice:");
            int ch;
            scanf("%d", &ch);
            switch (ch)
            {
            case 1:
            {
                printf("Balance is: Rs.%d\n", bal2);
            }
            break;
            case 2:
            {
                printf("Enter amount to deposit: Rs.");
                int dep;
                scanf("%d", &dep);
                deposit(dep);
                printf("Rs.%d has been sucessfully deposited in your account!\n", dep);
            }
            break;
            case 3:
            {
                printf("Enter amount to withdraw: Rs.");
                int w;
                scanf("%d", &w);
                if (w >= bal2)
                {
                    printf("You don't have Rs.%d in your account\n", w);
                }
                else
                {
                    withdraw(w);
                    printf("Rs.%d has been withdrawn from your account\n", w);
                }
            }
            break;
            case 4:
            {
                printf("            =====Exiting=====\n");
                return 0;
            }
            break;
            default:
            {
                printf("         =====Unknown Option Entered=====\n\n");
            }
            }
            goto acc1;
        }
    }
    break;
    default:
    {
        printf("Unknown PIN entered\n");
        return 0;
    }
    }
}

void deposit(int i)
{
    if (a == 1)
    {
        bal1 += i;
    }
    else
    {
        bal2 += i;
    }
}

void withdraw(int i)
{
    if (a == 1)
    {
        bal1 -= i;
    }
    else
    {
        bal2 -= i;
    }
}



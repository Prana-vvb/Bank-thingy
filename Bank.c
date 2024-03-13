#include <stdio.h>
#include <string.h>

int a; // flag to indicate the account type
static int bal[] = {548734, 243532};
char usn[][10] = {"Pranav", "Null"}; // usernames

void deposit(int i); // function to deposit amount
void withdraw(int i); // function to withdraw amount
void acc(char *name, int bal);

int main()
{
    int pin;
    printf("         =====Welcome To Bank!!=====\n");
    printf("=============================================\n");
    printf("Please sign in to your account to continue\n");
    printf("PIN code: ");
    scanf("%d", &pin);
    switch (pin)
    {
    case 2316:
        acc(&usn[0][0], bal[0]);
        break;
    case 1099:
        acc(&usn[1][0], bal[0]);
        break;
    default:
        printf("Unknown PIN entered\n");
        return 0;
    }
}

void deposit(int i)
{
    if (a == 1)
    {
        bal[0] += i;
        printf("%d\n", bal[0]);
    }
    else
    {
        bal[1] += i;
    }
}

void withdraw(int i)
{
    if (a == 1)
    {
        bal[0] -= i;
    }
    else
    {
        bal[1] -= i;
    }
}

void acc(char *name, int bal)
{
    strcpy(usn, name);
        a = 1; // set account type to 1
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
                printf("Balance is: Rs.%d\n", bal);
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
                if (w >= bal)
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
                return;
            }
            break;
            default:
            {
                printf("         =====Unknown Option Entered=====\n\n");
            }
            }
        }
}



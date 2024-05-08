#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int accNo;
    char name[100];
    int pin;
    float bal;
}account;

void displayBalance(account *acc){
    printf("Balance is: Rs. %.2f\n", acc->bal);
}

void deposit(account *acc, float amount){
    acc->bal += amount;
}

void withdraw(account *acc, float amount){
    if(amount > acc->bal){
        printf("You don't have Rs. %.2f in your account\n", amount);
    }
    else{
        acc->bal -= amount;
        printf("Rs. %.2f has been withdrawn from your account\n", amount);
    }
}

void createAcc(account *acc, char *name, int pin, float amount){
    static int accNoCounter = 1;
    acc->accNo = accNoCounter++;
    strcpy(acc->name, name);
    acc->pin = pin;
    acc->bal = amount;
}

int main(){
    int numAccounts = 0;
    account *accounts = malloc(numAccounts * sizeof(account));

    int pin;
    printf("         =====Welcome To Bank!!=====\n");
    printf("=============================================\n");
    printf("Please sign in to your account by entering your PIN to continue or type 1 to create a new account\n");
    scanf("%d", &pin);

    if(pin == 1){
        char name[100];
        int newPin;
        float initialAmount;

        printf("Enter your name: ");
        scanf("%s", name);
        printf("Enter a PIN: ");
        scanf("%d", &newPin);
        printf("Enter initial deposit amount: Rs. ");
        scanf("%f", &initialAmount);

        accounts = realloc(accounts, (numAccounts + 1) * sizeof(account));
        createAcc(&accounts[numAccounts++], name, newPin, initialAmount);
        printf("New account created successfully!\n");

        pin = newPin;
    }

    int found = 0;
    account *currentAccount;
    for(int i = 0; i < numAccounts; i++){
        if (pin == accounts[i].pin) {
            currentAccount = &accounts[i];
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Unknown PIN entered\n");
        free(accounts);
        return 0;
    }

    while(1){
        printf("=============================================\n");
        printf("         =====Account: %s=====\n", currentAccount->name);
        printf("Options:\n1) Check account balance\n2) Deposit\n3) Withdraw\n4) Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch(choice){
            case 1:
                displayBalance(currentAccount);
                break;
            case 2:
                printf("Enter amount to deposit: Rs. ");
                float depositAmount;
                scanf("%f", &depositAmount);
                deposit(currentAccount, depositAmount);
                printf("Rs. %.2f has been successfully deposited in your account!\n", depositAmount);
                break;
            case 3:
                printf("Enter amount to withdraw: Rs. ");
                float withdrawAmount;
                scanf("%f", &withdrawAmount);
                withdraw(currentAccount, withdrawAmount);
                break;
            case 4:
                printf("            =====Exiting=====\n");
                free(accounts);
                return 0;
            default:
                printf("         =====Unknown Option Entered=====\n\n");
                break;
        }
    }
}

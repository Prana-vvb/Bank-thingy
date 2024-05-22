#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int accNo;
    char name[100];
    char accType[10];
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

void createAcc(FILE *fp, account *acc, char *name, char *type, int pin, float amount, int lc){
    acc->accNo = lc;
    strcpy(acc->name, name);
    strcpy(acc->accType, type);
    acc->pin = pin;
    acc->bal = amount;

    //Write to file
    int cols = 5;
    for(int i = 0; i < cols; i++){
        if(i != 0){
            fprintf(fp, ",");
        }
        switch(i){
            case 0:
                fprintf(fp, "%d", lc);
                break;
            case 1:
                fprintf(fp, "%s", name);
                break;
            case 2:
                fprintf(fp, "%s", type);
                break;
            case 3:
                fprintf(fp, "%d", pin);
                break;
            case 4:
                fprintf(fp, "%.2f", amount);
        }
    }
    fprintf(fp, "\n");
}

int numAcc(FILE *fp){
    char line[100];
    int count = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        char *token;
        int elements = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            elements++;
            token = strtok(NULL, ",");
        }
        if (elements == 5) {
            count++;
        }
    }
    return count;
}

int main(){
    FILE *fp = fopen("accounts.csv", "a+");
    int numAccounts = numAcc(fp);
    account *accounts = malloc(numAccounts * sizeof(account));
    int pin;

    printf("%d         =====Welcome To Bank!!=====\n", numAccounts);
    printf("=============================================\n");
    printf("Please sign in to your account by entering your PIN to continue or type 1 to create a new account\n");
    scanf("%d", &pin);

    if(pin == 1){
        numAccounts++;
        char name[100];
        char type[10];
        int newPin;
        float initialAmount;

        printf("Enter your name: ");
        scanf("%s", name);
        printf("Enter account type: ");
        scanf("%s", type);
        printf("Enter a PIN: ");
        scanf("%d", &newPin);
        printf("Enter initial deposit amount: Rs. ");
        scanf("%f", &initialAmount);

        accounts = realloc(accounts, numAccounts*sizeof(account));
        createAcc(fp, &accounts[numAccounts], name, type, newPin, initialAmount, numAccounts);
        printf("New account created successfully!\n");
        main();
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

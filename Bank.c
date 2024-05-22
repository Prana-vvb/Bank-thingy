#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int accNo;
    char name[100];
    char accType[10];
    int pin;
    float bal;
}account;

int lc = 0;

int read(FILE *fp, account *acc, int pin){
    char line[100];
    int count = 0;
    while(fgets(line, 100, fp) != NULL){
        acc->accNo = atoi(strtok(line, ","));
        strcpy(acc->name, strtok(NULL, ","));
        strcpy(acc->accType, strtok(NULL, ","));
        acc->pin = atoi(strtok(NULL, ","));
        acc->bal = atof(strtok(NULL, ","));
        if(acc->pin == pin){
            return 1;
        }
    }
    return 0;
}

int write(FILE *fp, account acc){
    int accNo;
    char line[100];
    long int pos;

    rewind(fp);
    while(fgets(line, 100, fp) != NULL){
        pos = ftell(fp);

        accNo = atoi(strtok(line, ","));
        if(accNo == acc.accNo){
            fseek(fp, pos, SEEK_SET);
            fprintf(fp, "%d,%s,%s,%d,%.2f\n", acc.accNo, acc.name, acc.accType, acc.pin, acc.bal);
            printf("Account modified successfully.\n");
            return 0;
        }
    }

    printf("Account not found.\n");
    return 1;
}

void displayBalance(account acc) {
    printf("Balance is: Rs. %.2f\n", acc.bal);
}

void deposit(account *acc, float amount) {
    acc->bal += amount;
    return;
}

void withdraw(account *acc, float amount) {
    if (amount > acc->bal) {
        printf("You don't have Rs. %.2f in your account\n", amount);
    } else {
        acc->bal -= amount;
        printf("Rs. %.2f has been withdrawn from your account\n", amount);
    }
    return;
}

void createAcc(FILE *fp){
    lc++;
    char name[100];
    char type[10];
    int pin;
    float amt;

    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter account type: ");
    scanf("%s", type);
    printf("Enter a PIN: ");
    scanf("%d", &pin);
    printf("Enter initial deposit amount: Rs. ");
    scanf("%f", &amt);

    fprintf(fp, "%d,%s,%s,%d,%.2f\n", lc, name, type, pin, amt);
    printf("New account created successfully!\n");
    return;
}

int numAcc(FILE *fp) {
    char line[100];
    int count = 0;
    while(fgets(line, sizeof(line), fp) != NULL){
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
    rewind(fp);
    return count;
}

int main(){
    FILE *fp = fopen("accounts.csv", "a+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    lc = numAcc(fp);

    account acc;
    int pin;

    printf("         =====Welcome To Bank!!=====\n");
    printf("=============================================\n");
    printf("Please sign in to your account by entering your PIN to continue or type 1 to create a new account\n");
    scanf("%d", &pin);

    if(pin == 1){
        createAcc(fp);

        printf("Please sign in to your account by entering your PIN to continue or type 1 to create a new account\n");
        scanf("%d", &pin);
    }

    int found = read(fp, &acc, pin);

    if(!found){
        printf("Unknown PIN entered\n");
        fclose(fp);
        return 0;
    }

    while(1){
        printf("=============================================\n");
        printf("         =====Account: %s=====\n", acc.name);
        printf("Options:\n1) Check account balance\n2) Deposit\n3) Withdraw\n4) Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch(choice){
            case 1:
                displayBalance(acc);
                break;
            case 2:
                printf("Enter amount to deposit: Rs. ");
                float depositAmount;
                scanf("%f", &depositAmount);
                deposit(&acc, depositAmount);
                printf("Rs. %.2f has been successfully deposited in your account!\n", depositAmount);
                break;
            case 3:
                printf("Enter amount to withdraw: Rs. ");
                float withdrawAmount;
                scanf("%f", &withdrawAmount);
                withdraw(&acc, withdrawAmount);
                break;
            case 4:
                char ch;
                printf("Save changes and exit?[y/n]: ");
                scanf(" %c", &ch);
                if(ch == 'y'){
                    int s = write(fp, acc);
                    if(s){
                        printf("Save unsuccessful!\n");
                        printf("            =====Exiting=====\n");
                        fclose(fp);
                        return s;
                    }
                    printf("Save successful!\n");
                    printf("            =====Exiting=====\n");
                    fclose(fp);
                    return s;
                }
                break;
            default:
                printf("         =====Unknown Option Entered=====\n\n");
                break;
        }
    }

    fclose(fp);
    return 0;
}

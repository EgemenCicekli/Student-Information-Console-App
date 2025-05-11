#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>



void ListTxtFiles();
void CreateNewClass();
void DeleteClass(char className[30]);
void GiveStudentsData(char className[30]);
void SearchStudent(int searchingID);
void ChangePassword(char password[30]);
void EncryptPassword(const char password[30], char *encryptedPassword);
void DecryptPassword(const char password[30], char *realPassword);


void Entrance(){
    bool isContinue = true;
    while(isContinue){


        FILE* fptr;



        if((fptr = fopen("AccountInfo.txt","r")) != NULL){
            char blockedPassword[30];
            char decryptedPassword[30];


            fgets(blockedPassword,sizeof(blockedPassword),fptr);



            DecryptPassword(blockedPassword,decryptedPassword);

            char userInput[30];

            printf("|Please enter your password|\n");
            fgets(userInput,30,stdin);

            if(strlen(userInput) >0 && userInput[strlen(userInput)-1] == '\n'){
                userInput[strlen(userInput)-1] = '\0';
            }

            for(int ch=0;userInput[ch] != '\0';ch++){
                if(isalpha(userInput[ch])){
                    userInput[ch] = tolower(userInput[ch]);

                }
            }

            if(strcmp(userInput,decryptedPassword) == 0){
                printf("Login successful!\n");
                fclose(fptr);
                isContinue = false;     //Time to pass
            }else {

                printf("Incorrect password! Please try again.\n");
            }


        }
        else{
            printf("There is missing file!");
            isContinue = false;
        }



    }



}



int main()
{
    printf("------------------Student Information System------------------\n");

    FILE *fptr = fopen("AccountInfo.txt","r");
    if (fptr != NULL) {
         Entrance();
        fclose(fptr);
        printf("Password successfully changed!\n");
    } else {
        printf("Set a password:\n");
        char password[30];
        scanf("%s",password);
        ChangePassword(password);
    }




    int operation;
    bool isContinue= true;

    int method;
    int studentId = 0;

    char newPass[30];

    while(isContinue){
            printf("------------------Please choose a operation-------------------\n");
            printf("1->List classes\n");
            printf("2->Read a class data\n");
            printf("3->Create a new class\n");
            printf("4->Delete a class\n");
            printf("5->Search a student\n");
            printf("6->Change password\n");
            printf("7->Exit\n");
            scanf("%d",&operation);

            switch (operation){
            case 1:
                ListTxtFiles();
                break;

            case 2:
                ListTxtFiles();

                printf("Please write a class name\n");

                char className[30];
                scanf("%s",className);

                GiveStudentsData(className);

                printf("--Successful!\n");

                break;

            case 3:
                CreateNewClass();
                printf("--Successful!\n");
                break;
            case 4:

                ListTxtFiles();
                printf("Please write a class name to delete\n");
                scanf("%s",className);

                DeleteClass(className);
                break;

            case 5:
                printf("Please enter the student ID:");
                scanf("%d",&studentId);
                if(isdigit(studentId)){SearchStudent(studentId);}



                break;
            case 6:
                printf("Write new password=>");
                scanf("%s",newPass);

                ChangePassword(newPass);
                break;
            case 7:
                printf("Good Bye");
                isContinue=false;
                break;
            }
    }

    return 0;
}
void ChangePassword(char password[30]){
    char encryptedPass[30];

    EncryptPassword(password,encryptedPass);

    FILE *fptr = fopen("AccountInfo.txt","w+");

    if (fptr != NULL) {
        fprintf(fptr, "%s", encryptedPass);
        fclose(fptr);
        printf("Password successfully changed!\n");
    } else {
        printf("Error\n");
    }
}

void SearchStudent(int searchingID){
    int id;
    char name[25];
    char sex[5];
    int age;

    struct dirent *de; // Directory entry pointer
    DIR *dir = opendir(".");

    if (dir == NULL) {
        printf("Could not find any student\n");
        return;
    }
    while ((de = readdir(dir)) != NULL) {

        char *fileName = de->d_name;
        int len = strlen(fileName);



        if (len >= 1 && strcmp(fileName + len - 4, ".txt") == 0) {
            FILE *fptr = fopen(fileName,"r");

            while(fscanf(fptr,"%d %s %d %s",&id,name,&age,sex) == 4){
                if(searchingID==id){
                    fileName[len - 4] = '\0';
                    printf("Student\nId=%d \nName=%s \nAge=%d \nSex=%s \nClass=%s\n",id,name,age,sex,fileName);
                }


            }
            fclose(fptr);

        }
    }
    closedir(dir);

}

void ListTxtFiles() {
    struct dirent *de; // Directory entry pointer
    DIR *dir = opendir(".");

    if (dir == NULL) {
        printf("Could not find any file\n");
        return;
    }
    printf("FILES:\n");

    while ((de = readdir(dir)) != NULL) {

        char *name = de->d_name;
        int len = strlen(name);

        if (len >= 1 && strcmp(name + len - 4, ".txt") == 0 && strcmp(name, "AccountInfo.txt") != 0) {
            printf("%s\n", name);
        }
    }

    closedir(dir);
}

void GiveStudentsData(char className[30]){
    int id;
    char name[25];
    char sex[5];
    int age;

    char fileName[35];

    snprintf(fileName,sizeof(fileName),"%s.txt",className);

    FILE *fptr = fopen(fileName,"r");


    while(fscanf(fptr,"%d %s %d %s",&id,name,&age,sex) == 4){
        printf("|%d |%s |%d |%s |\n",id,name,age,sex);

    }
    fclose(fptr);
}

void CreateNewClass(){
    FILE *fptr;
    char className[30];
    char fileName[35];

    printf("Write the class name ->");
    scanf("%s",className);

    snprintf(fileName,sizeof(fileName),"%s.txt",className);

    fptr = fopen(fileName,"w");

    fclose(fptr);
}

void DeleteClass(char className[30]){
    char fileName[35];

    snprintf(fileName,sizeof(fileName),"%s.txt",className);

    if (remove(fileName) == 0) {
        printf("%s deleted successfully.\n",className);
    } else {
        printf("Error: Unable to delete the file.\n");
    }
}


void DecryptPassword(const char password[30],char *realPassword){
    int reffNumber = 0;

    //Find shift number
    for(int i=0;password[i] != '\0';i++){

        if(isdigit(password[i])){
        reffNumber += password[i] - '0';
     }
    }

    for(int i=0;password[i] != '\0';i++){
        char ch = password[i];
        if(isalpha(ch)){
            ch = tolower(password[i]);
            realPassword[i] = ((ch - 'a' - reffNumber +26)% 26) + 'a';
        }
        else{
            realPassword[i] = ch;
        }

    }
    realPassword[strlen(password)] = '\0';
}


void EncryptPassword(const char password[30],char *encryptedPassword){
    int reffNumber = 0;

    //Find shift number
    for(int i=0;password[i] != '\0';i++){
        if(isdigit(password[i])){
        reffNumber += password[i] - '0';

     }
    }
    char ch;
    for(int i=0;password[i] != '\0';i++){
        ch = password[i];
        if(isalpha(ch)){
            encryptedPassword[i] = ((ch - 'a' + reffNumber ) % 26) + 'a';//Encryption

        }else {
            encryptedPassword[i] = ch;
        }
    }

    encryptedPassword[strlen(password)] = '\0';
}




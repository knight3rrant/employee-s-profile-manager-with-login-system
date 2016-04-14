#include <stdio.h> ///for input output functions like printf, scanf
#include <stdlib.h>
#include <windows.h> ///for windows related functions (not important)
#include <string.h>  ///string operations

/** List of Global Variable */
COORD coord = {0,0}; /// top-left corner of window


void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/** Main function started */
int mainapp();
int logingate();
int main () {

    logingate();
}








int logingate() {
    struct workers{
        char name[10];
        char password[20];
    };
    struct workers s;

    char option;
    char u[12],p[12];
    long int logsize;

    FILE *fptr;
    fptr = fopen("login.txt","rb+");
    if(fptr == NULL)
    {
        fptr = fopen("login.txt","wb+");
        if(fptr == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }
    logsize = sizeof(s);
    int retry=3;
    printf("\tPlease Choose your Option\n");
    printf("\n\t1. Login");
    printf("\n\t2. Registration\n");
    fflush(stdin); /// flush the input buffer
    option  = getche();
    system("cls");
    switch(option){

        case '1':


            do {

                printf("\tEnter username: ");
                scanf("%s",u);
                printf("\tEnter password: ");
                scanf("%s",p);
                rewind(fptr);
                while(fread(&s,logsize,1,fptr)==1) {

                    if(strcmp(s.name,u) == 0 && strcmp(s.password,p) == 0) {

                        mainapp();
                    }
                    else{
                        system("cls");
                        printf("\tAccess Denied. \n");

                        if (retry==1) {
                            printf("\n\tProgram Closing.\n");
                            exit(0);
                        }
                        else {

                            printf("\tPlease try again.%d more try left!!\n",retry-1);
                            retry--;
                            break;
                        }
                    }
                }
            }while (retry>0);
            break;
        case '2':
            system("cls");
            fseek(fptr,0,SEEK_END);
            printf("\tYour given info will be stored for future login.\n");
            printf("\tUser name: ");
            scanf("%s", s.name);
            printf("\tPassword: ");
            scanf("%s", s.password);

            fwrite(&s,logsize,1,fptr);
            fclose(fptr);  /// close the file
            system("cls");
            printf("\tInformation saved!\n\tPress space to back to login page.\n");
            getch();
            system("cls");
            logingate();
            break;

        default:
            printf("\n\twrong input pressed! program ending!\n");

    }


    return 0;
}















int mainapp()
{
    FILE *fp, *ft; /// file pointers
    char another, choice;

    /** structure that represent a employee */
    struct emp
    {
        char name[40]; ///name of employee
        int age; /// age of employee
        float bs; /// basic salary of employee
    };

    struct emp e; /// structure variable creation

    char empname[40]; /// string to store name of the employee

    long int recsize; /// size of each record of employee

    /** open the file in binary read and write mode
     * if the file EMP.DAT already exists then it open that file in read write mode
     * if the file doesn't exit it simply create a new copy
     */
    fp = fopen("EMP.txt","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.txt","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }

    /// sizeo of each record i.e. size of structure variable e
    recsize = sizeof(e);

    /// infinite loop continues untile the break statement encounter
    while(1)
    {
        system("cls"); ///clear the console window
        gotoxy(15,7);
        printf(":::: Employee's Record Management System ::::: ");
        gotoxy(30,8);
        printf("-by Knight3rrant");
        gotoxy(30,10); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. Add Record"); /// option for add record
        gotoxy(30,12);
        printf("2. List Records"); /// option for showing existing record
        gotoxy(30,14);
        printf("3. Modify Records"); /// option for editing record
        gotoxy(30,16);
        printf("4. Delete Records"); /// option for deleting record
        gotoxy(30,18);
        printf("5. About"); /// option for About the software
        gotoxy(30,20);
        printf("6. Exit"); /// exit from the program
        gotoxy(30,22);
        printf("Your Choice: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        choice  = getche(); /// get the input from keyboard
        switch(choice)
        {
            case '1':  /// if user press 1
                system("cls");
                fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
                /// here 0 indicates moving 0 distance from the end of the file

                another = 'y';
                while(another == 'y')  /// if user want to add another record
                {
                    printf("\n\tEnter name: ");
                    scanf("%s",e.name);
                    printf("\n\tEnter age: ");
                    scanf("%d", &e.age);
                    printf("\n\tEnter basic salary: ");
                    scanf("%f", &e.bs);

                    fwrite(&e,recsize,1,fp); /// write the record in the file

                    printf("\n\tAdd another record(y/n) ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '2':
                system("cls");
                rewind(fp); ///this moves file cursor to start of the file
                printf("\tName\tAge\tSalary");
                while(fread(&e,recsize,1,fp)==1)  /// read the file and fetch the record one record per fetch
                {
                    printf("\n\t%s\t%d\t%.2f",e.name,e.age,e.bs); /// print the name, age and basic salary
                }
                getch();
                break;

            case '3':  /// if user press 3 then do editing existing record
                system("cls");
                another = 'y';
                while(another == 'y')
                {
                    printf("\tEnter the employee name to modify: ");
                    scanf("%s", empname);
                    rewind(fp);
                    while(fread(&e,recsize,1,fp)==1)  /// fetch all record from file
                    {
                        if(strcmp(e.name,empname) == 0)  ///if entered name matches with that in file
                        {
                            printf("\n\tEnter name: ");
                            scanf("%s",e.name);
                            printf("\n\tEnter age: ");
                            scanf("%d", &e.age);
                            printf("\n\tEnter basic salary: ");
                            scanf("%f", &e.bs);
                            fseek(fp,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                            fwrite(&e,recsize,1,fp); /// override the record
                            break;
                        }
                    }
                    printf("\n\tModify another record(y/n)");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '4':
                system("cls");
                another = 'y';
                while(another == 'y')
                {
                    printf("\n\tEnter name of employee to delete: ");
                    scanf("%s",empname);
                    ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                    rewind(fp); /// move record to starting of file
                    while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                    {
                        if(strcmp(e.name,empname) != 0)  /// if the entered record match
                        {
                            fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                        }
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("EMP.DAT"); /// remove the orginal file
                    rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                    fp = fopen("EMP.DAT", "rb+");
                    printf("\tDelete another record(y/n)");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '5':
                system("cls");
                gotoxy(10,5);
                printf("This is the very basic type of application for \n\temployee's information storing.\n\tThis application is build by Golam Rabbani & Ferdaus Rahman (_)\n\tThank You!");

                getch();
                break;
            case '6':
                fclose(fp);  /// close the file
                exit(0); /// exit from the program
        }
    }
    return 0;
}

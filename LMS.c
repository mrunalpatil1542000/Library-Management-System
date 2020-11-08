//Program for Library management system.
//update book module
#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 20
#define MAX_SIZE_PASSWORD  10
#define FILE_NAME  "LibraryBookData.bin"
// Macro related to the books info
#define MAX_BOOK_NAME   30
#define MAX_AUTHOR_NAME 30
#define MAX_STUDENT_NAME 30
#define MAX_STUDENT_ADDRESS 100
#define MAX_STUDENT_CLASS 20
#define FILE_HEADER_SIZE  sizeof(sFileHeader)

//structures to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;
typedef struct
{
    unsigned int bookid;
    char bookName[MAX_BOOK_NAME];
    char authorName[MAX_AUTHOR_NAME];
    char studentName[MAX_STUDENT_NAME];
    char studentAddr[MAX_STUDENT_ADDRESS];
    char studentClass[MAX_STUDENT_CLASS];
    Date bookIssueDate;
    Date bookArrivalDate;
              //structure Date object.
} BooksInfo;

//Function declarations..
void welcomeMessage();
int isNameValid(const char *);
int  IsLeapYear(int);
int isValidDate(Date *);
void add_books();
void search_books();
void delete_books();
void view_books();
void update_credentials();
void menu();
void init();
void validate();
int isFileExists(const char *);


//main starts..
int main()
{
    init();//to initiate logins
    welcomeMessage();
    validate();
    return 0;
}

//Functions definitions...
void welcomeMessage()
{
    printf("\n===============================================================================================");
    printf("\n**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**");
    printf("\n**_**                                   WELCOME TO                                        **_**");
    printf("\n**_**                               LIBRARY MANAGEMENT                                    **_**");
    printf("\n**_**                                    SYSTEM                                           **_**");
    printf("\n**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**_**");
    printf("\n===============================================================================================");
    printf("\n\nEnter any key to START....");
    getchar();
}
int isNameValid(const char *name)
{
    int validName = 0;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(((name[index]>=65 || name[index]<=91) ||(name[index]>=97 || name[index]<=123)) || (name[index]==""))
        {
            validName = 1;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
// Add books in list
void add_books()
{
    BooksInfo addBook = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("Can not add. Something went wrong.. :(\n");
        exit(1);
    }

    printf("\n\t\t\tBook ID NO  = ");
    fflush(stdin);
    scanf("%u",&addBook.bookid);

    printf("\n\t\t\tBook Name  = ");
    fflush(stdin);
    fgets(addBook.bookName,MAX_BOOK_NAME,stdin);

    do
    {
        printf("\n\t\t\tAuthor Name  = ");
        fflush(stdin);
        fgets(addBook.authorName,MAX_AUTHOR_NAME,stdin);
        status = isNameValid(addBook.authorName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }while(!status);

    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter book Arrival date in format (day/month/year): ");
        scanf("%d/%d/%d",&addBook.bookArrivalDate.dd,&addBook.bookArrivalDate.mm,&addBook.bookArrivalDate.yyyy);
        //check date validity
        status = isValidDate(&addBook.bookArrivalDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }while(!status);

    do
    {
        printf("\n\t\t\tStudent Name  =  (Not have Press ENTER)");
        fflush(stdin);
        fgets(addBook.studentName,MAX_STUDENT_NAME,stdin);
        status = isNameValid(addBook.studentName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }while(!status);

    if(strlen(addBook.studentName)>1)
    {
    do
    {
         printf("\n\t\t\tStudent Class   = ");
        fflush(stdin);
        fgets(addBook.studentClass,MAX_STUDENT_CLASS,stdin);
        printf("\n\t\t\tStudent Address  = ");
        fflush(stdin);
        fgets(addBook.studentAddr,MAX_STUDENT_ADDRESS,stdin);

        //get date year,month and day from user
        printf("\n\t\t\tEnter Issue date in format (day/month/year): ");
        scanf("%d/%d/%d",&addBook.bookIssueDate.dd,&addBook.bookIssueDate.mm,&addBook.bookIssueDate.yyyy);
        //check date validity
        status = isValidDate(&addBook.bookIssueDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }while(!status);
    }

    fwrite(&addBook,sizeof(addBook), 1, fp);
    fclose(fp);
    printf("\n\t\t\tBook added successfully.");
    getchar();
}

// search books
void search_books()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    BooksInfo addBook = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tRecord can not searched. Something went wrong.. :(\n");
        exit(1);
    }

    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Book Name to search:");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&addBook, sizeof(addBook), 1, fp))
    {
        if(!strcmp(addBook.bookName, bookName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\nBook id = %u",addBook.bookid);
        printf("\nBook Name = %s",addBook.bookName);
        printf("\nBook authorName = %s",addBook.authorName);
        printf("\nStudent Name = %s",addBook.studentName);
        printf("\nStudent Address = %s",addBook.studentAddr);
        printf("\nStudent Class = %s",addBook.studentClass);
        printf("\nBook arrival date(day/month/year) =  %d/%d/%d",addBook.bookArrivalDate.dd,
               addBook.bookArrivalDate.mm, addBook.bookArrivalDate.yyyy);
        printf("\nBook issue date(day/month/year) =  %d/%d/%d",addBook.bookIssueDate.dd,
               addBook.bookIssueDate.mm, addBook.bookIssueDate.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Books Available.");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key for main menu.....");
    getchar();
}

// v books function
void view_books()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    BooksInfo addBook = {0};
    FILE *fp = NULL;
    unsigned int countBook = 1;

    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("Books can not viewed. Something went wrong.. :(\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&addBook, sizeof(addBook), 1, fp))
    {
        printf("\n\t\t\tBook Count = %d\n\n",countBook);
        printf("\t\t\tBook id = %u",addBook.bookid);
        printf("\n\t\t\tBook name = %s",addBook.bookName);
        printf("\n\t\t\tBook authorName = %s",addBook.authorName);
        printf("\n\t\t\tBook Arrival date(day/month/year) =  (%d/%d/%d)",addBook.bookArrivalDate.dd,
               addBook.bookArrivalDate.mm, addBook.bookArrivalDate.yyyy);
        printf("\n\t\t\tStudent Name = %s",addBook.studentName);
        printf("\n\t\t\tStudent Address = %s",addBook.studentAddr);
        printf("\n\t\t\tStudent Class = %s",addBook.studentClass);
        printf("\n\t\t\tBook issue date(day/month/year) =  (%d/%d/%d)\n\n",addBook.bookIssueDate.dd,
               addBook.bookIssueDate.mm, addBook.bookIssueDate.yyyy);
        found = 1;
        countBook++;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Books Available.");
    }
    printf("\n\n\t\t\tPress any key for main menu.....");
    fflush(stdin);
    getchar();
}
// delete function
void delete_books() //copy all elements except deleting one in temp file from source file then delete source file and rename temp file as source file.
{
    int found = 0;
    int bookDeleteId = 0;
    sFileHeader credentials = {0};
    char bookName[MAX_BOOK_NAME] = {0};
    BooksInfo deletebook = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&credentials,FILE_HEADER_SIZE, 1, fp);
    fwrite(&credentials,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter Book ID NO. for delete:");
    scanf("%d",&bookDeleteId);
    while (fread (&deletebook, sizeof(deletebook), 1, fp))
    {
        if(deletebook.bookid != bookDeleteId)
        {
            fwrite(&deletebook,sizeof(deletebook), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    if(found)
        printf("\n\t\t\tRecord deleted successfully.....");
    else
        printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
    getchar();
}
void update_credentials()
{
    sFileHeader credentials = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&credentials,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter New Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tEnter New Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(credentials.username,userName,sizeof(userName));
    strncpy(credentials.password,password,sizeof(password));
    fwrite(&credentials,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}
void menu()
{
    int choice = 0;
    do
    {
        system("cls");
        printf("\n===============================================================================================");
        printf("\n=====                              LIBRARY MANAGEMENT                                     =====");
        printf("\n=====                                   SYSTEM                                            =====");
        printf("\n===============================================================================================");
        printf("\n\n===============================================================================================");
        printf("\n\t\t\t\tMain Menu");
        printf("\n===============================================================================================");
        printf("\n1.Add Book...\t\t2.Delete Book...\t3.Search Book...\n\n4.Display Book...\t5.Update Book...\t6.Update Password...\n\n\t\t\t\t0.Exit...");
        printf("\n===============================================================================================");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            add_books();
            break;
        case 2:
            delete_books();
            getchar();
            break;
        case 3:
            search_books();
            break;
        case 4:
            view_books();
            break;
        case 5:
            printf("\nBook updated successfully...");
            break;
        case 6:
            update_credentials();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                           //Switch Ended
    }while(choice!=0);
}

//login password
void validate()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int v_count=1;
    sFileHeader credentials = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&credentials,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    while(v_count<=3)
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,credentials.username)) && (!strcmp(password,credentials.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            v_count++;
        }
    }

    if(v_count>3)
    {
        printf("\n SORRY.....You are not valid user :(");
        getch();
        system("cls");
    }
}
int isFileExists(const char *path)//declaring path pointer to collect base address of file name.
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="Librarian\n";
    const char defaultPassword[] ="LIB123\n";
    sFileHeader credentials = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //user logins first time.(status=0)
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(credentials.password,defaultPassword,sizeof(defaultPassword));
            strncpy(credentials.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&credentials,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

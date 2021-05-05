#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
struct Book {
    char id_book[30];
    char name_book[30];
    char type_book[30];
    char name_author[30];
    int year_published;
};
// void menuStudent();
//NOTE: ADMIN
void menuAdmin(FILE *file, char *path ,Book *book, int numberBooks, int &totalBooks, char search[30], char id_delete[], char search_type[], char id_edit[]);
void enter(Book *book);
void enterBooks(Book *&book, int &numberBooks);
void printBooks(Book *book, int numberBooks);
void searchAuthor(char search[30]);
void addBook(Book *&book, int numberBooks, const Book output);
Book *findBooksbyAuthor(Book *book, int numberBooks, int &totalBooks, char search[]);
int countBooksByAuthor(Book *input, int numberBooks, char search[30]);
void arrangeBookByYear(Book *book, int numberBooks);
void arrangeBookByLetter(Book *book, int numberBooks);
void deleteBook(Book *book, int &numberBooks, char id_delete[]);
void exportBook(FILE *file, char *path, Book *book, int numberBooks);
int countBooks_Type(Book *book, int numberBooks, char search_type[30]);
void printTypeBooks(Book *book, int numberBooks, char search_type[30]);
void editBook(Book *book, int numberBooks, char id_edit[30]);
//NOTE: Standard string input
void standardInput(char *string);
void delete_space(char string[30], int delete_position);
void delete_leter(char *string);
void upperCase(char *string);
int main(){
    FILE *file;
    char *path = "./baitaplon/book.dat";
    Book *book;
    int numberBooks;
    book = (Book *)calloc(numberBooks,sizeof(Book));
    char search[30];
    int totalBooks = 0;
    char id_delete[30];
    char search_type[30];
    char id_edit[30];
    //The return string has the following format: Www Mmm dd hh: mm: ss where Www is the day of the week, Mmm is the characters for the month, dd is the day of the month, hh: mm: ss is the time, and yyyy is the year. .
    time_t curtime;
    time(&curtime);
    if(book == NULL){
        printf("\nError");
        exit(0);
    }
    printf("-----------------WELCOME TO LIBRARY-----------------");
    printf("\nAre you admin ?");
    int choice;
    char pass[6];
        printf("\n1. Yes I am Admin (click 1).");
        printf("\n2. No (click something).");
        printf("\n----------------------------------------------------");
        printf("\nYour choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("\n----------------------------------------------------");
            //NOTE: CHECK ADMIN
            char password[6] = "12345";
            int i;
            printf("\nPlease enter password: ");
            for(i = 0; i < 5; i++){
                
                // Get the hidden input
                // using getch() method
                pass[i] = getch();
                // Print * to show that
                // a character is entered
                printf("*");
            }
            pass[i] = '\0';
            if(strcmp(pass,password) == 0){
                printf("\nLOGIN TIME: %s", ctime(&curtime));
                printf("\nHello ADMIN\nWhat do you want ?");
                menuAdmin(file,path,book,numberBooks,totalBooks,search,id_delete,search_type,id_edit);
            } else {
                printf("\n----------------------------------------------------");
                printf("\nGood bye.");
                exit(0);
            }
    free(book);
    return 0;
    }
}
//NOTE: Standard String  input
void standardInput(char *string){
    delete_leter(string);
    upperCase(string);
}
void delete_space(char string[30], int delete_position){
    int n = strlen(string); // create the length of string
    for (int i = delete_position; i < n; i++)
    {
        string[i] = string[i + 1];
    }
    string[n - 1] = '\0';
}
void delete_leter(char *string){
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == ' ' && string[i + 1] == ' ')
        {
            delete_space(string, i);
            i--;
        }
        if (string[0] == ' ')
        {
            delete_space(string, 0);
        }
        if (string[strlen(string) - 1] == ' ')
        {
            delete_space(string, strlen(string) - 1);
        }
    }
}
void upperCase(char *string){
    for (int i = 0; i <= strlen(string); i++)
        {
            if (string[i] == ' ' && string[i + 1])
            string[i + 1] = toupper(string[i + 1]); 
        }
        //neu if dung thi viet hoa phan tu name[i+1]
    string[0] = toupper(string[0]);
    //luon thuc hien viet hoa phan tu name[0]
}
//NOTE: ADMIN
void menuAdmin(FILE *file, char *path ,Book *book, int numberBooks, int &totalBooks, char search[30], char id_delete[], char search_type[], char id_edit[])
{
    char choice_admin;
        do{
            printf("\n--------------------------MENU-----------------------\n");
            printf("1. Enter and print book\n");
            printf("2. Find books according to author.\n");
            printf("3. Arrange book according to year or letter (A->Z).\n");
            printf("4. Delete book.\n");
            printf("5. Print books.\n");
            printf("6. Count the type of book which you want to search.\n");
            printf("7. Update book.\n");
            printf("8. Exit by click ESC\n");
            printf("-----------------------------------------------------\n");
            printf("Your choise: ");
            fflush(stdin);
            choice_admin = getch();
            switch (choice_admin){
                case 49: 
                {
                    enterBooks(book, numberBooks);
                    printBooks(book, numberBooks);
                    break;
                }
                case 50: 
                {                    
                    searchAuthor(search);
                    printBooks(findBooksbyAuthor(book, numberBooks,totalBooks,search), countBooksByAuthor(book,numberBooks,search));
                    break;
                }
                case 51: 
                {
                    int choice_arr;
                        printf("1.Arrange book according to year.\n");
                        printf("2.Arrange book according to letter (A->Z).\n");
                        printf("-------------------------------------------------\n");
                        printf("Your choise: ");
                        scanf("%d", &choice_arr);
                        if(choice_arr == 1){
                            arrangeBookByYear(book, numberBooks);
                            printBooks(book, numberBooks);
                        } else if (choice_arr == 2){
                            arrangeBookByLetter(book,numberBooks); 
                            printBooks(book, numberBooks);
                        }    
                    
                    break;               
                }
                case 52: 
                {
                        deleteBook(book, numberBooks, id_delete);
                        printBooks(book, numberBooks);
                    break;
                }
                case 53: 
                {
                    exportBook(file,path,book,numberBooks);
                    break;
                }
                case 54: 
                {
                    countBooks_Type(book, numberBooks,search_type);
                    printTypeBooks(book, numberBooks,search_type);
                    break;
                }
                case 55: 
                {
                    editBook(book, numberBooks,id_edit);
                    printBooks(book, numberBooks);
                    break;
                }
                case 27: 
                {
                    printf("\nGOOD BYE\n");
                    break;
                }
                default:
                {
                    printf("\nChoice is non-valid.\n");
                }
            }
        } while (choice_admin != 27);
}
void enter(Book *book){
    printf("id: ");
    fflush(stdin);
    gets(book->id_book);
    printf("book's name: ");
    gets(book->name_book);
    standardInput(book->name_book);
    printf("type of book: ");
    gets(book->type_book);
    standardInput(book->type_book);
    printf("author: ");
    gets(book->name_author);
    standardInput(book->name_author);
    printf("year_publish: ");
    scanf("%d",&book->year_published);
}
void enterBooks(Book *&book, int &numberBooks){
    do{
        printf("\nEnter the amount of book: ");
        scanf("%d",&numberBooks);
        if(numberBooks <0){
            printf("\nPlease enter again.");
        }
    } while (numberBooks < 0);
    book = (Book *)realloc(book, numberBooks * sizeof(Book));
    for(int i = 0; i<numberBooks; i++){
        printf("\nEnter book [%d]: \n", i+1);
        enter((book+i));
    }
}
void printBooks(Book *book, int numberBooks){
    printf("\n------------------------DATA------------------------\n");
    printf("STT||ID\t\t||Book\t\t||Type\t\t||Author\t\t||Publish");
    for(int i = 0; i<numberBooks; i++){
        printf("\n00%d||%s\t\t||%s\t\t||%s\t\t||%s\t\t||%d", i+1, (book+i)->id_book, (book+i)->name_book, (book+i)->type_book, (book+i)->name_author, (book+i)->year_published);
    }
}
void addBook(Book *&book, int numberBooks, const Book output){
        numberBooks++;
        book = (Book *) realloc(book,numberBooks*sizeof(Book));
        *(book+numberBooks-1) = output;
}
Book *findBooksbyAuthor(Book *book, int numberBooks, int &totalBooks, char search[30]){
    Book *result;
    Book temp;
    totalBooks = 0;
    result = (Book*)calloc(totalBooks,sizeof(Book));
    for(int i=0;i<numberBooks; i++){
        if(strcmp((book+i)->name_author, search )== 0){
            temp = *(book+i);
            addBook(result,totalBooks,temp);
        }
    }
    return result;
}
int countBooksByAuthor(Book *input, int numberBooks, char search[30]){
        int count =0;
        for(int i=0; i < numberBooks; i++){
            if(strcmp((input+i)->name_author, search)==0){
                count++;
            }
        }
        return count;
}
void searchAuthor(char search[30]){
    printf("\nSearching author's book:");
    fflush(stdin);
    gets(search);
}
void arrangeBookByYear(Book *book, int numberBooks){
        Book temp;
        for(int i = 0; i < numberBooks-1; i++){
            for(int j = i+1; j <numberBooks; j++){
                if((book+i)->year_published > (book+j)->year_published){
                    temp =*(book+i);
                    *(book+i)= *(book+j);
                    *(book+j) = temp;
            }
        }
    }
}
void arrangeBookByLetter(Book *book, int numberBooks){
    Book temp;
    for(int i = 0; i < numberBooks-1; i++){
        for(int j = i+1; j < numberBooks; j++){
            if(strcmp((book+i)->name_book, (book+j)->name_book) > 0){
                temp = *(book+i);
                *(book+i) = *(book+j);
                *(book+j) = temp;
            }
        }
    }
}
void deleteBook(Book *book, int &numberBooks, char id_delete[]){
    bool check_book = false;
    fflush(stdin);
    printf("\nEnter the id of boook which you want to delete: ");
    gets(id_delete);
    for(int i = 0; i < numberBooks;i++){
        if(strcmp((book+i)->id_book, id_delete)==0){
            *(book+i) = *(book+i+1);
            check_book = true;
        }
    }
    numberBooks--;//delete the number of book
    if(check_book){
        printf("\nThe book has been completely deleted.");
    } else {
        printf("\nThe book doesn't exist.");
    }
}
void exportBook(FILE *file, char *path, Book *book, int numberBooks)
{   
    //if file doesn't exist, create new file
    char *mode = "a+b";
    file = fopen(path, mode);
    fprintf(file, "\nID\t\t||Book\t\t||Type\t\t||Author\t\t||Publish");
    for (int index = 0; index < numberBooks; index++)
    {
        fprintf(file, "\n%s\t\t||%s\t\t||%s\t\t||%s\t\t||%d", (book + index)->id_book, (book + index)->name_book, (book+ index)->type_book, (book+ index)->name_author, (book+index)->year_published);
    }
    fclose(file);
}
int countBooks_Type(Book *book, int numberBooks, char search_type[30]){
    int count = 0;
    for(int i=0; i < numberBooks; i++){
        if(strcmp((book+i)->type_book, search_type) == 0){
            count++;
        }
    }
    return count;
}
void printTypeBooks(Book *book, int numberBooks, char search_type[30]){
    if (numberBooks != 0) 
    {
    fflush(stdin);
    printf("\nEnter type of book which you want to search: ");
    gets(search_type);
    int result = countBooks_Type(book, numberBooks, search_type);
    printf("\nThe type of book you want to search have %d books", result);
    } else {
        printf("\nPlease input data.");
    }
};
void editBook(Book *book, int numberBooks, char id_edit[30]){
    bool has_book = false;
    fflush(stdin);
    printf("\nEnter id which you want to edit: ");
    gets(id_edit);
    for (int index = 0; index < numberBooks; index++)
    {
        if (strcmp(id_edit,(book + index)->id_book) == 0)
        {
            printf("\n======== EDIT BOOK ========");
            fflush(stdin);
            printf("\nName: ");
            gets((book + index)->name_book);
            standardInput(book->name_book);
            printf("\nAuthor's name: ");
            gets((book + index)->name_author);
            standardInput(book->name_author);
            printf("\nType: ");
            gets((book + index)->type_book);
            standardInput(book->type_book);
            printf("\nYear published: ");
            scanf("%d", &(book + index)->year_published);
            has_book = true;
        }
    }
    if (has_book)
    {
        printf("Done!\n");
    }
    else
    {
        printf("Not done !\n");
    }
}

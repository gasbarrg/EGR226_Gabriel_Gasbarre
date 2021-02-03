/**************************************************************************************
* Author: Gabriel Gasbarre
* Course: EGR 226 - 902
* Date: 02/03/2021
* Project: Book Database
* File: main.c
* Description: This program takes in a .csv file to read and tokenize information for storge in a book structure.
* users can then search information in the file like authors, titles, or ISBN's.
*
**************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_file();


typedef struct{                     //Book structure storage
    char title[255];
    char author_name[50];
    char ISBN[10];
    char pages[2000];
    char year_published[2021];
    }book;

void print_book();
void search_title();
void search_author();
void search_ISBN();

int main()
{
    book my_book_array[360];         //structure array of books
    char name[50];                   //filename to search
    char bTitle[255];                //Title of book to search
    char bAuthor[50];                //name of author to search
    char bISBN[10];                  //ISBN to search for
    int number = 360;                //number of books in array
    int choice;                      //while loop selection integer




    printf("Please enter the filename you would like to read in.\n\n");         // stores desired file to be read via user input
    scanf(" %s", &name);
    parse_file(name, my_book_array);


    while (1) {
            printf("Select one of the following options to search by:\n[0]Search by Title\n[1]Search by Author Name\n[2]Search by ISBN\n\n");
            scanf("%d", &choice);
    if(choice == 0){
    printf("Enter the title of the book you would like to search\n");
        fseek(stdin,0,SEEK_END);                                            //clears input buffer
        scanf("%[^\n]%*c", &bTitle);
        search_title(my_book_array, number, bTitle);
                    }
    else if (choice == 1){
    printf("Enter the name of the Author you would like to search:\n");
        fseek(stdin,0,SEEK_END);
        scanf("%[^\n]%*c", &bAuthor);
        search_author(my_book_array, number, bAuthor);
                        }
    else if (choice == 2){
    printf("Enter the ISBN of the book you would like to search:\n");
            fseek(stdin,0,SEEK_END);
            scanf("%[^\n]%*c", &bISBN);
            search_ISBN(my_book_array, number, bISBN);
                        }
            }
}






int parse_file(char filename[50], book book_array[]) {
/****| parse_file | *****************************************
* Brief:  Reads file input from user and tokenizes information for storage in book structure.
* param:  Filename, book_array
* return: N/A
*
*************************************************************/

 FILE* infile = fopen(filename, "r");                           // Attempt to open file
 if (infile == NULL) {
    printf("Failed to open file with name '%s'", filename);
    return 0;
    }
 char buffer[512];                                              // Create temporary string buffer variable
 int i = 0;                                                     // Indexer for book array

 while (fgets(buffer, 512, infile)) {                           // Loop collecting each line from the file
    char * ptr = strtok(buffer,",");                            // Parse string by commas and newline
    if(strcmp(ptr,"N/A")){                                      // Validate string
            strcpy(book_array[i].title,ptr);                    // First parse is title
    }
        else if (strcmp(ptr,"N/A") == 0) {                      //Handle null value
            strcpy(book_array[i].title,"N/A");
        }


 ptr = strtok(NULL,",\n");
    if(strcmp(ptr,"N/A")){                                       // Validate string
            strcpy(book_array[i].author_name,ptr);              // second parse is author

    }
            else if (strcmp(ptr,"N/A") == 0) {                   //Handle null value
            strcpy(book_array[i].author_name,"N/A");
        }


 ptr = strtok(NULL,",\n");
        if(strcmp(ptr,"N/A")){                                  // Validate string
            strcpy(book_array[i].ISBN,ptr);                     //Third parse is ISBN

        }
            else if (strcmp(ptr,"N/A") == 0) {                  //Handle null value
            strcpy(book_array[i].ISBN,"N/A");
        }


 ptr = strtok(NULL,",\n");
         if(strcmp(ptr,"N/A")){                                 // Validate string
            strcpy(book_array[i].pages,ptr);                    // Fourth parse is page count

        }
        else if (strcmp(ptr,"N/A") == 0) {                      //Handle null value
            strcpy(book_array[i].pages,"N/A");
        }


 ptr = strtok(NULL,",\n");
        if(strcmp(ptr,"N/A")){                                   // Validate string
            strcpy(book_array[i].year_published,ptr);            //Fifth parse is year published
        }
        else if (strcmp(ptr,"N/A") == 0) {                      //Handle null value
            strcpy(book_array[i].year_published,"N/A");
        }


 i++;
 }
 return(0);
}




void print_book(book b){
/****| print_book | *****************************************
* Brief:  receives single book structure and prints each of its component parts.
* param:  book b
* return: title, author name, ISBNN, pages, and year published.
*
*************************************************************/
    printf("\n%s, %s, %s, %s, %s\n", b.title, b.author_name, b.ISBN, b.pages, b.year_published );
}



void search_title(book book_array[],int n, char title[]){
    /****| search title | *****************************************
* Brief:  receives a book array and title to compare, and sends matches to function print_book
* param:  book_array, n (number of books in array) and title.
* return: printf staement with # of matching books found
*
*************************************************************/
    int i = 0;
    int j = 0;
    for (i ; i < n; i++) {
        if (strstr( book_array[i].title, title) != 0) {
            print_book(book_array[i]);
            j++; }
    }
    printf("Found %d books with that title string.\n\n\n", j);
}




void search_author(book book_array[],int n, char author[]){
    /****| search author | *****************************************
* Brief:  receives a book array and author to compare, and sends matches to function print_book
* param:  book_array, n (number of books in array) and author.
* return: printf staement with # of matching books found
*
*************************************************************/
    int i = 0;
    int j = 0;
    for (i ; i < n; i++) {
        if (strstr(book_array[i].author_name, author) != 0) {
            print_book(book_array[i]);
            j++;
        }


    }
    printf("Found %d books with that author string.\n\n\n", j);


}

void search_ISBN(book book_array[], int n, char ISBN[]){
    /****| search ISBN | *****************************************
* Brief:  receives a book array and ISBN to compare, and sends matches to function print_book
* param:  book_array, n (number of books in array) and ISBN.
* return: printf staement with # of matching books found
*
*************************************************************/
    int i = 0;
    int j = 0;
    for (i ; i < n; i++) {
        if (strcmp(ISBN, book_array[i].ISBN) == 0) {
            print_book(book_array[i]);
            j++;
        }


    }
    printf("Found %d books with that ISBN.\n\n\n", j);



}

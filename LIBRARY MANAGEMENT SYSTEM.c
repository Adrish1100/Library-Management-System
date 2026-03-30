/*
 * Library Management System
 * Made by Adrish Datta
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//-----------------------FUNCTION PROTOTYPES-------------------------
int menu();
void add_book();
void issue_book();
void return_book();
void show_books();
void search();
void change();

//---------------------MINI--FUNCTION PROTOTYPES------------------

int reuse_lower_cmp(char search[], char txt[]);
int reuse_lower_str(char search[], char txt[]);

//---------------------------------------------------------------------------------------

//-------------------------------------MAIN-----------------------------------------
int main()
{
	int tryagain;

	do
	{
		printf("-------------------------------------Library Management System by Adrish Datta-------------------------------------\n");
		int op = menu();

		if (op == 1)
			add_book();
		else if (op == 2)
			issue_book();
		else if (op == 3)
			return_book();
		else if (op == 4)
			show_books();
		else if (op == 5)
			search();
		else if (op == 6)
			change();
		else if (op == 7)
			return 0;

		printf("Do you wish to continue our Services?\n");
		printf("\n1.CONTINUE\n2.EXIT\n\nEnter an option: ");
		scanf("%d", &tryagain);
	} while (tryagain == 1);

	return 0;
} // main

//----------------------------------------------------------------------------------------
//----------------------------------FUNCTIONS-----------------------------------

int menu()
{
	system("cls");
	printf("-------------------Library Management System by Adrish Datta--------------------\n\n");
	int op;
	printf("-------------------------------------MAIN MENU--------------------------------\n\n");
	printf("1.ADD BOOKS\n2.ISSUE BOOK\n3.RETURN BOOK\n4.SHOW BOOKS\n5.SEARCH BAR\n6.CHANGE DATA\n7.EXIT\n");
	do
	{
		printf("Enter an option: ");
		if (scanf("%d", &op) != 1)
		{ // non-numeric input check
			op = 0;
			while (getchar() != '\n')
				; // flush bad input
		}
	} while (op < 1 || op > 7);
	if (op != 7)
		system("cls");
	return op;
}

void add_book()
{
	char book_name[100], book_author[100], book_scode[100], book_issued[50];
	float book_price;
	FILE *ptr;
	ptr = fopen("/sdcard/books.txt", "a");
	int n;
	printf("------------------------------ADD BOOKS----------------------------\n\n");
	printf("ENTER THE NUMBER OF BOOKS YOU WANT TO ADD: ");
	scanf("%d", &n);
	getchar(); // consume leftover newline

	for (int i = 0; i < n; i++)
	{
		printf("\nENTER THE BOOK'S NAME: ");
		fgets(book_name, 100, stdin);
		book_name[strcspn(book_name, "\n")] = 0; // remove newline

		printf("ENTER THE BOOK'S AUTHOR: ");
		fgets(book_author, 100, stdin);
		book_author[strcspn(book_author, "\n")] = 0; // remove newline

		printf("ENTER THE BOOK'S ISBN: ");
		fgets(book_scode, 100, stdin);
		book_scode[strcspn(book_scode, "\n")] = 0;

		printf("ENTER THE BOOK'S PRICE: ");
		scanf("%f", &book_price);
		getchar(); // consume leftover newline

		strcpy(book_issued, "available");

		fprintf(ptr, "%s|%s|%s|%.2f|%s\n", book_name, book_author, book_scode, book_price, book_issued);
	} // for

	fclose(ptr);
} // add_book

void issue_book()
{
	printf("------------------------------ISSUE BOOKS----------------------------\n\n");
	char book_name[100], book_author[100], book_scode[20], book_price[25], book_issued[15], code[20];
	int found = 0;
	FILE *ptr, *tptr;
	ptr = fopen("/sdcard/books.txt", "r");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!");
		return;
	}
	rewind(ptr);
	printf("%-15s %-15s %-11s %-10s\n", "Book's Name", "Book's Author", "ISBN", "Price");

	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", book_name, book_author, book_scode, book_price, book_issued) == 5)
	{
		if (strcmp(book_issued, "issued") == 0)
		{
			continue;
		}
		printf("------------------------------------------------------------------\n");
		printf("%-15s %-15s %-10s RS.%-10s\n",
			   book_name,
			   book_author,
			   book_scode,
			   book_price);
	}
	printf("------------------------------------------------------------------\n");

	printf("Choose any book from the following:\n\n");
	getchar();
	printf("Enter the book's ISBN: ");
	fgets(code, 50, stdin);
	code[strcspn(code, "\n")] = 0;
	rewind(ptr);

	tptr = fopen("/sdcard/temp.txt", "w");
	if (tptr == NULL)
	{
		printf("FILE NOT FOUND!!");
		return;
	}
	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", book_name, book_author, book_scode, book_price, book_issued) == 5)
	{
		if (reuse_lower_cmp(code, book_scode) == 0)
		{
			if (strcmp(book_issued, "available") == 0)
			{
				strcpy(book_issued, "issued");
				fprintf(tptr, "%s|%s|%s|%s|%s\n", book_name, book_author, book_scode, book_price, book_issued);
				printf("\nBook issued successfully");
			}
			else
			{
				fprintf(tptr, "%s|%s|%s|%s|%s\n", book_name, book_author, book_scode, book_price, book_issued);
				printf("\nThe book is already issued!\n");
			}
			found = 1;
		}
		else
		{
			fprintf(tptr, "%s|%s|%s|%s|%s\n", book_name, book_author, book_scode, book_price, book_issued);
		}
	}
	fclose(tptr);
	fclose(ptr);
	remove("/sdcard/books.txt");
	rename("/sdcard/temp.txt", "/sdcard/books.txt");
	if (found == 0)
	{
		printf("\nThe book couldn't be found!\n");
	}
} // issue_book

void return_book()
{
	printf("----------------------------RETURN BOOKS--------------------------\n\n");
	char book_name[100], book_author[100], book_scode[20], book_price[25], book_issued[15], code[20];
	int found = 0,
	try
		= 0;
	FILE *ptr, *tptr;
	ptr = fopen("/sdcard/books.txt", "r");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!");
		return;
	}
	rewind(ptr);
	printf("%-15s %-15s %-11s %-10s\n", "Book's Name", "Book's Author", "ISBN", "Price");

	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", book_name, book_author, book_scode, book_price, book_issued) == 5)
	{
		if (strcmp(book_issued, "available") == 0)
		{
			continue;
		}
		printf("------------------------------------------------------------------\n");
		printf("%-15s %-15s %-10s RS.%-10s\n", book_name, book_author, book_scode, book_price);
	}
	printf("------------------------------------------------------------------\n");

	getchar();
	do
	{
		tptr = fopen("/sdcard/temp.txt", "w");
		if (tptr == NULL)
		{
			printf("FILE NOT FOUND!!");
			return;
		}
		rewind(ptr);
		found = 0;
		printf("Enter the Book's ISBN: ");
		fgets(code, 100, stdin);
		code[strcspn(code, "\n")] = 0;

		while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", book_name, book_author, book_scode, book_price, book_issued) == 5)
		{
			if (strcmp(book_scode, code) == 0)
			{
				if (strcmp(book_issued, "issued") == 0)
				{
					printf("\nBook returned successfully\n");
					strcpy(book_issued, "available");
					found = 1;
				}
				else
				{
					printf("\nThe book isn't issued... wrong ISBN entered!\n");
					found = 1;
				}
			}
			fprintf(tptr, "%s|%s|%s|%s|%s\n", book_name, book_author, book_scode, book_price, book_issued);
		} //while
		if (found == 0)
		{
			printf("Invalid ISBN Entered!!\nWant to try again?\n1.YES\n2.NO\nEnter an option: ");
			scanf("%d", &try);
			getchar(); // consume leftover newline
		}
	} while (try == 1);
	fclose(tptr);
	fclose(ptr);
	remove("/sdcard/books.txt");
	rename("/sdcard/temp.txt", "/sdcard/books.txt");
} // return_book

void show_books()
{
	char book_name[100], book_author[100], book_scode[50], book_price[25], book_issued[15];
	FILE *ptr;
	ptr = fopen("/sdcard/books.txt", "r");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!");
		return;
	}
	printf("------------------------------SHOW BOOKS ----------------------------\n\n");
	printf("%-15s %-15s %-11s %-10s %-15s\n", "Book's Name", "Book's Author", "ISBN", "Price", "Status");
	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", book_name, book_author, book_scode, book_price, book_issued) == 5)
	{
		printf("------------------------------------------------------------------\n");

		printf("%-15s %-15s %-11s RS.%-10s %-15s\n", book_name, book_author, book_scode, book_price, book_issued);
	}
	printf("------------------------------------------------------------------\n");
	fclose(ptr);
} // show_book

void search()
{
	FILE *ptr;
	ptr = fopen("/sdcard/books.txt", "r");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!");
		return;
	}
	char book_name[100], book_author[100], book_scode[50], price[25], issued[15];
	char search[100];
	int searchagain = 0, found = 0;
	getchar();
	do
	{
		rewind(ptr);
		found = 0;
		printf("SEARCH BAR: ");
		fgets(search, 100, stdin);
		search[strcspn(search, "\n")] = 0;
		while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
					  book_name,
					  book_author,
					  book_scode,
					  price,
					  issued) == 5)
			if (reuse_lower_str(search, book_name) || reuse_lower_str(search, book_scode) || reuse_lower_str(search, book_author))
			{
				printf("BOOK FOUND WITH %s NAME BY AUTHOR %s WITH %s ISBN\n", book_name, book_author, book_scode);
				found = 1;
			}

		if (found == 0)
		{
			printf("Book not found!!\nWant to search again?\n1.YES\n2.NO\nEnter an option: ");
			scanf("%d", &searchagain);
			getchar(); // consume leftover newline
		}
	} while (searchagain == 1);
	fclose(ptr);
} // search
void change()
{
	printf("------------------------------EDIT DATA----------------------------\n\n");
	char book_name[100], book_author[100], book_scode[50], book_price[25], book_issued[15], edit_name[100], edit_author[100], edit_scode[50], edit_price[25];

	FILE *ptr, *tptr;
	ptr = fopen("/sdcard/books.txt", "r");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!");
		return;
	}
	int searchagain = 0, option = 0, match_count = 0;
	int choice;
	float newprice;
	char newname[100], search[100], matched_isbns[100][20], target_isbn[20];
	getchar();
	do
	{
		match_count = 0;
		rewind(ptr);
		printf("Enter the Book's Name or Author or ISBN: ");
		fgets(search, 100, stdin);
		search[strcspn(search, "\n")] = 0;

		while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", book_name, book_author, book_scode, book_price, book_issued) == 5)
		{
			if (!reuse_lower_str(search, book_name) &&
				!reuse_lower_str(search, book_author) &&
				!reuse_lower_str(search, book_scode))
			{
				continue;
			}
			printf("------------------------------------------------------------------\n");
			printf("%-15s %-15s %-10s RS.%-10s\n", book_name, book_author, book_scode, book_price);
			strcpy(matched_isbns[match_count], book_scode);
			match_count++;
		}
		printf("------------------------------------------------------------------\n");
		if (match_count == 0)
		{
			printf("no books matched!!\nWant to search again?\n1.YES\n2.NO\nEnter an option: ");
			scanf("%d", &searchagain);
			getchar();
		}
		else
		{
			if (match_count > 1)
			{
				printf("Enter which book to edit (1-%d): ", match_count);
				scanf("%d", &choice);
				getchar();
				strcpy(target_isbn, matched_isbns[choice - 1]);
				printf("\nEnter which field to edit:\n1.Edit Book Name\n2.Edit Author\n3.Edit ISBN\n4.Edit Price\nEnter an option: ");
				scanf("%d", &option);
				getchar();
			}
			else
			{
				strcpy(target_isbn, matched_isbns[0]);
				printf("Enter which field to edit:\n1.Edit Book Name\n2.Edit Author\n3.Edit ISBN\n4.Edit Price\nEnter an option: ");
				scanf("%d", &option);
				getchar();
			}

			switch (option)
			{
			case 1:
				printf("Enter the correct Name: ");
				fgets(newname, 100, stdin);
				newname[strcspn(newname, "\n")] = 0;
				strcpy(book_name, newname);
				printf("Name edited successfully!!\n");
				break;
			case 2:
				printf("Enter the correct Author: ");
				fgets(newname, 100, stdin);
				newname[strcspn(newname, "\n")] = 0;
				strcpy(book_author, newname);
				printf("Author Name edited successfully!!\n");
				break;
			case 3:
				printf("Enter the correct Isbn: ");
				fgets(newname, 100, stdin);
				newname[strcspn(newname, "\n")] = 0;
				strcpy(book_scode, newname);
				printf("Serial Code edited successfully!!\n");
				break;
			case 4:
				printf("Enter the correct Price: ");
				scanf("%f", &newprice);
				getchar();
				sprintf(book_price, "%.2f", newprice); //prints into a string
				printf("Price edited successfully!!\n");
				break;
			default:
				printf("Invalid input!!\n");
				break;
			} // switch

			strcpy(edit_name, book_name);
			strcpy(edit_author, book_author);
			strcpy(edit_scode, book_scode);
			strcpy(edit_price, book_price);

			rewind(ptr);
			tptr = fopen("/sdcard/temp.txt", "w");
			if (tptr == NULL)
			{
				printf("FILE NOT FOUND!!");
				return;
			}
			while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", book_name, book_author, book_scode, book_price, book_issued) == 5)
			{
				if (reuse_lower_cmp(target_isbn, book_scode) == 0)
				{
					fprintf(tptr, "%s|%s|%s|%s|%s\n", edit_name, edit_author, edit_scode, edit_price, book_issued);
				}
				else
					fprintf(tptr, "%s|%s|%s|%s|%s\n", book_name, book_author, book_scode, book_price, book_issued);
			}
			printf("\nWant to search again?\n1.YES\n2.NO\nEnter an option: ");
			scanf("%d", &searchagain);
			getchar();
			fclose(tptr);
			remove("/sdcard/books.txt");
			rename("/sdcard/temp.txt", "/sdcard/books.txt");
		}
	} while (searchagain == 1);
	fclose(ptr);
} // change
//---------------------------------------------------------------------------------------
//-----------------------------------MINI-FUNCTION---------------------------

int reuse_lower_cmp(char search[], char txt[])
{
	char a[100], btxt[100];
	strcpy(a, search);
	strcpy(btxt, txt);

	for (int i = 0; a[i]; i++)
		a[i] = tolower(a[i]);

	for (int i = 0; btxt[i]; i++)
		btxt[i] = tolower(btxt[i]);

	if (strcmp(a, btxt) == 0)
		return 0;
	return 1;
}

int reuse_lower_str(char search[], char txt[])
{
	char a[100], btxt[100];
	strcpy(a, search);
	strcpy(btxt, txt);

	for (int i = 0; a[i]; i++)
		a[i] = tolower(a[i]);

	for (int i = 0; btxt[i]; i++)
		btxt[i] = tolower(btxt[i]);

	if (strstr(btxt, a))
		return 1;
	else
		return 0;
}
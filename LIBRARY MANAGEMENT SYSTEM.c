#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int count = 0;

//-----------------------FUNCTION PROTOTYPES-------------------------
int menu();
void add_book();
void issue_book();
void return_book();
void show_books();
void search();
void change();

//---------------------MINI--FUNCTION PROTOTYPES------------------
int reuse_search(char search[100], int **indexptr);
int reuse_lower_cmp(char search[], char txt[]);
int reuse_lower_str(char search[], char txt[]);

//---------------------------------------------------------------------------------------
struct books
{
	char book_scode[100];
	char book_name[100];
	char book_author[100];
	int book_issued;
	float book_price;
}; // struct books

struct books b;

//-------------------------------------MAIN-----------------------------------------
int main()
{
	int tryagain;

	do
	{
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
	system("cls"); //clears the screen
	int op;
	printf("------------------------------MAIN MENU----------------------------\n\n");
	printf("1.ADD BOOKS\n2.ISSUE BOOK\n3.RETURN BOOK\n4.SHOW BOOKS\n5.SEARCH BAR\n6.CHANGE DATA\n7.EXIT\n");
	do
	{
		printf("Enter an option: ");
		scanf("%d", &op);
	} while (op < 1 || op > 7); // do-while
	if (op != 7)
		system("cls"); //clears the screen
	return op;
} // menu

void add_book()
{
	FILE *ptr;
	ptr = fopen("/sdcard/books.txt", "a");
	int n;
	printf("------------------------------ADD BOOKS----------------------------\n\n");
	printf("ENTER THE NUMBER OF BOOKS YOU WANT TO ADD: ");
	scanf("%d", &n);
	getchar(); // consume leftover newline

	for (int i = count; i < count + n; i++)
	{
		printf("\nENTER THE BOOK'S NAME: ");
		fgets(b.book_name, 100, stdin);
		b.book_name[strcspn(b.book_name, "\n")] = 0; // remove newline

		printf("ENTER THE BOOK'S AUTHOR: ");
		fgets(b.book_author, 100, stdin);
		b.book_author[strcspn(b.book_author, "\n")] = 0; // remove newline

			printf("ENTER THE BOOK'S ISBN: ");
			fgets(b.book_scode, 100, stdin);
			b.book_scode[strcspn(b.book_scode, "\n")] = 0;
		}

		printf("ENTER THE BOOK'S PRICE: ");
		scanf("%f", &b.book_price);
		getchar(); // consume leftover newline

		b.book_issued = 0;

		fprintf(ptr,"%s|%s|%s|RS. %.2f|%s\n",
				b.book_name,
				b.book_author,
				b.book_scode,
				b.book_price,
				
				b.book_issued == 0 ? "available" : "issued");
	} // for
	count += n;
	fclose(ptr);
} // add_book

void issue_book()
{
	printf("------------------------------ISSUE BOOKS----------------------------\n\n");
	char code[50];
	int found = 0;

	if (count == 0)
	{
		printf("\nNo books in the System\n");
	}
	else
	{
		printf("%-15s %-15s %-15s %-10s\n", "Book's Name", "Book's Author", "ISBN", "Price");

		for (int i = 0; i < count; i++)
		{
			if (b[i].book_issued == 1)
				continue;
			printf("------------------------------------------------------------------\n");
			printf("%-15s %-15s %-10s RS. %-10.2f\n",
				   b[i].book_name,
				   b[i].book_author,
				   b[i].book_scode,
				   b[i].book_price);
		}
		printf("------------------------------------------------------------------\n");

		printf("Choose any book from the following:\n");
		printf("Enter the book's ISBN: ");
		fgets(code, 50, stdin);
		code[strcspn(code, "\n")] = 0;

		for (int i = 0; i < count; i++)
		{
			if (reuse_lower_cmp(code, b[i].book_scode) == 0)
			{
				if (b[i].book_issued == 0)
				{
					printf("\nBook issued successfully\n");
					b[i].book_issued = 1;
					found = 1;
				}
				else
				{
					printf("\nThe book is already issued!\n");
					found = 1;
				}
				break;
			}
		}

		if (found == 0)
			printf("\nThe book couldn't be found!\n");
	}
} // issue_book

void return_book()
{
	printf("----------------------------RETURN BOOKS--------------------------\n\n");
	char code[100];
	int found = 0,
	try
		= 0;

	if (count == 0)
	{
		printf("\nNo books in the System\n");
	}
	else
	{
		do
		{
			found = 0;
			printf("Enter the Book's ISBN: ");
			fgets(code, 100, stdin);
			code[strcspn(code, "\n")] = 0;

			for (int i = 0; i < count; i++)
			{
				if (strcmp(b[i].book_scode, code) == 0)
				{
					if (b[i].book_issued == 1)
					{
						printf("\nBook returned successfully\n");
						b[i].book_issued = 0;
						found = 1;
						break;
					}
					else
					{
						printf("\nThe book isn't issued... wrong ISBN entered!\n");
						found = 1;
					}
					break;
				}
			}

			if (found == 0)
			{
				printf("Invalid ISBN Entered!!\nWant to try again?\n1.YES\n2.NO\nEnter an option: ");
				scanf("%d", &try);
				getchar(); // consume leftover newline
			}
		} while (try == 1);
	}
} // return_book

void show_books()
{
	printf("------------------------------BOOKS ----------------------------\n\n");
	if (count == 0)
	{
		printf("NO BOOKS AVAILABLE\n");
	}
	else
	{
		printf("%-15s %-15s %-11s %-10s %-15s\n", "Book's Name", "Book's Author", "Isbn", "Price", "Status");

		for (int i = 0; i < count; i++)
		{
			printf("------------------------------------------------------------------\n");
			printf("%-15s %-15s %-11s RS. %-10.2f %-15s\n",
				   b[i].book_name,
				   b[i].book_author,
				   b[i].book_scode,
				   b[i].book_price,
				   b[i].book_issued == 0 ? "available" : "issued");
		}
		printf("------------------------------------------------------------------\n");
	}
} // show_books

void search()
{
	if (count == 0)
	{
		printf("\nNo books in the System\n");
	}
	else
	{
		char search[100];
		int searchagain = 0, found = 0;
		do
		{
			found = 0;
			printf("SEARCH BAR: ");
			fgets(search, 100, stdin);
			search[strcspn(search, "\n")] = 0;

			for (int i = 0; i < count; i++)
			{
				if (reuse_lower_str(search, b[i].book_name) || reuse_lower_str(search, b[i].book_scode) || reuse_lower_str(b[i].book_author, search))
				{
					printf("BOOK FOUND WITH %s NAME BY AUTHOR %s WITH %s ISBN\n", b[i].book_name, b[i].book_author, b[i].book_scode);
					found = 1;
				}
			}

			if (found == 0)
			{
				printf("Book not found!!\nWant to search again?\n1.YES\n2.NO\nEnter an option: ");
				scanf("%d", &searchagain);
				getchar(); // consume leftover newline
			}
		} while (searchagain == 1);
	}
} // search

void change()
{
	printf("------------------------------EDIT DATA----------------------------\n\n");
	int searchagain = 0, option = 0;
	int index = 0, k = 0, choice, trya = 0;
	float newprice;
	int indexes[100];
	char newname[100], search[100];
	int *indexptr = &indexes[0];

	do
	{
		trya = 0;
		k = 0;

		if (count == 0)
		{
			printf("\nNo books in the System\n");
		}
		else
		{
			printf("Enter the Book's Name or Author or ISBN: ");
			fgets(search, 100, stdin);
			search[strcspn(search, "\n")] = 0;

			k = reuse_search(search, &indexptr);
			if (k > 1)
			{
				do
				{
					trya = 0;
					printf("Enter which book to edit (1-%d): ", k);
					scanf("%d", &choice);
					getchar();
					if (choice > k || choice < 1)
						trya = 1;
					else
					{
						trya = 0;
						index = indexes[choice - 1];
					}
				} while (trya == 1);
			}
			else
			{
				index = indexes[0];
			}

			printf("Enter which field to edit:\n1.Edit Book Name\n2.Edit Author\n3.Edit ISBN\n4.Edit Price\nEnter an option: ");
			scanf("%d", &option);
			getchar();

			switch (option)
			{
			case 1:
				printf("Enter the correct Name: ");
				fgets(newname, 100, stdin);
				newname[strcspn(newname, "\n")] = 0;
				strcpy(b[index].book_name, newname);
				printf("Name edited successfully!!\n");
				break;
			case 2:
				printf("Enter the correct Author: ");
				fgets(newname, 100, stdin);
				newname[strcspn(newname, "\n")] = 0;
				strcpy(b[index].book_author, newname);
				printf("Author Name edited successfully!!\n");
				break;
			case 3:
				printf("Enter the correct Isbn: ");
				fgets(newname, 100, stdin);
				newname[strcspn(newname, "\n")] = 0;
				strcpy(b[index].book_scode, newname);
				printf("Serial Code edited successfully!!\n");
				break;
			case 4:
				printf("Enter the correct Price: ");
				scanf("%f", &newprice);
				getchar();
				b[index].book_price = newprice;
				printf("Price edited successfully!!\n");
				break;
			default:
				printf("Invalid input!!\n");
				break;
			} // switch

			if (k == 0)
			{
				printf("No book found!\nWant to search again?\n1.YES\n2.NO\nEnter an option: ");
				scanf("%d", &searchagain);
				getchar();
			}
		}
	} while (searchagain == 1);
} // change

//---------------------------------------------------------------------------------------
//-----------------------------------MINI-FUNCTION---------------------------

int reuse_search(char search[100], int **indexptr)
{
	int k = 0;
	for (int i = 0; i < count; i++)
	{
		if (strstr(b[i].book_name, search) || strstr(b[i].book_scode, search) || strstr(b[i].book_author, search))
		{
			printf("----------------------------------------------------------------------\n");
			printf("%-2d %-20s %-20s %-15s RS.%-5.2f\n", k + 1, b[i].book_name, b[i].book_author, b[i].book_scode, b[i].book_price);
			**indexptr = i;
			(*indexptr)++;
			k++;
		}
	}
	printf("-----------------------------------------------------------------------------\n");
	return k;
}

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
	if (strstr(a, btxt))
		return 1;
	return 0;
}
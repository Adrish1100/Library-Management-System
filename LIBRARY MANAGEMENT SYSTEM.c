/*
 * Library Management System
 * Made by Adrish Datta
 */
/*--Preprocessor directives--*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

//system independent clears
#ifdef _WIN32
#define CLEAR system("cls")
#else
#define CLEAR system("clear")
#endif

#define NAME_LEN 100
#define AUTHOR_LEN 100
#define ISBN_LEN 50
#define PRICE_LEN 20
#define STATUS_LEN 20
#define DATE_LEN 20
#define ID_LEN 25
#define MEMBER_NAME_LEN 100
#define PHONE_LEN 15
#define ADDRESS_LEN 200
#define MEMBER_COUNT 50
#define FALSE 0
#define TRUE 1
#define gotoxy(x, y) printf("\033[%d;%dH", y, x)

/*--Function declarations--*/
int menu();
void add_book();
void issue_book();
void return_book();
void show_books();
void search();
void change();
void add_membership();
void cancel_membership();
void renew_membership();
void show_members();
void auto_expire();

int pass(char pass[]);
void screen(char pass[]);
int reuse_lower_cmp(char search[], char txt[]);
int reuse_lower_str(char search[], char txt[]);
int is_all_digit(char str[]);

enum op
{
	addop = 1,
	issueop,
	returnop,
	showop,
	searchop,
	changeop,
	add_memop,
	cancel_memop,
	renew_memop,
	show_memop,
	Exit
};

struct BOOK
{
	char name[NAME_LEN];
	char author[AUTHOR_LEN];
	char isbn[ISBN_LEN];
	char price[PRICE_LEN];
	char status[STATUS_LEN];
	char issue_date[DATE_LEN];
	char return_date[DATE_LEN];
};

typedef struct membership
{
	char id[ID_LEN];
	char name[MEMBER_NAME_LEN];
	char phone[PHONE_LEN];
	char address[ADDRESS_LEN];
	char join_date[DATE_LEN];
	char expiry_date[DATE_LEN];
	char status[STATUS_LEN];
	char adhaar[15];
	char nation[25];
	int act_age;
} mem;

FILE *ptr;
FILE *tptr;
FILE *fp;
FILE *fptr;

int main()
{
	char tryagain;

	void (*func_caller[])(void) =
		{add_book, issue_book, return_book, show_books, search, change, add_membership, cancel_membership, renew_membership, show_members};

	do
	{
		auto_expire();

		int op = menu();

		if (op >= addop && op <= show_memop)
			func_caller[op - 1]();
		else
			return 0;

		printf("\n\nWould you like to Continue our services?(Y/N). \nEnter choice: ");
		scanf(" %c", &tryagain);
		getchar();

		tryagain = toupper(tryagain);
	} while (tryagain == 'Y');

	return 0;
}

/*Functions*/

int menu()
{
	CLEAR;
	int op;
	CLEAR;
	gotoxy(15, 5);
	printf("**************************************");
	gotoxy(15, 6);
	printf("*                                    *");
	gotoxy(15, 7);
	printf("*      Library Management System     *");
	gotoxy(15, 8);
	printf("*              BY:ADRISH DATTA       *");
	gotoxy(15, 9);
	printf("*                                    *");
	gotoxy(15, 10);
	printf("**************************************");

	gotoxy(15, 12);
	printf("1. ADD BOOKS");
	gotoxy(15, 13);
	printf("2. ISSUE BOOK");
	gotoxy(15, 14);
	printf("3. RETURN BOOK");
	gotoxy(15, 15);
	printf("4. SHOW BOOKS");
	gotoxy(15, 16);
	printf("5. SEARCH");
	gotoxy(15, 17);
	printf("6. CHANGE");
	gotoxy(15, 18);
	printf("7. ADD MEMBERSHIP");
	gotoxy(15, 19);
	printf("8. CANCEL MEMBERSHIP");
	gotoxy(15, 20);
	printf("9. RENEW MEMBERSHIP");
	gotoxy(15, 21);
	printf("10. SHOW MEMBERS");
	gotoxy(15, 22);
	printf("11. EXIT");
	gotoxy(15, 23);
	printf("**************************************");

	do
	{
		printf("\n\t\tEnter your choice: ");

		if (scanf("%d", &op) != 1)
		{
			op = 0;
			while (getchar() != '\n')
				;
		}
	} while (op < addop || op > Exit);

	CLEAR;
	return op;
}

void add_book()
{
	struct BOOK b;
	ptr = fopen("books.txt", "a");
	int n;
	printf("\n\t------------------------------ADD BOOKS---------------------------\n\n");

	printf("\t\tNumber of books: ");
	scanf("%d", &n);
	getchar();

	for (int i = 0; i < n; i++)
	{
		printf("\t\tName: ");
		fgets(b.name, NAME_LEN, stdin);
		b.name[strcspn(b.name, "\n")] = 0;

		printf("\t\tAuthor: ");
		fgets(b.author, AUTHOR_LEN, stdin);
		b.author[strcspn(b.author, "\n")] = 0;

		printf("\t\tISBN Number: ");
		fgets(b.isbn, ISBN_LEN, stdin);
		b.isbn[strcspn(b.isbn, "\n")] = 0;

		printf("\t\tPrice: ");
		fgets(b.price, PRICE_LEN, stdin);
		b.price[strcspn(b.price, "\n")] = 0;

		fprintf(ptr, "%s|%s|%s|%s|available|NA|NA\n",
				b.name, b.author, b.isbn, b.price);
	}

	fclose(ptr);
}

void issue_book()
{
	struct BOOK b;
	printf("------------------------------ISSUE BOOKS----------------------------\n\n");
	char code[ID_LEN];
	int found = 0;

	FILE *ptr;
	FILE *tptr;
	ptr = fopen("books.txt", "r");
	tptr = fopen("temp.txt", "w");
	if (ptr == NULL || tptr == NULL)
	{
		printf("FILE NOT FOUND!!");
		perror("MSG");
		return;
	}
	rewind(ptr);
	printf("%-15s %-15s %-11s %-10s\n", "Book's Name", "Book's Author", "ISBN", "Price");

	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date) == 7)
	{
		if (strcmp(b.status, "issued") == 0)
		{
			continue;
		}
		printf("------------------------------------------------------------------\n");
		printf("%-15s %-15s %-10s RS.%-10s\n",
			   b.name,
			   b.author,
			   b.isbn,
			   b.price);
	}
	printf("------------------------------------------------------------------\n");

	printf("Choose any book from the following:\n\n");
	getchar();
	printf("Enter the book's ISBN: ");
	fgets(code, 50, stdin);
	code[strcspn(code, "\n")] = 0;

	rewind(ptr);

	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date) == 7)
	{
		if (reuse_lower_cmp(code, b.isbn))
		{
			printf("DEBUG: status = '%s' len=%zu\n", b.status, strlen(b.status));
			if (reuse_lower_cmp(b.status, "available"))
			{
				strcpy(b.status, "issued");
				/*get current time to set issue and return date*/
				time_t now = time(NULL);
				struct tm *curtime = localtime(&now);
				strftime(b.issue_date, DATE_LEN, "%Y-%m-%d", curtime);
				
				curtime->tm_mday += 15;
				mktime(curtime);
				strftime(b.return_date, DATE_LEN, "%Y-%m-%d", curtime);
				
				fprintf(tptr, "%s|%s|%s|%s|%s|%s|%s\n", b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date);
				printf("\nBook issued successfully");
			}
			else
			{
				fprintf(tptr, "%s|%s|%s|%s|%s|%s|%s\n", b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date);
				printf("\nThe book is already issued!\n");
			}
			found = 1;
		}
		else
		{
			fprintf(tptr, "%s|%s|%s|%s|%s|%s|%s\n", b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date);
		}
	}
	fclose(tptr);
	fclose(ptr);
	remove("books.txt");
	rename("temp.txt", "books.txt");
	if (found == 0)
	{
		printf("\nThe book couldn't be found!\n");
	}
}

void return_book()
{
	struct BOOK b;
	char memid[ID_LEN];
	screen(memid);
	if (!pass(memid))
		return;
	printf("----------------------------RETURN BOOKS--------------------------\n\n");

	char code[ISBN_LEN];
	int found;

	ptr = fopen("books.txt", "r");
	tptr = fopen("temp.txt", "w");

	if (ptr == NULL || tptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG:");
		sleep(2);
		return;
	}
	found = 0;
	getchar();
	printf("Enter ISBN: ");
	fgets(code, ISBN_LEN, stdin);
	code[strcspn(code, "\n")] = 0;

	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
				  b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date) == 7)
	{
		if (reuse_lower_cmp(b.isbn, code))
		{
			found = 1;

			if (reuse_lower_cmp(b.status, "issued"))
			{
				strcpy(b.status, "available");
				strcpy(b.issue_date, "NA");
				strcpy(b.return_date, "NA");
				printf("Returned successfully\n");
			}
			else
				printf("The Book Was Not issued\n");
		}

		fprintf(tptr, "%s|%s|%s|%s|%s|%s|%s\n",
				b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date);
	}

	if (!found)
	{
		fclose(tptr);
		fclose(ptr);
		remove("temp.txt");
		printf("\nPress Enter to Continue: ");
		getchar();
		return;
	}

	fclose(tptr);
	fclose(ptr);
	remove("books.txt");
	rename("temp.txt", "books.txt");
	printf("Invalid ISBN\nPress Enter to Continue: ");
	getchar();
	return;
}

void show_books()
{
	struct BOOK b;
	ptr = fopen("books.txt", "r");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG:");
		sleep(2);
		return;
	}
	printf("\n\t------------------------------------SHOW  BOOKS-----------------------------------\n\n");

	printf("------------------------------------------------------------------------------\n");
	printf("%-15s %-15s %-10s %-8s %-10s %-8s %-8s\n",
		   "Book", "Author", "ISBN", "Price", "Status", "I_Date", "R_Date");
	printf("------------------------------------------------------------------------------\n");

	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
				  b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date) == 7)
	{
		printf("%-15.12s %-15.12s %-10.10s %-8.5s %-10.9s %-8.8s %-8.8s\n",
			   b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date);
	}

	fclose(ptr);
}

void search()
{
	struct BOOK b;
	ptr = fopen("books.txt", "r");
	char search[100];
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG:");
		sleep(2);
		return;
	}
	int again;

	getchar();

	do
	{
		int found = 0;
		rewind(ptr);

		printf("Search: ");
		fgets(search, 100, stdin);
		search[strcspn(search, "\n")] = 0;

		while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
					  b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date) == 7)
		{
			if (reuse_lower_str(search, b.name) ||
				reuse_lower_str(search, b.author) ||
				reuse_lower_str(search, b.isbn))
			{
				printf("%s | %s | %s\n", b.name, b.author, b.isbn);
				found = 1;
			}
		}

		if (!found)
		{
			printf("Not found\n1.Try again\n2.Exit\n");
			scanf("%d", &again);
			getchar();
		}
		else
			break;

	} while (again == 1);

	fclose(ptr);
}

void change()
{
	struct BOOK b;
	printf("\n\t------------------------------EDIT DATA----------------------------\n\n");

	char edit_name[NAME_LEN], edit_author[AUTHOR_LEN], edit_scode[ISBN_LEN], edit_price[PRICE_LEN];

	ptr = fopen("books.txt", "r");
	tptr = fopen("temp.txt", "w");

	if (ptr == NULL || tptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG:");
		sleep(2);
		return;
	}

	int option = 0, match_count = 0;
	int choice;
	float newprice;

	char newname[100], search[100], matched_isbns[100][ISBN_LEN], target_isbn[ISBN_LEN];

	getchar();

	match_count = 0;
	printf("Enter the Book's Name or Author or ISBN: ");
	fgets(search, 100, stdin);
	search[strcspn(search, "\n")] = 0;

	while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
				  b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date) == 7)
	{
		if (!(reuse_lower_str(search, b.name) ||
			  reuse_lower_str(search, b.author) ||
			  reuse_lower_str(search, b.isbn)))
		{
			continue;
		}
		printf("------------------------------------------------------------------\n");
		printf("%-15s %-15s %-10s RS.%-10s\n",
			   b.name, b.author, b.isbn, b.price);

		strcpy(matched_isbns[match_count], b.isbn);
		match_count++;
	}
	printf("------------------------------------------------------------------\n");

	if (match_count == 0)
	{
		printf("no books matched!!\nPress Enter to Continue: ");
		getchar();
		return;
	}
	else
	{
		if (match_count > 1)
		{
			do
			{
				printf("Enter which book to edit (1-%d): ", match_count);
				scanf("%d", &choice);
				getchar();
			} while (choice < 1 || choice > match_count);
			strcpy(target_isbn, matched_isbns[choice - 1]);
		}
		else
		{
			strcpy(target_isbn, matched_isbns[0]);
		}

		printf("\nEnter which field to edit:\n1.Edit Book Name\n2.Edit Author\n3.Edit ISBN\n4.Edit Price\nEnter an option: ");
		scanf("%d", &option);
		getchar();

		switch (option)
		{
		case 1:
			printf("Enter the correct Name: ");
			fgets(newname, NAME_LEN, stdin);
			newname[strcspn(newname, "\n")] = 0;
			strcpy(edit_name, newname);
			break;

		case 2:
			printf("Enter the correct Author: ");
			fgets(newname, AUTHOR_LEN, stdin);
			newname[strcspn(newname, "\n")] = 0;
			strcpy(edit_author, newname);
			break;

		case 3:
			printf("Enter the correct ISBN: ");
			fgets(newname, ISBN_LEN, stdin);
			newname[strcspn(newname, "\n")] = 0;
			strcpy(edit_scode, newname);
			break;

		case 4:
			printf("Enter the correct Price: ");
			scanf("%f", &newprice);
			getchar();
			sprintf(edit_price, "%.2f", newprice);
			break;

		default:
			printf("Invalid input!!\n");
			break;
		}

		rewind(ptr);
		while (fscanf(ptr, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
					  b.name, b.author, b.isbn, b.price, b.status, b.issue_date, b.return_date) == 7)
		{
			if (reuse_lower_cmp(target_isbn, b.isbn))
			{
				if (option == 1)
					strcpy(b.name, edit_name);
				else if (option == 2)
					strcpy(b.author, edit_author);
				else if (option == 3)
					strcpy(b.isbn, edit_scode);
				else if (option == 4)
					strcpy(b.price, edit_price);
			}

			fprintf(tptr, "%s|%s|%s|%s|%s|%s|%s\n",
					b.name, b.author, b.isbn,
					b.price, b.status, b.issue_date, b.return_date);
		}

		printf("Press Enter to continue:");
		getchar();
	}

	fclose(ptr);
	fclose(tptr);
	remove("books.txt");
	rename("temp.txt", "books.txt");
}

void add_membership()
{
	mem members;

	ptr = fopen("membership.txt", "a");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG:");
		sleep(2);
		return;
	}
	char age[5];
	getchar();
	printf("\n\t----------------------ADD MEMBERSHIP---------------------\n\n");
	printf("\tENTER YOUR NAME: ");
	fgets(members.name, MEMBER_NAME_LEN, stdin);
	members.name[strcspn(members.name, "\n")] = '\0';

	printf("\tENTER YOUR ADDRESS: ");
	fgets(members.address, ADDRESS_LEN, stdin);
	members.address[strcspn(members.address, "\n")] = '\0';

	printf("\tENTER YOUR NATIONALITY: ");
	fgets(members.nation, sizeof(members.nation), stdin);
	members.nation[strcspn(members.nation, "\n")] = '\0';

	if (reuse_lower_cmp("Indian", members.nation))
	{
		while (1)
		{
			printf("\tENTER YOUR ADHAAR NUMBER: ");
			fgets(members.adhaar, sizeof(members.adhaar), stdin);
			members.adhaar[strcspn(members.adhaar, "\n")] = '\0';
			if ((is_all_digit(members.adhaar)) && (strlen(members.adhaar) == 12))
				break;
			else
				printf("ADHAAR number should contain 12 digits only!!");
		}
	}
	else
	{
		strcpy(members.adhaar, "NA");
	}

	while (1)
	{
		printf("\tENTER YOUR AGE: ");
		fgets(age, sizeof(age), stdin);
		age[strcspn(age, "\n")] = '\0';
		if (is_all_digit(age))
		{
			sscanf(age, "%d", &members.act_age);
			break;
		}
	}
	while (1)
	{
		printf("\tENTER YOUR PHONE NUMBER: ");
		fgets(members.phone, sizeof(members.phone), stdin);
		members.phone[strcspn(members.phone, "\n")] = '\0';
		if (is_all_digit(members.phone))
			break;
	}

	sprintf(members.id, "M%ld", ftell(ptr));
	printf("YOUR MEMBERSHIP ID: %s", members.id);
	strcpy(members.status, "active");

	time_t now = time(NULL);
	struct tm *curtime = localtime(&now);
	strftime(members.join_date, DATE_LEN, "%Y-%m-%d", curtime);

	struct tm exptime = *curtime;
	exptime.tm_mon += 1;
	mktime(&exptime);
	strftime(members.expiry_date, DATE_LEN, "%Y-%m-%d", &exptime);

	fprintf(ptr, "%s|%s|%d|%s|%s|%s|%s|%s|%s|%s\n", members.id, members.name, members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status);

	fclose(ptr);
}

void cancel_membership()
{
	mem members;
	ptr = fopen("membership.txt", "r");
	tptr = fopen("temp.txt", "w");

	if (ptr == NULL || tptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG");
		sleep(2);
		return;
	}

	char cancel_id[ID_LEN];
	getchar();
	printf("\n\t----------------------CANCEL MEMBERSHIP---------------------\n\n");
	printf("\tENTER YOUR MEMBER ID: : ");
	fgets(cancel_id, ID_LEN, stdin);
	cancel_id[strcspn(cancel_id, "\n")] = '\0';

	while (fscanf(ptr, " %[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", members.id, members.name, &members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status) == 10)
	{
		if (!strcmp(cancel_id, members.id))
		{
			strcpy(members.status, "cancelled");
		}
		fprintf(tptr, "%s|%s|%d|%s|%s|%s|%s|%s|%s|%s\n", members.id, members.name, members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status);
	}
	fclose(ptr);
	fclose(tptr);
	remove("membership.txt");
	rename("temp.txt", "membership.txt");
}

void renew_membership()
{
	mem members;

	ptr = fopen("membership.txt", "r");
	tptr = fopen("temp.txt", "w");

	if (ptr == NULL || tptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG");
		sleep(2);
		return;
	}

	char renew_id[ID_LEN];
	getchar();
	printf("\n\t----------------------RENEW MEMBERSHIP---------------------\n\n");
	printf("\tENTER YOUR MEMBER ID: : ");
	fgets(renew_id, ID_LEN, stdin);
	renew_id[strcspn(renew_id, "\n")] = '\0';

	while (fscanf(ptr, " %[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", members.id, members.name, &members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status) == 10)
	{
		if (!strcmp(renew_id, members.id))
		{
			strcpy(members.status, "active");
			time_t now = time(NULL);
			struct tm *exptime = localtime(&now);
			exptime->tm_mon += 6;
			mktime(exptime);
			strftime(members.expiry_date, DATE_LEN, "%Y-%m-%d", exptime);
		}
		fprintf(tptr, "%s|%s|%d|%s|%s|%s|%s|%s|%s|%s\n", members.id, members.name, members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status);
	}

	fclose(ptr);
	fclose(tptr);
	remove("membership.txt");
	rename("temp.txt", "membership.txt");
}

void auto_expire()
{
	mem members;
	char cur_time[DATE_LEN];
	ptr = fopen("membership.txt", "r");
	tptr = fopen("temp.txt", "w");

	if (ptr == NULL || tptr == NULL)
	{
		return;
	}
	time_t now = time(NULL);
	struct tm *curtime = localtime(&now);
	strftime(cur_time, DATE_LEN, "%Y-%m-%d", curtime);

	while (fscanf(ptr, " %[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", members.id, members.name, &members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status) == 10)
	{
		if ((strcmp(cur_time, members.expiry_date) > 0) && (reuse_lower_cmp("Active", members.status)))
		{
			strcpy(members.status, "expired");
		}
		fprintf(tptr, "%s|%s|%d|%s|%s|%s|%s|%s|%s|%s\n", members.id, members.name, members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status);
	}
	fclose(ptr);
	fclose(tptr);
	remove("membership.txt");
	rename("temp.txt", "membership.txt");
	return;
}

void show_members()
{
	mem members;
	ptr = fopen("membership.txt", "r");
	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG:");
		sleep(2);
		return;
	}
	printf("\n\t------------------------------------SHOW  MEMBERS-----------------------------------\n\n");

	printf("------------------------------------------------------------------------------\n");
	printf("%-15s %-5s %-5s %-5s %-10s %-10s %-10s\n",
		   "Member name", "Member ID", "Age", "Phone No.", " Status", "Join Date", "Expiry_Date");
	printf("------------------------------------------------------------------------------\n");

	while (fscanf(ptr, " %[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", members.id, members.name, &members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status) == 10)
	{
		printf("%-15.12s %-5s %-5d %-8.10s %-10.9s  %-10.8s %-10.8s\n",
			   members.name, members.id, members.act_age, members.phone, members.status,
			   members.join_date, members.expiry_date);
	}

	fclose(ptr);
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

	return strcmp(a, btxt) == 0; // 1 = equal, 0 = not equal
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

	return strstr(btxt, a) != NULL; // 1 = found, 0 = not found
}

int is_all_digit(char str[])
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
			return 0;
	}
	return 1;
}

int pass(char pass[])
{
	mem members;
	ptr = fopen("membership.txt", "r");
	int found = 0;

	if (ptr == NULL)
	{
		printf("FILE NOT FOUND!!\n");
		perror("MSG:");
		sleep(2);
		return 0; // 0 = fail
	}
	while (fscanf(ptr, " %[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", members.id, members.name, &members.act_age, members.phone, members.nation, members.address, members.adhaar, members.join_date, members.expiry_date, members.status) == 10)
	{
		if (strcmp(members.id, pass) == 0)
		{
			found = 1;
			if (reuse_lower_cmp("active", members.status))
			{
				gotoxy(15, 12);
				printf("Valid ID. Access granted to %s\n", members.name);
				sleep(1);
				fclose(ptr);
				return 1; // 1 = success
			}
			else
			{
				gotoxy(15, 12);
				printf("Membership %s. Access denied.\n", members.status);
				sleep(2);
				fclose(ptr);
				;
				return 0;
			}
		}
	}

	if (!found)
	{
		gotoxy(15, 12);
		printf("Invalid ID! Authorized personnel only\n");
		sleep(2);
	}

	fclose(ptr);
	return 0; // 0 = fail
}

void screen(char pass[])
{
	getchar();
	gotoxy(15, 5);
	printf("********************************************");
	gotoxy(15, 6);
	printf("*                                         *");
	gotoxy(15, 7);
	printf("* This Mode needs Membership ID to Access *");
	gotoxy(15, 8);
	printf("*        Enter Membership ID:              *");
	gotoxy(15, 9);
	printf("*                                         *");
	gotoxy(15, 10);
	printf("********************************************");

	gotoxy(45, 8);
	fgets(pass, 25, stdin);
	pass[strcspn(pass, "\n")] = 0;
}
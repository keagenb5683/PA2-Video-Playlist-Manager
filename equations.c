#include "header.h"


void printMenu(void)
{
	printf("~-~-|| Video Playlist Manager ||-~-~\n\n");
	printf("1.| Load Videos\n");
	printf("2.| Store Videos\n");
	printf("3.| Display Videos\n");
	printf("4.| Insert Video\n");
	printf("5.| Delete Video\n");
	printf("6.| Edit Videos\n");
	printf("7.| Sort Videos\n");
	printf("8.| Rate Video\n");
	printf("9.| Play Video\n");
	printf("10.| Shuffle Videos\n");
	printf("11.| Exit\n");

	printf("Enter your selection: \n");
}


struct node* createNode(FILE* infile)
{
	// For correct implementation for allocating space for Node on list
	listNode* newNode = malloc(sizeof(struct node));

	char* temp = NULL;
	char line[250];
	int identifier = 1;

	fgets(line, 250, infile);

	// Store Title
	temp = strtok(line, ",");
	if (temp != NULL)
	{
		strcpy(newNode->Data.title, temp);
	}
	else
	{
		strcpy(newNode->Data.title, "Unknown Title");
	}

	// Store Director
	temp = strtok(NULL, ",");
	if (temp != NULL)
	{
		strcpy(newNode->Data.director, temp);
	}
	else
	{
		strcpy(newNode->Data.director, "Unknown Director");
	}

	// Store Description
	temp = strtok(NULL, ",");
	if (temp != NULL)
	{
		strcpy(newNode->Data.description, temp);
	}
	else
	{
		strcpy(newNode->Data.description, "Unknown Description");
	}

	// Store Genre
	temp = strtok(NULL, ",");
	if (temp != NULL)
	{
		strcpy(newNode->Data.genre, temp);
	}
	else
	{
		strcpy(newNode->Data.genre, "Unknown Genre");
	}

	// Begin to Store Runtime
	temp = strtok(NULL, ",");
	char* length = temp;

	// Store Year
	temp = strtok(NULL, ",");
	if (temp != NULL)
	{
		newNode->Data.year = atoi(temp);
	}
	else
	{
		newNode->Data.year = 0;
	}

	// Store Plays
	temp = strtok(NULL, ",");
	if (temp != NULL)
	{
		newNode->Data.numPlayed = atoi(temp);
	}
	else
	{
		newNode->Data.numPlayed = 0;
	}

	// Store Rating
	temp = strtok(NULL, ",");
	if (temp != NULL)
	{
		newNode->Data.rating = atoi(temp);
	}
	else
	{
		newNode->Data.rating = 0;
	}


	// Parse length for Runtime
	char *hourMin = NULL;
	hourMin = strtok(length, ":");
	if (hourMin != NULL)
	{
		newNode->Data.runtime.Hours = atoi(hourMin);
		hourMin = strtok(length, ":");
		newNode->Data.runtime.Minutes = atoi(hourMin);
	}
	else
	{
		newNode->Data.runtime.Hours = 0;
		newNode->Data.runtime.Minutes = 0;
	}

	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

// For implementation of insertFront()
void insertFront(struct node** headPtr, FILE* infile)
{
	// If list is empty, make new node
	if (*headPtr == NULL)
	{
		listNode* newNode = createNode(infile);
		*headPtr = newNode;

		newNode->prev = NULL;
		newNode->next = NULL;
	}

	else
	{
		listNode* newNode = createNode(infile);
		listNode* temp = *headPtr;
		*headPtr = newNode;

		newNode->next = temp;
		newNode->prev = NULL;
		temp->prev = newNode;
	}
}

void createList(struct node** headPtr, FILE* infile)
{
	int count = 1;
	while (!feof(infile))
	{
		insertFront(headPtr, infile);
		count++;
	}
}

//(2) Store
void storeList(struct node* head, FILE* infile)
{
	struct node* current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}

	while (current->prev != NULL)
	{
		fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d,%d", current->Data.title, current->Data.director, current->Data.description,
			current->Data.genre, current->Data.runtime.Hours, current->Data.runtime.Minutes, current->Data.year, current->Data.numPlayed, current->Data.rating);

		current = current->prev;
	}
}

void indexID(struct node* pList)
{
	int index = 1;
	listNode* current = pList;

	while (current != NULL)
	{
		current->Data.ID = index;
		index++;
		current = current->next;
	}
}

// For correct implementation of printList()
void printList(struct node* pList)
{
	int select = 0;

	do
	{
		system("cls");
		printf("~-~-|| Display ||-~-~\n\n");
		printf("1.| Print all movies\n");
		printf("2.| Print all records from a director\n");
		printf("3.| Print all records from a year\n\n");
		printf("Enter your selection: \n");
		scanf("%d", &select);
	} while ((select != 1) && (select != 2) && (select != 3));

	listNode* current = pList;

	switch (select)
	{
	case 1:
		system("cls");
		printf("Printing all movies...\n");
		system("pause");
		while (current != NULL)
		{
			printf("Title:        | %s\n", current->Data.title);
			printf("Director:     | %s\n", current->Data.director);
			printf("Description:  | %s\n", current->Data.description);
			printf("Genre:        | %s\n", current->Data.genre);
			printf("Runtime:      | %d:%d\n", current->Data.runtime.Hours, current->Data.runtime.Minutes);
			printf("Year:         | %d\n", current->Data.year);
			printf("Times Played: | %d\n", current->Data.numPlayed);
			printf("Rating:       | %d\n", current->Data.rating);
			printf("ID:           | %d\n\n", current->Data.ID);

			current = current->next;
		}
		break;


	}
	
}

void print(struct node* pList)
{
	listNode* current = pList;

	while (current != NULL)
	{
		printf("Title:        | %s\n", current->Data.title);
		printf("Director:     | %s\n", current->Data.director);
		printf("Description:  | %s\n", current->Data.description);
		printf("Genre:        | %s\n", current->Data.genre);
		printf("Runtime:      | %d:%d\n", current->Data.runtime.Hours, current->Data.runtime.Minutes);
		printf("Year:         | %d\n", current->Data.year);
		printf("Times Played: | %d\n", current->Data.numPlayed);
		printf("Rating:       | %d\n\n", current->Data.rating);

		current = current->next;
	}
}

void search(struct node* pList)
{
	listNode* current = pList;
	int choiceM = 0;

	while (current != NULL)
	{
		if (current->Data.ID == 7)
		{
			do
			{
				printf("Is '%s' the movie you would like to edit?\n", current->Data.title);
				printf("1.| Yes\n2.| No\n\nEnter your selection: |n");
				scanf(" %d", &choiceM);
			} while ((choiceM != 1) && (choiceM != 2));
		}

		current = current->next;
	}
}

void editInfo(struct node* head)
{
	struct node* current = head;
	char temp[50];
	int choice = 0, newYear = 0;
	do
	{
		system("cls");
		printf("~-~-|| Movie to edit: %s||-~-~\n\n", current->Data.title);
		printf("1.| Title\n");
		printf("2.| Director\n");
		printf("3.| Description\n");
		printf("4.| Genre\n");
		printf("5.| Year\n");
		printf("What would you like to edit?\n");
		scanf(" %d", &choice);
	} while ((choice < 1) && (choice > 5));

	switch (choice)
	{
	case 1:
		printf("Current title: %s\n", current->Data.title);
		printf("What would you like the new title to be?\n");
		getchar();
		fgets(temp, 50, stdin);
		strcpy(current->Data.title, temp);
		printf("New title: %s", current->Data.title);
		system("pause");
		break;

	case 2:
		printf("Current director: %s\n", current->Data.director);
		printf("What would you like the new director to be?\n");
		getchar();
		fgets(temp, 50, stdin);
		strcpy(current->Data.director, temp);
		printf("New director: %s", current->Data.director);
		system("pause");
		break;

	case 3:
		printf("Current description: %s\n", current->Data.description);
		printf("What would you like the new description to be?\n");
		getchar();
		fgets(temp, 50, stdin);
		strcpy(current->Data.description, temp);
		printf("New description: %s", current->Data.description);
		system("pause");
		break;

	case 4:
		printf("Current genre: %s\n", current->Data.genre);
		printf("What would you like the new genre to be?\n");
		getchar();
		fgets(temp, 50, stdin);
		strcpy(current->Data.genre, temp);
		printf("New genre: %s", current->Data.genre);
		system("pause");
		break;

	case 5:
		printf("Current year: %d\n", current->Data.year);
		printf("What would you like the new year to be?\n");
		scanf(" %d", &newYear);
		current->Data.year = newYear;
		printf("New year: %s", current->Data.year);
		system("pause");
		break;
	}
}


void editList(struct node* head)
{
	struct node* current = head;
	int choiceD = 0, choiceM = 0;
	char director[50] = { 0 };

	do
	{
		system("cls");
		printf("~-~-|| Edit Movie Listings ||-~-~\n\n");
		printf("1.| Todd Phillips\n");
		printf("2.| Martin Scorsese\n");
		printf("3.| John G. Avildsen\n");
		printf("4.| Pierre Coffin\n");
		printf("5.| Andy Fickman\n\n");
		printf("Select the artist you would like to sort by: \n");
		scanf(" %d", &choiceD);
	} while ((choiceD < 1) && (choiceD > 5));

	switch (choiceD)
	{
	case 1: // Pick Todd Phillips (7)
		while (current != NULL)
		{
			if (current->Data.ID == 7)
			{
				do
				{
					printf("Is '%s' the movie you would like to edit?\n", current->Data.title);
					printf("1.| Yes\n2.| No\n\nEnter your selection: \n");
					scanf(" %d", &choiceM);
				} while ((choiceM != 1) && (choiceM != 2));

				if (choiceM == 1)
				{
					editInfo(current);
				}
				else if (choiceM == 2)
				{
					break;
				}
			}

			current = current->next;
		}
		break;
	case 2: // Pick Martin Scorsese (4,5,6)
		while (current != NULL)
		{
			if (current->Data.ID == 4 || current->Data.ID == 5 || current->Data.ID == 6)
			{
				do
				{
					printf("Is '%s' the movie you would like to edit?\n", current->Data.title);
					printf("1.| Yes\n2.| No\n\nEnter your selection: \n");
					scanf(" %d", &choiceM);
				} while ((choiceM != 2) && (choiceM != 1));
				if (choiceM == 1)
				{
					editInfo(current);
				}
				else if (choiceM == 2)
				{
					break;
				}
			}
			break;
	case 3: // Pick John G. Avildsen (3)
		while (current != NULL)
		{
			if (current->Data.ID == 3)
			{
				do
				{
					printf("Is '%s' the movie you would like to edit?\n", current->Data.title);
					printf("1.| Yes\n2.| No\n\nEnter your selection: \n");
					scanf(" %d", &choiceM);
				} while ((choiceM != 2) && (choiceM != 1));
				if (choiceM == 1)
				{
					editInfo(current);
				}
				else if (choiceM == 2)
				{
					break;
				}
			}
			current = current->next;
		}
		break;
	case 4: // Pick Pierre Coffin (2)
		while (current != NULL)
		{
			if (current->Data.ID == 2)
			{
				do
				{
					printf("Is '%s' the movie you would like to edit?\n", current->Data.title);
					printf("1.| Yes\n2.| No\n\nEnter your selection: \n");
					scanf(" %d", &choiceM);
				} while ((choiceM != 2) && (choiceM != 1));
				if (choiceM == 1)
				{
					editInfo(current);
				}
				else if (choiceM == 2)
				{
					break;
				}
			}
			current = current->next;
		}
		break;
	case 5: // Pick Andy Fickman (1)
		while (current != NULL)
		{
			if (current->Data.ID == 1)
			{
				do
				{
					printf("Is '%s' the movie you would like to edit?\n", current->Data.title);
					printf("1.| Yes\n2.| No\n\nEnter your selection: \n");
					scanf(" %d", &choiceM);
				} while ((choiceM != 2) && (choiceM != 1));
				if (choiceM == 1)
				{
					editInfo(current);
				}
				else if (choiceM == 2)
				{
					break;
				}
			}
			current = current->next;
		}
		break;
		} // switch(choiceD)
	}
}


void rateMovie(struct node* head)
{
	struct node* current = head;
	int choice = 0, rating = 0, ID = 0;
	char director[50];
	do
	{
		printf("~-~-|| Movie Ratings ||-~-~\n\n");
		printf("1.| Joker\n");
		printf("2.| The Irishman\n");
		printf("3.| Shutter Island\n");
		printf("4.| Taxi Driver\n");
		printf("5.| Rocky\n");
		printf("6.| Despicable Me\n");
		printf("7.| You Again\n");
		printf("Enter the movie you would like to rate: \n");
		scanf(" %d", &choice);
	} while ((choice < 1) && (choice > 7));

	switch (choice)
	{
	case 1:
		ID = 7;
		break;

	case 2:
		ID = 6;
		break;

	case 3:
		ID = 5;
		break;

	case 4:
		ID = 4;
		break;

	case 5:
		ID = 3;
		break;

	case 6:
		ID = 2;
		break;

	case 7:
		ID = 1;
		break;
	}


	while (current != NULL)
	{
		if (current->Data.ID == ID)
		{
			printf("Movie: %s\n", current->Data.title);
			printf("Current rating: %d\n", current->Data.rating);
			printf("What would you like to rate the movie?");
			scanf(" %d", &rating);
			current->Data.rating = rating;
			printf("New rating: %d\n", current->Data.rating);

		}
		current = current->next;
	}
}


void playMovie(struct node* head)
{
	struct node* current = head;
	int choice = 0, rating = 0, ID = 0;
	
	do
	{
		printf("~-~-|| Play Movies ||-~-~\n\n");
		printf("1.| Joker\n");
		printf("2.| The Irishman\n");
		printf("3.| Shutter Island\n");
		printf("4.| Taxi Driver\n");
		printf("5.| Rocky\n");
		printf("6.| Despicable Me\n");
		printf("7.| You Again\n");
		printf("Enter the movie you would like to begin playing: \n");
		scanf(" %d", &choice);
	} while ((choice < 1) && (choice > 7));

	switch (choice)
	{
	case 1:
		ID = 7;
		break;

	case 2:
		ID = 6;
		break;

	case 3:
		ID = 5;
		break;

	case 4:
		ID = 4;
		break;

	case 5:
		ID = 3;
		break;

	case 6:
		ID = 2;
		break;

	case 7:
		ID = 1;
		break;
	}


	while (current != NULL)
	{
		if (current->Data.ID == ID)
		{
			while (current != NULL)
			{
				printf("Title:        | %s\n", current->Data.title);
				printf("Director:     | %s\n", current->Data.director);
				printf("Description:  | %s\n", current->Data.description);
				printf("Genre:        | %s\n", current->Data.genre);
				printf("Runtime:      | %d:%d\n", current->Data.runtime.Hours, current->Data.runtime.Minutes);
				printf("Year:         | %d\n", current->Data.year);
				printf("Times Played: | %d\n", current->Data.numPlayed);
				printf("Rating:       | %d\n\n", current->Data.rating);
				system("pause");
				current = current->prev;
			}

		}
		current = current->next;
	}
}

/*
PA 3 FUNCTION DEFINITIONS
*/

// (17pts) Correct insert implimentation
void insertNew(struct node** headPtr)
{
	listNode* newMovie = malloc(sizeof(struct node));
	
	// Prompt for each attribute
	char artistNew[50];
	printf("Enter the name of the new title: \n");
	gets(artistNew);
	gets(artistNew);
	strcpy(newMovie->Data.title, artistNew);
	printf("New movie title: %s\n", newMovie->Data.title);
	

	char directorNew[50];
	printf("Enter the name of the new director: \n");
	
	gets(directorNew);
	strcpy(newMovie->Data.director, directorNew);
	printf("New director: %s\n", newMovie->Data.director);
	

	char descriptionNew[150];
	printf("Enter the new description: \n");
	gets(descriptionNew);
	strcpy(newMovie->Data.description, descriptionNew);
	printf("New description: %s\n", newMovie->Data.description);
	

	char genreNew[50];
	printf("Enter the name of the new genre: \n");
	gets(genreNew);
	strcpy(newMovie->Data.genre, genreNew);
	printf("New genre: %s\n\n", newMovie->Data.genre);
	

	int hours = 0, minutes = 0;
	printf("Enter the hours of the runtime: \n");
	scanf("%d", &hours);
	printf("Enter the minutes of the runtime: \n");
	scanf("%d", &minutes);
	newMovie->Data.runtime.Hours = hours;
	newMovie->Data.runtime.Minutes = minutes;
	printf("New runtime: %d:%d\n\n", newMovie->Data.runtime.Hours, newMovie->Data.runtime.Minutes);

	int year;
	printf("Enter the year of the new movie: \n");
	scanf("%d", &year);
	newMovie->Data.year = year;
	printf("New year: %d\n\n", newMovie->Data.year);

	int numPlayed;
	printf("Enter the number of times the movie has been played: \n");
	scanf("%d", &numPlayed);
	newMovie->Data.numPlayed = numPlayed;
	printf("New number times played: %d\n\n", newMovie->Data.numPlayed);

	int rating;
	printf("Enter the rating of the movie: \n");
	scanf("%d", &rating);
	newMovie->Data.rating = rating;
	printf("New rating: %d\n\n", newMovie->Data.rating);
	system("pause");
	system("cls");
	printf("~-~-|| New Movie ||-~-~\n\n");
	printf("Title:        | %s\n", newMovie->Data.title);
	printf("Director:     | %s\n", newMovie->Data.director);
	printf("Description:  | %s\n", newMovie->Data.description);
	printf("Genre:        | %s\n", newMovie->Data.genre);
	printf("Runtime:      | %d:%d\n", newMovie->Data.runtime.Hours, newMovie->Data.runtime.Minutes);
	printf("Year:         | %d\n", newMovie->Data.year);
	printf("Times Played: | %d\n", newMovie->Data.numPlayed);
	printf("Rating:       | %d\n\n", newMovie->Data.rating);

	listNode* temp = *headPtr;
	// Correctly insert at front of list
	if (*headPtr == NULL)
	{
		*headPtr = newMovie;
		newMovie->next = NULL;
		newMovie->prev = NULL;
		printf("Movie has been inserted into empty list successfully.\n");
		return;
	}
	else
	{
		newMovie->next = *headPtr;
		newMovie->prev = NULL;
		*headPtr = newMovie;
		printf("Movie was inserted into list successfully.\n");
		return;
	}
}

// (23pts) Correct delete implimentation
int delete(struct node* headPtr)
{
	struct node* current = headPtr;

	int choice = 0, ID = 0;
	// Prompting for movie title
	do
	{
		printf("~-~-|| Delete Movies ||-~-~\n\n");
		printf("1.| Joker\n");
		printf("2.| The Irishman\n");
		printf("3.| Shutter Island\n");
		printf("4.| Taxi Driver\n");
		printf("5.| Rocky\n");
		printf("6.| Despicable Me\n");
		printf("7.| You Again\n");
		printf("Enter the movie you would like to delete: \n");
		scanf(" %d", &choice);
	} while ((choice < 1) && (choice > 7));

	
	switch (choice)
	{
	case 1:
		ID = 7;
		break;

	case 2:
		ID = 6;
		break;

	case 3:
		ID = 5;
		break;

	case 4:
		ID = 4;
		break;

	case 5:
		ID = 3;
		break;

	case 6:
		ID = 2;
		break;

	case 7:
		ID = 1;
		break;
	}

	// Get specific movie selection
	while (current != NULL)
	{
		if (current->Data.ID == ID)
		{
			// Deleting current movie, then reconnecting the prev and next movies within list
			current->next->prev = current->prev;
			current->prev->next = current->next;
			printf("Movie to delete: %s\n", current->Data.title);
			free(current);
			printf("Movie succesfully deleted\n");
			printf("Go to 3.| Display Videos, then 1.| Print All and you will see that it is not there!\n");

			return 0;
		}
		current = current->next;
	}
}

// (15pts) for shuffle implementation
void shuffle(struct node* head)
{
	system("cls");

	int size = 0;
	listNode* current = head;
	char numbers[7] = { 1,2,3,4,5,6,7 };
	char shuffle[7] = { 0 };

	int j = 0, new, i = 0, ID = 0, count = 0;

	// Generating random order
	for (i = 0; i < 7; i++)
	{
		new = (rand() % 7 + 1);
		if (numbers[new - 1] != 0)
		{
			shuffle[i] = new;
		}
	}

	/*
	for (i = 0; i < 7; i++)
	{
		printf("%d\n", shuffle[i]);
	}
	*/

	i = 0;
	
	// Moving through the list with the randomized order
		while (current != NULL)
		{
			if (current->Data.ID == shuffle[i])
			{

				printf("Title:        | %s\n", current->Data.title);
				printf("Director:     | %s\n", current->Data.director);
				printf("Description:  | %s\n", current->Data.description);
				printf("Genre:        | %s\n", current->Data.genre);
				printf("Runtime:      | %d:%d\n", current->Data.runtime.Hours, current->Data.runtime.Minutes);
				printf("Year:         | %d\n", current->Data.year);
				printf("Times Played: | %d\n", current->Data.numPlayed);
				printf("Rating:       | %d\n\n", current->Data.rating);
				printf("Loading next movie...\n\n");
				system("pause");

				current = head;
				i++;
			}
			current = current->next;
		}
	
}

void sortTitle(struct node* head)
{

}

void sortRating(struct node* head)
{
	int temporary = 0, i = 0, count = 0;

	listNode* current = head;
	listNode* temp = NULL;

	int array[7] = { 0 };

	while (count != 6)
	{
		while (current != NULL)
		{
			if (temp->Data.rating <= current->next->Data.rating)
			{
			temp = current;
			}
			current = current->next;
		}
		current = head;
		array[i] = temp->Data.ID;
		printf("%d\n", temp->Data.rating);
		count++;
		i++;
	}
}
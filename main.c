#include "header.h"

int main(void)
{
	FILE* infile = NULL;
	infile = fopen("moviePlayList.csv", "r");

	listNode* head = NULL;
	listNode** headPtr = &head;
	listNode* current = head;

	// Correct load command (I have it do it here right when the menu opens to be safe)
	// For correctly constructing a doubly linked list (see the function for more)
	createList(headPtr, infile);
	indexID(head);

	int running = 1, input = 0, choiceD = 0, choiceM = 0;
	char director[50] = { 0 };


	// While loop that runs whole program
	while (running == 1)
	{
		// For correctly displaying menu
		system("cls");
		printf("~-~-|| Video Playlist Manager ||-~-~\n\n");
		printf("1.| Load Videos\n");
		printf("2.| Store Videos\n");
		printf("3.| Display Videos\n");
		printf("4.| Insert Video *NEW*\n");
		printf("5.| Delete Video *NEW*\n");
		printf("6.| Edit Videos\n");
		printf("7.| Sort Videos\n");
		printf("8.| Rate Video\n");
		printf("9.| Play Video\n");
		printf("10.| Shuffle Videos *NEW*\n");
		printf("11.| Exit\n");
		do
		{
			printf("Enter your selection: \n");
			scanf("%d", &input);
		} while ((input < 1) && (input > 10));

		// For looping back to main menu (the breaks in the switch will take you back after executing the command)
		switch(input)
		{
		case 1:
			system("cls");
			printf("Movies loaded from infile.\n");
			system("pause");
			break;


		case 2:
			// Correct store command implementation
			storeList(head, infile);
			system("pause");
			break;


		case 3:
			// For correct display command implementation
			printList(head);
			system("pause");
			break;


		case 4:
			system("cls");
			insertNew(head);
			system("pause");
			break;


		case 5:
			system("cls");
			delete(head);
			system("pause");
			break;


		case 6:
			system("cls");
			editList(head);
			system("pause");
			break;


		case 7:
			system("cls");
			int sortChoice = 0;
			printf("~-~-|| Sort Videos ||-~-~\n\n");
			printf("1.| Sort based on movie title\n2.| Sort based on director\n3.| Sort based on rating\n4.| Sort based on times played\n\n");

			do
			{
				printf("Enter your selection: \n");
				scanf("%d", &sortChoice);
			} while (sortChoice < 1 || sortChoice > 4);

			switch (sortChoice)
			{
			case 1:
			{
				printf("Sorting based on movie title...\n\n");
				
				system("pause");
			}//case 1

			case 2:
			{

			}//case 2

			case 3:
			{
				printf("Sorting based on rating...\n\n");
				sortRating(head);
				system("pause");


			}//case3

			case 4:
			{

			}//case 4

			}



			system("pause");
			break;

			// Correct rate command implementation
		case 8:
			system("cls");
			rateMovie(head);
			system("pause");
			break;


		case 9:
			system("cls");
			playMovie(head);
			break;


		case 10:
			system("cls");
			shuffle(head);
			system("pause");
			break;


		case 11:
			// Correct exit command implementation
			system("cls");
			printf("Thanks for using CougTube!\n\n");
			printf("Program closing...\n");
			storeList;
			running = 0;

			fclose(infile);
			break;



		} // switch(input)

	} // while(running == 1)


	return 0;
}
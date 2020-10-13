#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Appropriate top-down design

/*
Programmer: Keagen Brendle - 11630902
Class: CptS 122, Spring, 2020
Programming Assignment: PA2
Date: February 10th, 2020
Description: 
*/


// For definition of struct Duration
typedef struct duration
{
	int Hours;
	int Minutes;
}Duration;

// For definition of struct Record
typedef struct record
{
	char title[50];
	char director[50];
	char description[200];
	char genre[20];
	Duration runtime;
	int year;
	int numPlayed;
	int rating;
	int ID;
}Record;

// For definition of struct Node
typedef struct node
{
	Record Data;
	struct node* next;
	struct node* prev;
}listNode;

// Prints out the main menu options and prompts user for choice
void printMenu(void);

// Function creates new node each time new movie data needs to be entered
struct node* createNode(FILE* infile);

// Takes the newly created node and places it within the doubly linked list
void insertFront(struct node** headPtr, FILE* infile);

// Uses both createNode and insertFront to parse through the entire infile and load in all of the movie data
void createList(struct node** headPtr, FILE* infile);

// Outputs new data to infile
void storeList(struct node* head, FILE* infile);

// Prints out all movie data within the linked list
void printList(struct node* pList);

// Prompts user for director, then movies from said director that the user would like to edit
void editList(struct node* head);

// Prompts the user for which movie they would like to give a new rating to, then updates the rating for that movie
void rateMovie(struct node* head);

// Plays through all of the movies starting with the one the user selects (for some reason exits entire program?)
void playMovie(struct node* head);

// Something I added that gives each movie its own integer ID to make it easier to find
void indexID(struct node* pList);

// A test for searching for a specific movie within the linked list 
void search(struct node* pList);

// Prompts user for which specific data points should be edited within the movie struct 
void editInfo(struct node* head);


/*
PA 3 FUNCTION HEADERS *NEW*
*/

void insertNew(struct node** headPtr);

int delete(struct node* headPtr);

void shuffle(struct node* head);

void sortTitle(struct node* head);

void sortRating(struct node* head);

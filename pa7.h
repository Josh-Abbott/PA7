#ifndef PA7_H
#define PA7_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int run_menu();
void print_rules();
void shuffle(int wDeck[][13]);
void deal(const char* wFace[], const char* wSuit[], struct Hand *hand, int card_amt, int card_change);
int pair(struct Hand hand, char* suit[], char* face[], int frequency[13]);
int pairs(struct Hand hand, char* suit[], char* face[], int frequency[13]);
int three_of_a_kind(struct Hand hand, char* suit[], char* face[], int frequency[13]);
int four_of_a_kind(struct Hand hand, char* suit[], char* face[], int frequency[13]);
int straight(struct Hand hand, char* suit[], char* face[], int frequency[13]);
int flush(struct Hand hand, char* suit[], char* face[], int frequency[4]);
int comp_check(int points);
void count_faces(struct Hand hand, int *frequency[13]);
void count_suits(struct Hand hand, int* frequency[4]);
int check_hand(struct Hand hand, char* suit[], char* face[], int frequency[13], int frequency2[4]);
void print_hand(struct Hand hand, char* suit[], char* face[], int plr);

typedef struct Card
{
	int face_index;
	int suit_index;
} Card;

typedef struct Hand
{
	Card cards[5];
} Hand;

#endif
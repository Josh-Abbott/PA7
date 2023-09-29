#include "pa7.h"

/* shuffle cards in deck */

void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck */
void deal(const char* wFace[], const char* wSuit[], struct Hand *hand, int card_amt, int card_change)
{
	int wDeck[4][13] = { 0 };
	shuffle(wDeck);
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int card_counter = 0;
	
	if (card_change != 0)
	{
		row = rand() % 4;
		column = rand() % 13;
		hand->cards[card_change].face_index = column;
		hand->cards[card_change].suit_index = row;
	}
	else
	{
		/* deal each of the 52 cards */
		for (card = 1; card <= card_amt; card++)
		{
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, display card */
					if (wDeck[row][column] == card)
					{
						//printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t');
						hand->cards[card_counter].face_index = column;
						hand->cards[card_counter].suit_index = row;
						card_counter += 1;
					}
				}
			}
		}
	}
}

int run_menu()
{
	int loop_num = 0, selection = 0;
	while (loop_num == 0)
	{
		system("cls");
		printf("*** == P O K E R == ***");
		printf("\n1. View game rules");
		printf("\n2. Play");
		printf("\n3. Exit\n");
		scanf("%d", &selection);
		if (selection == 1 || selection == 2 || selection == 3)
		{
			loop_num = 1;
		}
	}
	return selection;
}

void print_rules()
{
	system("cls");
	printf("In five card poker, you and the computer (the dealer) will both be dealt 5 cards.\n");
	printf("You'll be able to see your own cards, but not the dealer's.\n");
	printf("Both of you will be able to redraw between 1-3 cards to help better your hand.\n");
	printf("The quality of your hand will depend on the poker combinations.\n");
	printf("These combinations, in order of best to worst, are:\n");
	printf("1. Four of a Kind (four cards of the same face)\n");
	printf("2. Flush (five cards with the same suit)\n");
	printf("3. Straight (five cards with consecutive values)\n");
	printf("4. Three of a Kind (three cards of the same face)\n");
	printf("5. Pairs (four cards that make two pairs)\n");
	printf("6. Pair (two cards of the same face)\n");
	system("pause");
}

void print_hand(struct Hand hand, const char* wSuit[], const char* wFace[], int plr)
{
	if (plr == 1)
	{
		printf("*YOUR CARDS:*\n");
	}
	else if (plr == 2)
	{
		printf("*DEALER'S CARDS:*\n");
	}
	for (int i = 0; i <= 4; i++) {
		int face = hand.cards[i].face_index;
		int suit = hand.cards[i].suit_index;
		printf("#%d: %5s of %-8s%c", i+1, wFace[face], wSuit[suit], i % 2 == 0 ? '\n' : '\t');
	}
}

void count_faces(struct Hand hand, int* frequency[13])
{
	for (int i = 1; i <= 13; i++)
	{
		int counter = 0;
		for (int j = 0; j < 5; j++)
		{
			int face = hand.cards[j].face_index;
			if (face == i)
			{
				counter += 1;
			}
		}
		frequency[i - 1] = counter;
	}
}

void count_suits(struct Hand hand, int* frequency[4])
{
	for (int i = 1; i <= 4; i++)
	{
		int counter = 0;
		for (int j = 0; j < 5; j++)
		{
			int suit = hand.cards[j].suit_index;
			if (suit == i)
			{
				counter += 1;
			}
		}
		frequency[i - 1] = counter;
	}
}

int pair(struct Hand hand, char* suit[], char* face[], int frequency[13])
{
	for (int i = 0; i < 13; i++)
	{
		if (frequency[i] == 2)
		{
			return 1;
		}
	}
	return 0;
}

int pairs(struct Hand hand, char* suit[], char* face[], int frequency[13])
{
	int pair_count = 0;
	for (int i = 0; i < 13; i++)
	{
		if (frequency[i] == 2)
		{
			pair_count += 1;
		}
	}
	if (pair_count == 2)
	{
		return 1;
	}
	return 0;
}

int three_of_a_kind(struct Hand hand, char* suit[], char* face[], int frequency[13])
{
	for (int i = 0; i < 13; i++)
	{
		if (frequency[i] == 3)
		{
			return 1;
		}
	}
	return 0;
}

int four_of_a_kind(struct Hand hand, char* suit[], char* face[], int frequency[13])
{
	for (int i = 0; i < 13; i++)
	{
		if (frequency[i] == 4)
		{
			return 1;
		}
	}
	return 0;
}

int flush(struct Hand hand, char* suit[], char* face[], int frequency[4]) 
{
	for (int i = 0; i < 4; i++)
	{
		if (frequency[i] == 5)
		{
			return 1;
		}
	}
	return 0;
}

int straight(struct Hand hand, char* suit[], char* face[], int frequency[13])
{
	int counter = 0;
	for (int i = 0; i <= 13; i++)
	{
		if (frequency[i] == 1)
		{
			counter += 1;
		}
		else if (counter == 5 && frequency[i] == 0)
		{
			return 1;
		}
		else
		{
			counter = 0;
		}
	}

	return 0;
}

int check_hand(struct Hand hand, char* suit[], char* face[], int frequency[13], int frequency2[4])
{
	int score = 0;
	if (pair(hand, suit, face, frequency) == 1)
	{
		score += 1;
	}
	if (pairs(hand, suit, face, frequency) == 1)
	{
		score += 2;
	}
	if (three_of_a_kind(hand, suit, face, frequency) == 1)
	{
		score += 3;
	}
	if (straight(hand, suit, face, frequency) == 1)
	{
		score += 4;
	}
	if (flush(hand, suit, face, frequency2) == 1)
	{
		score += 5;
	}
	if (four_of_a_kind(hand, suit, face, frequency) == 1)
	{
		score += 6;
	}
	return score;
}

int comp_check(int points)
{
	int drawn_num = 0;
	if (points == 0 || points == 1)
	{
		drawn_num = 3;
	}
	else if (points == 2 || points == 3)
	{
		drawn_num = 2;
	}
	else if (points == 4 || points == 5)
	{
		drawn_num = 1;
	}
	else if (points > 5)
	{
		drawn_num = 0;
	}

	return drawn_num;
}
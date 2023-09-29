#include "pa7.h"

int main(void)
{
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	int* frequency1f[13] = { 0 };
	int* frequency1s[4] = { 0 };
	int* frequency2f[13] = { 0 };
	int* frequency2s[4] = { 0 };

	int menu_loop = 0, menu_num = 0, game_loop = 1;

	srand((unsigned)time(NULL));

	while (menu_loop == 0)
	{
		menu_num = run_menu();

		switch (menu_num)
		{
		case 1:
			system("cls");
			print_rules();
			break;
		case 2:
			game_loop = 0;
			menu_loop = 1;
			break;
		case 3:
			system("cls");
			menu_loop = 1;
			printf("Thank you for playing poker, goodbye!");
			break;
		default:
			system("cls");
			break;
		}
	}

	while (game_loop == 0)
	{
		int* frequency1f[13] = { 0 };
		int* frequency1s[4] = { 0 };
		int* frequency2f[13] = { 0 };
		int* frequency2s[4] = { 0 };

		int prompt_loop = 0, player1_score = 0,
			player2_score = 0, redraw_amount = 0, redraw_num = 0, comp_drawn = 0;

		struct Hand hand1;
		struct Hand hand2;

		system("cls");
		deal(face, suit, &hand1, 5, 0);
		deal(face, suit, &hand2, 5, 0);
		printf("Player's hands have been dealt!\n");

		system("pause");
		system("cls");
		print_hand(hand1, suit, face, 1);

		count_faces(hand1, &frequency1f);
		count_suits(hand1, &frequency1s);
		count_faces(hand2, &frequency2f);
		count_suits(hand2, &frequency2s);

		char response = 'a';
		while (prompt_loop == 0)
		{
			printf("\nWould you like to redraw any cards? (y/n): \n");
			scanf(" %c", &response);
			if (response == 'y' || response == 'n')
			{
				prompt_loop = 1;
			}
			else
			{
				system("cls");
				print_hand(hand1, suit, face, 1);
			}
		}
		if (response == 'y')
		{
			prompt_loop = 0;
			while (prompt_loop == 0)
			{
				printf("\nHow many cards would you like to redraw, with a max of 3?: ");
				scanf("%d", &redraw_amount);
				if (redraw_amount > 0 && redraw_amount <= 3)
				{
					prompt_loop = 1;
				}
			}
			system("cls");
			print_hand(hand1, suit, face, 1);
			for (int i = 0; i < redraw_amount; i++)
			{
				prompt_loop = 0;
				while (prompt_loop == 0)
				{
					printf("Enter the card number you'd like to replace (1-5): ");
					scanf("%d", &redraw_num);
					if (redraw_num >= 1 && redraw_num <= 5)
					{
						prompt_loop = 1;
					}
					else
					{
						system("cls");
						print_hand(hand1, suit, face, 1);
					}
				}
				deal(face, suit, &hand1, 1, redraw_num - 1);
				system("cls");
				print_hand(hand1, suit, face, 1);
			}
		}
		comp_drawn = comp_check(player2_score);
		for (int i = 0; i < comp_drawn; i++)
		{
			int redraw_num = rand() % 5;
			deal(face, suit, &hand2, 1, redraw_num - 1);
		}
		printf("\nThe dealer has chosen to redraw %d of their cards.\n", comp_drawn);

		count_faces(hand1, &frequency1f);
		count_suits(hand1, &frequency1s);
		count_faces(hand2, &frequency2f);
		count_suits(hand2, &frequency2s);
		player1_score = check_hand(hand1, suit, face, frequency1f, frequency1s);
		player2_score = check_hand(hand2, suit, face, frequency2f, frequency2s);

		system("pause");
		system("cls");

		//EVALUATE WHO WON
		if (player1_score > player2_score)
		{
			printf("Your hand won this round!\n");
			print_hand(hand1, suit, face, 1);
			printf("\n");
			print_hand(hand2, suit, face, 2);
		}
		else if (player2_score > player1_score)
		{
			printf("The dealer's hand won this round!\n");
			print_hand(hand1, suit, face, 1);
			printf("\n");
			print_hand(hand2, suit, face, 2);
		}
		else if (player1_score == player2_score)
		{
			printf("Both hands have tied!\n");
			print_hand(hand1, suit, face, 1);
			printf("\n");
			print_hand(hand2, suit, face, 2);
		}
		system("pause");
		system("cls");

		response = 'a';
		prompt_loop = 0;
		while (prompt_loop == 0)
		{
			printf("Would you like to play another round? (y/n): \n");
			scanf(" %c", &response);
			if (response == 'y' || response == 'n')
			{
				prompt_loop = 1;
			}
			else
			{
				system("cls");
			}
		}
		if (response == 'n')
		{
			system("cls");
			printf("Thank you for playing poker, goodbye!");
			game_loop = 1;
			return 0;
		}
	}
}
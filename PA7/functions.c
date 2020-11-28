#include "functions.h"

void display_menu() 
{
	printf("Hello, welcome to five card poker...\n\n1. Play\n2. Rules\n3. Exit");

}

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
void deal(Hand *player, int current_player, int wDeck[][13], const char* wFace[], const char* wSuit[])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	
	printf("\n\nPlayer %d cards: \n", current_player);
	if (current_player == 2)
		printf("Player 2's cards have been hidden from you...\n");

	/* deal 5 cards to the player*/
	for (card = 1; card <= 10; card++)
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
					// player 1 recieves these cards
					if (card <= 5 && current_player == 1) 
					{

						// set cards to hand array
						player->hand_array[card-1].face_index = column;
						player->hand_array[card-1].suit_index = row;

						// display player 1's cards
						printf("%5s of %-8s%c",
							wFace[column], wSuit[row],
							card % 2 == 0 ? '\n' : '\t');
						
					} 
					// player 2 recieves these cards
					else if (card > 5 && current_player == 2) 
					{

						// set cards to hand array
						player->hand_array[card-6].face_index = column;
						player->hand_array[card-6].suit_index = row;

					}
				}
			}
		}
	}
}

int get_bet_amount(int player)
{
	int option;
	if (player == 1) {
		printf("\Please pick an option.\t\n1. Call\n2. Raise\n3. Fold\n");
		scanf("%d", &option);

		switch (option) {
			//call
		case 1: printf("\nCall option picked...\n");
			return 100;
			break;
		case 2: printf("\nRaise option picked...\n");
			return 200;
			break;
		case 3: printf("Fold option picked...\n");
			return 0;
		}
	}
	else if (player == 2) {
		option = rand() % 3;

		switch (option) {
			//call
		case 1: printf("\nPlayer 2 picked call option...\n");
			return 100;
			break;
		case 2: printf("\nPlayer 2 picked raise option...\n");
			return 200;
			break;
		case 3: printf("Player 2 picked fold option...\n");
			return 0;
		}
	}

	
	

}

void auto_select_cards(Hand* player, Hand* selection_array, int pair, int three_of_a_kind,
	int four_of_a_kind, int flush, int straight) 
{
	int option = 0, row = 0, col = 0;
	Card current = { 0 , 0 }, selection = { 0 , 0 };

	// determine the best option
	if (straight >= 1) 
	{
		// best option, pursure this first
		option = 6;
	}
	else if (flush >= 1) 
	{
		// second best option
		option = 5;
	}
	else if (four_of_a_kind >= 1) 
	{
		// third best option
		option = 4;
	}
	else if (three_of_a_kind >= 1)
	{
		// fourth best option
		option = 3;
	}
	else if (pair >= 2)
	{
		// double pair, fifth best option
		option = 2;
	}
	else if (pair == 1) 
	{
		// single pair, sixth best option
		option = 1;
	}

}

void select_cards(Hand* player, Hand *selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[])
{
	int option = 0, row = 0, col = 0;
	Card current = { 0 , 0 }, selection = { 0 , 0 };

	for (int i = 0; i < 5; i++) 
	{
		// current card in players hand
		current = player->hand_array[i];

		printf("\nKeep this card? \n%5s of %-8s%c\n1. y\n2. n\n",
			wFace[current.face_index], wSuit[current.suit_index],
			i % 2 == 0 ? '\n' : '\t');

		scanf("%d", &option);
		
		switch (option) {

		// yes
		case 1:

			// matches the position of the orignial hand array
			selection_array->hand_array[i] = current;
			break;
		// no
		case 2:
			selection_array->hand_array[i].face_index = 0;
			selection_array->hand_array[i].suit_index = 0;
			break;
		}
	}
}

void draw_cards(Hand* player, Hand *selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[])
{
	Card selection = { 0,0 }, current = { 0,0 };

	for (int i = 0; i < 5; i++)
	{
		selection = selection_array->hand_array[i];
		current = player->hand_array[i];


		// needs to be drawn from the deck of cards to keep
		// fair circulation of each card. This doesnt do that. - 5 pts
		if (selection.face_index == 0)
		{
			// random generated card, not from the real deck...
			selection_array->hand_array[i].face_index = rand() % 13;
			selection_array->hand_array[i].suit_index = rand() % 4;

			selection = selection_array->hand_array[i];

			player->hand_array[i] = selection;

		}

		printf("%5s of %-8s%c",
			wFace[selection.face_index], wSuit[selection.suit_index],
			i % 2 == 0 ? '\n' : '\t');
	}
	

}

int determine_pair(Hand* player, Hand *selection_array)
{
	int pair = 0;
	Card current = { 0,0 }, next = { 0,0 };
	for (int i = 0; i < 5; i++) {

		

		for (int j = i; j < 4; j++) {
			
			current = player->hand_array[i];
			next = player->hand_array[j+1];

			// detects if any 2 cards are alike
			if (current.face_index == next.face_index) {

				selection_array->hand_array[i] = current;
				selection_array->hand_array[j + 1] = next;
				
				pair++;
			}
		}
	}
	

	if (pair > 1) {
		printf("\nTwo pairs found!\n");
	}
	else if (pair == 1) {
		printf("\nOne pair found!\n");
	}
	else
		printf("\nNo pairs found...\n");

	return pair;
}

int determine_three(Hand* player, Hand* selection_array)
{
	int triple = 0;
	Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 };
	for (int i = 0; i < 5; i++) {

		for (int j = i; j < 4; j++) {

			for (int x = j; x < 3; x++) 
			{
				current = player->hand_array[i];
				next = player->hand_array[j + 1];
				next2 = player->hand_array[x + 2];

				// detects if any 3 cards are alike
				if (current.face_index == next.face_index && current.face_index == next2.face_index) 
				{
					triple++;
				}
			}
		}
	}


	if (triple > 1) {
		printf("\nThree of a kind found!\n");
	}
	else
		printf("\nThree of a kind not found...\n");

	return triple;
}

int determine_four(Hand* player, Hand* selection_array)
{
	int four = 0;
	Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 }, next3 = { 0,0 };
	for (int i = 0; i < 5; i++) {

		for (int j = i; j < 4; j++) {

			for (int x = j; x < 3; x++)
			{
				for (int q = x; q < 2; q++)
				{
					current = player->hand_array[i];
					next = player->hand_array[j + 1];
					next2 = player->hand_array[x + 2];
					next3 = player->hand_array[q + 3];

					// detects if any 4 cards are alike
					if (current.face_index == next.face_index && current.face_index == next2.face_index
						&& current.face_index == next3.face_index) 
					{
						four++;
					}
				}
			}
		}
	}


	if (four > 1) {
		printf("\nFour of a kind found!\n");
	}
	else
		printf("\nFour of a kind not found...\n");

	return four;
}

int determine_flush(Hand* player, Hand* selection_array)
{
	int flush = 0;
	Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 }, next3 = { 0,0 }, next4 = { 0,0 };

	
	
		current = player->hand_array[0];
		next = player->hand_array[1];
		next2 = player->hand_array[2];
		next3 = player->hand_array[3];
		next4 = player->hand_array[4];

		// detects if any 5 cards are alike
		if (current.suit_index == next.suit_index && current.suit_index == next2.suit_index &&
			current.suit_index == next3.suit_index && current.suit_index == next4.suit_index)
		{
				flush++;
		}
	
	if (flush > 1) {
		printf("\nFlush found!\n");
	}
	else
		printf("\nFlush not found...\n");

	return flush;
}

int determine_straight(Hand* player, Hand* selection_array)
{
	
	int straight = 0, temp = 0;
	Card current = { 0,0 }, next = { 0,0 };

	for (int i = 0; i <= 5; i++)
	{
		// checks if the current card is equal to the next card - 1.

		// needs to be in ascending order to function

		// sort array in ascending order
		for (int index = 0; index < 5; index++) {
			for (int index2 = index + 1; index2 < 5; index2++) {

				if (current.face_index > next.face_index) {
					
					temp = current.face_index;
					current.face_index = next.face_index;
					next.face_index = temp;
				}
			}
		}

		if (current.face_index == (next.face_index) - 1)
		{
			straight++;
		}
	}
	
	if (straight > 1) {
		printf("\nStraight found!\n");
	}
	else
		printf("\nStraight not found...\n");

	return straight;
}
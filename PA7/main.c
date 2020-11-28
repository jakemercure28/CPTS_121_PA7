/*
This program is a game of poker (5 card draw)

Programmer: Jake Mercure

Date: 4/29/2020
*/

#include "functions.h"

int main(void) {

	// initialize player hands
	Hand player1, player2, selection_array, selection_array2 = { 0,0,0,0,0 };
	int current_player = 1, current_bet_amount, bet_amount_p1, bet_amount_p2,
		bank_p1 = 500, bank_p2 = 500, menu = 1, win = 2;

	int pair_p1, three_of_a_kind_p1, four_of_a_kind_p1, flush_p1, straight_p1,
		pair_p2, three_of_a_kind_p2, four_of_a_kind_p2, flush_p2, straight_p2;


	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initalize deck array */
	int deck[4][13] = { 0 };

	srand((unsigned)time(NULL)); /* seed random-number generator */

	// initialize deck and shuffle cards
	shuffle(deck);

	// display menu
	display_menu();

	do {
		scanf("%d", &menu);

		if (menu == 3) {
			break;
		}
		else if (menu == 2)
			printf("\nRules:  http://en.wikipedia.org/wiki/5_card_draw");
		// deal to player 1
		deal(&player1, current_player, deck, face, suit);

		// deal to the computer, player 2
		current_player = 2;
		deal(&player2, current_player, deck, face, suit);

		// get bet options from each player (call, raise, fold)
		bet_amount_p2 = get_bet_amount(2);
		bet_amount_p1 = get_bet_amount(1);

		// choose cards to keep, replace with new cards
		select_cards(&player1, &selection_array, deck, face, suit);

		/*

			Determine best scoring option for player 2

		*/

		// find pairs
		printf("\nFinding scores for Player 2\n");
		pair_p2 = determine_pair(&player2, &selection_array2);

		// find three of a kind
		three_of_a_kind_p2 = determine_three(&player2, &selection_array2);

		// find four of a kind
		four_of_a_kind_p2 = determine_four(&player2, &selection_array2);

		// find flush
		flush_p2 = determine_flush(&player2, &selection_array2);

		// find straight
		straight_p2 = determine_straight(&player2, &selection_array2);

		// select best option
		auto_select_cards(&player2, &selection_array2, pair_p2, three_of_a_kind_p2,
			four_of_a_kind_p2, flush_p2, straight_p2);

		// get 2nd bet options from each player
		bet_amount_p2 += get_bet_amount(2);
		bet_amount_p1 += get_bet_amount(1);

		/*


		determine scores for player 1


		*/

		printf("\nFinding scores for Player 1\n");
		// find pairs
		pair_p1 = determine_pair(&player1, deck, face, suit);

		// find three of a kind
		three_of_a_kind_p1 = determine_three(&player1, deck, face, suit);

		// find four of a kind
		four_of_a_kind_p1 = determine_four(&player1, deck, face, suit);

		// find flush
		flush_p1 = determine_flush(&player1, deck, face, suit);

		// find straight
		straight_p1 = determine_straight(&player1, deck, face, suit);

		// draw new cards from the deck
		printf("\nPlayer 1 cards: \n");
		draw_cards(&player1, &selection_array, deck, face, suit);

		printf("\nPlayer 2 cards: \n");
		draw_cards(&player2, &selection_array2, deck, face, suit);

		if (straight_p1 > straight_p2)
			win = 1;
		else if (flush_p1 > flush_p2)
			win = 1;
		else if (four_of_a_kind_p1 > four_of_a_kind_p2)
			win = 1;
		else if (three_of_a_kind_p1 > three_of_a_kind_p2)
			win = 1;
		else if (pair_p1 > pair_p2)
			win = 1;

		printf("Player %d is the winner!!!\n\n", win);
	
		printf("Press any key to play again...\t\t...or press 0 to end game");
		scanf("%d", &menu);

		system("cls");

	
	} while (menu != 0);

	return 0;
}
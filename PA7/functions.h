#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


typedef struct card {

	int face_index;
	int suit_index;

}Card; 

typedef struct hand {

	Card hand_array[5];

}Hand;


void shuffle(int wDeck[][13]);

void deal(Hand *player, int current_player, int wDeck[][13], const char* wFace[], const char* wSuit[]);

void display_menu();

int get_bet_amount(int player);

void select_cards(Hand* player, Hand *selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]);

void auto_select_cards(Hand* player, Hand* selection_array, int pair, int three_of_a_kind,
	int four_of_a_kind, int flush, int straight);

void draw_cards(Hand* player, Hand *selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]);

int determine_pair(Hand* player, Hand* selection_array);

int determine_three(Hand* player, Hand* selection_array);

int determine_four(Hand* player, Hand* selection_array);

int determine_flush(Hand* player, Hand* selection_array);

int determine_straight(Hand* player, Hand* selection_array);
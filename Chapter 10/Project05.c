#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS (13)
#define NUM_SUITS (4)
#define NUM_CARDS (5)

bool flush, four, three;
int straight, pairs;

void read_cards(char num_in_rank[NUM_RANKS],
				char num_in_suit[NUM_SUITS]);
void analyze_hand(char num_in_rank[NUM_RANKS],
				  char num_in_suit[NUM_SUITS]);
void print_result(void);

int main(void)
{
	char num_in_rank[NUM_RANKS];
	char num_in_suit[NUM_SUITS];

	for (;;) {
		read_cards(num_in_rank, num_in_suit);
		analyze_hand(num_in_rank, num_in_suit);
		print_result();
	}

	return 0;
}

void read_cards(char num_in_rank[NUM_RANKS], char num_in_suit[NUM_SUITS])
{
	bool card_exists[NUM_RANKS][NUM_SUITS];
	char ch, rank_ch, suit_ch;
	int rank, suit;
	bool bad_card;
	int cards_read = 0;

	for (rank = 0; rank < NUM_RANKS; rank++) {
		num_in_rank[rank] = 0;
		for (suit = 0; suit < NUM_RANKS; suit++)
			card_exists[rank][suit] = false;
	}

	for (suit = 0; suit < NUM_SUITS; suit++)
		num_in_suit[suit] = 0;

	while (cards_read < NUM_CARDS) {
		bad_card = false;

		printf("Enter a card: ");

		rank_ch = getchar();
		switch (rank_ch) {
		case '0':			exit(EXIT_SUCCESS);
		case '2':			rank = 0; break;
		case '3':			rank = 1; break;
		case '4':			rank = 2; break;
		case '5':			rank = 3; break;
		case '6':			rank = 4; break;
		case '7':			rank = 5; break;
		case '8':			rank = 6; break;
		case '9':			rank = 7; break;
		case 't': case 'T': rank = 8; break;
		case 'j': case 'J': rank = 9; break;
		case 'q': case 'Q': rank = 10; break;
		case 'k': case 'K': rank = 11; break;
		case 'a': case 'A': rank = 12; break;
		default:			bad_card = true;
		}

		suit_ch = getchar();
		switch (suit_ch) {
			case 'c': case 'C': suit = 0; break;
			case 'd': case 'D': suit = 1; break;
			case 'h': case 'H': suit = 2; break;
			case 's': case 'S': suit = 3; break;
			default:			bad_card = true;
		}

		while ( (ch = getchar()) != '\n')
			if (ch != ' ') bad_card = true;

		if (bad_card)
			printf("Bad card; ignored. \n");
		else if (card_exists[rank][suit])
			printf("Duplicate card; ignored. \n");
		else {
			num_in_rank[rank]++;
			num_in_suit[suit]++;
			card_exists[rank][suit] = true;
			cards_read++;
		}
	}
}

void analyze_hand(char num_in_rank[NUM_RANKS], char num_in_suit[NUM_SUITS])
{
	int num_consec = 0;
	int rank, suit, low;

	flush = false;
	four = false;
	three = false;
	straight = pairs = 0;

	for (suit = 0; suit < NUM_SUITS; suit++)
		if (num_in_suit[suit] == NUM_CARDS)
			flush = true;

	rank = 0;
	while (num_in_rank[rank] == 0) rank++;
	for (low = rank; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
		num_consec++;

	if (num_consec == NUM_CARDS) {
		if (num_in_rank[12] > 0)
			straight = 2;	// royal straigh 
		else
			straight = 1;	// straight
		return;
	} else {
		if (num_consec == NUM_CARDS - 1)
			if (num_in_rank[12] > 0 && low == 0)
				straight = -1;	//ace-low straight
	}

	for (rank = 0; rank < NUM_RANKS; rank++) {
		if (num_in_rank[rank] == 4) four = true;
		if (num_in_rank[rank] == 3) three = true;
		if (num_in_rank[rank] == 2) pairs++;
	}
}

void print_result(void)
{
	if (straight != 0 && flush) {
		printf("%s flush", (straight == 2) ? ("royal") : ("straight"));
	}
	else if (four)		   printf("Four of a kind");
	else if (three &&
			 pairs == 1)   printf("Full house");
	else if (flush)        printf("Flush");
	else if (straight)     printf("%sStraight", (straight < 0) ? ("ace-low ") : (""));
	else if (three)        printf("Three of a kind");
	else if (pairs == 2)   printf("Two pairs");
	else if (pairs == 1)   printf("Pairs");
	else                   printf("High card");

	printf("\n\n");
}

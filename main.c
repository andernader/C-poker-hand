#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUM_RANK 13
#define NUM_SUIT 4
#define CARD_IN_HAND 5

int num_in_rank[NUM_RANK];
int num_in_suit[NUM_SUIT];

bool flush, straight, four, three;
int pairs;

void read_card(void);
void analyze_hand(void);
void print_result(void);

int main(void){
    for(;;){
        read_card();
        analyze_hand();
        print_result();
    }
    return 0;
}

/************************************************************************
 * read_card(): 1.Resets the global variables.                          *
 *              2.Read 2 chars representing the input card.             *
 *              3.Checks if the card is an invalid input = bad card.    *
 *                or Duplicated card.                                   *
 *              4.If not it stores the card. up to 5 cards in hand      *
 ************************************************************************/
void read_card(void){
    int rank_index, suit_index;
    bool available_card[NUM_SUIT][NUM_RANK] = {false};
    bool bad_card = false;

    char char_rank, char_suit;
    int num_card = 0;
    //resetting:
    for(int i = 0; i < NUM_RANK; i++)
        num_in_rank[i] = 0;
    for(int i = 0; i < NUM_SUIT; i++)
        num_in_suit[i] = 0;
    ////////////

    while(num_card < CARD_IN_HAND){
        bad_card = false;

        printf("Enter a card: ");
        char_rank = getchar();
        switch(char_rank){
        case '0':           exit(EXIT_SUCCESS);
        case '2':           rank_index = 0; break;
        case '3':           rank_index = 1; break;
        case '4':           rank_index = 2; break;
        case '5':           rank_index = 3; break;
        case '6':           rank_index = 4; break;
        case '7':           rank_index = 5; break;
        case '8':           rank_index = 6; break;
        case '9':           rank_index = 7; break;
        case 't': case 'T': rank_index = 8; break;
        case 'j': case 'J': rank_index = 9; break;
        case 'q': case 'Q': rank_index = 10; break;
        case 'k': case 'K': rank_index = 11; break;
        case 'a': case 'A': rank_index = 12; break;
        default :           bad_card = true; break;
        }

        char_suit = getchar();
        switch(char_suit){
        case 'c': case 'C': suit_index = 0; break;
        case 'd': case 'D': suit_index = 1; break;
        case 'h': case 'H': suit_index = 2; break;
        case 's': case 'S': suit_index = 3; break;
        default :           bad_card = true; break;
        }

        while(getchar() != '\n');

        if(bad_card == true)
            printf("Bad card! ignored\n");
        else if(available_card[suit_index][rank_index] == true)
            printf("Duplicated card! ignored\n");
        else{
            num_in_rank[rank_index]++;
            num_in_suit[suit_index]++;
            available_card[suit_index][rank_index] = true;
            num_card++;
        }
    }
}

/************************************************************************
 * analyze_hand(): 1. Resets Global variables like flush, straight etc..*
 *                 2.analyze whether it is straight, flush etc..        *
 ************************************************************************/
 void analyze_hand(void){
    int rank_temp, suit_temp;
    int card_consec = 0;

    flush = straight = four = three = false;
    pairs = false;


    //Check flush
    suit_temp = 0;
    while(num_in_suit[suit_temp] == 0)suit_temp++;
    if(num_in_suit[suit_temp] == CARD_IN_HAND)
        flush = true;

    //Check straight
    rank_temp = 0;
    while(num_in_rank[rank_temp] == 0)rank_temp++;
    for(; num_in_rank[rank_temp] != 0; rank_temp++)
        card_consec++;
    if(card_consec == CARD_IN_HAND){
        straight = true;
        return;
    }

    //Check four, three and pairs
    for(int i = 0; i < NUM_RANK; i++){
        if(num_in_rank[i] == 4)four = true;
        if(num_in_rank[i] == 3)three = true;
        if(num_in_rank[i] == 2)pairs++;
    }
 }

void print_result(void){
    if(straight && flush) printf("Straight flush");
    else if(four)         printf("Four of a kind");
    else if(three && pairs == 1)printf("Full house");
    else if(flush)        printf("Flush");
    else if(straight)     printf("Straight");
    else if(three)        printf("Three of a kind");
    else if(pairs == 2)   printf("Two pairs");
    else if(pairs == 1)   printf("Pair");
    else                  printf("High card");

    printf("\n\n");
}



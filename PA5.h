/*
Name: Chase Lewis
Date: 10/11/19
Description: Game of Yahtzee
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// prints rules
void print_rules(void);

// displays menu and takes in user option
int menu_select(void);

// actual game function called by main. initializes scorecard lists and loops to call player_turn function 13 times. calls add_up_scorecard function to determine winner
void play_game(void);

// sets random value within 1-6 for die
int roll_die(void);

// loops to call roll_die function 5 times, displaying scorecard and prompting as needed
void roll_dice(int dice[], int scorecard[]);

// display dice so user can decide
void print_dice(int dice[]);

// asks user if they want to keep rolling or not. for use in roll_dice function
char prompt_keep_rolling(int rolls_left);

// updates list of y/n values so that each die is rolled at user's discretion
void which_dice_roll(char roll_die_again[]);

// conducts everthing necessary for a player's turn
void player_turn(int player, int scorecard[]);

// changes array so that the index corresponds to die value, and the integer at that index represents the number of the dice that showed that die value
void convert_dice(int dice[], int indexed_dice[]);

// prints indexed list of dice for debugging
void print_indexded_dice(int indexed_dice[]);

// prints scorecard
void print_scorecard(int scores[]);

// prompts user to choose combo. makes sure it hasnt been used already, unless it is yahtzee
int choose_combo(int scorecard[], int indexed_dice[]);

// case for each of 13 combos. "Sum ofs" call function that sums dice values that match the value entered by user
// other cases have unique algorithm
int check_option(int option, int indexed_dice[]);

// sums dice values that match the value entered by user (if user chose 5, and there are three 5's, returns 15)
int sum_matches(int multiplier, int indexed_dice[]);

// adds all dice values together and returns. used for three of a kind, four of a kind, and chance
int sum_all_dice(int indexed_dice[]);

// checks if any die number is present at least 3 times, and if so, sums all dice
int three_of_a_kind(int indexed_dice[]);

// checks if any die number is present at least 4 times, and if so, sums all dice
int four_of_a_kind(int indexed_dice[]);

// checks if any die number is present 3 times, and if so, checks if a different number is present 2 times. both satisfied is 25 points
int full_house(int indexed_dice[]);

// checks any die number is present 5 times and returns 50 if so
int yahtzee(int indexed_dice[]);

// checks for 5 consecutive die values by looping through 1, 2 and checking for existence of next 4 numbers after each. returns 40 if found
int large_straight(int indexed_dice[]);

// checks for 4 consecutive die values by looping through 1, 2 and 3, and checking for existence of next 3 numbers after each. returns 30 if found
int small_straight(int indexed_dice[]);

// adds up total for scorecard. adds 35 if top half is at least 63
int add_up_scorecard(int scorecard[]);

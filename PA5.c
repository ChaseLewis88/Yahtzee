#include "PA5.h"

// prints rules
void print_rules(void)
{
	printf("Rules:\n\nYou can roll five dice up to three times. You can choose which dice to reroll if any. The goal is to get "
		"certain combinations with the dice."
		"\nThe options are: Sum of 1's, Sum of 2's, Sum of 3's, Sum of 4's, Sum of 5's, Sum of 6's, Three-of-a-kind, "
		"Four-of-a-kind, Full House, Small Straight, Large Straight, Yahtzee, and Chance."
		"\nEach combination is worth points and can only be used once."
		"\nThe \"Sum ofs\" are worth the sum of the dice showing the respective number. Getting at least 63 points in the \"Sum ofs\" grants an extra 35 points."
		"\nA Three-of-a-kind is when at least 3 dice show the same number and is worth the sum of all dice."
		"\nA Four-of-a-kind is when at least 4 dice show the same number and is worth the sum of all di ce."
		"\nA Small Straight is when 4 consecutive values are comprised by the dice values and is worth 30 points."
		"\nA Large Straight is when 5 consecutive values are comprised by the dice values and is worth 40 points."
		"\nA Yahtzee is a five-of-a-kind and is worth 50 points. Yahtzees can be counted multiple times unlike other combinations."
		"\nAdditional Yahtzees are worth 100 points."
		"\nChance is a \"freebie\" slot. It is worth the sum of all dice, no matter what. Use wisely!"
		"\nThere are 13 turns total. The winner is determined at the end."
		"\nThis version of the game can only be played by two players.\n\n");
}

// displays menu and takes in user option
int menu_select(void)
{
	int option = 0;

	printf("Please enter an option:\n\n");
	printf("1. Print Game Rules\n");
	printf("2. Play Game\n");
	printf("3. Exit\n");

	scanf("%d", &option);

	return option;
}

// actual game function called by main. initializes scorecard lists and loops to call player_turn function 13 times. calls add_up_scorecard function to determine winner
void play_game(void)
{
	// initializations
	int player1_total_score = 0, player2_total_score = 0;
	char input_to_return_to_menu = 0;

	// first index is skipped for simplicity and never used. remaining values represent 13 options. each starts at -1, which means not used yet. 
	int player1_scorecard[] = { 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int player2_scorecard[] = { 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

	// calls player_turn function 13 times by looping
	for (int turn = 1; turn < 14; turn++)
	{
		printf("Turn %d\n\n", turn);
		player_turn(1, player1_scorecard);
		player_turn(2, player2_scorecard);
	}
	
	// determines final scores
	player1_total_score = add_up_scorecard(player1_scorecard);
	player2_total_score = add_up_scorecard(player2_scorecard);
	
	// displays scores
	printf("Player 1 finished with %d points.\n", player1_total_score);
	printf("Player 2 finished with %d points.\n\n", player2_total_score);

	// displays outcome
	if (player1_total_score == player2_total_score)
	{
		printf("The players tied!\n");
	}
	if (player1_total_score > player2_total_score)
	{
		printf("Player 1 wins!\n");
	}
	if (player1_total_score < player2_total_score)
	{
		printf("Player 2 wins!\n");
	}
	printf("\nGame Over.\n\n");
	printf("Enter any non-whitespace character to return to menu: \n");
	// scanf value not important, but prompts user to enter key to move on
	scanf(" %c", &input_to_return_to_menu);
}

// sets random value within 1-6 for die
int roll_die(void)
{
	int die = 0;
	die = rand() % 6 + 1;
	return die;
}

// loops to call roll_die function 5 times, displaying scorecard and prompting as needed
void roll_dice(int dice[], int scorecard[])
{
	// initializations
	int rolls = 0, current_die = 0, rolls_left = 3;
	//  index correlated to dice array. for first roll, all dice set to "yes" so that all are rolled
	char roll_die_again[5] = { 'y', 'y', 'y', 'y', 'y' };
	char user_roll_die = 0, keep_rolling = 'y';

	// shows scorecard at beginning of turn
	print_scorecard(scorecard);

	// they can stop rolling early, or use up all 3 rolls
	while (rolls < 3 && keep_rolling == 'y')
	{
		// enter key to move on
		printf("\nEnter any non-whitespace character to roll dice: \n");
		scanf(" %c", &user_roll_die);

		// cleans up and redisplays scorecard
		system("cls");
		print_scorecard(scorecard);
		printf("\n");

		// actuall loop part. loops through dice array and sets 5 values
		for (int i = 0; i < 5; i++)
		{
			// only rolls a die if the user wants
			if (roll_die_again[i] == 'y')
			{
				current_die = i + 1;
				dice[i] = roll_die();
				printf("You roll a %d for die %d.\n", dice[i], current_die);
			}
		}

		// displays dice so user can make decisions
		print_dice(dice);

		// roll update
		rolls++;
		rolls_left--;

		// prompts them to end early if they want
		if (rolls < 3)
		{
			keep_rolling = prompt_keep_rolling(rolls_left);
			if (keep_rolling == 'y')
			{
				// prompts user if die should be rolled again for each invidual die
				which_dice_roll(roll_die_again);
			}
		}
		else
		{
			// no prompt to end early if out of rolls
			printf("\nYou have used all three rolls.\n\n");
		}
	}
}

// display dice so user can decide
void print_dice(int dice[])
{
	int current_die = 0;
	printf("\nDice Results: \n");
	for (int i = 0; i < 5; i++)
	{
		current_die = i + 1;
		printf("Die %d: %d\n", current_die, dice[i]);
	}
}

// asks user if they want to keep rolling or not. for use in roll_dice function
char prompt_keep_rolling(int rolls_left)
{
	char keep_rolling = 0;
	if (rolls_left == 2)
	{
		printf("\nWould you like to keep rolling? You have %d rolls left.\n", rolls_left);
	}
	if (rolls_left == 1)
	{
		printf("\nWould you like to keep rolling? You have %d roll left.\n", rolls_left);
	}
	// input validation
	do {
		printf("Please enter 'y' for 'yes' or 'n' for 'no'.\n");
		scanf(" %c", &keep_rolling);
		if (keep_rolling != 'y' && keep_rolling != 'n')
		{
			printf("That is not an acceptable input.\n\n");
		}
	} while (keep_rolling != 'y' && keep_rolling != 'n');
	return keep_rolling;
}

// updates list of y/n values so that each die is rolled at user's discretion
void which_dice_roll(char roll_die_again[])
{
	int current_die = 0;
	for (int i = 0; i < 5; i++)
	{
		current_die = i + 1;
		printf("\nWould you like to roll die %d again?\n", current_die);
		// input validation
		do {
			printf("Please enter 'y' for 'yes' or 'n' for 'no'.\n");
			scanf(" %c", &roll_die_again[i]);
			if (roll_die_again[i] != 'y' && roll_die_again[i] != 'n')
			{
				printf("That is not an acceptable input.\n");
			}
		} while (roll_die_again[i] != 'y' && roll_die_again[i] != 'n');
	}
}

// conducts everthing necessary for a player's turn
void player_turn(int player, int scorecard[])
{
	int option = 0, score = 0;
	char user_input_to_continue = 0;

	printf("Player %d Start\n\n", player);

	int dice[5], indexed_dice[7] = { 0, 0, 0, 0, 0, 0, 0 };

	// stores 5 random die values in array
	roll_dice(dice, scorecard);

	// changes array so that the index corresponds to die value, and the integer at that index represents the number of the dice that showed that die value
	convert_dice(dice, indexed_dice);

	// prompts user to choose scorecord option. checks that it's not a repeated option
	option = choose_combo(scorecard, indexed_dice);

	// based on option, directs to appropriate functions, which finally return score value. value is 0 if combo conditions were not satisfied
	score = check_option(option, indexed_dice);

	// if yahtzee already rolled, new ones score double (100 points)
	if (option == 12 && scorecard[option] > 0)
	{
		score *= 2;
		scorecard[option] += score;
	}
	// first yahtzee only 50 points
	else
	{
		scorecard[option] = score;
	}
	
	// clears screen and prints scorecard at end of player's turn
	system("cls");
	print_scorecard(scorecard);
	printf("\nEnd of Player %d's turn\n\n", player);
	printf("Enter any non-whitespace character to continue: \n");
	scanf(" %c", &user_input_to_continue);
	system("cls");
}

// changes array so that the index corresponds to die value, and the integer at that index represents the number of the dice that showed that die value
void convert_dice(int dice[], int indexed_dice[])
{
	for (int i = 0; i < 5; i++)
	{
		indexed_dice[dice[i]]++;
	}
}

// prints indexed list of dice for debugging
void print_indexded_dice(int indexed_dice[])
{
	printf("\nIndexed dice: \n\n");
	for (int i = 1; i < 7; i++)
	{
		printf("Number of %d's: %d\n", i, indexed_dice[i]);
	}
}

// prints scorecard
void print_scorecard(int scores[])
{
	// array of scoring combinations for printing based on index
	char scorecard_titles[][24] = { "", "1. Sum of 1's       ", "2. Sum of 2's       ", "3. Sum of 3's       ", "4. Sum of 4's       ", "5. Sum of 5's       ", "6. Sum of 6's       ", 
		"7. Three-of-a-kind  ", "8. Four-of-a-kind   ", "9. Full House       ", "10. Small straight  ", "11. Large straight  ", "12. Yahtzee         ", "13. Chance          " };

	printf("Current scorecard: \n\n");
	// cool top visual
	printf(" ___________________________\n");
	for (int i = 1; i < 14; i++)
	{
		// prints whitespace only if the value is -1. this means the combo hasnt been used yet.
		if (scores[i] == -1)
		{
			printf("| %s:     |\n", scorecard_titles[i]);
		}
		// prints differently based on number of digits so it looks better. "|" character is used for sides of visual scorecard
		else if (scores[i] < 10)
		{
			printf("| %s: %d   |\n", scorecard_titles[i], scores[i]);
		}
		else if (scores[i] < 100)
		{
			printf("| %s: %d  |\n", scorecard_titles[i], scores[i]);
		}
		else
		{
			printf("| %s: %d |\n", scorecard_titles[i], scores[i]);
		}
	}
	// cool bottom visual
	printf("|___________________________|\n");
}

// prompts user to choose combo. makes sure it hasnt been used already, unless it is yahtzee
int choose_combo(int scorecard[], int indexed_dice[])
{
	int option = 0, is_yahtzee = 0;
	printf("\nChoose one of the scorecard options above by entering in the number associated with it. If you do not have the necessary combination, then you will scratch. "
		"You may not choose an option that is already filled. You may choose Yahtzee multilple times if it is not scratched.\n");
	// do-while for input validation
	do {
		// do-while for input validation
		do {
			scanf("%d", &option);
			if (option < 1 || option > 13)
			{
				printf("You must enter a value within 1 and 13.\n");
			}
			// checks that value is within 1-13
		} while (option < 1 || option > 13);

		// if option is 12 (yahtzee) and is already scratched, returns to outer loop. if you had a yatzee already and try to scratch, returns to outer loop. finishes loop otherwise
		if (option == 12)
		{
			if (scorecard[option] == 0)
			{
				printf("You have already filled this part of the scorecard. Please choose a different option.\n");
			}
			if (scorecard[option] > 0)
			{
				is_yahtzee = yahtzee(indexed_dice);
				if (is_yahtzee != 50)
				{
					printf("You don't have a Yahtzee, and you can't scratch Yahtzee since you already have had a Yahtzee.\n");
				}
			}
		}
		// selected combo is not yahtzee, so can't be used more than once. if the value is greater than -1, then it has already been used, so returns to outer loop 
		else
		{
			if (scorecard[option] > -1)
			{
				printf("You have already filled this part of the scorecard. Please choose a different option.\n");
			}
		}
	} while ((option == 12 && (scorecard[option] == 0) || (scorecard[option] > 0 && is_yahtzee != 50)) || (option != 12 && scorecard[option] > -1));
	return option;
}

// case for each of 13 combos. "Sum ofs" call function that sums dice values that match the value entered by user
// other cases have unique algorithm
int check_option(int option, int indexed_dice[])
{
int score = 0;
switch (option)
{
case 1:
	score = sum_matches(option, indexed_dice);
	break;
case 2:
	score = sum_matches(option, indexed_dice);
	break;
case 3:
	score = sum_matches(option, indexed_dice);
	break;
case 4:
	score = sum_matches(option, indexed_dice);
	break;
case 5:
	score = sum_matches(option, indexed_dice);
	break;
case 6:
	score = sum_matches(option, indexed_dice);
	break;
case 7:
	score = three_of_a_kind(indexed_dice);
	break;
case 8:
	score = four_of_a_kind(indexed_dice);
	break;
case 9:
	score = full_house(indexed_dice);
	break;
case 10:
	score = small_straight(indexed_dice);
	break;
case 11:
	score = large_straight(indexed_dice);
	break;
case 12:
	score = yahtzee(indexed_dice);
	break;
case 13:
	score = sum_all_dice(indexed_dice);
	break;
}
return score;
}

// sums dice values that match the value entered by user (if user chose 5, and there are three 5's, returns 15)
int sum_matches(int multiplier, int indexed_dice[])
{
	int score = 0;
	score = indexed_dice[multiplier] * multiplier;
	return score;
}

// adds all dice values together and returns. used for three of a kind, four of a kind, and chance
int sum_all_dice(int indexed_dice[])
{
	int score = 0;
	for (int i = 0; i < 7; i++)
	{
		score += indexed_dice[i] * i;
	}
	return score;
}

// checks if any die number is present at least 3 times, and if so, sums all dice
int three_of_a_kind(int indexed_dice[])
{
	int score = 0;
	for (int i = 0; i < 7; i++)
	{
		if (indexed_dice[i] >= 3)
		{
			score = sum_all_dice(indexed_dice);
		}
	}
	return score;
}

// checks if any die number is present at least 4 times, and if so, sums all dice
int four_of_a_kind(int indexed_dice[])
{
	int score = 0;
	for (int i = 0; i < 7; i++)
	{
		if (indexed_dice[i] >= 4)
		{
			score = sum_all_dice(indexed_dice);
		}
	}
	return score;
}

// checks if any die number is present 3 times, and if so, checks if a different number is present 2 times. both satisfied is 25 points
int full_house(int indexed_dice[])
{
	int score = 0;
	for (int i = 1; i < 7; i++)
	{
		if (indexed_dice[i] == 3)
		{
			for (int j = 1; j < 7; j++)
			{
				if (indexed_dice[j] == 2)
				{
					score = 25;
				}
			}
		}
	}
	return score;
}

// checks any die number is present 5 times and returns 50 if so
int yahtzee(int indexed_dice[])
{
	int score = 0;
	for (int i = 1; i < 7; i++)
	{
		if (indexed_dice[i] == 5)
		{
			score = 50;
		}
	}
	return score;
}

// checks for 5 consecutive die values by looping through 1, 2 and checking for existence of next 4 numbers after each. returns 40 if found
int large_straight(int indexed_dice[])
{
	int score = 0;
	for (int i = 1; i < 3; i++)
	{
		if (indexed_dice[i] == 1 && indexed_dice[i + 1] == 1 && indexed_dice[i + 2] == 1 && indexed_dice[i + 3] == 1 && indexed_dice[i + 4] == 1)
		{
			score = 40;
		}
	}
	return score;
}

// checks for 4 consecutive die values by looping through 1, 2 and 3, and checking for existence of next 3 numbers after each. returns 30 if found
int small_straight(int indexed_dice[])
{
	int score = 0;
	for (int i = 1; i < 4; i++)
	{
		if (indexed_dice[i] > 0 && indexed_dice[i + 1] > 0 && indexed_dice[i + 2] > 0 && indexed_dice[i + 3] > 0 )
		{
			score = 30;
		}
	}
	return score;
}

// adds up total for scorecard. adds 35 if top half is at least 63
int add_up_scorecard(int scorecard[])
{
	int total_score = 0, check_63_sum = 0;
	for (int i = 1; i < 14; i++)
	{
		if (scorecard[i] > -1)
		{
			if (i < 7)
			{
				check_63_sum += scorecard[i];
			}
			total_score += scorecard[i];
		}
	}
	if (check_63_sum >= 63)
	{
		total_score += 35;
	}
	return total_score;
}
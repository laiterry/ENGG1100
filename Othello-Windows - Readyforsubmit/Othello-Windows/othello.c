/**
* ENGG1110 Problem Solving by Programming
*
* Course Project (Baseline OR Bonus implementation)
*
* I declare that the assignment here submitted is original
* except for source material explicitly acknowledged,
* and that the same or closely related material has not been
* previously submitted for another course.
* I also acknowledge that I am aware of University policy and
* regulations on honesty in academic work, and of the disciplinary
* guidelines and procedures applicable to breaches of such
* policy and regulations, as contained in the website.

*
* University Guideline on Academic Honesty:
* http://www.cuhk.edu.hk/policy/academichonesty/
* Faculty of Engineering Guidelines to Academic Honesty:
* http://star.erg.cuhk.edu.hk/upload/ENGG_Discipline.pdf
*
* Student Name :LAI JINTAO
* Student ID : 1155043805
* Class/Section: L
* Date : April 17
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//#define FILENAME  "G:\\Dropbox_Work\\Dropbox\\2015Term2\\ENGG1110\\Project\\Othello-Windows\\Debug\\board.txt"
#define FILENAME  ".\\board.txt"
////////////////// function:           print_board //////////////////

#define BONUS 0


//functions
int can_flip_opponent(int board[8][8], int row, int column, int current_player);
void print_board(int board[8][8], int current_player);
void print_game_details(int board[8][8], int current_player);
int need_pass(int board[8][8], int current_player);
int is_end_game(int board[8][8]);
int is_wrong_input_range(int row, int column);
int is_empty_cell(int board[8][8], int row, int column);
int can_flip_opponent(int board[8][8], int row, int column, int current_player);
void flip_opponent(int board[8][8], int row, int column, int current_player);
void print_winner(int board[8][8]);
void SaveBoard(int board[8][8], int save_board[64][8][8], int round);
void RollBack(int board[8][8], int save_board[64][8][8], int  round);




int main(int argc, char **argv) {
	int current_player = 1;  // current_player can be 1 or 2;
	int board[8][8];           // store the current game board
	int save_board[64][8][8];           // store the current game board
	int round = 0;
	int row, column, mode, stop, all_test_pass;

	printf("Select Mode: [1. Normal Mode | 2. Debug Mode] ?\n");
	scanf("%d", &mode);

	//system("cls");
	/*
	Do your work below:

	mode == 1: normal mode
	mode == 2: debug mode

	So, please initialize the board variable accordingly.
	*/

	if (mode == 1) {
		/*
		Initialize the board as instructed in
		P.3 of the specification.
		*/

		int i = 0, j = 0;
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				board[i][j] = 0;
			}
		}
		board[3][4] = 1;
		board[4][3] = 1;
		board[3][3] = 2;
		board[4][4] = 2;
	}
	else if (mode == 2) {
		/*
		Initialize the board based on the
		input file format as described in
		P.7 of the specification.
		*/
		int i = 0, j = 0;
		FILE *fptr;
		int num;
		fptr = fopen(FILENAME, "r"); // open file

		if (fptr == NULL) {
			printf("Cannot open file!\n");
			printf("\r\n");system("Pause");
			return 0;
		}

		while (1) {
			if (fscanf(fptr, "%d", &num) != 1)
				break;

			// Process num here
			board[i][j] = num;
			j++;
			if (j == 8)
			{
				j = 0;
				i++;
			}
		}
		fclose(fptr); // close file
	}


	stop = 0;

	while (stop == 0) { // the big game loop begins

		printf("\r\n\r\n<<<< Round %d >>>>\r\n\r\n", round+1);
		print_board(board, current_player);
		print_game_details(board, current_player);


		
		SaveBoard(board, save_board, round); 
		round++;

		if (is_end_game(board) == 1) {
			stop = 1;
			break;
		}

		if (need_pass(board, current_player) == 1) {
			printf("You have to pass this turn\n");
			printf("\r\n");
		//	system("Pause");
		}
		else {
			/*
			Inside the else body, you have several things to do.

			- Read input.

			- Check if "row" & "column" are in the wrong input range
			[ Case 1, table in P.10 of specification ]

			- If "row" & "column" are in the correct input range,
			check if (row, column) points to an empty cell
			[ Case 2, table in P.10 of specification ]

			- If (row, column) points to an empty cell,
			check if the new disc in (row, column) can flip any
			opponent's discs
			[ Case 3, table in P.10 of specification ]


			When (row, column) passes all the above three tests,
			flip the opponent's discs
			*/



			do {
				printf("\r\n");
				all_test_pass = 1;

				if (BONUS)
				{
					printf("Row[0-7]    (Undo:-1): ");
				}
				else
				{
					printf("Row: [0-7]: ");
				}
				

				scanf("%d", &row);

				if (BONUS)
				{
					if (row == -1)
					{
						if (round >= 2)
						{
							round = round - 2;
							RollBack(board, save_board, round);

						}
						else
						{
							printf("already back to the beginning\r\n");
							round--;

							if (current_player == 1)
								current_player = 2;
							else
								current_player = 1;

							printf("\r\n"); system("pause");
						}
						break;
					}
				}
			
				if (BONUS)
				{
					printf("Column[0-7] (Undo:-1): ");
				}
				else
				{
					printf("Column: [0-7]: ");
				}
			
				

				scanf("%d", &column);
				if (BONUS)
				{
					if (column == -1)
					{
						if (round >= 2)
						{
							round = round - 2;
							RollBack(board, save_board, round);
						}
						else
						{
							printf("Already back to the beginning\r\n");
							if (current_player == 1)
								current_player = 2;
							else
								current_player = 1;

							printf("\r\n"); system("Pause");
						}
						break;
					}
				}


				if (is_wrong_input_range(row, column) == 1) {
					printf("Wrong input range\n");
					all_test_pass = 0;
				}
				else if (is_empty_cell(board, row, column) == 0) {
					printf("Invalid location(not empty): (%d,%d) \n", row, column);
					all_test_pass = 0;
				}
				else if (can_flip_opponent(board, row, column, current_player) == 0) {
					printf("Invalid location(can not flip): (%d,%d) \n", row, column);
					all_test_pass = 0;
				}

				if (all_test_pass == 1) {
					flip_opponent(board, row, column, current_player);
				}

			} while (all_test_pass == 0);

		} // end of else body //

		/*
		Important!!!!!!!!!!

		You must change the current player before
		going back to the start of the big game loop.

		Add the code below!
		*/

		if (current_player == 1)
			current_player = 2;
		else
			current_player = 1;

		
	}  // the big game loop ends

	printf("\r\n<<<< Quit loop; print board and show the winner >>>>\r\n\r\n"); 
	print_board(board, current_player);
	print_winner(board);
	printf("\r\n");
	system("Pause");

	return 0;
}



//done
void print_board(int board[8][8], int current_player) {
	/*
	Purpose: print the board using the layout
	described in P.7 of the specification

	No return value.
	*/


	//system("cls");




	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	int i = 0, j = 0;



	printf("    0   1   2   3   4   5   6   7\r\n");
	for (i = 0; i < 8; i++)
	{
		printf("  +---+---+---+---+---+---+---+---+\r\n");
		printf("%d ", i);
		for (j = 0; j < 8; j++)
		{
			printf("|");
			switch (board[i][j])
			{
			case 0:
				if (BONUS)
				{
					if (can_flip_opponent(board, i, j, current_player) == 1)
					{
						if (current_player == 1)
							SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_BLUE);//设置为蓝色
						else
							SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED);//设置为绿色
					}

				}


				printf("   ");

				if (BONUS)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}

				break;

			case 1:
				if (BONUS)
				{
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//设置为蓝色
					printf("O●");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				else
				{
					printf(" O ");
				}




				break;

			case 2:
				if (BONUS)
				{
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//设置为绿色
					printf("#▆");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				else
				{
					printf(" # ");
				}


				break;
			}

		}
		printf("|\r\n");
	}

	printf("  +---+---+---+---+---+---+---+---+\r\n");



}

////////////////// function:    print_game_details //////////////////


//done
void print_game_details(int board[8][8], int current_player) {
	/*
	Purpose: print the game details as described in
	P.9 of the specification

	No return value.
	*/
	int i = 0, j = 0, player_1 = 0, player_2 = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			switch (board[i][j])
			{
			case 0:
				break;

			case 1:
				player_1++;
				break;

			case 2:
				player_2++;
				break;
			}

		}
	}

	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);


	if (BONUS)
	{
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_BLUE);//设置为蓝色
		printf("Player O : %d", player_1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("\t\t");

		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_RED);//设置为绿色
		printf("Player #: %d\r\n", player_2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		printf("Current Turn : ");


		if (current_player == 1)
		{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//设置为蓝色
			printf("O●");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//设置为绿色
			printf("#▆");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		}
	}
	else
	{
		printf("Player O : %d", player_1);
		printf("\t\t");
		printf("Player #: %d\r\n", player_2);
		printf("Current Turn : ");
		if (current_player == 1)
		{
			printf("O");
		}
		else
		{
			printf("#");

		}
	}



	printf("\r\n");

}

////////////////// function:             need_pass //////////////////

int need_pass(int board[8][8], int current_player) {
	/*
	Purpose: to determine if current_player can find at least one cell
	to place a new disc

	Return value:
	0: can find at least one cell.
	1: cannot find any cell.
	*/


	int result = 1;

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (board[row][col] == 0 && can_flip_opponent(board, row, col, current_player) == 1)
			{
				result = 0;
				break;
			}

		}

	}


	return result;
}


////////////////// function:          is_end_game //////////////////

int is_end_game(int board[8][8]) {
	/*
	Purpose: to determine if the game has been ended or not

	Return value:
	0: false, i.e., the game is not ended.
	1: true,  i.e., the game is ended.
	*/
	int result = 0;

	int full = 1;

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (board[row][col] == 0)
			{
				full = 0;
				break;
			}

		}

	}


	int both_need_pass = 0;
	if (need_pass(board, 1) && need_pass(board, 2))
		both_need_pass = 1;


	if (full || both_need_pass)
	{
		result = 1;
	}

	return result;
}

////////////////// function: is_wrong_input_range //////////////////


//done
int is_wrong_input_range(int row, int column) {
	/*
	Purpose: to determine if the input is in the wrong range

	Return value:
	0: no,  i.e., correct input.
	1: yes, i.e., wrong input.
	*/

	if (row < 0 || row > 7 || column < 0 || column > 7)
		return 1;
	else
		return 0;


}

////////////////// function:        is_empty_cell //////////////////


//done
int is_empty_cell(int board[8][8], int row, int column) {
	/*
	Purpose: to determine if (row, column) refers to an empty cell

	Return value:
	0: no,  i.e., not empty.
	1: yes, i.e., empty.
	*/
	if (board[row][column] != 0)
		return 0;
	else
		return 1;

}

////////////////// function:    can_flip_opponent //////////////////

//done
int can_flip_opponent(int board[8][8], int row, int column, int current_player) {
	/*
	Purpose: to determine the new disc in (row, column)
	can flip any opponent's discs

	Return value:
	0: no,  i.e., cannot flip.
	1: yes, i.e., can flip.
	*/


	int can_flip = 0;
	int cp_disc_position;


	// up
	cp_disc_position = -1;
	for (int r = row - 1; r >= 0 && board[r][column] != 0 && cp_disc_position == -1; r--)
	{
		if (board[r][column] == current_player)
			cp_disc_position = r;
	}

	if (cp_disc_position != -1 && cp_disc_position < row - 1)
	{
		can_flip = 1;
		return can_flip;
	}

	//down
	cp_disc_position = -1;
	for (int r = row + 1; r < 8 && board[r][column] != 0 && cp_disc_position == -1; r++)
	{
		if (board[r][column] == current_player)
			cp_disc_position = r;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (cp_disc_position != -1 && cp_disc_position > row + 1)
	{
		can_flip = 1;
		return can_flip;
	}


	// right 
	cp_disc_position = -1;
	for (int c = column + 1; c < 8 && board[row][c] != 0 && cp_disc_position == -1; c++)
	{
		if (board[row][c] == current_player)
			cp_disc_position = c;
	}

	if (cp_disc_position != -1 && cp_disc_position > column + 1)
	{
		can_flip = 1;
		return can_flip;
	}

	// left
	cp_disc_position = -1;
	for (int c = column - 1; c >= 0 && board[row][c] != 0 && cp_disc_position == -1; c--)
	{
		if (board[row][c] == current_player)
			cp_disc_position = c;
	}

	if (cp_disc_position != -1 && cp_disc_position < column - 1)
	{
		can_flip = 1;
		return can_flip;
	}


	// up-left
	cp_disc_position = -1;
	int c = column - 1;
	for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != 0 && cp_disc_position == -1; r--)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c--;
	}

	if (cp_disc_position != -1 && cp_disc_position < row - 1)
	{
		can_flip = 1;
		return can_flip;
	}

	//  up-right 
	cp_disc_position = -1;
	c = column + 1;
	for (int r = row - 1; c < 8 && r >= 0 && board[r][c] != 0 && cp_disc_position == -1; r--)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c++;
	}

	if (cp_disc_position != -1 && cp_disc_position < row - 1)
	{
		can_flip = 1;
		return can_flip;
	}

	//  down-left 
	cp_disc_position = -1;
	c = column - 1;
	for (int r = row + 1; c >= 0 && r < 8 && board[r][c] != 0 && cp_disc_position == -1; r++)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c--;
	}

	if (cp_disc_position != -1 && cp_disc_position > row + 1)
	{
		can_flip = 1;
		return can_flip;
	}

	// down-right
	cp_disc_position = -1;
	c = column + 1;
	for (int r = row + 1; c < 8 && r < 8 && board[r][c] != 0 && cp_disc_position == -1; r++)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c++;
	}

	if (cp_disc_position != -1 && cp_disc_position > row + 1)
	{
		can_flip = 1;
		return can_flip;
	}

	return can_flip;
}

////////////////// function:        flip_opponent //////////////////

//done
void flip_opponent(int board[8][8], int row, int column, int current_player) {
	/*
	Purpose: using a new disc in (row, column) to flip opponent's disc

	Because "board" is an array, update it in this function
	will also change the variable in the main function.

	No return value.
	*/

	board[row][column] = current_player;
	int cp_disc_position;

	// up
	cp_disc_position = -1;
	for (int r = row - 1; r >= 0 && board[r][column] != 0 && cp_disc_position == -1; r--)
	{
		if (board[r][column] == current_player)
			cp_disc_position = r;
	}

	if (cp_disc_position != -1 && cp_disc_position < row - 1)
	{
		// Flip discs above
		for (int r = row - 1; r > cp_disc_position; r--)
		{
			board[r][column] = current_player;
		}
	}

	//down
	cp_disc_position = -1;
	for (int r = row + 1; r < 8 && board[r][column] != 0 && cp_disc_position == -1; r++)
	{
		if (board[r][column] == current_player)
			cp_disc_position = r;
	}

	if (cp_disc_position != -1 && cp_disc_position > row + 1)
	{
		// Flip discs below
		for (int r = row + 1; r < cp_disc_position; r++)
		{
			board[r][column] = current_player;
		}
	}


	// right 
	cp_disc_position = -1;
	for (int c = column + 1; c < 8 && board[row][c] != 0 && cp_disc_position == -1; c++)
	{
		if (board[row][c] == current_player)
			cp_disc_position = c;
	}

	if (cp_disc_position != -1 && cp_disc_position > column + 1)
	{
		// Flip discs to the right
		for (int c = column + 1; c < cp_disc_position; c++)
		{
			board[row][c] = current_player;
		}

	}

	// left
	cp_disc_position = -1;
	for (int c = column - 1; c >= 0 && board[row][c] != 0 && cp_disc_position == -1; c--)
	{
		if (board[row][c] == current_player)
			cp_disc_position = c;
	}

	if (cp_disc_position != -1 && cp_disc_position < column - 1)
	{
		// Flip discs to the left
		for (int c = column - 1; c > cp_disc_position; c--)
		{
			board[row][c] = current_player;
		}
	}


	// up-left
	cp_disc_position = -1;
	int c = column - 1;
	for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != 0 && cp_disc_position == -1; r--)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c--;
	}

	if (cp_disc_position != -1 && cp_disc_position < row - 1)
	{
		c = column - 1;
		for (int r = row - 1; r > cp_disc_position; r--)
		{
			board[r][c] = current_player;
			c--;
		}
	}

	//  up-right 
	cp_disc_position = -1;
	c = column + 1;
	for (int r = row - 1; c < 8 && r >= 0 && board[r][c] != 0 && cp_disc_position == -1; r--)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c++;
	}

	if (cp_disc_position != -1 && cp_disc_position < row - 1)
	{
		c = column + 1;
		for (int r = row - 1; r > cp_disc_position; r--)
		{
			board[r][c] = current_player;
			c++;
		}
	}

	//  down-left 
	cp_disc_position = -1;
	c = column - 1;
	for (int r = row + 1; c >= 0 && r < 8 && board[r][c] != 0 && cp_disc_position == -1; r++)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c--;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (cp_disc_position != -1 && cp_disc_position > row + 1)
	{
		c = column - 1;
		for (int r = row + 1; r < cp_disc_position; r++)
		{
			board[r][c] = current_player;
			c--;
		}
	}

	// down-right
	cp_disc_position = -1;
	c = column + 1;
	for (int r = row + 1; c < 8 && r < 8 && board[r][c] != 0 && cp_disc_position == -1; r++)
	{
		if (board[r][c] == current_player)
			cp_disc_position = r;
		c++;
	}

	if (cp_disc_position != -1 && cp_disc_position > row + 1)
	{
		c = column + 1;
		for (int r = row + 1; r < cp_disc_position; r++)
		{
			board[r][c] = current_player;
			c++;
		}
	}

}

////////////////// function:         print_winner //////////////////

void print_winner(int board[8][8]) {
	/*
	Purpose:
	- print number of 'O' in the board;
	- print number of '#' in the board;
	- print who the winner is / draw grame
	*/

	int i = 0, j = 0, player_1 = 0, player_2 = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			switch (board[i][j])
			{
			case 0:
				break;

			case 1:
				player_1++;
				break;

			case 2:
				player_2++;
				break;
			}

		}
	}

	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (BONUS)
	{
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_BLUE);//设置为蓝色
		printf("Player O : %d", player_1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		printf("\t\t");

		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_RED);//设置为绿色
		printf("Player # : %d\r\n", player_2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else
	{
		printf("Player O: %d", player_1);
		printf("\t\t");
		printf("Player #: %d\r\n", player_2);
	}







	int winner = 0;
	if (player_1 != player_2)
	{
		if (player_1 > player_2)
			winner = 1;
		else
			winner = 2;

		printf("Winner : ");
		HANDLE handle;
		handle = GetStdHandle(STD_OUTPUT_HANDLE);

		if (BONUS)
		{
			if (winner == 1)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//设置为蓝色
				printf("Player O!");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else
			{
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//设置为绿色
				printf("Player #!");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			}
		}
		else
		{
			if (winner == 1)
			{
				printf("Player O!");
			}
			else
			{
				printf("Player #!");

			}
		}





	}
	else
		printf("Draw Game!");


	printf("\r\n");
}

///////////////// Main /////////////////

void SaveBoard(int board[8][8], int save_board[64][8][8], int round)
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			save_board[round][i][j] = board[i][j];
	}
}


void RollBack(int board[8][8], int save_board[64][8][8], int  round)
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			board[i][j] = save_board[round][i][j];
	}
}


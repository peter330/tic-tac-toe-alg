#include<bits/stdc++.h> 
using namespace std; 

struct Move 
{ 
	int row, col; 
}; 

char player = 'x', opponent = 'o'; 

 bool isMovesLeft(char board[3][3])
{ 
	for (int i = 0; i<3; i++) 
		for (int j = 0; j<3; j++) 
			if (board[i][j]=='_') 
				return true; 
	return false; 
} 

int evaluate(char b[3][3])
{ 
	// Checking for Rows for X or O victory. 
	for (int row = 0; row<3; row++) 
	{ 
		if (b[row][0]==b[row][1] && 
			b[row][1]==b[row][2]) 
		{ 
			if (b[row][0]==player) 
				return +10; 
			else if (b[row][0]==opponent) 
				return -10; 
		} 
	} 

	// Checking for Columns for X or O victory. 
	for (int col = 0; col<3; col++) 
	{ 
		if (b[0][col]==b[1][col] && 
			b[1][col]==b[2][col]) 
		{ 
			if (b[0][col]==player) 
				return +10; 

			else if (b[0][col]==opponent) 
				return -10; 
		} 
	} 

	// Checking for Diagonals for X or O victory. 
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
	{ 
		if (b[0][0]==player) 
			return +10; 
		else if (b[0][0]==opponent) 
			return -10; 
	} 

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
	{ 
		if (b[0][2]==player) 
			return +10; 
		else if (b[0][2]==opponent) 
			return -10; 
	} 

	// Else if none of them have won then return 0 
	return 0; 
} 

int minimax(char board[3][3], int depth, int alpha, int beta, bool isMax)
{ 
	int score = evaluate(board); 

	// If Maximizer has won the game return his/her 
	// evaluated score 
	if (score == 10) 
		return score; 

	// If Minimizer has won the game return his/her 
	// evaluated score 
	if (score == -10) 
		return score; 

	// If there are no more moves and no winner then 
	// it is a tie 
	if (!isMovesLeft(board))
		return 0; 

	// If this maximizer's move 
	if (isMax) 
	{ 
		int best = -1000; 

		// Traverse all cells 
		for (int i = 0; i<3; i++) 
		{ 
			for (int j = 0; j<3; j++) 
			{ 
				// Check if cell is empty 
				if (board[i][j]=='_') 
				{ 
					// Make the move 
					board[i][j] = player; 

					// Call minimax recursively and choose 
					// the maximum value 
					best = max(best, minimax(board, depth+1, alpha, beta, !isMax)); 
					alpha = max(alpha, best);

					// Undo the move 
					board[i][j] = '_'; 

					// Alpha Beta Pruning 
					if (beta <= alpha)
						break;
				} 
			} 
		} 
		return best; 
	} 

	// If this minimizer's move 
	else
	{ 
		int best = 1000; 

		// Traverse all cells 
		for (int i = 0; i<3; i++) 
		{ 
			for (int j = 0; j<3; j++) 
			{ 
				// Check if cell is empty 
				if (board[i][j]=='_') 
				{ 
					// Make the move 
					board[i][j] = opponent; 

					// Call minimax recursively and choose 
					// the minimum value 
					best = min(best, minimax(board, depth+1, alpha, beta, !isMax)); 
					beta = min(beta, best);

					// Undo the move 
					board[i][j] = '_'; 

					// Alpha Beta Pruning 
					if (beta <= alpha)
						break;
				} 
			} 
		} 
		return best; 
	} 
} 

Move findBestMove(char board[3][3])
{ 
	int bestVal = -1000; 
	Move bestMove{};
	bestMove.row = -1; 
	bestMove.col = -1; 

	// Traverse all cells, evaluate minimax function for 
	// all empty cells. And return the cell with optimal 
	// value. 
	for (int i = 0; i<3; i++) 
	{ 
		for (int j = 0; j<3; j++) 
		{ 
			// Check if cell is empty 
			if (board[i][j]=='_') 
			{ 
				// Make the move 
				board[i][j] = player; 

				// compute evaluation function for this 
				// move. 
				int moveVal = minimax(board, 0, -1000, 1000, false); 

				// Undo the move 
				board[i][j] = '_'; 

				// If the value of the current move is 
				// more than the best value, then update 
				// best/ 
				if (moveVal > bestVal) 
				{ 
					bestMove.row = i; 
					bestMove.col = j; 
					bestVal = moveVal; 
				} 
			} 
		} 
	} 

	printf("The value of the best Move is : %d\n\n", 
			bestVal); 

	return bestMove; 
} 

int main()
{
    clock_t start, end;

    /* Recording the starting clock tick.*/
    start = clock();



    char board[3][3] =
            {
                    { '_', 'o', 'x' },
                    { 'o', 'x', '_' },
                    { 'o', '_', '_' }
            };

    Move bestMove = findBestMove(board);

    printf("The Optimal Move is :\n");
    printf("ROW: %d COL: %d\n\n", bestMove.row,
           bestMove.col );
    // Recording the end clock tick.
    end = clock();

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
} 
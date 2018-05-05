// *******************************************
//      MAIN ENTRYPOINT FOR APPLICATION
// *******************************************

#include "CTicTacToe.h"

// Program entry point
int main()
{
	// The game brain
	CTicTacToe tttGame;

	// Start a new game
	tttGame.NewGame();

	// Winning sequence location
	std::vector<int> winRows;
	std::vector<int> winCols;

	// Game over
	std::cout << std::endl << ".............. BEGIN GAME .............." << std::endl;

	// Loop variables
	MARKER_TYPE marker = X_MARKER;
	int row = -1, col = -1;

	// Play until game over
	do
	{
		// Make best move for current marker
		tttGame.GetBestMove(marker, row, col);
		tttGame.SetMark(row, col, marker);

		// Change sides
		if (marker == X_MARKER)
			marker = O_MARKER;
		else
			marker = X_MARKER;

		// Print board
		std::cout << std::endl << "Turn #" << tttGame.GetTurnCount() << std::endl;
		tttGame.PrintBoard(winRows, winCols);
		std::cout << std::endl;
	}
	while (!tttGame.IsGameOver(winRows, winCols));

	// Game over
	std::cout << ".............. GAME OVER .............." << std::endl;

	// Indicate winner
	if (winRows.size() > 0)
	{
		// Print winner info.
		MARKER_TYPE winMark = tttGame.GetMark(winRows[0], winCols[0]);
		std::cout << "Winner: " << tttGame.markerName[winMark] << std::endl;
		tttGame.PrintBoard(winRows, winCols);
		std::cout << std::endl;
	}
}


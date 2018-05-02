#ifdef THIS_FILE
#undef THIS_FILE
#endif
#define THIS_FILE "TicTacToeV8.cpp"

#include <nan.h>
#include "CTicTacToe.h"

// The game brain
CTicTacToe tttGame;

// ********************************************************************
//   Javascript interface
// ********************************************************************

// *** NewGame()
// *** IsGameOver()
// *** DoTurn()
// *** DoAiTurn()
// *** IsGameOver()

class CTicTacToe
{
public:
	// Start a new game
	void NewGame(void);

	// Get current marker at specified cell
	MARKER_TYPE GetMark(int row, int col);

	// Set specified cell to specified marker (returns FALSE if cell was already marked)
	bool SetMark(int row, int col, MARKER_TYPE marker);

	// Choose best move for specified marker
	void GetBestMove(MARKER_TYPE marker, int &row, int &col);

	// Check for game over (returns winning row if applicable)
	bool IsGameOver(std::vector<int> &rows, std::vector<int> &cols);

	// Get number of turns that have been played
	int GetTurnCount(void);

	// Undo turn
	void UndoTurn(void);

	// Print the current board state
	void PrintBoard(std::vector<int> &winRows, std::vector<int> &winCols);

	// Marker names for printing
	static std::string const markerName[];
	static std::string const winnerName[];
}



// Init the TicTacToe Engine
NAN_METHOD(Startup)
{
	// Start a new game
	tttGame.NewGame();

	// Winning sequence location
	std::vector<int> winRows;
	std::vector<int> winCols;

	// Loop variables
	MARKER_TYPE marker = X_MARKER;
	int row = -1, col = -1;


	// Set Javascript status delegate
	// assume info[0]->IsFunction()
	jsStatusDelegate.Reset(info[0].As<v8::Function>());
}

// Shutdown CGDV on Main UI thread
NAN_METHOD(Shutdown)
{
	// Start CGDV
	tttGame->Shutdown();
}

// Reset game
NAN_METHOD(NewGame)
{
	// Reset game
	tttGame.NewGame();

	// Reset local state
}

// Do player turn
NAN_METHOD(DoTurn)
{
	// Extract Javascript parameters (row, column)

	// Set player marker on specified ceel
	tttGame->SetMark(row, col, X_MARKER);
}

// Do AI turn
NAN_METHOD(DoAiTurn)
{
	// Make AI move
	tttGame->SetMark(row, col, O_MARKER);

	// Set parameters to Javascript (row, col)
}

// Check if game is over
NAN_METHOD(IsGameOver)
{
	// Make AI move
	bool gameOver = tttGame.IsGameOver(winRows, winCols);
	if (gameOver)
	{
		// Determine type of end game
	}

	// Set parameters to Javascript (gameOver, winRows, winCols)
}

// Module initialization logic
NAN_MODULE_INIT(Initialize)
{
	// Export CGDV methods
	NAN_EXPORT(target, Startup);
	NAN_EXPORT(target, Shutdown);
	NAN_EXPORT(target, NewGame);
	NAN_EXPORT(target, DoTurn);
	NAN_EXPORT(target, DoAiTurn);
	NAN_EXPORT(target, IsGameOver);
}

// Create the add-on module and initialize it (created with NAN_MODULE_INIT macro)
NODE_MODULE(tic-tac-svc, Initialize);


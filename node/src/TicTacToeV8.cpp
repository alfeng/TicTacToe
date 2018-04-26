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

	// 'info' is a macro's "implicit" parameter - it's a bridge object between C++ and JavaScript runtimes
	// You would use info to both extract the parameters passed to a function as well as set the return value.
	info.GetReturnValue().Set(message);
}

// Update CGDV on Main UI thread
NAN_METHOD(NewGame)
{
	// Start CGDV
	tttGame.Update();
}

// Revalidate CGDV on Main UI thread
NAN_METHOD(Validate)
{
	// Start CGDV
	tttGame->Revalidate();
}

// Shutdown CGDV on Main UI thread
NAN_METHOD(Shutdown)
{
	// Start CGDV
	tttGame->Shutdown();
}

// Module initialization logic
NAN_MODULE_INIT(Initialize)
{
	// Export CGDV methods
	NAN_EXPORT(target, Startup);
	NAN_EXPORT(target, Update);
	NAN_EXPORT(target, Validate);
	NAN_EXPORT(target, Shutdown);
	NAN_EXPORT(target, Suspend);
	NAN_EXPORT(target, Resume);

	// Create CGDV App Helper
	cgdvApp = CgdvApp::GetSingleton();

	// Init CGDV status class so Javascript can use it
	v8CgdvStatus::Init(target);
}

// Create the add-on module and initialize it (created with NAN_MODULE_INIT macro)
NODE_MODULE(tic-tac-svc, Initialize);

